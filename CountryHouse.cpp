#include "CountryHouse.h"

CountryHouse::CountryHouse(unsigned int worth, unsigned int distanceFromCity): Property(worth)
{
	this->distanceFromCity = distanceFromCity;
}

CountryHouse::CountryHouse()
{
	this->distanceFromCity = 0;
}

int CountryHouse::propertyTax()
{
	if (this->distanceFromCity <= LIMIT_DISTANCE_FROM_CITY)
	{
		return this->getWorth() * APPARTMENT_TAX;
	}
	else
	{
		return this->getWorth() * COUNTRY_HOUSE_TAX;
	}
}

void CountryHouse::printProp()
{
	cout << "-«агородный дом (стоимость - " << this->getWorth() << ", удаленность от города - " << this->distanceFromCity << ")" << endl;
}

void CountryHouse::fromJson(json json)
{
	this->distanceFromCity = json.at("distanceFromCity");
	this->setWorth(json.at("worth"));
}

json CountryHouse::toJson()
{
	return
	{

	};
}
