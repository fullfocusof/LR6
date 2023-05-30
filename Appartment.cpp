#include "Appartment.h"

Appartment::Appartment(unsigned int worth, double square): Property(worth)
{
	this->square = square;
}

Appartment::Appartment()
{
	this->square;
}

int Appartment::propertyTax()
{
	if (square <= LIMIT_APPARTMENT_SQUARE)
	{
		return this->getWorth() * APPARTMENT_TAX;
	}
	else
	{
		return this->getWorth() * APPARTMENT_LUXURY_TAX;
	}
}

void Appartment::printProp()
{
	cout << "- вартира (стоимость - " << this->getWorth() << ", площадь - " << this->square << ")" << endl;
}

void Appartment::fromJson(json json)
{
	this->square = json.at("square");
	this->setWorth(json.at("worth"));
}

json Appartment::toJson()
{
	return
	{

	};
}
