#pragma once

#define BIN 0
#define TXT 1

typedef int FILEMODE;
typedef int Mode;

void SaveFile(FILEMODE mode);
int LoadFile(FILEMODE mode);
void UpdateColor(Mode Gamemode);
int ClearFile(FILEMODE mode);
void UpdateSettingFromFile();
void UpdateSettingFromGame();
