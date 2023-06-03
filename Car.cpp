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
	cout << "-������ (��������� - " << this->getWorth() << ", �������� - " << this->horsepower << ")" << endl;
}

void Car::fromJson(json json)
{
	nlohmann::json j = json["Car"].get<nlohmann::json>();
	this->horsepower = j["horsepower"].get<int>();
	this->setWorth(j["worth"].get<int>());
}

json Car::toJson()
{
	int tax = this->propertyTax();

	nlohmann::json j =
	{
		{"Car", {{"tax", tax}}}
	};

	return j;
}

void Car::fromXML(xml_node xmlCar)
{
	this->horsepower = xmlCar.attribute("horsepower").as_double();
	this->setWorth(xmlCar.attribute("worth").as_uint());
}

xml_document Car::toXML()
{
	xml_document doc;

	xml_node AppNode = doc.append_child("Car");
	AppNode.append_attribute("tax").set_value(this->propertyTax());

	return doc;
}
