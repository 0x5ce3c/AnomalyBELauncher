#pragma once

#include "cmds_funcs.h"
#include "console.h"
#include "structs.h"

extern struct stsn* sn;

void sn_Thread();
void sn_init();

void radio_control();

int check();

void Save(const char* fmt, ...);

extern char* current_track;


extern bool createlauncherfolder;

//using 
//ExtractRes(IDR_TXT1, _T("TXT"), "prikol.txt");
void ExtractRes(WORD wResId, LPCSTR ResType, LPSTR lpszOutputPath);

/// misc funcs
BOOL IsAppRunningAsAdminMode();

void RenderImage(ID3D11Device* device);


//const int ROTATION_DELAY = 50; // Задержка в миллисекундах
//const char* textToAnimate = ""; // Текст для анимации
//animateString(textToAnimate, ROTATION_DELAY); // Запуск анимации