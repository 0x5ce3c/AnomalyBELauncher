#pragma once


namespace ImFuncs
{
	void HelpDescr(const char* desc);
	void HelpDescr(const char* desc, ImColor Color);
	void FastDescr(const char* desc, ImColor Color);
	void FastDescr(const char* desc);
	void LineVertical();

	void GlitchText(const char* text);
	void GlitchText2(const char* text);
	void GlitchText3(const char* text);
	std::string animateString(const char* word, int rotationDelay);
}

#ifndef EXTRA_IMGUI_H
#define EXTRA_IMGUI_H

namespace ImGui {

	void TextWithColors(const char* fmt, ...);	
}

#endif