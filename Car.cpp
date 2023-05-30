#include "Car.h"

Car::Car(unsigned int worth, double horsepower): Property(worth)
{
	this->horsepower = horsepower;
}

Car::Car()
{
	this->horsepower = 0;
}

int Car::propertyTax()
{
	if (this->horsepower < LOW_HORSEPOWER)
	{
		return this->getWorth() * CAR_TAX;
	}
	else
	{
		if (this->horsepower > HIGH_HORSEPOWER)
		{
			return this->getWorth() * CAR_LUXURY_TAX;
		}
		else
		{
			return this->getWorth() * CAR_TRUCK_TAX;
		}
	}
}

void Car::printProp()
{
	cout << "-Машина (стоимость - " << this->getWorth() << ", мощность - " << this->horsepower << ")" << endl;
}

void Car::fromJson(json json)
{
	this->horsepower = json.at("horsepower");
	this->setWorth(json.at("worth"));
}

json Car::toJson()
{
	return
	{

	};
}
