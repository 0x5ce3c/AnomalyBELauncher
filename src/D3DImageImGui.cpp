#include "main.h"

#include <D3DX11tex.h>
#pragma comment(lib, "D3DX11.lib")
#include "mem_image.h"
ID3D11ShaderResourceView* Image = nullptr;

//IDirect3DTexture9* LoadTextureFromMemory(IDirect3DDevice9* device, const unsigned char* image_data, size_t image_size) 
//{
//	IDirect3DTexture9* texture = nullptr;	
//	D3DXIMAGE_INFO info;
//
//	HRESULT hr = D3DXCreateTextureFromFileInMemoryEx(device, image_data, image_size, D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &info, NULL, &texture);
//
//	if (FAILED(hr)) { return nullptr; }
//	return texture;
//}

static bool background_initialize = true;
void RenderImage(ID3D11Device* device) {
	//static IDirect3DTexture9* texture = LoadTextureFromMemory(device, bender, sizeof(bender));	

	if (background_initialize)
	{		
		D3DX11_IMAGE_LOAD_INFO info;
		ID3DX11ThreadPump* pump{ nullptr };
		D3DX11CreateShaderResourceViewFromMemory(device, bender, sizeof(bender), &info,
			pump, &Image, 0);
		sn->con.AddLog(u8"{00DD00}background() is init success");		
		background_initialize = 0;
	}
	//if (!texture) { sn->con.AddLog(u8"Ошибка загрузки текстуры"); return; }	

	ImGui::GetBackgroundDrawList()->AddImage((void*)Image, ImVec2{ 3,3 }, ImGui::GetContentRegionAvail());

}