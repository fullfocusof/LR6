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
	cout << "-���������� ��� (��������� - " << this->getWorth() << ", ����������� �� ������ - " << this->distanceFromCity << ")" << endl;
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

void CountryHouse::fromXML(xml_node xmlCH)
{
	this->distanceFromCity = xmlCH.attribute("distanceFromCity").as_uint();
	this->setWorth(xmlCH.attribute("worth").as_uint());
}

xml_document CountryHouse::toXML()
{
	xml_document doc;

	xml_node AppNode = doc.append_child("CountryHouse");
	AppNode.append_attribute("tax").set_value(this->propertyTax());

	return doc;
}
