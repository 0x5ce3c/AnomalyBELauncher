#pragma once

#ifndef PROTECT
#define PROTECT


#pragma message( "[AnomalyBELauncher]: Creating precompiled header...\n" )

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN   
#define _CRT_SECURE_NO_WARNINGS 1
#define PROJECT_FOLDER "AnomalyBELauncher"
#define LVER "0.0.0.1"
#define PROJECT_NAME "AnomalyBELauncher | ver -> " LVER
#define LOG_FILE "AnomalyBELauncher.log"

//precomp header

// API/SDK includes
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <cstdlib>
//#pragma comment(lib, "Ws2_32.lib")
#include <windows.h>
#include <stdlib.h>
#include <stdint.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
//#include <d3d9types.h>
#include <dxgi.h>
//#pragma comment(lib,"dxgi.lib")
#include <d3d11.h>
//#pragma comment(lib,"d3d11.lib")
#include <d3dcompiler.h>
#include <process.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <shellapi.h>
#include <Gdiplus.h>
#include <assert.h>
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <functional>
#include <codecvt>
#include <stdexcept>
#include <fstream>
#include <thread>
#include <future>
#include <sstream>
#include <iomanip>
#include <bitset>
#include <mutex>
#include <chrono>
#include "psapi.h"
#include <time.h>
#include <io.h>
#include <xthreads.h>
#include <tuple>
#include <filesystem>
#include <iostream> 
#include <immintrin.h>


//#include <Windows.h>
#include <conio.h>
//#include <iostream>
#include <locale>
#include <Wbemidl.h> 
#include <comdef.h>
#include <Wininet.h>


#define _WIN32_DCOM 
//#pragma comment(lib, "wbemuuid.lib") 
//#pragma comment(lib, "Wininet.lib") 

using namespace std::chrono_literals;
using namespace std;

#define IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DISABLE_DEMO_WINDOWS
#define IMGUI_DISABLE_DEBUG_TOOLS

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

#include "Fonts/itsmyfontforgocnet.h"
#include "Fonts/IconFontAwesome5.h"

#include "ImColor.h"
#include "ImFuncs.h"

#include "ThreadWrapper.hpp"

#include "gui.h"

void gen_random(char* s, const int len);

#include <Lmcons.h>

#include "resource.h"

#include "math_stuff.h"

//appdata path to settings app
TCHAR szPath[MAX_PATH];
char* CurrentPath;

#include "LauncherMain.h"

#include "Menu_Functions.h"
#include "misc_funcs.h"

int getTaskBarHeight();

//console logger processor - CLP
void Log(const char* fmt, ...);
void CreateUserltx(const char* fmt, ...);
//ini parser
#include "ini_parser.h"

#include "FileSystemManager.h"
#include "Systeminfo.h"

#endif // !PROTECT
