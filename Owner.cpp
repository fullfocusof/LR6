#include "Owner.h"

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

Owner::Owner(string fullname, string INN)
{
	this->fullname = fullname;
	this->INN = INN;
}

Owner::Owner()
{
	this->fullname = "";
	this->INN = "";
}

void Owner::getOwnerData()
{
	cout << this->fullname << endl 
		<< "ИНН - " << this->INN << endl;

	for (int i = 0; i < this->properties.size(); i++)
	{
		this->properties[i]->printProp();
	}

	cout << endl;
}

int Owner::getCntProp()
{
	return this->properties.size();
}

vector<Property*> Owner::getProp()
{
	return this->properties;
}

void Owner::addProperty(Property* prop)
{
	this->properties.push_back(prop);
}

void Owner::delProperty(int id)
{
	this->properties.erase(this->properties.begin() + id - 1);
}

unsigned int Owner::sumWorth()
{
	unsigned int sum = 0;

	for (int i = 0; i < this->properties.size(); i++)
	{
		sum += this->properties[i]->getWorth();
	}

	return sum;
}

void Owner::fromJson(json json)
{
	fullname = json["fullname"].get<std::string>();
	this->INN = json["inn"].get<std::string>();

	auto json_props = json["properties"].get<vector<nlohmann::json>>();
	for (auto& json_prop : json_props)
	{
		string key = json_prop.items().begin().key();
		Property* propobj = PropertyFactoryMethod::getProperty(key);
		propobj->fromJson(json_prop);
		this->addProperty(propobj);
	}
}

json Owner::toJson()
{
	int sumtax = 0;

	for (int i = 0; i < properties.size(); i++)
	{
		sumtax += properties[i]->propertyTax();
	}

	nlohmann::json j =
	{
		{"fullname" , this->fullname},
		{"inn", this->INN},
		{"sumtax", sumtax},
		{"taxs", json::array()}
	};

	for (int i = 0; i < properties.size(); i++)
	{
		j["taxs"].push_back(this->properties[i]->toJson());
	}

	return j;
}

void Owner::fromXML(xml_node xmlOwner)
{
	this->fullname = xmlOwner.attribute("fullname").as_string();
	this->INN = xmlOwner.attribute("inn").as_string();

	xml_node propertiesNode = xmlOwner.child("properties");
	for (xml_node propertyNode = propertiesNode.first_child(); propertyNode; propertyNode = propertyNode.next_sibling())
	{
		string key = propertyNode.name();
		Property* propobj = PropertyFactoryMethod::getProperty(key);
		propobj->fromXML(propertyNode);
		this->addProperty(propobj);
	}
}

xml_document Owner::toXML()
{
	xml_document doc;

	xml_node OwnerNode = doc.append_child("Owner");
	OwnerNode.append_attribute("fullname").set_value(this->fullname.c_str());
	OwnerNode.append_attribute("inn").set_value(this->INN.c_str());

	xml_node TaxsNode = OwnerNode.append_child("Taxs");
	for (int i = 0; i < this->properties.size(); i++)
	{
		xml_document propDoc = this->properties[i]->toXML();
		TaxsNode.append_copy(propDoc.first_child());
	}

	return doc;
}

Owner::~Owner()
{

}

void GoToXY(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}

void ConsoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show;
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

int PrintMenu(vector<string> &vecMenu, int &active_menu_point, int &key, bool &exitVar)
{
	while (!exitVar)
	{
		int x = 50, y = 12;
		GoToXY(x, y);

		for (int i = 0; i < vecMenu.size(); i++)
		{
			if (i == active_menu_point)
			{
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			else
			{
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			}
			GoToXY(x, y++);
			cout << vecMenu[i] << endl;
		}

		key = _getch();
		switch (key)
		{
		case KEY_ESC:
		{
			exit(0);
		}
		case KEY_UP:
		{
			if (active_menu_point > 0)
			{
				active_menu_point--;
			}
		}
		break;

		case KEY_DOWN:
		{
			if (active_menu_point < vecMenu.size() - 1)
			{
				active_menu_point++;
			}
		}
		break;

		case KEY_ENTER:
		{
			return active_menu_point;
			exitVar = true;
		}
		break;
		}
	}
}

bool PrintQuit()
{
	cout << endl << endl << "Backspace - возврат в меню";

	int answ = _getch();
	bool press = false;

	while (!press)
	{
		if (answ == 8)
		{
			system("cls");
			press = true;
			return press;
		}
		else
		{
			answ = _getch();
		}
	}
}