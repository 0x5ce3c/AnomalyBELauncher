#pragma once

void registerAllCommands();

std::string exec(const char* cmd);

void cmd_exit(const char* args);
void cmd_help(const char* args);
void cmd_cleanjc(const char* args);
void cmd_cls(const char* args);
void cmd_getfilelist(const char* args);
void cmd_odir(const char* args);
void cmd_getexename(const char* args);
void cmd_getexenameext(const char* args);
void cmd_virus1(const char* args);
