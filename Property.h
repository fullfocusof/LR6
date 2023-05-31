#pragma once
#include "Ijsonio.h"
#include "Ixmlio.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include <Windows.h>
#include <conio.h>

namespace TAX_RATES
{
	const double CAR_TAX = 0.0007;
	const double CAR_TRUCK_TAX = 0.007;
	const double CAR_LUXURY_TAX = 0.027;
	const double LOW_HORSEPOWER = 100;
	const double HIGH_HORSEPOWER = 200;

	const double APPARTMENT_TAX = 0.001;
	const double APPARTMENT_LUXURY_TAX = 0.004;
	const int LIMIT_APPARTMENT_SQUARE = 100;

	const double COUNTRY_HOUSE_TAX = 0.01;
	const unsigned int LIMIT_DISTANCE_FROM_CITY = 30;

}

using namespace TAX_RATES;
using namespace std;

class Property : public Ijsonio, public Ixmlio
{
	unsigned int worth;

public:

	Property(unsigned int worth);
	Property();

	unsigned int getWorth();
	void setWorth(unsigned int value);

	virtual int propertyTax() = 0;
	virtual void printProp() = 0;


	int incomeTax();
};