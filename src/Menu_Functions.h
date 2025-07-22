#pragma once

void ImGuiMenuTheme();

#define time_get() __time_current
extern uint64_t __time_current;

#ifndef MYGUI_API
#define MYGUI_API
#endif

namespace MyGui
{	
	MYGUI_API void renderImguiMenu(bool* p_open = NULL);
	MYGUI_API void SL(bool* p_open = NULL);
	MYGUI_API void SLogger(bool* p_open = NULL);
	MYGUI_API void SLoadModules(bool* p_open = NULL);
	MYGUI_API void BarMenu(bool* p_open = NULL);
	MYGUI_API void BarMenuMain(bool* p_open = NULL);
}

namespace MyGui
{
	static inline void  show_renderimguimenu() { return renderImguiMenu(); }
	static inline void  show_sl() { return SL(); }
	static inline void  show_slogger() { return SLogger(); }
	static inline void  show_sloadmodules() { return SLoadModules(); }
	static inline void  show_barmenu() { return BarMenu(); }
	static inline void  show_barmenumain() { return BarMenuMain(); }
}

//MyMenu
extern ImVec4 ImColorRed, ImColorBlue, ImColorGreen, ImColorOrange,
ImColorBanana, ImColorTransparentBlack, ImColorDeepOrange,
ImColorWhite, ImColorNone;

class CBlackLightMenu
{
public:
	void Initialize_ImGui_Menus(void); //good

	int GetLastMenu(void);
	int GetCurrentMenu(void);
		
	void AddButton(bool* bEnable, const char* szButtonName = (const char*)0, float fWidthDecrease = 0.0f);
	bool AddStaticButton(const char* szBtnName, float fWidthDecrease = 0.0f);
	void AddSlider(const char* szName, int& vSettings, int vMinValue, int vMaxValue, const char* szFormat = "%d");
	void AddSlider(const char* szName, float& vSettings, float vMinValue, float vMaxValue, const char* szFormat = "%.2f");

	void AddMenuText(const char* szText = (const char*)0, bool bStickAllign = false, ImVec4 ImColor = ImColorOrange, bool bSeparators = false);
	
	void AddTargetIncDecButtons(int& settings, bool bSameLine = true, const char* str_id_inc = (const char*)0, const char* str_id_dec = (const char*)0);
	void AddItemDescription(const char* szText, ImVec4 textColor = ImColorWhite);
	void AddHudItem(bool* bEnabled, const char* szItemName = (const char*)0, bool bItemDescription = false, const char* szDescription = (const char*)0);

	ImVec2 MenuItemMatchMenuWidth(void);
	ImVec2 MenuItemMatchMenuWidth(float fWidthCustomSet);

private:

};
extern CBlackLightMenu* pMenu;

extern char* settings;