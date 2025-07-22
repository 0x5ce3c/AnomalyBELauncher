#include "main.h"

#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

stCommand::stCommand(const char* pname, const char* pdescription, void(*pcallback)(const char* args))
{
	name = pname;
	description = pdescription;
	callback = pcallback;
}

Console::~Console()
{
	ClearLog();
	/*for (int i = 0; i < History.Size; i++)
		free(History[i]);*/
}

void Console::ClearLog()
{
	for (int i = 0; i < Items.Size; i++)
		free(Items[i]);
	Items.clear();
}

void Console::AddLog(const char* fmt, ...) IM_FMTARGS(2)
{
	//traceLastFunc("void Console::AddLog(const char* fmt, ...) IM_FMTARGS(2)");
	// FIXME-OPT
	char buf[0x1000];
	static int c = 0;
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
	buf[IM_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);
	Items.push_back(Strdup(cp1251_to_utf8(buf).c_str()));
	/*if (Items.Size > 256) {
		free(Items[0]);
		Items.erase(Items.begin());
	}*/
	/*HCHANNEL menu_log_message;
	static HSAMPLE menu_log_sample;
	menu_log_sample = BASS_SampleLoad(false, BE_MENU_LOGMESSAGEMP3, 0, 0, 1, NULL);
	menu_log_message = BASS_SampleGetChannel(menu_log_sample, FALSE);
	BASS_ChannelPlay(menu_log_message, FALSE);
	QWORD len = BASS_ChannelGetLength(menu_log_message, BASS_POS_BYTE);
	DWORD time = BASS_ChannelBytes2Seconds(menu_log_message, len);*/
	//PlaySound(MAKEINTRESOURCE(IDR_WAVE2),\
		NULL, SND_RESOURCE | SND_FILENAME | SND_ASYNC);
}

void Console::AddLog(int timer, const char* fmt, ...)IM_FMTARGS(2)
{
	//traceLastFunc("void Console::AddLog(int timer, const char* fmt, ...)IM_FMTARGS(2)");
	if (timer < 60) timer = 60;
	static DWORD tick = 0;
	DWORD tickc = GetTickCount();
	if (tickc - tick > timer)
	{
		tick = tickc;
		// FIXME-OPT
		char buf[1024];
		va_list args;
		va_start(args, fmt);
		vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);		
		buf[IM_ARRAYSIZE(buf) - 1] = 0;
		va_end(args);
		Items.push_back(Strdup(cp1251_to_utf8(buf).c_str()));
		/*if (Items.Size > 256) {
			free(Items[0]);
			Items.erase(Items.begin());
		}*/
		/*HCHANNEL menu_log_message;
		static HSAMPLE menu_log_sample;
		menu_log_sample = BASS_SampleLoad(false, "be_menu_log_message.mp3", 0, 0, 1, NULL);
		menu_log_message = BASS_SampleGetChannel(menu_log_sample, FALSE);
		BASS_ChannelPlay(menu_log_message, FALSE);
		QWORD len = BASS_ChannelGetLength(menu_log_message, BASS_POS_BYTE);
		DWORD time = BASS_ChannelBytes2Seconds(menu_log_message, len);*/
	}
}

void Console::Draw(const char* title)
{
	RECT	um;		// damn near killed um        

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	//Set the IMGUI ON TOP POSITION X : 0 Y : 0 of the actual screen resolution.
	//ImGui::SetNextWindowPos(ImVec2(0, 0));

	//Change the Y viewport size to 200 and let the X to take the full screen : 
 //   viewport->Size.y = ImGui::GetWindowSize().y; // / 2
   // ImGui::SetNextWindowSize(viewport->Size);
	//ImGui::SetNextWindowSize(ImVec2(GetWindowSize() / 2), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y / 2), ImGuiCond_FirstUseEver);

	static bool no_titlebar = false;
	static bool no_scrollbar = false;
	static bool no_menu = true;
	static bool no_move = false;
	static bool no_resize = false;
	static bool no_collapse = false;
	static bool no_nav = false;
	static bool autosize = false;
	static bool no_save = false;

	ImGuiWindowFlags wincon_flags = 0;
	if (no_titlebar)  wincon_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar) wincon_flags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)     wincon_flags |= ImGuiWindowFlags_MenuBar;
	if (no_move)      wincon_flags |= ImGuiWindowFlags_NoMove;
	if (no_resize)    wincon_flags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)  wincon_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)       wincon_flags |= ImGuiWindowFlags_NoNav;
	if (autosize)     wincon_flags |= ImGuiWindowFlags_AlwaysAutoResize;
	if (no_save)      wincon_flags |= ImGuiWindowFlags_NoSavedSettings;

	if (!ImGui::BeginChild(title))
	{
		ImGui::EndChild();
		return;
	}

	//Filter.Draw("Filter");
	//ImGui::BeginChild("###123");
	//ImGui::EndChild();
	//ImGui::Separator();

	const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
	ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);

	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing

	for (int i = 0; i < Items.Size; i++)
	{
		const char* item = Items[i];
		/*if (!Filter.PassFilter(item))
			continue;*/

		/*if (bemod->autoclear_log.enabled) {

		}*/
		//if (sn->con.Items.Size > 500)
			//sn->con.ClearLog();


		// Normally you would store more information in your item than just a string.
	   // (e.g. make Items[] an array of structure, store color/type etc.)
		ImVec4 color;
		bool has_color = false;
		if (strstr(item, "--> ")) { color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f); has_color = true; }		
		
		//Connected
		if (has_color)
			ImGui::PushStyleColor(ImGuiCol_Text, color);

		if (has_color)
		{
			ImGui::TextUnformatted(item);
			//ImGui::TextWrapped(item);
			ImGui::PopStyleColor();
		}
		else {
			ImGui::TextWithColors(item);
		}
	}

	if (ScrollToBottom || (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
		ImGui::SetScrollHereY(1.0f);
	ScrollToBottom = false;

	ImGui::PopStyleVar();
	ImGui::EndChild();
	ImGui::Separator();
	
	ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
	if (ImGui::InputTextWithHint(u8"#Ввод", u8"Чтобы узнать все команды введи: //cmds", InputBuf, IM_ARRAYSIZE(InputBuf), input_text_flags, &TextEditCallbackStub, (void*)this))
	{
		char* s = InputBuf;
		Strtrim(s);
		//if (s[0] == '/') {
			ExecCommand(s);
		//}		 
		memset(s, 0, sizeof(*s));
	}
	
	ImGui::SetItemDefaultFocus();

	if (ImGui::IsItemHovered() || (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) && !ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0)))
		ImGui::SetKeyboardFocusHere(-1);	

}

