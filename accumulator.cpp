#include "accumulator.h"

void Accumulator::change(const Date &date, double value)
{
	sum = getSum(date);
	lastDate = date;
	this->value = value;
}
void Accumulator::reset(const Date &date, double value)
{
	lastDate = date;
	this->value = value;
	sum = 0;
}