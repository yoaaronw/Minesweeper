#include "StoreTextures.h"

void StoreTextures::LoadTexture(string file)
{
    Texture newTexture;
    if (!newTexture.loadFromFile(file))
    {
        cout << "Could not load " << file << endl;
    }
    list[file.substr(0, file.size()-4)] = newTexture;
}
void StoreTextures::LoadNumberTexture(string file, int number)
{
    Texture newTexture;
    if (!newTexture.loadFromFile(file))
    {
        cout << "Could not load " << file << endl;
    }
    numList[number] = newTexture;
}
void StoreTextures::LoadAllNumbers()
{
    LoadNumberTexture("tile_revealed.png", 0);
    LoadNumberTexture("number_1.png", 1);
    LoadNumberTexture("number_2.png", 2);
    LoadNumberTexture("number_3.png", 3);
    LoadNumberTexture("number_4.png", 4);
    LoadNumberTexture("number_5.png", 5);
    LoadNumberTexture("number_6.png", 6);
    LoadNumberTexture("number_7.png", 7);
    LoadNumberTexture("number_8.png", 8);
}
void StoreTextures::LoadAll()
{
    LoadTexture("debug.png");
    LoadTexture("digits.png");
    LoadTexture("face_happy.png");
    LoadTexture("face_lose.png");
    LoadTexture("face_win.png");
    LoadTexture("flag.png");
    LoadTexture("leaderboard.png");
    LoadTexture("mine.png");
    LoadTexture("number_1.png");
    LoadTexture("number_2.png");
    LoadTexture("number_3.png");
    LoadTexture("number_4.png");
    LoadTexture("number_5.png");
    LoadTexture("number_6.png");
    LoadTexture("number_7.png");
    LoadTexture("number_8.png");
    LoadTexture("pause.png");
    LoadTexture("play.png");
    LoadTexture("tile_hidden.png");
    LoadTexture("tile_revealed.png");
}
