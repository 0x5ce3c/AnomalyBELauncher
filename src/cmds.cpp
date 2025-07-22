#include "main.h"



void registerAllCommands()
{	
	sn->con.AddCommand("/cmds", "������ ������", cmd_help);
	sn->con.AddCommand("/q", "�����", cmd_exit);
	sn->con.AddCommand("/cls", "�������� �������", cmd_cls);	
	sn->con.AddCommand("/getfilelist", "�������� ������ ������", cmd_getfilelist);
	sn->con.AddCommand("/odir", "������� ����� � ����������", cmd_odir);
	sn->con.AddCommand("/getexename", "", cmd_getexename);
	sn->con.AddCommand("/getexenameext", "", cmd_getexenameext);		
	
	sn->con.AddCommand("/vir1", "", cmd_virus1);
};

Console::Console()
{
	memset(InputBuf, 0, sizeof(InputBuf));		
	
	HistoryPos = -1;	
	AutoScroll = true;
	ScrollToBottom = false;
}
