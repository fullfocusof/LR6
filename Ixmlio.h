#pragma once
#include <pugixml.hpp>

using namespace pugi;

class Ixmlio
{
public:
	virtual void fromXML(xml_node xmldoc) = 0;
	virtual xml_document toXML() = 0;
	virtual ~Ixmlio() {};
};