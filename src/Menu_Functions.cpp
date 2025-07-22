#include "main.h"

uint64_t					__time_current;

char movies_content_show[512];
void ImGuiMenuTheme()
{
	ImGuiStyle& Style = ImGui::GetStyle();
	auto Color = Style.Colors;

	Style.WindowMinSize = ImVec2(200, 140);	

	Style.WindowTitleAlign = ImVec2(0.50f, 0.50f);
	Style.FrameRounding = 0.0;
	Style.WindowPadding = ImVec2(2, 2);
	Style.WindowRounding = 0.5f;
	Style.ItemSpacing = ImVec2(1, 2);
	Style.ItemInnerSpacing = ImVec2(2, 0);
	//style.IndentSpacing = 25.0f;
	Style.ScrollbarSize = 15.0f;
	Style.ScrollbarRounding = 9.0f;
	Style.FramePadding = ImVec2(2, 1);

	//borders
	Style.WindowBorderSize = 0.3f;
	Style.ChildBorderSize = 0.3f;
	Style.FrameBorderSize = 0.3f;
	Style.PopupBorderSize = 0.3f;
	Style.TabBorderSize = 0.3f;


	Color[ImGuiCol_WindowBg] = ImColor(20, 20, 30, 200);

	Color[ImGuiCol_FrameBg] = ImColor(24, 24, 24, 128);
	Color[ImGuiCol_FrameBgActive] = ImColor(24, 24, 24, 255);
	Color[ImGuiCol_FrameBgHovered] = ImColor(24, 24, 24, 255);

	Color[ImGuiCol_Button] = ImColor(0, 0, 150, 255);
	Color[ImGuiCol_ButtonActive] = ImColor(150, 150, 150, 255);
	Color[ImGuiCol_ButtonHovered] = ImColor(0, 150, 150, 255);	

	Color[ImGuiCol_Tab] = ImColor(150, 0, 0, 200);

	Color[ImGuiCol_Border] = ImColor(95, 95, 95, 255);
	Color[ImGuiCol_Separator] = ImColor(95, 95, 95, 255);

	Color[ImGuiCol_ResizeGrip] = ImColor(95, 0, 0, 200);
	Color[ImGuiCol_ResizeGripActive] = ImColor(30, 30, 30, 255);
	Color[ImGuiCol_ResizeGripHovered] = ImColor(30, 30, 30, 255);

	Color[ImGuiCol_ChildBg] = ImColor(26, 26, 26, 64);

	Color[ImGuiCol_ScrollbarBg] = ImColor(34, 34, 34, 255);
	Color[ImGuiCol_ScrollbarGrab] = ImColor(64, 64, 64, 255);
	Color[ImGuiCol_ScrollbarGrabActive] = ImColor(94, 94, 94, 255);
	Color[ImGuiCol_ScrollbarGrabHovered] = ImColor(64, 64, 64, 255);

	Color[ImGuiCol_Header] = ImColor(39, 39, 39, 255);
	Color[ImGuiCol_HeaderActive] = ImColor(39, 39, 39, 255);
	Color[ImGuiCol_HeaderHovered] = ImColor(39, 39, 39, 255);
	Color[ImGuiCol_CheckMark] = ImColor(255, 255, 255, 255);
	Color[ImGuiCol_PlotHistogram] = ImColor(0, 64, 64, 255);
}

static void Descr(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

char* settings;



ImVec4
ImColorRed = ImVec4(0.882f, 0.035f, 0.066f, 1.000f),
ImColorBlue = ImVec4(0.782f, 0.935f, 1.066f, 1.000f),
ImColorGreen = ImVec4(0.105f, 0.733f, 0.027f, 1.000f),
ImColorOrange = ImVec4(1.000f, 0.807f, 0.483f, 1.000f), //menu text
ImColorBanana = ImVec4(1.000f, 0.898f, 0.726f, 1.000f), //menus
ImColorTransparentBlack = ImVec4(0.000f, 0.000f, 0.000f, 0.741f), //window background
ImColorDeepOrange = ImVec4(1.000f, 0.537f, 0.000f, 1.000f),
ImColorWhite = ImVec4(1.000f, 1.000f, 1.000f, 1.000f),
ImColorNone = ImVec4(0.000f, 0.000f, 0.000f, 0.000f),
ImColorSlider = ImVec4(0.348f, 0.348f, 0.348f, 0.557f),
ImColorSliderHovered = ImVec4(0.428f, 0.428f, 0.428f, 0.577f),
ImColorSliderActive = ImVec4(0.552f, 0.552f, 0.552f, 0.761f),
ImColorSliderGrab = ImVec4(0.033f, 0.597f, 0.488f, 1.000f),
ImColorSliderGrabActive = ImVec4(0.013f, 0.652f, 0.662f, 1.000f);


CBlackLightMenu* pMenu;

void CBlackLightMenu::Initialize_ImGui_Menus(void)
{
	//this->ImBlackLightMenu();		
}

void CBlackLightMenu::AddButton(bool* bEnable, const char* szButtonName, float fWidthDecrease)
{
	if (*bEnable)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.8f);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);
	}
	else
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);
	}

	if (*bEnable)
	{
		ImGui::PushStyleColor(ImGuiCol_Border, bEnable ? fsm->ColorOpacityPulse(ImVec4(0.000f, 0.766f, 0.091f, 1.000f), 0.050f, 1.000f, 0.100f, 60) : ImVec4(0.000f, 0.766f, 0.091f, 1.000f));
		ImGui::PushStyleColor(ImGuiCol_Button, bEnable ? fsm->ColorOpacityPulse(ImVec4(0.466f, 0.066f, 0.091f, 1.000f), 0.050f, 1.000f, 0.100f, 20) : ImVec4(0.466f, 0.066f, 0.091f, 1.000f));

		//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.516f, 0.896f, 0.169f, 0.400f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.000f, 0.350f, 0.750f, 0.750f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.139f, 0.139f, 0.139f, 0.600f));
	}
	else {
		ImGui::PushStyleColor(ImGuiCol_Border, ImColorNone);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.000f, 0.000f, 0.000f, 0.600f));
		//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.516f, 0.896f, 0.169f, 0.478f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.000f, 0.350f, 0.750f, 0.750f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.139f, 0.139f, 0.139f, 0.493f));
	}
	if (ImGui::Button(szButtonName, pMenu->MenuItemMatchMenuWidth(fWidthDecrease)))
	{
		*bEnable = !(*bEnable);
	}
	ImGui::PopStyleColor(4);
	ImGui::PopStyleVar(2);
}

