#pragma once

#include <Pdh.h>
#define IDLE (0)
#define CPU_PID (1)
#define MEM_PID (2)

using namespace std;

struct thread_info {
	int pid;
	HANDLE handle;
	DWORD dwThreadID;
};


struct ModuleManager {
	
	int max_cnt;
	int cnt;
	int mod;
	int arg;
	thread_info* stack;
	string file_name;
	string dir;
	ModuleManager(int max_cnt, const char* file_name, const char* dir, int mod, int arg);
	~ModuleManager();


	void add_module();
	void del_module(void);
};