int Console::TextEditCallback(ImGuiInputTextCallbackData* data)
{
	//traceLastFunc("int Console::TextEditCallback(ImGuiInputTextCallbackData* data)");
	//AddLog("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
	switch (data->EventFlag)
	{
	case ImGuiInputTextFlags_CallbackCompletion:
	{

		//if (data->Buf[0] != '/') break;

		// Locate beginning of current word
		const char* word_end = (data->Buf + data->CursorPos);
		const char* word_start = word_end;
		while (word_start > data->Buf + 1)
		{
			const char c = word_start[-1];
			if (c == ' ' || c == '\t' || c == ',' || c == ';')
				break;
			word_start--;
		}

		// Build a list of candidates
		ImVector<const char*> candidates;
		for (int i = 0; i < Commands.Size; i++)
			if (Strnicmp(Commands[i]->name, word_start, (int)(word_end - word_start)) == 0)
				candidates.push_back(Commands[i]->name);

		if (candidates.Size == 0)
		{
			// No match
			AddLog("No match for \"%.*s\"!\n", (int)(word_end - word_start), word_start);
		}
		else if (candidates.Size == 1)
		{
			// Single match. Delete the beginning of the word and replace it entirely so we've got nice casing
			data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
			data->InsertChars(data->CursorPos, candidates[0]);
			data->InsertChars(data->CursorPos, " ");
		}
		else
		{
			// Multiple matches. Complete as much as we can, so inputing "C" will complete to "CL" and display "CLEAR" and "CLASSIFY"
			int match_len = (int)(word_end - word_start);
			for (;;)
			{
				int c = 0;
				bool all_candidates_matches = true;
				for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
					if (i == 0)
						c = toupper(candidates[i][match_len]);
					else if (c == 0 || c != toupper(candidates[i][match_len]))
						all_candidates_matches = false;
				if (!all_candidates_matches)
					break;
				match_len++;
			}

			if (match_len > 0)
			{
				data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
				data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
			}

			// List matches
			AddLog("Возможные совпадения:");
			for (int i = 0; i < candidates.Size; i++)
				AddLog("- %s", candidates[i]);
		}

		break;
	}
	case ImGuiInputTextFlags_CallbackHistory:
	{
		// Example of HISTORY
		const int prev_history_pos = HistoryPos;
		if (data->EventKey == ImGuiKey_UpArrow)
		{
			if (HistoryPos == -1)
				HistoryPos = History.Size - 1;
			else if (HistoryPos > 0)
				HistoryPos--;
		}
		else if (data->EventKey == ImGuiKey_DownArrow)
		{
			if (HistoryPos != -1)
				if (++HistoryPos >= History.Size)
					HistoryPos = -1;
		}

		// A better implementation would preserve the data on the current input line along with cursor position.
		if (prev_history_pos != HistoryPos)
		{
			const char* history_str = (HistoryPos >= 0) ? History[HistoryPos] : "";
			data->DeleteChars(0, data->BufTextLen);
			data->InsertChars(0, history_str);
		}
	}
	}
	return 0;
}

void Console::AddCommand(const char* name, const char* description, void(*callback)(const char* args))
{
	Commands.push_back(new stCommand(name, description, callback));
	//AddLog("Зарегистрирована команда -> %s - %s", name, description);
}

void Console::AddHistory(const char* content)
{
	// Insert into history. First find match and delete it so it can be pushed to the back. This isn't trying to be smart or optimal.
	HistoryPos = -1;
	for (int i = History.Size - 1; i >= 0; i--)
		if (Stricmp(History[i], content) == 0)
		{
			free(History[i]);
			History.erase(History.begin() + i);
			break;
		}
	History.push_back(Strdup(content));
}

void Console::ExecCommand(const char* command_line)
{
	AddLog("--> %s", command_line);

	AddHistory(command_line);

	//copy
	char buffer[256];
	memset(buffer, 0, 256); //Always remember to empty this char array, or there will be a argument problem.
	strcpy(buffer, &command_line[1]);

	//separate command and arguments
	int length = strlen(buffer);
	int cmdlen = 0;
	for (int i = 0; i < length; i++) {
		if (buffer[cmdlen] == ' ' || buffer[cmdlen] == '\0') break;
		cmdlen++;
	}
	const char* arguments = &buffer[cmdlen + 1];
	buffer[cmdlen] = 0x00;

	// Process command
	bool found = false;
	for (int i = 0; i < Commands.Size; i++) {
		if (Stricmp(buffer, Commands[i]->name) == 0) {
			Commands[i]->callback(arguments);
			found = true;
			break;
		}
	}
	if (!found)
		AddLog("Неизвестная команда --> '%s'", command_line);

	// On commad input, we scroll to bottom even if AutoScroll==false
	ScrollToBottom = true;
}