#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
using namespace std;
const unsigned MAX_SEATS_IN_HALLS = 100;
enum number {
	hall1, hall2, hall3
};
struct Hall {
	number hall_num;
	bool date[30][12];
	char seats[10][10];
}; 

class Perf {
private:
	string performance_name;
	int day, month;
	Hall hall;
	fstream PerformanceFile;
public:
	Perf() {

	}
	Perf(string performance_name, int day, int month, Hall hall) {
		this->performance_name = performance_name;
		this->day = day;
		this->month = month;
		this->hall = hall;
	
	}
	Perf(const Perf& perf) {
		performance_name = perf.performance_name;
		day = perf.day;
		month = perf.month;
		hall = perf.hall;
	}
	Perf& operator=(const Perf& perf) {
		if (this != &perf)
		{
			this->performance_name = perf.performance_name;
			this->day = perf.day;
			this->month = perf.month;
			this->hall = perf.hall;
		}
		return *this;
	}
	~Perf() {

	}
	
	void Write(string filename) {
		PerformanceFile.open(filename,  ios::app);
		if (PerformanceFile.is_open()) {
			PerformanceFile << "Performance name: " << performance_name << " Performance date: " << day << " / " << month << endl;
			PerformanceFile.close();
		}
		else {
			cout << "Error! File is not open!" << endl;
		}
	}
	void setPerf(vector<Hall>& hall_list) {
		cout << "Set Performance" << endl;
		cout << "Enter name for your performance!" << endl;
		cin >> performance_name;
		cout << "Now choose a hall (1-3)" << endl;
		int choice;
		cin >> choice;
		switch (choice) {
		case 1:
			for (unsigned k = 0; k < hall_list.size() - 1; k++) {
				if (hall_list[k].hall_num == number::hall1) {
					setDate(hall_list[k]);
					Write("hall1.txt");
					break;
				}
			}
			break;
		case 2:
			for (unsigned k = 0; k < hall_list.size() - 1; k++) {
				if (hall_list[k].hall_num == number::hall2) {
					setDate(hall_list[k]);
					Write("hall2.txt");
					break;
				}
			}
			break;
		case 3:
			for (unsigned k = 0; k < hall_list.size() - 1; k++) {
				if (hall_list[k].hall_num == number::hall3) {
					setDate(hall_list[k]);
					Write("hall3.txt");
					break;
				}
			}
			break;
		default: cout << "Error!" << endl;
		}
	}
	void setDate(Hall& h) {
		cout << "Enter a day and a month for your performance" << endl;
		cin >> day >> month; 
		if (day < 1 || day > 30 || month < 1 || month >12) {
			cout << "Error! Invalid input for day or month!" << endl;
		}
		else {
			if (h.date[day][month] == true) {
				cout << "Date is already reserved!" << endl;
			}
			else {
				h.date[day][month] = true;
				cout << "Successfully reserved date!" << endl;
				hall = h;
			}
		}
		
	}

	
	Hall getHall() {
		return hall;
	}
	string getName() {
		return performance_name;
	}
};
class Reservation {
private:
	unsigned respassword;
	unsigned seats_row, seats_col;
	Perf perf;
	fstream PerformanceFile;
public:
	Reservation() {
		
	}
	Reservation(unsigned respassword, unsigned seats_row, unsigned seats_col) {
		this->respassword = respassword;
		this->seats_row = seats_row;
		this->seats_col = seats_col;
	}
	Reservation(const Reservation& reserve) {
		respassword = reserve.respassword;
		seats_row = reserve.seats_row;
		seats_col = reserve.seats_col;
	}
	Reservation& operator=(const Reservation& reserve) {
		if (this != &reserve)
		{
			this->respassword = reserve.respassword;
			this->seats_row = reserve.seats_row;
			this->seats_col = reserve.seats_col;
			this->perf = reserve.perf;
		}
		return *this;
	}
	~Reservation() {

	}
	void WriteRes(string filename) {
		PerformanceFile.open(filename, ios::app);
		if (PerformanceFile.is_open()) {
			PerformanceFile << "Reserved seats: " << seats_row << " / " << seats_col << endl;
			PerformanceFile.close();
		}
		else {
			cout << "Error! File is not open!" << endl;
		}
	}
	void TicketRes(vector<Perf>& perf_list) {
		cout << "Ticket res" << endl;
		cout << "Choose a performance!" << endl;
		int perfchoice;
		for (unsigned l = 0; l < perf_list.size(); l++) {
			cout << perf_list[l].getName() << endl;
		}
		cin >> perfchoice;
		cout << "Please choose a row and a seat" << endl;
		unsigned row, col;
		cin >> row >> col;
		if (perf_list[perfchoice-1].getHall().seats[row][col] == 'R') { //res
			cout << "Seat is already reserved!" << endl;
		}
		else {
			perf_list[perfchoice - 1].getHall().seats[row][col] = 'R'; //res
			cout << "Successfully reserved seat!" << endl;
			seats_row = row;
			seats_col = col;
			perf = perf_list[perfchoice - 1];

			cout << "Now set a password for your reservation!" << endl;
			cin >> respassword;
			cout << "Password set" << endl;

			switch (perf.getHall().hall_num) {
			case number::hall1:WriteRes("hall1.txt"); break;
			case number::hall2:WriteRes("hall2.txt"); break;
			case number::hall3:WriteRes("hall3.txt"); break;
			default: cout << "Error!" << endl;
			}
		}
	}
	void CancelRes() {
		cout << "Cancelling reservation" << endl;
		cout << "Enter your reservation password!" << endl;
		unsigned checkpass;
		cin >> checkpass;
		if (checkpass == respassword) {
			perf.getHall().seats[seats_row][seats_col] = 'F';  //free
			cout << "Reservation canceled" << endl;
		}
		else {
			cout << "Password does not match " << endl;
		}

	}	

