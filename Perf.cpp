#include "Perf.h"
Perf::Perf()
{

}
Perf& Perf::operator=(const Perf& perf)
{
	if (this != &perf)
	{
		this->performance_name = perf.performance_name;
		this->day = perf.day;
		this->month = perf.month;
		this->hall = perf.hall;
	}
	return *this;
}
Perf::Perf(std::string performance_name, int day, int month, Hall hall)
{
	this->performance_name = performance_name;
	this->day = day;
	this->month = month;
	this->hall = hall;
}
Perf::Perf(const Perf& perf)
{
	this->performance_name = perf.performance_name;
	this->day = perf.day;
	this->month = perf.month;
	this->hall = perf.hall;
}

Perf::~Perf()
{

}

void Perf::Write(const std::string& filename)
{
	std::fstream PerformanceFile;
	PerformanceFile.open(filename, std::ios::app);
	if (PerformanceFile.is_open()) {
		PerformanceFile << "Performance name: " << performance_name << " Performance date: " << day << " / " << month << std::endl;
		PerformanceFile.close();
	}
	else {
		std::cout << "Error! File is not open!" << std::endl;
	}
}
void Perf::setPerf(std::vector<Hall>& hall_list)
{
	std::cout << "Set Performance" << std::endl;
	std::cout << "Enter name for your performance!" << std::endl;
	std::cin >> performance_name;
	std::cout << "Now choose a hall (1-3)" << std::endl;
	int choice;
	std::cin >> choice;
	switch (choice) {
	case 1:
		for (unsigned k = 0; k < hall_list.size() - 1; k++) {
			if (hall_list[k].hall_num == Hall_Number::hall1) {
				setDate(hall_list[k]);
				Write("hall1.txt");
				break;
			}
		}
		break;
	case 2:
		for (unsigned k = 0; k < hall_list.size() - 1; k++) {
			if (hall_list[k].hall_num == Hall_Number::hall2) {
				setDate(hall_list[k]);
				Write("hall2.txt");
				break;
			}
		}
		break;
	case 3:
		for (unsigned k = 0; k < hall_list.size() - 1; k++) {
			if (hall_list[k].hall_num == Hall_Number::hall3) {
				setDate(hall_list[k]);
				Write("hall3.txt");
				break;
			}
		}
		break;
	default: std::cout << "Error!" << std::endl;
	}
}
void Perf::setDate(Hall& h)
{
	std::cout << "Enter a day and a month for your performance" << std::endl;
	std::cin >> day >> month;
	if (day < 1 || day > 30 || month < 1 || month >12) {
		std::cout << "Error! Invalid input for day or month!" << std::endl;
	}
	else {
		if (h.hallday == true && h.hallmonth == true) {
			std::cout << "Date is already reserved!" << std::endl;
		}
		else {
			h.hallday = true;
			h.hallmonth = true;
			std::cout << "Successfully reserved date!" << std::endl;
			hall = h;
		}
	}

}
void Perf::setSeat(int row, int col, char s) {
	hall.seats[row][col] = s;
}
Hall Perf::getHall() {
	return hall;
}
std::string Perf::getName() {
	return performance_name;
}
