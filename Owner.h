#pragma once
#include "PropertyFactoryMethod.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_BACKSPACE 8

class Owner : public Ijsonio
{
	string fullname;
	string INN;
	vector<Property*> properties;

public:

	Owner(string fullname, string INN);
	Owner();
	void getOwnerData();
	int getCntProp();
	vector<Property*> getProp();

	void addProperty(Property* prop);
	void delProperty(int id);

	unsigned int sumWorth();

	void fromJson(json json) override;
	json toJson() override;

	~Owner();
};

void GoToXY(short x, short y);
void ConsoleCursorVisible(bool show, short size);

int PrintMenu(vector<string>& vecMenu, int& active_menu_point, int& key, bool &exitVar);
bool PrintQuit();