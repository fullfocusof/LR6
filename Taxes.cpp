#include "Property.h"
#include "Appartment.h"
#include "Car.h"
#include "CountryHouse.h"
#include "Owner.h"

int main()
{
	SetConsoleTitle(L"Налоги");
	ConsoleCursorVisible(false, 100);
	setlocale(LC_ALL, "ru");

	vector <Owner> mainVec;

	ifstream fin("Owners.json");
	if (!fin) throw exception("error");

	json j;
	j = json::parse(fin);

	mainVec.resize(j.size());

	for (int i = 0; i < mainVec.size(); i++)
	{
		Owner().fromJson(j);
	}

	vector<string> menu = { "Добавить собственника", "Удалить собственника", "Добавить имущество", "Удалить имущество", "Просмотр собственников", "Подсчет налогов", "Подсчет налогов (общий)", "Выход" };
	int active_menu = 0;
	bool exitMenu = false;
	int keyInputMenu;

	vector<string> propmenu = { "Квартира", "Машина", "Загородный дом" };
	int active_propmenu = 0;
	bool exitPropmenu = false;
	int keyInputPropmenu;

	bool exitProg = false;

	while (!exitProg)
	{
		int num = PrintMenu(menu, active_menu, keyInputMenu, exitMenu);

		switch (num)
		{
		case 0:
		{
			system("cls");

			cout << "Введите ФИО нового собственника" << endl;
			string name;
			getline(cin, name);

			cout << endl << "Введите ИНН" << endl;
			string INN;
			cin >> INN;

			cout << endl << "Данные успешно добавлены";

			Owner temp(name, INN);

			mainVec.push_back(temp);

			PrintQuit();

		}
		break;

		case 1:
		{
			system("cls");

			for (int i = 0; i < mainVec.size(); i++)
			{
				mainVec[i].getOwnerData();
			}

			cout << "Введите номер собственника, которого вы хотите удалить" << endl;
			int num;
			cin >> num;

			mainVec.erase(mainVec.begin() + num - 1);

			cout << endl << "Данные успешно удалены";

			PrintQuit();

		}
		break;

		case 2:
		{
			system("cls");

			for (int i = 0; i < mainVec.size(); i++)
			{
				mainVec[i].getOwnerData();
			}

			cout << "Введите номер собственника, которому вы хотите добавить имущество" << endl;
			int num;
			cin >> num;

			system("cls");

			mainVec[num - 1].getOwnerData();

			cout << "Выберите имущество" << endl;

			switch (PrintMenu(propmenu, active_propmenu, keyInputPropmenu, exitPropmenu))
			{
				case 0:
				{
					system("cls");

					cout << "Введите площадь квартиры" << endl;
					double square;
					cin >> square;

					cout << "Введите стоимость квартиры" << endl;
					unsigned int worthAppart;
					cin >> worthAppart;

					Appartment kv(worthAppart, square);

					mainVec[num - 1].addProperty(&kv);

					cout << endl << "Данные успешно добавлены";

					PrintQuit();
				}
				break;

				case 1:
				{
					system("cls");

					cout << "Введите мощность машины" << endl;
					double hp;
					cin >> hp;

					cout << "Введите стоимость машины" << endl;
					unsigned int worthCar;
					cin >> worthCar;

					Car car(worthCar, hp);

					mainVec[num - 1].addProperty(&car);

					cout << endl << "Данные успешно добавлены";

					PrintQuit();
				}
				break;

				case 2:
				{
					system("cls");

					cout << "Введите удаленность загородного дома от города" << endl;
					unsigned int distance;
					cin >> distance;

					cout << "Введите стоимость загородного дома" << endl;
					unsigned int worthCntryHouse;
					cin >> worthCntryHouse;

					CountryHouse CH(worthCntryHouse, distance);

					mainVec[num - 1].addProperty(&CH);

					cout << endl << "Данные успешно добавлены";

					PrintQuit();
				}
				break;
			}
		}
		break;

		case 3:
		{
			system("cls");

			for (int i = 0; i < mainVec.size(); i++)
			{
				mainVec[i].getOwnerData();
			}

			cout << "Введите номер собственника, у которого вы хотите удалить имущество" << endl;
			int num;
			cin >> num;

			system("cls");

			mainVec[num - 1].getOwnerData();

			cout << "Введите номер имущества, которое хотите удалить" << endl;
			int numProp;
			cin >> numProp;

			mainVec[num - 1].delProperty(numProp);

			cout << endl << "Данные успешно удалены";

			PrintQuit();

		}
		break;

		case 4:
		{
			system("cls");

			for (int i = 0; i < mainVec.size(); i++)
			{
				mainVec[i].getOwnerData();
			}

			PrintQuit();
		}
		break;

		case 5:
		{
			system("cls");

			for (int i = 0; i < mainVec.size(); i++)
			{
				mainVec[i].getOwnerData();
			}

			cout << "Введите номер собственника, у которого нужно подсчитать налоги" << endl;
			int numOwner;
			cin >> numOwner;

			system("cls");

			mainVec[numOwner - 1].getOwnerData();

			cout << "Выберите имущество, на которое нужно подсчитать налог" << endl;
			int numTax;
			cin >> numTax;


			cout << "Налог на имущество" << endl;
			mainVec[numOwner - 1].getProp()[numTax - 1]->printProp();
			cout << "составляет " << mainVec[numOwner - 1].getProp()[numTax - 1]->propertyTax();

			PrintQuit();
		}
		break;
		
		case 6:
		{
			system("cls");

			for (int i = 0; i < mainVec.size(); i++)
			{
				mainVec[i].getOwnerData();
			}

			cout << "Введите номер собственника, у которого нужно подсчитать налоги" << endl;
			int numOwner;
			cin >> numOwner;

			system("cls");

			mainVec[numOwner - 1].getOwnerData();

			cout << "Общий налог составляет " << mainVec[numOwner - 1].sumWorth();

			PrintQuit();
		}
		break;

		case 7:
		{
			exit(0);
		}
		break;

		}
	}
}