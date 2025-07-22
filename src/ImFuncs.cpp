#include "main.h"
#include "ImFuncs.h"

void ImFuncs::HelpDescr(const char* desc)
{
	///ImGui::TextDisabled("(?)");
	///ImGui::Text("(?)");
	ImGui::TextColored(ImVec4(2.00, 0.00, 0.00, 2.00), u8"[?]");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		///ImGui::TextUnformatted(desc);
		ImGui::TextWithColors(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void ImFuncs::HelpDescr(const char* desc, ImColor Color)
{
	ImGui::TextColored(Color, "(?)");
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip(desc);
}

void ImFuncs::FastDescr(const char* desc)
{
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		///ImGui::TextUnformatted(desc);
		ImGui::TextWithColors(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}



void ImFuncs::LineVertical()
{
	ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
}


// Can be edited to accept colors in the form of arguments
void ImFuncs::GlitchText(const char* text)
{
	ImVec2 pos = ImGui::GetCursorPos();
	ImVec2 size = ImGui::GetWindowSize();

	// Red Text
	ImGui::SetCursorPosX(pos.x - (1 + (rand() % 3)));
	ImGui::SetCursorPosY(pos.y - (rand() % 2));
	ImGui::PushStyleColor(ImGuiCol_Text, ImColor(235, 5, 90, 100 + (rand() % 60)).Value);
	ImGui::Text(text);

	// Cyan Text
	ImGui::SetCursorPos(ImVec2(pos.x + (1 + (rand() % 3)), pos.y));
	ImGui::SetCursorPosY(pos.y + (rand() % 2));
	ImGui::PushStyleColor(ImGuiCol_Text, ImColor(32, 217, 217, 100 + (rand() % 60)).Value);
	ImGui::Text(text);
	ImGui::PopStyleColor(2);

	// Real Text
	ImGui::SetCursorPos(pos);
	ImGui::Text(text);
}

void ImFuncs::GlitchText2(const char* text)
{
	ImVec2 pos = ImGui::GetCursorPos();
	ImVec2 size = ImGui::GetWindowSize();

	// Calculate the animation offsets based on time
	float xOffset = sinf(ImGui::GetTime() * 1.5f) * 1.0f; // Adjust the values to control the speed and range of motion
	float yOffset = cosf(ImGui::GetTime() * 0.5f) * 3.0f; // Adjust the values to control the speed and range of motion

	// Red Text
	ImGui::SetCursorPosX(pos.x - (1 + (rand() % 3)) + xOffset);
	ImGui::SetCursorPosY(pos.y - (rand() % 2) + yOffset);
	ImGui::PushStyleColor(ImGuiCol_Text, ImColor(232, 0, 0, 100 + (rand() % 60)).Value);
	ImGui::Text(text);

	// Cyan Text
	ImGui::SetCursorPos(ImVec2(pos.x + (1 + (rand() % 3)) + xOffset, pos.y + yOffset));
	ImGui::SetCursorPosY(pos.y + (rand() % 2) + yOffset);
	ImGui::PushStyleColor(ImGuiCol_Text, ImColor(161, 161, 161, 100 + (rand() % 60)).Value);
	ImGui::Text(text);
	ImGui::PopStyleColor(2);

	// Real Text
	ImGui::SetCursorPos(pos);
	ImGui::Text(text);
}

void ImFuncs::GlitchText3(const char* text)
{
	ImVec2 pos = ImGui::GetCursorPos();
	ImVec2 size = ImGui::GetWindowSize();

	// Calculate the animation offset based on time
	float offset = sinf(ImGui::GetTime() * 2.0f) * 10.0f; // Adjust the values to control the speed and range of motion

	// Red Text
	ImGui::SetCursorPosX(pos.x - (1 + (rand() % 3)) + offset);
	ImGui::SetCursorPosY(pos.y - (rand() % 2));
	ImGui::PushStyleColor(ImGuiCol_Text, ImColor(235, 5, 90, 100 + (rand() % 60)).Value);
	ImGui::Text(text);

	// Cyan Text
	ImGui::SetCursorPos(ImVec2(pos.x + (1 + (rand() % 3)) + offset, pos.y));
	ImGui::SetCursorPosY(pos.y + (rand() % 2));
	ImGui::PushStyleColor(ImGuiCol_Text, ImColor(32, 217, 217, 100 + (rand() % 60)).Value);
	ImGui::Text(text);
	ImGui::PopStyleColor(2);

	// Real Text
	ImGui::SetCursorPos(pos);
	ImGui::Text(text);
}

void sleep(long ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

char getRandomSymbol(char from, char to) {
	return from + rand() % (to - from + 1);
}

std::string ImFuncs::animateString(const char* word, int rotationDelay)
{
	static int currentIndex = 0; // Сохраняем текущий индекс
	int length = strlen(word);
	std::vector<char> output(length, ' '); // Создаем вектор с пробелами

	// Устанавливаем минимальное значение задержки
	if (rotationDelay > 100) {
		rotationDelay = 100;
	}

	// Получаем текущее время
	static auto lastUpdateTime = std::chrono::steady_clock::now();
	auto now = std::chrono::steady_clock::now();

	// Проверяем, прошло ли достаточно времени для обновления
	if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdateTime).count() >= rotationDelay) {
		lastUpdateTime = now; // Обновляем время последнего обновления

		// Анимация для текущего символа
		for (int j = 0; j < length; ++j) {
			if (j < currentIndex) {
				output[j] = word[j]; // Заполняем уже анимированные символы
			}
			else {
				// Заполняем случайными печатаемыми символами
				output[j] = getRandomSymbol(32, 126);
			}
		}

		// Если текущий индекс меньше длины слова, увеличиваем его
		if (currentIndex < length) {
			currentIndex++;
		}
	}

	// Если анимация завершена, возвращаем финальный текст
	if (currentIndex >= length) {
		return std::string(word); // Возвращаем оригинальный текст
	}

	// Возвращаем текущую анимированную строку
	return std::string(output.data());
}


namespace ImGui {

	const char ColorMarkerStart = '{';
	const char ColorMarkerEnd = '}';

	const char szDefaultStyleFile[] = "style.bin";

	bool processInlineHexColor(const char* start, const char* end, ImVec4& color) {
		const int hexCount = (int)(end - start);
		if (hexCount == 6 || hexCount == 8)
		{
			char hex[9];
			strncpy(hex, start, hexCount);
			hex[hexCount] = 0;

			unsigned int hexColor = 0;
			if (sscanf(hex, "%x", &hexColor) > 0)
			{
				color.x = static_cast<float>((hexColor & 0x00FF0000) >> 16) / 255.0f;
				color.y = static_cast<float>((hexColor & 0x0000FF00) >> 8) / 255.0f;
				color.z = static_cast<float>((hexColor & 0x000000FF)) / 255.0f;
				color.w = 1.0f;

				if (hexCount == 8)
				{
					color.w = static_cast<float>((hexColor & 0xFF000000) >> 24) / 255.0f;
				}

				return true;
			}
		}

		return false;
	}

	void TextWithColors(const char* fmt, ...)
	{
		char tempStr[4096];

		va_list argPtr;
		va_start(argPtr, fmt);
		_vsnprintf(tempStr, sizeof(tempStr), fmt, argPtr);
		va_end(argPtr);
		tempStr[sizeof(tempStr) - 1] = '\0';

		bool pushedColorStyle = false;
		const char* textStart = tempStr;
		const char* textCur = tempStr;
		while (textCur < (tempStr + sizeof(tempStr)) && *textCur != '\0')
		{
			if (*textCur == ColorMarkerStart)
			{
				// Print accumulated text
				if (textCur != textStart)
				{
					ImGui::TextUnformatted(textStart, textCur);
					ImGui::SameLine(0.0f, 0.0f);
				}

				// Process color code
				const char* colorStart = textCur + 1;
				do
				{
					++textCur;
				} while (*textCur != '\0' && *textCur != ColorMarkerEnd);

				// Change color
				if (pushedColorStyle)
				{
					ImGui::PopStyleColor();
					pushedColorStyle = false;
				}

				ImVec4 textColor;
				if (processInlineHexColor(colorStart, textCur, textColor))
				{
					ImGui::PushStyleColor(ImGuiCol_Text, textColor);
					pushedColorStyle = true;
				}

				textStart = textCur + 1;
			}
			else if (*textCur == '\n')
			{
				// Print accumulated text an go to next line
				ImGui::TextUnformatted(textStart, textCur);
				textStart = textCur + 1;
			}

			++textCur;
		}

		if (textCur != textStart)
		{
			ImGui::TextUnformatted(textStart, textCur);
		}
		else
		{
			ImGui::NewLine();
		}

		if (pushedColorStyle)
		{
			ImGui::PopStyleColor();
		}
	}
}