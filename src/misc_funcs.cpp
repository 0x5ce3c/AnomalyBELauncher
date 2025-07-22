#include "main.h"


static bool func_nnabler_init = true;

void funcs_enabler()
{
	if (func_nnabler_init)
	{
		//sn->con.AddLog("{00DD00}control hook() is init success");
		func_nnabler_init = 0;
	}	

	static bool dbg_a = false;
	if (sn->dbg.enabled)
	{
		if (!dbg_a)
		{
			sn->con.AddLog("[info]: Debug Mode Enabled");
			dbg_a = 1;
		}
	}
	else
	{
		if (dbg_a)
		{
			sn->con.AddLog("[info]: Debug Mode Disabled");
			dbg_a = 0;
		}
	}	
	
}

void sleep(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
};

void GetListFiles(std::string path)
{	
	for (/*const auto& file*/ const std::filesystem::directory_entry &file: filesystem::directory_iterator(path))
	{
		if (filesystem::is_directory(file))
		{			
			sn->con.AddLog("[Сканер] > %s\\", file.path().string());			
		}
		else
		{								
			sn->con.AddLog("[Сканер] > %s", file.path().string());			
		}
	}	
};





using std::string;
string getFileNameWithExtension(const string& s) {
	char sep = '/';
#ifdef _WIN32
	sep = '\\';
#endif
	size_t i = s.rfind(sep, s.length());
	if (i != string::npos)
	{
		string filename = s.substr(i + 1, s.length() - i);
		string rawname = filename.substr(0, s.length());
		return(rawname);
	}
	return("");
}
string getFileNameWithoutExtension(const string& s) {
	char sep = '/';
#ifdef _WIN32
	sep = '\\';
#endif
	size_t i = s.rfind(sep, s.length());
	if (i != string::npos)
	{
		string filename = s.substr(i + 1, s.length() - i);
		size_t lastindex = filename.find_last_of(".");
		string rawname = filename.substr(0, lastindex);
		return(rawname);
	}
	return("");
}