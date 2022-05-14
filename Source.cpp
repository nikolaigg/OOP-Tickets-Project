#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
using namespace std;
const unsigned MAX_SEATS_IN_ZALA = 100;
enum nomer {
	zala1, zala2, zala3
};
struct Zala {
	nomer zala;
	bool svobodnadata[30][12];
	char seats[10][10];
	
	
}; 

class Perf {
private:
	string perfname;
	int den, mesec;
	Zala zala;
	fstream PerformanceFile;

public:
	
	
	Perf() {
		
	}
	Perf(string perfname, int den, int mesec, Zala zala) {
		this->perfname = perfname;
		this->den = den;
		this->mesec = mesec;
		this->zala = zala;
	
	}
	Perf(const Perf& perf) {
		perfname = perf.perfname;
		den= perf.den;
		mesec= perf.mesec;
		zala = perf.zala;
	}
	Perf& operator=(const Perf& perf) {
		if (this != &perf)
		{
			this->perfname = perf.perfname;
			this->den = perf.den;
			this->mesec = perf.mesec;
			this->zala = perf.zala;
		}
		return *this;
	}
	~Perf() {

	}
	
	void Write(string filename) {
		PerformanceFile.open(filename,  ios::app);
		if (PerformanceFile.is_open()) {
			PerformanceFile << "Perf name: " << perfname << " Perf date: " << den << " / " << mesec<< endl;
			PerformanceFile.close();
		}
		else {
			cout << "error file is not open" << endl;
		}
	}
	void setPerf(vector<Zala>& spisakzali) {
		cout << "Set Perf" << endl;
		cout << " enter name" << endl;
		cin >> perfname;
		cout << "now choose zala 1-3" << endl;
		int choice;
		cin >> choice;
		switch (choice) {
		case 1:
			for (int k = 0; k < spisakzali.size() - 1; k++) {
				if (spisakzali[k].zala == nomer::zala1) {
					setDate(spisakzali[k]);
					Write("zala1.txt");
					break;
				}
			}
			break;
		case 2:
			for (int k = 0; k < spisakzali.size() - 1; k++) {
				if (spisakzali[k].zala == nomer::zala2) {
					setDate(spisakzali[k]);
					Write("zala2.txt");
					break;
				}
			}
			break;
		case 3:
			for (int k = 0; k < spisakzali.size() - 1; k++) {
				if (spisakzali[k].zala == nomer::zala3) {
					setDate(spisakzali[k]);
					Write("zala3.txt");
					break;
				}
			}
			break;
		default: cout << "error" << endl;
		}
	}
	void setDate(Zala& z) {
		cout << "enter day and month" << endl;
		cin >> den >> mesec; //if
		if (z.svobodnadata[den][mesec] == true) {
			cout << "zaeta data" << endl;
		}
		else {
			z.svobodnadata[den][mesec] = true;
			cout << "uspeshno zapazena data" << endl;
			zala = z;
		}
	}

	
	Zala getZala() {
		return zala;
	}
	string getName() {
		return perfname;
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
	Reservation& operator=(const Reservation& event) {

	}
	~Reservation() {

	}
	void WriteRes(string filename) {
		PerformanceFile.open(filename, ios::app);
		if (PerformanceFile.is_open()) {
			PerformanceFile << "Res Mesta: " << seats_row << " / " << seats_col << endl;
			PerformanceFile.close();
		}
		else {
			cout << "error file is not open" << endl;
		}
	}
	void TicketRes(vector<Perf>& spisakperf) { 
		cout << "Ticket res" << endl;
		cout << "choose perf " << endl;
		int perfchoice;
		for (int l = 0; l < spisakperf.size(); l++) {
			cout << spisakperf[l].getName() << endl;
		}
		cin >> perfchoice;
		cout << "Please choose a row and a seat" << endl;
		unsigned row, col;
		cin >> row >> col;
		if (spisakperf[perfchoice-1].getZala().seats[row][col] == 'R') { //res
			cout << "zaeto mqsto" << endl;
		}
		else {
			spisakperf[perfchoice - 1].getZala().seats[row][col] = 'R'; //res
			cout << "perf reserv choice zala seats: " << spisakperf[perfchoice - 1].getZala().seats[row][col] << endl;
			cout << "uspeshno zapazeno mqsto" << endl;
			seats_row = row;
			seats_col = col;
			perf = spisakperf[perfchoice - 1];

			cout << "set password for your res " << endl;
			cin >> respassword;
			cout << "pass set" << endl;

			switch (perf.getZala().zala) {
			case nomer::zala1:WriteRes("zala1.txt"); break;
			case nomer::zala2:WriteRes("zala2.txt"); break;
			case nomer::zala3:WriteRes("zala3.txt"); break;
			default: cout << "error" << endl;
			}
		}
	}
	void CancelRes() {

		cout << "enter your res password " << endl;
		unsigned checkpass;
		cin >> checkpass;
		if (checkpass == respassword) {
			perf.getZala().seats[seats_row][seats_col] = 'F';  //free
			cout << "res canceled " << endl;
		}
		else {
			cout << "password does not match " << endl;
		}

	}	

	void BuyTickets(vector<Perf>& spisakperf) {
		cout << "choose perf " << endl;
		int perfchoice;
		for (int l = 0; l < spisakperf.size(); l++) {
			cout << spisakperf[l].getName() << endl;
		}
		cin >> perfchoice;
		cout << "Please choose a row and a seat" << endl;
		unsigned row, col;
		cin >> row >> col;
		cout << "perf buy choice zala seats: " << spisakperf[perfchoice - 1].getZala().seats[row][col] << endl;
		if (spisakperf[perfchoice-1].getZala().seats[row][col] == 'B') { //bought
			cout << "zaeto mqsto" << endl;
			
		}
		else if (spisakperf[perfchoice-1].getZala().seats[row][col] == 'R') { //res
			cout << "please enter your password " << endl;
			unsigned checkpass;
			cin >> checkpass;
			if (checkpass == respassword) {
				spisakperf[perfchoice-1].getZala().seats[seats_row][seats_col] = 'B';  //bought
			cout << "res mqsto -> kupeno mqsto " << endl;
			}
			else {
				cout << "password does not match " << endl;
			}
		}
		else  { //free
			spisakperf[perfchoice-1].getZala().seats[row][col] = 'B'; //bought
			cout << "uspeshno zakupeno mqsto" << endl;
		}
	}
};

void Checkseats(vector<Perf> spisakperf) {
	cout << "choose perf " << endl;
	int perfchoice;
	for (int l = 0; l < spisakperf.size() - 1; l++) {
		cout << spisakperf[l].getName() << endl;
	}
	cin >> perfchoice;
	Perf izbranperf = spisakperf[perfchoice];
	int rescounter = 0;
	for (unsigned i = 0; i < sizeof(izbranperf.getZala().seats) - 1; i++) {
		for (unsigned j = 0; j < sizeof(izbranperf.getZala().seats[i]) - 1; j++)
			if (izbranperf.getZala().seats[i][j] == 'R' || izbranperf.getZala().seats[i][j] == 'B') { //res || bought
				rescounter++;
			}
		cout << "nonres are " << MAX_SEATS_IN_ZALA - rescounter << endl;
	}
}
void ClearFile(string filename) {
	fstream PerformanceFile;
	PerformanceFile.open(filename, ios::out | ios::trunc);
}

int main() {
	
	// 0) clear file
	ClearFile("zala1.txt");
	ClearFile("zala2.txt");
	ClearFile("zala3.txt");

	// 1) create zala
	Zala z1, z2, z3;
	z1.zala = nomer::zala1;
	z2.zala = nomer::zala2;
	z3.zala = nomer::zala3;

	// 2) create perf
	vector<Zala> spisakzali;
	spisakzali.push_back(z1);
	spisakzali.push_back(z2);
	spisakzali.push_back(z3);
	Perf perf1, perf2;
	
	perf1.setPerf(spisakzali);
	//perf2.setPerf(spisakzali);
	
	// 3) create reservation
	vector<Perf> spisakperf;
	spisakperf.push_back(perf1);
	//spisakperf.push_back(perf2);
	Reservation reserv1, reserv2;
	reserv1.TicketRes(spisakperf);
	//reserv2.TicketRes(spisakperf);

	// 4) cancel reservation
	//reserv1.CancelRes();

	// 5) buy tickets
	reserv1.BuyTickets(spisakperf);
	//reserv2.BuyTickets(spisakperf);
	return 0;
}
