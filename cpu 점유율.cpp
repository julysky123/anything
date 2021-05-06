
#pragma comment(lib, "pdh.lib")

#include <windows.h>
#include <pdh.h>
#include <pdhmsg.h>
#include <iostream>

using namespace std;

class CpuUsage
{
private:
	PDH_HQUERY              m_hQuery;
	PDH_HCOUNTER    m_hCounter;

public:
	CpuUsage() : m_hQuery(0), m_hCounter(0) {}
	~CpuUsage() { destroy(); }

	bool    init()
	{
		PDH_STATUS      status = PdhOpenQuery(0, 0, &m_hQuery);

		if (status != ERROR_SUCCESS)
			return false;

		status = PdhAddCounter(m_hQuery, "\\Processor(_TOTAL)\\% Processor Time", 0, &m_hCounter);

		if (status != ERROR_SUCCESS)
			return false;

		status = PdhCollectQueryData(m_hQuery);

		if (status != ERROR_SUCCESS)
		{
			return false;
		}

		return true;
	}

	void    destroy()
	{
		if (m_hQuery)
			PdhCloseQuery(m_hQuery);
		m_hQuery = 0;
	}

	bool    getCpuUsage(double* val)
	{
		PDH_STATUS      status = PdhCollectQueryData(m_hQuery);

		if (status != ERROR_SUCCESS)
			return false;

		PDH_FMT_COUNTERVALUE    value;

		status = PdhGetFormattedCounterValue(m_hCounter, PDH_FMT_DOUBLE, 0, &value);

		if (status != ERROR_SUCCESS)
			return false;
		*val = value.doubleValue;
		return true;
	}

};


int main(int argc, char* argv[])
{
	CpuUsage cpuUsage;
	if (cpuUsage.init() == false)
		return 1;

	int i = 0;
	double total = 0;
	while (i<120)
	{
		i++;
		double  val = 0.0;
		if (cpuUsage.getCpuUsage(&val))
			cout <<"#"<<i<< ": CPU Usage : " << val << "%\n";
		total += val;
		Sleep(500);
	}
	cout << "------------------------" << "\n";
	cout << "average CPU Usage : "<< total/120<<"%\n";
	cout << "------------------------" << "\n";
	cout << "\t\thttp://fehead.tistory.com\n";


	return 0;
}
