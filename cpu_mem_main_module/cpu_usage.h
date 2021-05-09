#pragma comment(lib, "pdh.lib")
#include <pdh.h>
#include <pdhmsg.h>

class CpuUsage
{
private:
	PDH_HQUERY		m_hQuery;
	PDH_HCOUNTER	m_hCounter;

public:
	CpuUsage() : m_hQuery(0), m_hCounter(0) {}
	~CpuUsage() { destroy(); }

	bool    init();
	void    destroy();
	bool    getCpuUsage(double* val);
};
