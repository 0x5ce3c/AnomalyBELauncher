#pragma once

struct stCommand {
    const char* name;
    const char* description;
    void (*callback)(const char* args);

    stCommand(const char* pname, const char* pdescription, void(*pcallback)(const char* args));
};

struct Console
{

    char                  InputBuf[256];
    ImVector<char*>       Items;
    ImVector<stCommand*>  Commands;
    ImVector<char*>       History;
    int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
    ImGuiTextFilter       Filter;
    bool                  AutoScroll;
    bool                  ScrollToBottom;
    bool                  cmds_registered;
    //IM_FMTARGS(2)
    Console();
    ~Console();

    // Portable helpers
    static int   Stricmp(const char* s1, const char* s2) { int d; while ((d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; } return d; }
    static int   Strnicmp(const char* s1, const char* s2, int n) { int d = 0; while (n > 0 && (d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; n--; } return d; }
    static char* Strdup(const char* s) { size_t len = strlen(s) + 1; void* buf = malloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)s, len); }
    static void  Strtrim(char* s) { char* str_end = s + strlen(s); while (str_end > s && str_end[-1] == ' ') str_end--; *str_end = 0; }

    void    ClearLog();
    void    AddLog(const char* fmt, ...)IM_FMTARGS(2);
    void    AddLog(int timer, const char* fmt, ...)IM_FMTARGS(2);
    //void    Draw(const char* title, bool* p_open);
    void    Draw(const char* title);
    void    ExecCommand(const char* command_line);
    void    AddHistory(const char* content);
    void    AddCommand(const char* name, const char* description, void(*callback)(const char* args));

    // In C++11 you'd be better off using lambdas for this sort of forwarding callbacks
    static int TextEditCallbackStub(ImGuiInputTextCallbackData* data)
    {
        Console* console = (Console*)data->UserData;
        return console->TextEditCallback(data);
    }

    int     TextEditCallback(ImGuiInputTextCallbackData* data);

};

typedef void(__cdecl* CMDPROC) (PCHAR);