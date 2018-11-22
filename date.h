//date.h
#ifndef DATE_H
#define DATE_H

class Date
{
public:
	Date(int year, int month, int day);
	~Date() {}
	int getYear() const {return year;}
	int getMonth() const {return month;}
	int getDay() const {return day;}
	int getMaxDay() const ;
	bool isLeapYear() const {return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;}
	void show() const;
	int distance(const Date &date) const {return totalDays - date.totalDays;}
private:
	int year;
	int month;
	int day;
	int totalDays;
};

#endif
