#pragma once
#include "Perf.h"

class Reservation
{
private:
	unsigned respassword;
	unsigned seats_row, seats_col;
	Perf perf;
public:
	Reservation();
	Reservation(unsigned respassword, unsigned seats_row, unsigned seats_col);
	Reservation(const Reservation& reserve);
	Reservation& operator=(const Reservation& reserve);
	~Reservation();
	void WriteRes(const std::string& filename);
	void TicketRes(std::vector<Perf>&perf_list);
	void CancelRes();
	void BuyTickets(std::vector<Perf>& perf_list);
};

