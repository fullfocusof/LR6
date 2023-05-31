#pragma once
#include "Property.h"

class Car: public Property
{
	double horsepower;

public:

	Car(unsigned int worth, double horsepower);
	Car();

	int propertyTax() override;

	void printProp() override;

	void fromJson(json json) override;
	json toJson() override;

	void fromXML(xml_node xmlCar) override;
	xml_document toXML() override;
};