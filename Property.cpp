#include "Property.h"

Property::Property(unsigned int worth)
{
	this->worth = worth;
}

Property::Property()
{
	this->worth = 0;
}

unsigned int Property::getWorth()
{
	return this->worth;
}

void Property::setWorth(unsigned int value)
{
	this->worth = value;
}

int Property::incomeTax()
{
	return (this->worth * (13 / 100));
}