#include "Property.h"
#include "Appartment.h"
#include "Car.h"
#include "CountryHouse.h"
#include "Owner.h"

//int argc, char* argv[];

int main()
{
	SetConsoleTitle(L"Налоги");
	ConsoleCursorVisible(false, 100);
	setlocale(LC_ALL, "ru");

	vector <Owner> mainVec;

	system("cls");

	/*if (argc != 3) 
	{
		cerr << "неправильный ввод для " << argv[0] << endl << "правильное использование аргументов: "  << endl << argv[0] << " input_file output_file" << endl;
		return 1;
	}*/

	const char* input_filename = "OwnersJson.json";
	const char* output_filename = "OwnersWriteJson.json";

	string extensionInputFile = strrchr(input_filename, '.');
	if (!extensionInputFile.empty()) 
	{
		extensionInputFile = extensionInputFile.substr(1);
	}
	string extensionOutputFile = strrchr(output_filename, '.');
	if (!extensionOutputFile.empty()) 
	{
		extensionOutputFile = extensionOutputFile.substr(1);
	}

	ifstream ifs(input_filename);
	if (!ifs) throw exception("ErrorOpenFileInput");
	if (extensionInputFile == "xml")
	{
		xml_document docInput;
		xml_parse_result result = docInput.load_file(input_filename);
		if (!result) throw exception("ErrorParseXml");

		xml_node root = docInput.child("root");

		for (xml_node OwnerNode = root.child("Owner"); OwnerNode; OwnerNode = OwnerNode.next_sibling("Owner"))
		{
			Owner o;
			o.fromXML(OwnerNode);
			mainVec.push_back(o);
		}
	}
	else
	{
		json j;
		j = json::parse(ifs);

		for (auto elem : j)
		{
			Owner o;
			o.fromJson(elem);
			mainVec.push_back(o);
		}
	}
	ifs.close();


	ofstream ofs(output_filename);
	if (!ofs) throw exception("ErrorOpenFileOutput");
	if (extensionOutputFile == "xml")
	{
		xml_document docOutput;

		xml_node decl = docOutput.prepend_child(node_declaration);
		decl.append_attribute("version") = "1.0";
		decl.append_attribute("encoding") = "UTF-8";

		xml_node root = docOutput.append_child("root");

		for (int i = 0; i < mainVec.size(); i++)
		{
			xml_document OwnerDoc = mainVec[i].toXML();
			xml_node OwnerNode = root.append_copy(OwnerDoc.first_child());
		}

		docOutput.save(ofs);
	}
	else
	{
		json jwrite = json::array();

		for (int i = 0; i < mainVec.size(); i++)
		{
			json jOwner = mainVec[i].toJson();
			jwrite.push_back(jOwner);
		}

		ofs << jwrite.dump(4);
	}
	ofs.close();


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
				cout << i + 1 << ") ";
				mainVec[i].getOwnerData();
			}

			if (mainVec.empty())
			{
				cout << "Список собственников пуст";

				PrintQuit();
				break;
			}

			cout << "Введите номер собственника, которого вы хотите удалить" << endl;
			int num;
			cin >> num;
			while (num > mainVec.size() || num < 1)
			{
				cout << "Неверный номер" << endl;
				cin >> num;
			}

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
				cout << i + 1 << ") ";
				mainVec[i].getOwnerData();
			}

			if (mainVec.empty())
			{
				cout << "Список собственников пуст";

				PrintQuit();
				break;
			}

			cout << "Введите номер собственника, которому вы хотите добавить имущество" << endl;
			int num;
			cin >> num;
			while (num > mainVec.size() || num < 1)
			{
				cout << "Неверный номер" << endl;
				cin >> num;
			}

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

					mainVec[num - 1].addProperty(new Appartment (worthAppart, square));

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

					mainVec[num - 1].addProperty(new Car(worthCar, hp));

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

					mainVec[num - 1].addProperty(new CountryHouse (worthCntryHouse, distance));

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
				cout << i + 1 << ") ";
				mainVec[i].getOwnerData();
			}

			if (mainVec.empty())
			{
				cout << "Список собственников пуст";

				PrintQuit();
				break;
			}

			cout << "Введите номер собственника, у которого вы хотите удалить имущество" << endl;
			int num;
			cin >> num;
			while (num > mainVec.size() || num < 1)
			{
				cout << "Неверный номер" << endl;
				cin >> num;
			}


			system("cls");

			mainVec[num - 1].getOwnerData();

			if (mainVec[num - 1].getProp().empty())
			{
				cout << "У собственника отсутствует имущество";

				PrintQuit();
				break;
			}

			cout << "Введите номер имущества, которое хотите удалить" << endl;
			int numProp;
			cin >> numProp;
			while (numProp > mainVec[num - 1].getProp().size() || numProp < 1)
			{
				cout << "Неверный номер" << endl;
				cin >> numProp;
			}

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
				cout << i + 1 << ") ";
				mainVec[i].getOwnerData();
			}

			if (mainVec.empty())
			{
				cout << "Список собственников пуст";

				PrintQuit();
				break;
			}

			PrintQuit();
		}
		break;

		case 5:
		{
			system("cls");

			for (int i = 0; i < mainVec.size(); i++)
			{
				cout << i + 1 << ") ";
				mainVec[i].getOwnerData();
			}

			if (mainVec.empty())
			{
				cout << "Список собственников пуст";

				PrintQuit();
				break;
			}

			cout << "Введите номер собственника, у которого нужно подсчитать налоги" << endl;
			int numOwner;
			cin >> numOwner;
			while (numOwner > mainVec.size() || numOwner < 1)
			{
				cout << "Неверный номер" << endl;
				cin >> numOwner;
			}

			system("cls");

			mainVec[numOwner - 1].getOwnerData();

			if (mainVec[numOwner - 1].getProp().empty())
			{
				cout << "У собственника отсутствует имущество";

				PrintQuit();
				break;
			}

			cout << "Выберите имущество, на которое нужно подсчитать налог" << endl;
			int numTax;
			cin >> numTax;
			while (numTax > mainVec[numOwner - 1].getProp().size() || numTax < 1)
			{
				cout << "Неверный номер" << endl;
				cin >> numTax;
			}


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
				cout << i + 1 << ") ";
				mainVec[i].getOwnerData();
			}

			if (mainVec.empty())
			{
				cout << "Список собственников пуст";

				PrintQuit();
				break;
			}

			cout << "Введите номер собственника, у которого нужно подсчитать налоги" << endl;
			int numOwner;
			cin >> numOwner;
			while (numOwner > mainVec.size() || numOwner < 1)
			{
				cout << "Неверный номер" << endl;
				cin >> numOwner;
			}


			system("cls");

			mainVec[numOwner - 1].getOwnerData();

			if (mainVec[numOwner - 1].getProp().empty())
			{
				cout << "У собственника отсутствует имущество";

				PrintQuit();
				break;
			}

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