
#include <iostream>
#include "module_manager.h"

#define BUFF_SIZE (1024)
#define MAX_PID (65536)

using namespace std;

int pid_used[MAX_PID];	// pid 최대값 어떻게 구함?

const string tasklist_1 = "TASKLIST /FI \"ImageName eq ";
const string tasklist_2 = "\" /FO LIST | FINDSTR PID";
const string taskkill = "TASKKILL /F /PID ";

void int_to_str(char*, int);
DWORD WINAPI thread_func(LPVOID lpParam);

ModuleManager::ModuleManager(int max_cnt, const char* file_name, const char* dir, int mod, int arg)
{
	this->file_name = file_name;
	this->dir = dir;
	this->mod = mod;
	this->arg = arg;
	this->max_cnt = max_cnt;
	this->cnt = 0;
	this->stack = new thread_info[max_cnt];
}

ModuleManager::~ModuleManager()
{
	delete this->stack;
}

void ModuleManager::add_module()
{
	if (cnt >= max_cnt)
	{
		printf("[CAUTION] threads are full!\n");
		return;
	}

	char buff[BUFF_SIZE];
	this->stack[cnt].handle = CreateThread(NULL, 0, thread_func, (LPVOID)this, 0, &this->stack[cnt].dwThreadID);

	int flag = 0;

	while (flag == 0)
	{
		Sleep(1000);
		FILE* fp = _popen((tasklist_1 + file_name + tasklist_2).c_str(), "r");
		while (fgets(buff, BUFF_SIZE, fp))
		{
			//printf("%s\n", buff);
			int pid = 0;
			for (int i = 0;; i++)
			{
				if (buff[i] < '0' || buff[i]>'9')
				{
					if ((buff[i] == '\n' || buff[i] == '\0') && (i>0 && buff[i - 1] >= '0' && buff[i - 1] <= '9'))
					{
						if (pid_used[pid] == IDLE)
						{
							pid_used[pid] = mod;
							stack[cnt].pid = pid;
							//printf("parse pid : %d\n", pid);
							flag = 1;
							break;
						}
						pid = 0;
					}
				}
				else
				{
					pid = pid * 10 + buff[i] - '0';
				}
				if (buff[i] == '\0') break;
			}
		}
	}
	printf("[CREATE] [thread ID] %u [PID] %d \n", stack[cnt].dwThreadID,stack[cnt].pid);
	cnt++;
}

void ModuleManager::del_module()
{
	if (cnt == 0)
	{
		printf("[CAUTION] there is no thread!\n");
		return;
	}
	char pid_str[10];
	cnt--;
	int pid = stack[cnt].pid;
	int_to_str(pid_str, pid);
	system((taskkill + pid_str).c_str());

	pid_used[pid] = IDLE;
	printf("[DELETE] [thread ID] %u [PID] %d \n", stack[cnt].dwThreadID, stack[cnt].pid);
	//printf("pid : %d, pid_str : %s\n", pid, pid_str);
	Sleep(1000);
}

void int_to_str(char* str, int var)
{
	int digit = 0;
	for (int i = var; i > 0; i /= 10)
	{
		digit++;
	}
	str[digit] = '\0';
	for (int i = var; i > 0; i /= 10)
	{
		str[--digit] = i % 10 + '0';
	}
}

DWORD WINAPI thread_func(LPVOID lpParam)
{
	ModuleManager* module = (ModuleManager*)lpParam;

	char arg[12];
	int_to_str(arg, module->arg);
	printf("[START] cpu_module %s\n", arg);
	system(("cmd /c" + module->dir + "\\" + module->file_name + " " + arg).c_str());
	printf("[TERMINATE] cpu_module %s\n", arg);
	return 0;
}