	void BuyTickets(vector<Perf>& perf_list) {
		cout << "Choose a performance" << endl;
		int perfchoice;
		for (unsigned l = 0; l < perf_list.size(); l++) {
			cout << perf_list[l].getName() << endl;
		}
		cin >> perfchoice;
		cout << "Please choose a row and a seat" << endl;
		unsigned row, col;
		cin >> row >> col;
		if (perf_list[perfchoice-1].getHall().seats[row][col] == 'B') { //bought
			cout << "Seat already bought" << endl;
			
		}
		else if (perf_list[perfchoice-1].getHall().seats[row][col] == 'R') { //res
			cout << "Please enter your password " << endl;
			unsigned checkpass;
			cin >> checkpass;
			if (checkpass == respassword) {
				perf_list[perfchoice-1].getHall().seats[seats_row][seats_col] = 'B';  //bought
			cout << "Your reserved seat is succesfully bought" << endl;
			}
			else {
				cout << "Password does not match " << endl;
			}
		}
		else  { //free
			perf_list[perfchoice-1].getHall().seats[row][col] = 'B'; //bought
			cout << "Successfully bought seat" << endl;
		}
	}
};

void Checkseats(vector<Perf> perf_list) {
	cout << "Check seats" << endl;
	cout << "Choose a performance" << endl;
	int perfchoice;
	for (unsigned l = 0; l < perf_list.size() - 1; l++) {
		cout << perf_list[l].getName() << endl;
	}
	cin >> perfchoice;
	Perf chosen_perf = perf_list[perfchoice];
	int rescounter = 0;
	for (unsigned i = 0; i < sizeof(chosen_perf.getHall().seats) - 1; i++) {
		for (unsigned j = 0; j < sizeof(chosen_perf.getHall().seats[i]) - 1; j++)
			if (chosen_perf.getHall().seats[i][j] == 'R' || chosen_perf.getHall().seats[i][j] == 'B') { //res || bought
				rescounter++;
			}
		cout << "Nonreserved seats: " << MAX_SEATS_IN_HALLS - rescounter << endl;
	}
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
	z1.hall_num = number::hall1;
	z2.hall_num = number::hall2;
	z3.hall_num = number::hall3;

	// 2) create perf
	vector<Hall> hall_list;
	hall_list.push_back(z1);
	hall_list.push_back(z2);
	hall_list.push_back(z3);
	Perf perf1, perf2;
	
	perf1.setPerf(hall_list);
	perf2.setPerf(hall_list);
	
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
	return 0;
}
