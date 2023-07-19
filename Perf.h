#pragma once
#include "Halls.h"
#include "includes.h"
class Perf
{
private:
	std::string performance_name;
	int day, month;
	Hall hall;
public:
	Perf();
	Perf(std::string performance_name, int day, int month, Hall hall);
	Perf(const Perf& perf);
	Perf& operator=(const Perf& perf);
	~Perf();

	void Write(const std::string& filename);
	void setPerf(std::vector<Hall>& hall_list);
	void setDate(Hall& h);
	void setSeat(int row, int col, char s);
	Hall getHall();
	std::string getName();
};

