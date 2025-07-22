#include "main.h"
#include "gui.h"
#include "Fonts/imgui_fonts.h"

ImFont* pFont, * pFonts23;

long __stdcall WindowProcess(
    HWND window,
    UINT message,
    WPARAM wideParameter,
    LPARAM longParameter)
{
    if (ImGui_ImplWin32_WndProcHandler(window, message, wideParameter, longParameter))
        return true;

    switch (message)
    {
    case WM_SIZE: {       
        if (gui::device && wideParameter != SIZE_MINIMIZED)
        {
            // Resize the swap chain and render target view
            gui::ResetDevice();
        }
    } return 0;

    case WM_SYSCOMMAND: {
        if ((wideParameter & 0xfff0) == SC_KEYMENU)
            return 0;
    } break;

    case WM_DESTROY: {
        PostQuitMessage(0);
    } return 0;

    case WM_LBUTTONDOWN: {
        gui::position = MAKEPOINTS(longParameter);
    } return 0;

    case WM_MOUSEMOVE: {
        if (wideParameter == MK_LBUTTON)
        {
            const auto points = MAKEPOINTS(longParameter);
            auto rect = ::RECT{ };
            GetWindowRect(gui::hwnd, &rect);
            rect.left += points.x - gui::position.x;
            rect.top += points.y - gui::position.y;
            if (gui::position.x >= 0 &&
                gui::position.x <= gui::WINDOW_WIDTH &&
                gui::position.y >= 0 && gui::position.y <= 20)
                SetWindowPos(
                    gui::hwnd,
                    HWND_TOPMOST,
                    rect.left,
                    rect.top,
                    0, 0,
                    SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER
                );
            int newLeft = rect.left;
            int newTop = rect.top;
            if (gui::size.x != (rect.right - rect.left) || gui::size.y != (rect.bottom - rect.top)) {
                SetWindowPos(
                    gui::hwnd,
                    HWND_TOPMOST,
                    newLeft,
                    newTop,
                    gui::size.x,
                    gui::size.y,
                    SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOMOVE
                );
            }
        }
    } return 0;
    }

    return DefWindowProc(window, message, wideParameter, longParameter);
}

void gui::CreateHWindow() noexcept
{
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_CLASSDC;
    wc.lpfnWndProc = WindowProcess;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandleA(0);
    wc.hIcon = 0;
    wc.hCursor = 0;
    wc.hbrBackground = 0;
    wc.lpszMenuName = 0;
    wc.lpszClassName = PROJECT_NAME;
    wc.hIconSm = 0;    

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    int posX = (screenWidth - WINDOW_WIDTH) / 2;
    int posY = (screenHeight - WINDOW_HEIGHT) / 2;

    RegisterClassEx(&wc);

    hwnd = CreateWindowA(
        wc.lpszClassName,
        PROJECT_NAME,
        WS_POPUP,
        posX,
        posY,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0,
        0,
        wc.hInstance,
        0
    );

    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);
}

void gui::DestroyHWindow() noexcept
{
    DestroyWindow(hwnd);
    UnregisterClassA(wc.lpszClassName, wc.hInstance);
}

bool gui::CreateDevice() noexcept
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hwnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &swapChain, &device, &featureLevel, &context);

    if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &swapChain, &device, &featureLevel, &context);

    if (res != S_OK) {
        OutputDebugString("Failed to create device and swap chain.");
        return false;
    }

    ID3D11Texture2D* pBackBuffer;
    res = swapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    if (FAILED(res)) {
        OutputDebugString("Failed to get back buffer.");
        return false;
    }

    res = device->CreateRenderTargetView(pBackBuffer, nullptr, &renderTargetView);
    pBackBuffer->Release();
    if (FAILED(res)) {
        OutputDebugString("Failed to create render target view.");
        return false;
    }

    // Установите рендер-таргет в контексте
    context->OMSetRenderTargets(1, &renderTargetView, nullptr);

    return true;
}

void gui::ResetDevice() noexcept
{
    ImGui_ImplDX11_InvalidateDeviceObjects();

    HRESULT result = swapChain->ResizeBuffers(1, WINDOW_WIDTH, WINDOW_HEIGHT, DXGI_FORMAT_UNKNOWN, 0);
    //if (result == DXGI_ERROR_INVALIDCALL) IM_ASSERT(0);

    // Recreate the render target view
    ID3D11Texture2D* backBuffer;
    HRESULT hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    if (SUCCEEDED(hr))
    {
        device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
        backBuffer->Release();
    }

    context->OMSetRenderTargets(1, &renderTargetView, nullptr);
    ImGui_ImplDX11_CreateDeviceObjects();
}

void gui::DestroyDevice() noexcept
{
    if (renderTargetView) { renderTargetView->Release(); renderTargetView = nullptr; }
    if (swapChain) { swapChain->Release(); swapChain = nullptr; }
    if (context) { context->Release(); context = nullptr; }
    if (device) { device->Release(); device = nullptr; }
}

void gui::CreateImGui() noexcept
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    io.IniFilename = NULL;

    ImFontConfig config;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    
    io.Fonts->AddFontFromMemoryTTF(devfont, sizeof(devfont), 17.f, &config, io.Fonts->GetGlyphRangesCyrillic());
    pFont = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(font, sizeof(font), 17.f, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    IM_ASSERT(pFont != NULL);
    pFonts23 = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(font, sizeof(font), 46.f, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    IM_ASSERT(pFonts23 != NULL);

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(device, context);

    // Initialize other components
    sn_init();
    PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void gui::DestroyImGui() noexcept
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void gui::BeginRender() noexcept
{
    MSG message;
    while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);

        if (message.message == WM_QUIT)
        {
            isRunning = false; // Set to false to exit the loop
            return;
        }
    }
    
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void gui::EndRender() noexcept
{
    ImGui::EndFrame();

    // Очистка рендер-таргета
    const float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // Черный фон
    context->ClearRenderTargetView(renderTargetView, clearColor);

    // Рендеринг ImGui
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // Представление буфера на экран
    HRESULT hr = swapChain->Present(1, 0); // VSync включен
    if (FAILED(hr)) {
        OutputDebugString("Failed to present swap chain.");
    }
}

void gui::Render() noexcept // Main rendering function
{
    ImGui::SetNextWindowPos({ 0, 0 });
    ImGui::SetNextWindowSize({ gui::WINDOW_WIDTH, gui::WINDOW_HEIGHT });
    ImGuiMenuTheme();
    ImGui::Begin(
        PROJECT_NAME,
        &isRunning,
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
    );

    size = ImGui::GetWindowSize();
    RenderImage(gui::device);

    int width = strlen(PROJECT_NAME) * 4;
    ImGui::SameLine(ImGui::GetWindowWidth() / 2 - width);
    ImGui::PushFont(pFont);
    ImGui::Text(PROJECT_NAME);

    ImGui::SameLine(ImGui::GetWindowWidth() - 30);
    if (ImGui::Button("--"))
    {
        ShowWindow(GetActiveWindow(), SW_SHOWMINIMIZED);
    }
    ImFuncs::FastDescr(u8"{FF0008}свернуть"); // R G B A
    ImGui::SameLine();
    if (ImGui::Button("X"))
    {
        ExitProcess(0);
    }
    ImFuncs::FastDescr(u8"{FF0009}закрыть"); // R G B A                
    ImGui::PopFont();

    MyGui::renderImguiMenu();
    ImGui::End();

  /*  ImGui::SaveIniSettingsToDisk("SkyNet_widgets.ini");
    ImGui::LoadIniSettingsFromDisk("SkyNet_widgets.ini");*/
}


