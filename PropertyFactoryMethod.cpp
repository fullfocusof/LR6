#include "PropertyFactoryMethod.h"

Property* PropertyFactoryMethod::getProperty(string key)
{
	Property* prop = nullptr;

	if (key == "Appartment")
	{
		prop = new Appartment;
	}
	else if (key == "Car")
	{
		prop = new Car;
	}
	else if (key == "CountryHouse")
	{
		prop = new CountryHouse;
	}

	return prop;
}
