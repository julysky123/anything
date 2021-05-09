#include <iostream>
#include <random>
#include "module_manager.h"
#include "cpu_usage.h"

using namespace std;
#define BUFF_SIZE (1024)

#define CPU_MODULE "cpu_module_custom.exe"
#define CPU_DIR "D:\\cpu_module"
#define CPU_THREAD_MAX (20)

#define CPU_GOAL_UPPER_BOUND (80.0)
#define CPU_GOAL_LOWER_BOUND (10.0)
#define CPU_THRESHOLD (5.0)
#define CPU_UNIT_USAGE (3.0)

#define CPU_USAGE_CYCLE (500)		//ms
#define CPU_UPDATE_CYCLE (10000)		//ms
#define CPU_USAGE_LENGTH ((CPU_UPDATE_CYCLE)/(CPU_USAGE_CYCLE))

#define GOAL_CYCLE (60000)			//ms
#define GOAL_LENGTH ((GOAL_CYCLE)/(CPU_UPDATE_CYCLE))

#define MEM_MODULE "mem_module.exe"
#define MEM_DIR ""
#define MEM_THREAD_MAX (20)
#define MEM_GOAL (0.0)

#define MEM_GOAL_UPPER_BOUND (80.0)
#define MEM_GOAL_LOWER_BOUND (10.0)


using namespace std;


CpuUsage cpuUsage;
double val = 0.0, total = 0.0;
double cpu_usage[CPU_USAGE_LENGTH];


double cpu_average_usage()
{
	for (int i = 0; i < CPU_USAGE_LENGTH; i++)
	{
		total -= cpu_usage[i];
		bool flag = cpuUsage.getCpuUsage(&val);
		cpu_usage[i] = val;
		total += cpu_usage[i];
		printf("[INFO] CPU USAGE : %lf%%\n", (total / CPU_USAGE_LENGTH));
		Sleep(CPU_USAGE_CYCLE);
	}

	return (total / CPU_USAGE_LENGTH);
}

void cpu_unit_adjust(ModuleManager* module, double cpu_default_usage)
{
	int s = 1, e = (1 << 30) - 1;
	int m;
	int ret = e + 1;
	while (s <= e)
	{
		m = (s + e) / 2;
		printf("[INIT] adjusting cpu_module's argument.. (%d)\n",m);
		module->arg = m;
		module->add_module();
		double diff = cpu_average_usage()-cpu_default_usage;
		if (diff > CPU_UNIT_USAGE)
		{
			ret = m;
			e = m - 1;
		}
		else
		{
			s = m + 1;
		}
		module->del_module();
	}
	module->arg = ret;
	printf("[INIT] cpu_module's argument : %d\n",ret);
}



int main()
{
	printf("exec Command!!\n");
	/*--------------------INIT---------------------*/
	srand(1);

	int cpu_arg = (1<<29)-1;

	ModuleManager cpu_module(CPU_THREAD_MAX, CPU_MODULE, CPU_DIR, CPU_PID, cpu_arg);
	
	if (cpuUsage.init() == false)
		return 1;

	int i = 0;

	double cpu_goal = 0;	//random 용.

	printf("[INIT] CPU USAGE INITIALIZE \n");

	Sleep(5000);

	for(int i=0;i<CPU_USAGE_LENGTH;i++)
	{
		cpuUsage.getCpuUsage(&val);
		cpu_usage[i] = val;
		total += cpu_usage[i];
		Sleep(CPU_USAGE_CYCLE);
		printf(">>%d/%d..\n", i, CPU_USAGE_LENGTH);
		printf("[INFO] CPU USAGE : %lf%%\n", (total / (i+1)));
	}

	double cpu_default_usage = total / CPU_USAGE_LENGTH;
	cpu_unit_adjust(&cpu_module, cpu_default_usage);

	/*-------------------------------------------------*/
	for (;;)
	{
		double cpu_goal = (double)(rand() % ((int)(CPU_GOAL_UPPER_BOUND - CPU_GOAL_LOWER_BOUND)) + CPU_GOAL_LOWER_BOUND);
		printf("[INFO] CPU GOAL : %lf%%\n", cpu_goal);
		for (int j=0;j<GOAL_LENGTH;j++)
		{
			printf("[INFO] CPU USAGE : %lf%% CPU GOAL : %lf%%\n", (total / CPU_USAGE_LENGTH), cpu_goal);
			if ((total / CPU_USAGE_LENGTH) < cpu_goal-CPU_THRESHOLD)
			{
				cpu_module.add_module();
			}
			else if ((total / CPU_USAGE_LENGTH) > cpu_goal + CPU_THRESHOLD)
			{
				cpu_module.del_module();
			}
			cpu_average_usage();
		}
	}
}


/*
목표 (완료):
cpu_goal 
cpu_now : (30초 평균)

for(;;)
{
	for(;;) 30초간 cpu 평균값 확인.
	if(cpu_goal>cpu_now) cpu 하나 추가
	else cpu 하나 종료
}
*/

/*
2목표

cpu_module 의 cpu 변화량이 1%가 되게 cpu module 내 for문 조절.
(init time에 이분탐색으로 1%~10% 되게 조절)

이에따라 cpu_thread 개수 제한도 조절.

*/
