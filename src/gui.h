#pragma once

namespace gui
{
	constexpr int WINDOW_WIDTH = 762; // Это ширина вашего будущего окна ///962
	constexpr int WINDOW_HEIGHT = 426; // Это высота ///493

	inline bool isRunning = true;

	inline HWND hwnd = nullptr;
	inline WNDCLASSEX wc = { };

	inline POINTS position = { };

	// Remove Direct3D 9 specific types
	// inline PDIRECT3D9 d3d = nullptr;

	// Change from LPDIRECT3DDEVICE9 to ID3D11Device
	inline ID3D11Device* device = nullptr;
	inline ID3D11DeviceContext* context = nullptr; // Add context for DirectX 11
	inline IDXGISwapChain* swapChain = nullptr;
	inline ID3D11RenderTargetView* renderTargetView = nullptr;
	inline IDXGIFactory* dxgiFactory = nullptr;

	

	// Remove D3DPRESENT_PARAMETERS
	// inline D3DPRESENT_PARAMETERS presentParameters = { };

	void CreateHWindow() noexcept;
	void DestroyHWindow() noexcept;

	bool CreateDevice() noexcept;
	void ResetDevice() noexcept;
	void DestroyDevice() noexcept;

	void CreateImGui() noexcept;
	void DestroyImGui() noexcept;

	void BeginRender() noexcept;
	void EndRender() noexcept;
	void Render() noexcept;

	inline ImVec2 size = {};
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter
);

extern ImFont* pFont, * pFonts23;