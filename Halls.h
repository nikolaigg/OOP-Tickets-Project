#pragma once
enum Hall_Number {
	hall1, hall2, hall3
};
struct Hall {
	Hall_Number hall_num;
	bool hallday, hallmonth;
	char seats[10][10];
};