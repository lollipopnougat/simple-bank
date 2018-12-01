//accumulator.h
#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H
#include "date.h"

class Accumulator
{
public:
	Accumulator(const Date &date, double value): lastDate(date), value(value), sum(0) {}
	~Accumulator() {}
	double getSum(const Date &date) const {return sum + value * (date - lastDate);}
	void change(const Date &date, double value);
	void reset(const Date &date, double value);
private:
	Date lastDate;
	double value;
	double sum;
};
#endif
