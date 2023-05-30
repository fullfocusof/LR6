#pragma once
#include "Property.h"

class CountryHouse: public Property
{
	unsigned int distanceFromCity;

public:

	CountryHouse(unsigned int worth, unsigned int distanceFromCity);
	CountryHouse();

	int propertyTax() override;

	void printProp() override;

	void fromJson(json json) override;
	json toJson() override;
};