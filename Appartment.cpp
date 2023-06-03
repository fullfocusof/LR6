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
	this->square = xmlApp.attribute("square").as_double();
	this->setWorth(xmlApp.attribute("worth").as_uint());
}

xml_document Appartment::toXML()
{
	xml_document doc;

	xml_node AppNode = doc.append_child("Appartment");
	AppNode.append_attribute("tax").set_value(this->propertyTax());

	return doc;
}