#pragma once
#include "Property.h"

class Appartment: public Property
{
	double square;

public:

	Appartment(unsigned int worth, double square);
	Appartment();

	int propertyTax() override;

	void printProp() override;

	void fromJson(json json) override;
	json toJson() override;
};