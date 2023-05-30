#include "PropertyFactoryMethod.h"

Property* PropertyFactoryMethod::getProperty(string key)
{
	Property* prop = nullptr;

	if (key == "Appartment")
	{
		prop = new Appartment(0,0);
	}
	else if (key == "Car")
	{
		prop = new Car(0, 0);
	}
	else if (key == "CountryHouse")
	{
		prop = new CountryHouse(0, 0);
	}

	return prop;
}
