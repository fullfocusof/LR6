#pragma once
#include "Appartment.h"
#include "Car.h"
#include "CountryHouse.h"

class PropertyFactoryMethod
{
public:
	static Property* getProperty(string key);
};