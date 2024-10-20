#include <iostream>
#include <random>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Board.h"
using namespace std;
using namespace chrono;
using namespace sf;

bool MouseOverBoard(int cols, int rows, RenderWindow &window)
{
    int width = cols*32;
    int height = rows*32;
    int mX = Mouse::getPosition(window).x;
    int mY = Mouse::getPosition(window).y;

    if (mX >= 0 && mX <= width && mY >= 0 && mY <= height)
    {
        return true;
    }
    return false;
}

int main()
{
    // get board size
    int cols, rows, mines;
    fstream config("board_config.cfg");
    config >> cols >> rows >> mines;
    int boardWidth = cols*32;
    int boardHeight = rows*32+100;
    // load font
    Font font;
    if (!font.loadFromFile("font.ttf"))
    {
        cout << "Could not load font" << endl;
    }
    // welcome window
    RenderWindow welcomeWindow(VideoMode(boardWidth, boardHeight), "Minesweeper", Style::Close);
    WelcomeWindow WWindow(boardWidth, boardHeight, font);
    WWindow.InitializeText();
    while (welcomeWindow.isOpen())
    {
        Event event;
        while (welcomeWindow.pollEvent(event))
        {
            if (event.type == Event::TextEntered)
            {
                if (isalpha((char)event.text.unicode))
                {
                    WWindow.UpdatePlayerName(welcomeWindow, (char)event.text.unicode);
                }
            }
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Enter)
                {
                    if (!WWindow.PlayerNameEmpty())
                    {
                        WWindow.StorePlayerName();
                        welcomeWindow.close();
                    }
                }
                if (event.key.code == Keyboard::BackSpace)
                {
                    WWindow.DeleteLetter(welcomeWindow);
                }
            }
            if (event.type == Event::Closed)
            {
                welcomeWindow.close();
                return 0;
            }
        }
        WWindow.DrawWindow(welcomeWindow);
    }
    // game window
    RenderWindow gameWindow(VideoMode(boardWidth, boardHeight), "Minesweeper", Style::Close);
    // leaderboard
    LeaderboardWindow LWindow(boardWidth, boardHeight, font);
    LWindow.ReadLeaderboard();
    LWindow.CreateLeaderboard();
    LWindow.InitializeText();
    // board
    Board board(cols, rows, mines);
    board.InitializeTextures();
    board.InitializeSprites();
    board.CreateTiles();
    board.SetAdjacentTiles();
    int flagCount;
    // game states
    bool gameOver = false;
    bool win = false;
    bool paused = false;
    bool alreadyPaused = false;
    bool leaderboardOpen = false;
    bool debugMode = false;
    //timer
    auto pauseStart = high_resolution_clock::now();
    auto pauseTime = 0s;
    auto leaderboardStart = high_resolution_clock::now();
    auto leaderboardTime = 0s;
    auto startTime = high_resolution_clock::now();
    auto elapsedTime = high_resolution_clock::now() - startTime - pauseTime;
    while (gameWindow.isOpen())
    {
        Event event;
        while (gameWindow.pollEvent(event))
        {
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                if (MouseOverBoard(cols, rows, gameWindow))
                {
                    if (!gameOver)
                    {
                        if (board.MineHit(gameWindow))
                        {
                            gameOver = true;
                        }
                        else
                        {
                            int xMousePos = Mouse::getPosition(gameWindow).x;
                            int yMousePos = Mouse::getPosition(gameWindow).y;
                            int selectedIndex = board.SelectedTileIndex(xMousePos, yMousePos);
                            board.RevealTiles(selectedIndex);
                            if (board.GameWon())
                            {
                                gameOver = true;
                                win = true;
                                board.FlagMines();
                                LWindow.UpdateLeaderboard(elapsedTime, WWindow.GetPlayerName());
                                LWindow.InitializeText();
                                leaderboardOpen = true;
                            }
                        }
                    }
                }
                if (board.MouseOverButton("pause", gameWindow))
                {
                    if (!paused)
                    {
                        paused = true;
                        alreadyPaused = true;
                        pauseStart = high_resolution_clock::now();
                    }
                    else
                    {
                        paused = false;
                        alreadyPaused = false;
                        auto pauseEnd = high_resolution_clock::now() - pauseStart;
                        pauseTime = pauseTime + duration_cast<chrono::seconds>(pauseEnd);
                    }
                }
                if (board.MouseOverButton("leaderboard", gameWindow))
                {
                    if (paused)
                    {
                        alreadyPaused = true;
                        paused = true;
                        leaderboardOpen = true;
                    }
                    else
                    {
                        paused = true;
                        leaderboardOpen = true;
                        pauseStart = high_resolution_clock::now();
                    }
                }
                if (board.MouseOverButton("debug", gameWindow))
                {
                    if (!paused)
                    {
                        if (!debugMode)
                        {
                            debugMode = true;
                        }
                        else
                        {
                            debugMode = false;
                        }
                    }
                }
                if (board.MouseOverButton("face_happy", gameWindow))
                {
                    paused = false;
                    leaderboardOpen = false;
                    debugMode = false;
                    gameOver = false;
                    win = false;
                    LWindow.CreateLeaderboard();
                    LWindow.InitializeText();
                    board.ResetBoard();
                    board.DrawBoard(gameWindow);
                    startTime = high_resolution_clock::now();
                    pauseTime = 0s;
                }
            }
            if (Mouse::isButtonPressed(Mouse::Right))
            {
                if (!gameOver)
                {
                    if (MouseOverBoard(cols, rows, gameWindow))
                    {
                        board.FlagUnFlagTile(gameWindow);
                    }
                }
            }
            if (event.type == Event::Closed)
            {
                gameWindow.close();
                return 0;
            }
        }
        gameWindow.clear(Color::White);
        board.DrawSprite(gameWindow, "debug");
        board.DrawSprite(gameWindow, "pause");
        board.DrawSprite(gameWindow, "leaderboard");
        flagCount = mines - board.numFlags();
        board.MineCounter(gameWindow, flagCount);
        if (!gameOver)
        {
            board.DrawSprite(gameWindow, "face_happy");
            if (paused)
            {
                auto pausedDisplay = pauseStart - startTime - pauseTime - leaderboardTime;
                board.Timer(gameWindow, pausedDisplay);
                board.PausedBoard(gameWindow);
                board.DrawSprite(gameWindow, "play");
            }
            else
            {
                elapsedTime = high_resolution_clock::now() - startTime - pauseTime;
                board.Timer(gameWindow, elapsedTime);
                if (debugMode)
                {
                    board.DebugMode(gameWindow);
                }
                else
                {
                    board.DrawBoard(gameWindow);
                }
            }
        }
        else
        {
            if (win)
            {
                board.DrawSprite(gameWindow, "face_win");
                board.Timer(gameWindow, elapsedTime);
                board.DrawBoard(gameWindow);
            }
            else
            {
                board.DrawSprite(gameWindow, "face_lose");
                board.Timer(gameWindow, elapsedTime);
                board.DrawBoard(gameWindow);
                board.DrawMines(gameWindow);
            }
        }
        gameWindow.display();

        if (leaderboardOpen)
        {
            RenderWindow leaderboardWindow(VideoMode(boardWidth/2, boardHeight/2), "Minesweeper", Style::Close);
            while (leaderboardWindow.isOpen())
            {
                Event event2;
                while (leaderboardWindow.pollEvent(event2))
                {
                    if (event2.type == Event::Closed)
                    {
                        if (alreadyPaused)
                        {
                            leaderboardOpen = false;
                            leaderboardWindow.close();
                        }
                        else
                        {
                            paused = false;
                            auto pauseEnd = high_resolution_clock::now() - pauseStart;
                            pauseTime = pauseTime + duration_cast<chrono::seconds>(pauseEnd);
                            leaderboardOpen = false;
                            leaderboardWindow.close();
                        }
                    }
                }
                LWindow.DrawWindow(leaderboardWindow);
            }
        }
    }

    return 0;
}