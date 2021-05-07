#include <iostream>
#include <process.h>
#include <Pdh.h>
#include <string>
using namespace std;
#define BUFF_SIZE (1024)
#define CPU_MODULE "cpuUsageTest2"
#define MEM_MODULE "memUsageTest"


using namespace std;

int pid_queue[10];
int pid[65536];	// pid 최대값 어떻게 구함?

string tasklist = "TASKLIST | FINDSTR ";
string dir = "C:\\Users\\mj.gwak\\source\\repos\\cpuUsageTest2\\Release";


int main()
{
	printf("exec Command!!\n");

    char  buff[BUFF_SIZE];
    FILE* fp;
    
   
    for (int i = 0; i < 3; i++)
    {
        system((dir + "\\" + CPU_MODULE + ".exe").c_str());
        Sleep(1000);

    }


    fp = _popen((tasklist + "cpuUsageTest2").c_str(), "r");
    if (NULL == fp)
    {
        perror("popen() 실패");
        return -1;
    }

    while (fgets(buff, BUFF_SIZE, fp))
        printf("%s", buff);

    _pclose(fp);

    return 0;


}
