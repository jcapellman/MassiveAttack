#pragma once

#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS

#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include <windows.h>

#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <malloc.h>
#include <hash_set>
#include <unordered_map>

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2Main.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_ttf.lib")

using namespace std;

const string TEXTURES_ROOT_PATH = "base/textures/";
const string MAPS_ROOT_PATH = "base/maps/";
const string SOUNDS_ROOT_PATH = "base/sounds/";
const string FONTS_ROOT_PATH = "base/fonts/";