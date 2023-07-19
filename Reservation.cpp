#include "Reservation.h"
Reservation::Reservation()
{

}
Reservation::Reservation(unsigned respassword, unsigned seats_row, unsigned seats_col)
{
	this->respassword = respassword;
	this->seats_row = seats_row;
	this->seats_col = seats_col;
}
Reservation::Reservation(const Reservation& reserve)
{
	respassword = reserve.respassword;
	seats_row = reserve.seats_row;
	seats_col = reserve.seats_col;
}
Reservation& Reservation::operator=(const Reservation& reserve)
{
	if (this != &reserve)
	{
		this->respassword = reserve.respassword;
		this->seats_row = reserve.seats_row;
		this->seats_col = reserve.seats_col;
		this->perf = reserve.perf;
	}
	return *this;
}
Reservation::~Reservation()
{

}
void Reservation::WriteRes(const std::string& filename) {
	std::fstream PerformanceFile;
	PerformanceFile.open(filename, std::ios::app);
	if (PerformanceFile.is_open()) {
		PerformanceFile << "Reserved seats: " << seats_row << " / " << seats_col << std::endl;
		PerformanceFile.close();
	}
	else {
		std::cout << "Error! File is not open!" << std::endl;
	}
}
void Reservation::TicketRes(std::vector<Perf>& perf_list) {
	std::cout << "Ticket res" << std::endl;
	std::cout << "Choose a performance!" << std::endl;
	int perfchoice;
	for (unsigned l = 0; l < perf_list.size(); l++) {
		std::cout << perf_list[l].getName() << std::endl;
	}
	std::cin >> perfchoice;
	std::cout << "Please choose a row and a seat" << std::endl;
	unsigned row, col;
	std::cin >> row >> col;
	if (perf_list[perfchoice - 1].getHall().seats[row][col] == 'R') { //res
		std::cout << "Seat is already reserved!" << std::endl;
	}
	else {
		perf_list[perfchoice - 1].setSeat(row, col, 'R'); //res
		std::cout << "Seat successfully reserved !" << std::endl;
		seats_row = row;
		seats_col = col;
		perf = perf_list[perfchoice - 1];

		std::cout << "Now set a password for your reservation!" << std::endl;
		std::cin >> respassword;
		std::cout << "Password set" << std::endl;

		switch (perf.getHall().hall_num) {
		case Hall_Number::hall1:WriteRes("hall1.txt"); break;
		case Hall_Number::hall2:WriteRes("hall2.txt"); break;
		case Hall_Number::hall3:WriteRes("hall3.txt"); break;
		default: std::cout << "Error!" << std::endl;
		}
	}
}
void Reservation::CancelRes() {
	std::cout << "Cancelling reservation" << std::endl;
	std::cout << "Enter your reservation password!" << std::endl;
	unsigned checkpass;
	std::cin >> checkpass;
	if (checkpass == respassword) {
		perf.setSeat(seats_row, seats_col, 'F');  //free
		std::cout << "Reservation canceled" <<std::endl;
	}
	else {
		std::cout << "Password does not match " << std::endl;
	}

}
void Reservation::BuyTickets(std::vector<Perf>& perf_list) {
	std::cout << "Buy Tickets" << std::endl;
	std::cout << "Choose a performance" << std::endl;
	int perfchoice;
	for (unsigned l = 0; l < perf_list.size(); l++) {
		std::cout << perf_list[l].getName() << std::endl;
	}
	std::cin >> perfchoice;
	std::cout << "Please choose a row and a seat" << std::endl;
	unsigned row, col;
	std::cin >> row >> col;
	if (perf_list[perfchoice - 1].getHall().seats[row][col] == 'B') { //bought
		std::cout << "Seat already bought" << std::endl;
	}
	else if (perf_list[perfchoice - 1].getHall().seats[row][col] == 'R') { //res
		std::cout << "Please enter your password " << std::endl;
		unsigned checkpass;
		std::cin >> checkpass;
		if (checkpass == respassword) {
			perf_list[perfchoice - 1].setSeat(row, col, 'B');  //bought
			std::cout << "Your reserved seat is succesfully bought" << std::endl;
		}
		else {
			std::cout << "Password does not match " << std::endl;
		}
	}
	else { //free
		perf_list[perfchoice - 1].setSeat(row, col, 'B'); //bought
		std::cout << "Seat successfully bought!" << std::endl;
	}
}