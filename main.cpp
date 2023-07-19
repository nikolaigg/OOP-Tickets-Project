#include "Reservation.h"
using namespace std;
const unsigned MAX_SEATS_IN_HALLS = 100;

void Checkseats(vector<Perf>& perf_list) {
	cout << "Check seats" << endl;
	cout << "Choose a performance" << endl;
	int perfchoice;
	for (unsigned l = 0; l < perf_list.size(); l++) {
		cout << perf_list[l].getName() << endl;
	}
	cin >> perfchoice;
	Perf& chosen_perf = perf_list[perfchoice];
	int rescounter = 0;
	for (unsigned i = 0; i < sizeof(chosen_perf.getHall().seats) - 1; i++) {
		for (unsigned j = 0; j < sizeof(chosen_perf.getHall().seats[i]) - 1; j++)
			if (chosen_perf.getHall().seats[i][j] == 'R' || chosen_perf.getHall().seats[i][j] == 'B') { //res || bought
				rescounter++;
			}
		
	} cout << "Nonreserved seats: " << MAX_SEATS_IN_HALLS - rescounter << endl;
}
void ClearFile(string filename) {
	fstream PerformanceFile;
	PerformanceFile.open(filename, ios::out | ios::trunc);
}

int main() {
	
	// 0) clear file
	ClearFile("hall1.txt");
	ClearFile("hall2.txt");
	ClearFile("hall3.txt");

	// 1) create hall
	Hall z1, z2, z3;
	z1.hall_num = Hall_Number::hall1;
	z2.hall_num = Hall_Number::hall2;
	z3.hall_num = Hall_Number::hall3;

	// 2) create perf
	vector<Hall> hall_list;
	hall_list.push_back(z1);
	hall_list.push_back(z2);
	hall_list.push_back(z3);
	Perf perf1, perf2;
	
	perf1.setPerf(hall_list);//
	perf2.setPerf(hall_list);//
	
	// 3) create reservation
	vector<Perf> perf_list;
	perf_list.push_back(perf1);
	perf_list.push_back(perf2);
	Reservation reserv1, reserv2;
	reserv1.TicketRes(perf_list);
	reserv2.TicketRes(perf_list);


	// 4) cancel reservation
	reserv1.CancelRes();

	// 5) buy tickets
	reserv1.BuyTickets(perf_list);
	reserv2.BuyTickets(perf_list);

	//6) check seats
	Checkseats(perf_list);
	return 0;
}
