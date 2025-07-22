#include  "main.h"

FILE* g_flLog = NULL;
FILE* g_fluserltx = NULL;

char					g_szLastFunc[256];

void traceLastFunc ( const char *szFunc )
{
	_snprintf_s( g_szLastFunc, sizeof(g_szLastFunc)-1, szFunc );
}

int getTaskBarHeight() //учёт высоты панели задач
{
	RECT rect;
	HWND taskBar = FindWindowA("Shell_traywnd", NULL);
	if (taskBar && GetWindowRect(taskBar, &rect))
	{
		return rect.bottom - rect.top;
	}
}
POINTS m_Pos;
//winmain here...
//int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
//{     
//    WNDCLASSEX wc = { 
//        sizeof(WNDCLASSEX),     /// UINT        cbSize;
//        CS_CLASSDC,             /// UINT        style;
//        WndProc,                /// WNDPROC     lpfnWndProc;
//        0L,                     /// int         cbClsExtra;
//        0L,                     /// int         cbWndExtra;
//        GetModuleHandle(NULL),  /// HINSTANCE   hInstance;
//        NULL,                   /// HICON       hIcon;
//        NULL,                   /// HCURSOR     hCursor;
//        NULL,                   /// HBRUSH      hbrBackground;
//        NULL,                   /// LPCSTR      lpszMenuName;
//        PROJECT_NAME,           /// LPCSTR      lpszClassName;
//        NULL                    /// HICON       hIconSm;
//    };
//    RegisterClassEx(&wc);
//
//    RECT	um;		// damn near killed um
//            GetWindowRect(GetDesktopWindow(), &um); // разрешение экрана
//            int x = m_Pos.x;//um.right / 2 - WINDOW_WIDTH / 2;// - 150;
//            int y = m_Pos.y;//um.bottom / 2 - WINDOW_HEIGHT / 2;// - 75;
//
//    Window = CreateWindowA(wc.lpszClassName, PROJECT_NAME, WS_POPUP, 0, 0, 5, 5, NULL, \
//        NULL, wc.hInstance, NULL);
//
//    if (!CreateDeviceD3D(Window)) {
//        CleanupDeviceD3D();
//        UnregisterClass(wc.lpszClassName, wc.hInstance);
//        return 1;
//    }    
//
//    ShowWindow(Window, SW_HIDE);
//    UpdateWindow(Window);
//
//    ImGui::CreateContext();
//
//    ImGuiIO& io = ImGui::GetIO();
//
//    ///char	filename[512];\
//    _snprintf(filename, sizeof(filename), "%s\\%s\\%s", GetExePath().c_str(), PROJECT_FOLDER, WIDGETS_INI);
//
//    io.IniFilename = NULL;
//    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
//    
//    io.DeltaTime = 1.0f / 60.0f;
//
//    ImGuiStyle& style = ImGui::GetStyle();
//    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
//    {
//        style.WindowRounding = 0.0f;
//        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
//    }    
//            
//    ImFontConfig config;
//    config.FontDataOwnedByAtlas = false;       
//
//    // Load Fonts
//    io.Fonts->AddFontFromMemoryTTF(devfont, sizeof(devfont), 17.f, &config, io.Fonts->GetGlyphRangesCyrillic());
//
//
//    pFont = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(font, sizeof(font), 17.f, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
//    IM_ASSERT(pFont != NULL);
//
//    pFonts23 = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(font, sizeof(font), 46.f, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
//    IM_ASSERT(pFonts23 != NULL);
//
//    //fa_icon_regular_400
//    //fa_icon_solid_900
//    //itsmyfontforgocnet
//
//    //unsigned meme fa_icon_solid_900[204580];
//    static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
//    ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
//    ImFont* picon = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(&fa_icon_solid_900, sizeof fa_icon_solid_900, 16.0f, /*&config*/&icons_config, icon_ranges);
//   
//
//    //icons			            
//    config.MergeMode = true;
//    config.GlyphMinAdvanceX = 13.0f; // if use monospace
//
//
//    ImGui_ImplWin32_Init(Window);
//    ImGui_ImplDX9_Init(g_pd3dDevice_);
//
//    //skynet initialize
//    sn_init();
//    PlaySound(MAKEINTRESOURCE(IDR_WAVE1),
//        NULL, SND_RESOURCE | SND_FILENAME | SND_ASYNC | SND_LOOP);
//
//    MSG msg;
//    ZeroMemory(&msg, sizeof(msg));
//    while (msg.message != WM_QUIT)
//    {
//        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
//        {
//            TranslateMessage(&msg);
//            DispatchMessage(&msg);
//            continue;
//        }
//
//        ImGui_ImplDX9_NewFrame();
//        ImGui_ImplWin32_NewFrame();
//        ImGui::NewFrame();
//        //Menu::Theme();
//        ImGuiMenuTheme();
//        {
//            //RECT	um;		// damn near killed um
//            //GetWindowRect(GetDesktopWindow(), &um); // разрешение экрана
//            //int x = um.right / 2;// - 150;
//            //int y = um.bottom / 2;// - 75;
//            //int width = um.right;
//            //int height = um.bottom - getTaskBarHeight();//um.bottom - um.top;	
//            //ImGui::SetNextWindowViewport(ImGui::GetMainViewport()->ID);
//            //MyGui::BarMenuMain();
//
//            ImGui::SetNextWindowPos(ImVec2(0, 0));                      
//            ImGui::SetNextWindowSize(ImVec2(g_d3dpp.BackBufferWidth, g_d3dpp.BackBufferHeight));            
//            static bool theme_editor = false;
//            static bool font_editor = false;
//            
//            ImGui::Begin(PROJECT_NAME, nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar);
//            {                                
//                RenderImage(g_pd3dDevice_);                
//                
//                MyGui::renderImguiMenu();
//               /// char	filename[512];\
//                _snprintf(filename, sizeof(filename), "%s\\%s\\%s", GetExePath().c_str(), PROJECT_FOLDER, WIDGETS_INI);\
//                ImGui::SaveIniSettingsToDisk(filename);\
//                ImGui::LoadIniSettingsFromDisk(filename);
//            }
//            ImGui::End();
//        }
//        ImGui::EndFrame();
//
//        g_pd3dDevice_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
//        if (g_pd3dDevice_->BeginScene() >= 0)
//        {
//            ImGui::Render();
//            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
//            g_pd3dDevice_->EndScene();
//        }
//
//        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
//        {
//            ImGui::UpdatePlatformWindows();
//            ImGui::RenderPlatformWindowsDefault();
//        }
//
//        HRESULT result = g_pd3dDevice_->Present(NULL, NULL, NULL, NULL);
//        if (result == D3DERR_DEVICELOST && g_pd3dDevice_->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
//            ResetDevice();
//        }
//        if (!Enabled) {
//            msg.message = WM_QUIT;
//        }
//    }
//
//    ImGui_ImplDX9_Shutdown();
//    ImGui_ImplWin32_Shutdown();
//    ImGui::DestroyContext();
//
//    CleanupDeviceD3D();
//    DestroyWindow(Window);
//    UnregisterClass(wc.lpszClassName, wc.hInstance);
//
//    return (int)msg.wParam;
//}

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(
    HINSTANCE,
    HINSTANCE,
    LPSTR,
    int)
{

    gui::CreateHWindow(); // название вашего окна, заголовок
    gui::CreateDevice();
    gui::CreateImGui();
    while (gui::isRunning) // цикл рендера
    {
        gui::BeginRender();
        gui::Render();
        gui::EndRender();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    gui::DestroyImGui(); // выход из программы
    gui::DestroyDevice();
    gui::DestroyHWindow();
    
    return EXIT_SUCCESS;
}

//LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
//        return true;
//    LRESULT retval = 0;
//
//    switch (uMsg)
//    {    
//
//    case WM_SYSCOMMAND:
//        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
//            return 0;
//        break;    
//
//    
//
//    case WM_SIZE:
//        if (g_pd3dDevice_ != NULL && wParam != SIZE_MINIMIZED)
//        {
//            g_d3dpp.BackBufferWidth = LOWORD(lParam);
//            g_d3dpp.BackBufferHeight = HIWORD(lParam);
//            //g_d3dpp.Windowed = true;
//            ResetDevice();
//        }       
//        break;   
//
//    case WM_LBUTTONDOWN:
//    {
//        m_Pos = MAKEPOINTS(lParam);
//        return 0;
//    }
//    case WM_MOUSEMOVE:
//    {
//        if (wParam == MK_LBUTTON)
//        {
//            POINTS p = MAKEPOINTS(lParam);
//
//            RECT rect;
//            GetWindowRect(hWnd, &rect);
//
//            rect.left += p.x - m_Pos.x;
//            rect.top += p.y - m_Pos.y; //      - 20 ниже - если есть кнопка закрытия окна внутри самого окна
//            if (m_Pos.x >= 0 && m_Pos.x <= WINDOW_WIDTH - 20 && // 700 - ширина окна, ставь своё значение
//                m_Pos.y >= 0 && m_Pos.y <= WINDOW_HEIGHT /* или ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 4.0f*/) // насколько высокой будет рамка за которую можно потянуть окно
//                SetWindowPos(hWnd, NULL, rect.left, rect.top, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER);
//        }
//        return 0;
//    }
//
//   /* case WM_SETFOCUS:        
//        ShowWindow(Window, SW_SHOW);
//        break;*/
//    
//    case WM_KILLFOCUS:        
//        ShowWindow(Window, SW_SHOW);
//        break;
//
//    case WM_DESTROY:                
//        PostQuitMessage(0);
//        break;
//
//    ///default:
//        ///retval = DefWindowProcA(hWnd, uMsg, wParam, lParam);
//       /// break;
//    }
//    return ::DefWindowProcA(hWnd, uMsg, wParam, lParam);
//}

void Log(const char* fmt, ...)
{
	//if (!g_szWorkingDirectory) return;
	
	SYSTEMTIME	time;
	va_list		ap;

	if (g_flLog == NULL)
	{
		char	filename[512];
        _snprintf(filename, sizeof(filename), "%s\\%s", GetExePath().c_str(), LOG_FILE);

		g_flLog = fopen(filename, "w+");

		if (g_flLog == NULL)
			return;
	}

	GetLocalTime(&time);
	fprintf(g_flLog, "[%02d:%02d:%02d.%03d] ", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	va_start(ap, fmt);
	vfprintf(g_flLog, fmt, ap);		
	va_end(ap);
	fprintf(g_flLog, "\n");	
	fflush(g_flLog);
    //fclose(g_flLog);
}

void CreateUserltx(const char* fmt, ...)
{        
    SYSTEMTIME	time;
    va_list		ap;

    if (g_fluserltx == NULL)
    {
        char	filename[512];
        snprintf(filename, sizeof(filename), "appdata\\user.ltx");

        g_fluserltx = fopen(filename, "w");/// Перезапись каждый раз

        if (g_fluserltx == NULL)
            return;
    }

    GetLocalTime(&time);
    fprintf(g_fluserltx, "", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
    va_start(ap, fmt);
    vfprintf(g_fluserltx, fmt, ap);
    va_end(ap);
    //fprintf(g_fluserltx, "\n");
    fflush(g_fluserltx);
    fclose(g_fluserltx);
}
