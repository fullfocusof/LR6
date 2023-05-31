#include "Appartment.h"

Appartment::Appartment(unsigned int worth, double square): Property(worth)
{
	this->square = square;
}

Appartment::Appartment()
{
	this->square = 0;
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
	nlohmann::json j = json["Appartment"].get<nlohmann::json>();
	setWorth(j["worth"].get<int>());	
	square = j["square"].get<double>();
}

json Appartment::toJson()
{
	int tax = this->propertyTax();

	nlohmann::json j =
	{ 
		{"Appartment", {{"tax", tax}}  }
	};

	return j;
}

void Appartment::fromXML(xml_node xmlApp)
{
	this->square = xmlApp.child("Appartment").child("square").text().as_double();
	this->setWorth(xmlApp.child("Appartment").child("worth").text().as_int());
}

xml_document Appartment::toXML()
{
	return xml_document();
}
