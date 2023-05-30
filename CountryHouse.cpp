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
	nlohmann::json j = json["CountryHouse"].get<nlohmann::json>();
	this->distanceFromCity = j["distanceFromCity"].get<int>();
	this->setWorth(j["worth"].get<int>());
}

json CountryHouse::toJson()
{
	int tax = this->propertyTax();

	nlohmann::json j =
	{
		{"CountryHouse", {{"tax", tax}}}
	};

	return j;
}