bool CBlackLightMenu::AddStaticButton(const char* szBtnName, float fWidthDecrease)
{
	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.8f);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.000f, 0.766f, 0.091f, 0.000f));
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.000f, 0.000f, 0.000f, 0.600f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.000f, 0.350f, 0.750f, 0.750f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.139f, 0.139f, 0.139f, 0.493f));
	if (ImGui::Button(szBtnName, pMenu->MenuItemMatchMenuWidth(fWidthDecrease == 0.0f ? 0.0f : fWidthDecrease)))
	{
		return true;
	}
	ImGui::PopStyleColor(4);
	ImGui::PopStyleVar(2);

	return false;
}

void CBlackLightMenu::AddSlider(const char* szName, int& vSettings, int vMinValue, int vMaxValue, const char* szFormat)
{
	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImColorSlider);
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImColorSliderHovered);
	ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImColorSliderActive);
	ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImColorSliderGrab);
	ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImColorSliderGrabActive);
	ImGui::SetNextItemWidth(-FLT_MIN);
	ImGui::SliderInt(szName, &vSettings, vMinValue, vMaxValue, szFormat);
	ImGui::PopStyleColor(5);

}

void CBlackLightMenu::AddSlider(const char* szName, float& vSettings, float vMinValue, float vMaxValue, const char* szFormat)
{
	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImColorSlider);
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImColorSliderHovered);
	ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImColorSliderActive);
	ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImColorSliderGrab);
	ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImColorSliderGrabActive);
	ImGui::SetNextItemWidth(-FLT_MIN);
	ImGui::SliderFloat(szName, &vSettings, vMinValue, vMaxValue, szFormat);
	ImGui::PopStyleColor(5);
}

void CBlackLightMenu::AddMenuText(const char* szText, bool bStickAllign, ImVec4 ImColor, bool bSeparators)
{
	if (bSeparators)
	{
		ImGui::PushStyleColor(ImGuiCol_Separator, ImColorBanana);
		ImGui::Separator();
		ImGui::PopStyleColor(1);
	}	
	ImGui::Text("");
	ImGui::PushStyleColor(ImGuiCol_Text, ImColor);
	ImGui::SameLine(bStickAllign ? 1.0f : (ImGui::GetWindowSize().x / 2) - ImGui::CalcTextSize(szText).x / 2); ImGui::Text(szText);
	ImGui::PopStyleColor(1);	
	if (bSeparators)
	{
		ImGui::PushStyleColor(ImGuiCol_Separator, ImColorBanana);
		ImGui::Separator();
		ImGui::PopStyleColor(1);
	}
}

void CBlackLightMenu::AddItemDescription(const char* szText, ImVec4 textColor)
{
	if (ImGui::IsItemHovered())
	{
		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImColorTransparentBlack);
		ImGui::PushStyleColor(ImGuiCol_Border, ImColorBanana);
		ImGui::PushStyleVar(ImGuiStyleVar_PopupBorderSize, 1.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, 0.0f);
		ImGui::BeginTooltip();		
		ImGui::TextColored(textColor, szText);		
		ImGui::EndTooltip();
		ImGui::PopStyleVar(2);
		ImGui::PopStyleColor(2);
	}
}

void CBlackLightMenu::AddHudItem(bool* bEnabled, const char* szItemName, bool bItemDescription, const char* szDescription)
{
	if (*bEnabled == true)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImColorWhite);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.105f, 0.733f, 0.027f, 0.600f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.348f, 0.348f, 0.348f, 0.557f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.348f, 0.348f, 0.348f, 0.650f));
		ImGui::PushStyleColor(ImGuiCol_Border, ImColorNone);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.0f);
	}
	else
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImColorWhite);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.882f, 0.035f, 0.066f, 0.600f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.348f, 0.348f, 0.348f, 0.557f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.348f, 0.348f, 0.348f, 0.650f));
		ImGui::PushStyleColor(ImGuiCol_Border, ImColorNone);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);
	}
	ImGui::SameLine();
	if (ImGui::Button(szItemName, ImVec2(0.0f, 18.5f)))
	{
		*bEnabled ^= true;
	}
	ImGui::PopStyleColor(5);
	ImGui::PopStyleVar(2);
	if (bItemDescription)
		pMenu->AddItemDescription(szDescription == nullptr ? "Click to toggle\nOn/Off" : szDescription);
}

//buttons
ImVec2 CBlackLightMenu::MenuItemMatchMenuWidth(void)
{
	return ImVec2(-FLT_MIN, 25.0f);
}

ImVec2 CBlackLightMenu::MenuItemMatchMenuWidth(float fWidthCustomSet)
{
	return ImVec2(-FLT_MIN - fWidthCustomSet, 25.0f);
}