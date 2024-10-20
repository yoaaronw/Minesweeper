#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class StoreTextures {
public:
    map<string, Texture> list;
    map<int, Texture> numList;
    void LoadTexture(string file);
    void LoadNumberTexture(string file, int number);
    void LoadAllNumbers();
    void LoadAll();
};

