#pragma once

constexpr int DEFAULT_WINDOW_WIDTH = 800;
constexpr int DEFAULT_WINDOW_HEIGHT = 600;
constexpr bool DEFAULT_FULLSCREEN = true;

constexpr char SETTINGS_FILE_PATH[] = ".\\settings.ini";
constexpr char TEXTURES_FOLDER_PATH[] = "Data/Textures";
constexpr char WINDOW_NAME[] = "Bomberman";

constexpr float FRAME_TIME = 0.01666;

// shows how many pixels from the corner you must be for cornering to work
constexpr float CORNERING = 50.f;
constexpr float EPS = 0.0001f;
constexpr int MAP_WIDTH = 11;
constexpr int MAP_HEIGHT = 11;
constexpr float MAP_SCALE = 100.f;