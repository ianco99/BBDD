#include <mysql.h>
#include <iostream>

using namespace std;

enum class MenuOption
{
	AddData = 1,
	UpdateData,
	RemoveData,
	ReadData,
	Quit
};

enum class TableData
{
	Sports = 1,
	Athletes,
	Medals,
	Stadiums,
	Nations
};

struct Sport
{
	string name;
	string maxParticipants;
};

struct Athlete
{
	string name;
	string lastName;
};

MYSQL* sqlConnection = new MYSQL();
MYSQL_ROW fila;
MYSQL_RES* resultado;

int input;
int q_state = -1;

void AddData();
void UpdateData();
void ReadData();
void RemoveData();
void ShowData(string table, TableData option);
string DataPerTable(string table, TableData option, string id, bool add);
int GetMaxFields(TableData option);

int main()
{
	bool running = false;

	sqlConnection = mysql_init(0);
	sqlConnection = mysql_real_connect(sqlConnection, "localhost", "root", "25072003", "mydatabase", 3306, NULL, 0);

	if (sqlConnection)
	{
		cout << "Connected to database!" << endl;
		system("PAUSE");
		system("CLS");

		running = true;

		while (running)
		{
			system("CLS");
			cout << "Olympic Games Developer Center" << endl;
			cout << "1. Add data" << endl;
			cout << "2. Update data" << endl;
			cout << "3. Remove data" << endl;
			cout << "4. Read data" << endl;
			cout << "5. Quit" << endl;

			cin >> input;

			MenuOption chosen = (MenuOption)input;

			switch (chosen)
			{
			case MenuOption::AddData:
				AddData();
				break;
			case MenuOption::UpdateData:
				UpdateData();
				break;
			case MenuOption::RemoveData:
				RemoveData();
				break;
			case MenuOption::ReadData:
				ReadData();
				break;
			case MenuOption::Quit:
				running = false;
				break;
			default:
				break;
			}
		}




	}
	else
	{
		cout << "Failed to connect to database." << endl;
	}

	cout << "Ending program." << endl;
	return 0;
}

void AddData()
{
	TableData option;
	string table;
	string answer;

	cout << "Which table would you like to add information to?" << endl;
	cout << "1. Sports table" << endl;
	cout << "2. Athletes table" << endl;
	cout << "3. Medals table" << endl;
	cout << "4. Stadium table" << endl;
	cout << "5. Nations table" << endl;

	cin >> input;
	option = (TableData)input;

	switch (option)
	{
	case TableData::Sports:
		table = "sport";
		break;
	case TableData::Athletes:
		table = "athlete";
		break;
	case TableData::Medals:
		table = "medal";
		break;
	case TableData::Stadiums:
		table = "stadium";
		break;
	case TableData::Nations:
		table = "nation";
		break;
	default:
		break;
	}

	string insert = DataPerTable(table, option, "s", true);
	const char* i = insert.c_str();
	cout << insert << endl;
	q_state = mysql_query(sqlConnection, i);

	cout << endl;
	if (!q_state)
	{
		cout << "Ingreso exitoso!";
	}
	else
	{
		cout << "Ingreso fallido.";
	}
	cout << endl;

	system("PAUSE");
}

void UpdateData()
{
	string table;
	string stdInput;

	Sport newSport;
	Athlete newAthlete;

	string consulta;

	system("CLS");
	cout << "Which table would you like to update information to?" << endl;
	cout << "1. Sports table" << endl;
	cout << "2. Athletes table" << endl;
	cout << "3. Medals table" << endl;
	cout << "4. Stadium table" << endl;
	cout << "5. Nations table" << endl;

	cin >> input;
	TableData option = (TableData)input;

	switch (option)
	{
	case TableData::Sports:
		table = "sport";
		break;
	case TableData::Athletes:
		table = "athlete";
		break;
	case TableData::Medals:
		table = "medal";
		break;
	case TableData::Stadiums:
		table = "stadium";
		break;
	case TableData::Nations:
		table = "nation";
	default:
		break;
	}

	system("CLS");

	cout << "Insert id of the element you want to update from " + table + " table." << endl << endl;
	ShowData(table, option);
	cout << '\n';
	cin >> stdInput;

	consulta = DataPerTable(table, option, stdInput, false);

	const char* c = consulta.c_str();
	q_state = mysql_query(sqlConnection, c);
	cout << consulta;

	cout << endl;


	if (!q_state)
	{
		cout << "Consulta exitosa" << endl;
	}
	else
	{
		cout << "Consulta failed" << endl;
	}

	system("PAUSE");
}

string DataPerTable(string table, TableData option, string id, bool add)
{
	string consulta;

	Sport newSport;
	Athlete newAthlete;
	string stdInput;

	switch (option)
	{
	case TableData::Sports:

		if (add)
			cout << "Write name of the new sport" << endl;
		else
			cout << "Write updated name of the sport" << endl;

		cin >> newSport.name;
		
		if (add)
			cout << "Write maximum number of participants of the new sport" << endl;
		else
			cout << "Write updated maximum number of participants for the sport" << endl;

		cin >> newSport.maxParticipants;

		if (add)
			consulta = "insert into " + table + "(name, maxParticipants) values ('" + newSport.name + "','" + newSport.maxParticipants + "')";
		else
			consulta = "update sport set name = '" + newSport.name + "', maxParticipants = '" + newSport.maxParticipants + "' where id_sport = " + id;
		break;

	case TableData::Athletes:
		
		if (add)
			cout << "Write name of the new athlete" << endl;
		else
			cout << "Write updated name of the athlete" << endl;

		cin >> newAthlete.name;
		
		if (add)
			cout << "Write last name of the new athlete" << endl;
		else
			cout << "Write updated last name of the new athlete" << endl;

		cin >> newAthlete.lastName;

		if (add)
			consulta = "insert into " + table + "(name, lastName) values ('" + newAthlete.name + "','" + newAthlete.lastName + "')";
		else
			consulta = "update athlete set name = '" + newAthlete.name + "', lastName = '" + newAthlete.lastName + "' where id_athlete = " + id;
		break;

	case TableData::Medals:

		if (add)
			cout << "Write name of the new medal" << endl;
		else
			cout << "Write updated name of the medal" << endl;
		
		cin >> stdInput;

		if (add)
			consulta = "insert into " + table + "(name) values ('" + stdInput + "')";
		else
			consulta = "update medal set name = '" + table + "' where id_medal = " + id;
		break;

	case TableData::Stadiums:
		
		if (add)
			cout << "Write name of the new stadium" << endl;
		else
			cout << "Write updated name of the stadium" << endl;
		
		cin >> stdInput;

		if (add)
			consulta = "insert into " + table + "(name) values ('" + stdInput + "')";
		else
			consulta = "update stadium set name = '" + table + "' where id_stadium = " + id;
		break;

	case TableData::Nations:
		
		if (add)
			cout << "Write name of the new nation" << endl;
		else
			cout << "Write updated name of the nation" << endl;
		
		cin >> stdInput;

		if (add)
			consulta = "insert into " + table + "(name) values ('" + stdInput + "')";
		else
			consulta = "update nation set name = '" + table + "' where id_nation = " + id;
		break;
	default:
		break;
	}

	return consulta;
}

void RemoveData()
{
	string table;
	string stdInput;

	system("CLS");
	cout << "Which table would you like to remove information from?" << endl;
	cout << "1. Sports table" << endl;
	cout << "2. Athletes table" << endl;
	cout << "3. Medals table" << endl;
	cout << "4. Stadium table" << endl;
	cout << "5. Nations table" << endl;

	cin >> input;
	TableData option = (TableData)input;

	switch (option)
	{
	case TableData::Sports:
		table = "sport";
		break;
	case TableData::Athletes:
		table = "athlete";
		break;
	case TableData::Medals:
		table = "medal";
		break;
	case TableData::Stadiums:
		table = "stadium";
		break;
	case TableData::Nations:
		table = "nation";
	default:
		break;
	}

	system("CLS");
	ShowData(table, option);
	cout << "Insert id to delete from " + table + " table." << endl;
	cin >> stdInput;

	string consulta = "delete from " + table + " where id_" + table + " = '" + stdInput + "'";
	const char* c = consulta.c_str();
	q_state = mysql_query(sqlConnection, c);
	cout << consulta;

	cout << endl;

	if (!q_state)
	{
		cout << "Deletion successful." << endl;
	}
	else
	{
		cout << "Deletion failed." << endl;
	}

	system("PAUSE");
}

void ReadData()
{
	string table;

	system("CLS");
	cout << "Which table would you like to read information from?" << endl;
	cout << "1. Sports table" << endl;
	cout << "2. Athletes table" << endl;
	cout << "3. Medals table" << endl;
	cout << "4. Stadium table" << endl;
	cout << "5. Nations table" << endl;

	cin >> input;
	TableData option = (TableData)input;

	switch (option)
	{
	case TableData::Sports:
		table = "sport";
		break;
	case TableData::Athletes:
		table = "athlete";
		break;
	case TableData::Medals:
		table = "medal";
		break;
	case TableData::Stadiums:
		table = "stadium";
		break;
	case TableData::Nations:
		table = "nation";
		break;
	default:
		break;
	}

	ShowData(table, option);

	system("PAUSE");
}

void ShowData(string table, TableData option)
{
	string consulta = "select * from " + table;
	const char* c = consulta.c_str();
	q_state = mysql_query(sqlConnection, c);

	int maxFields = GetMaxFields(option);

	if (!q_state)
	{
		cout << endl;

		resultado = mysql_store_result(sqlConnection);
		while (fila = mysql_fetch_row(resultado))
		{
			for (int i = 0; i < maxFields; i++)
			{
				if (i == 0)
					cout << fila[i];
				else
					cout << " , " << fila[i];
			}

			cout << endl;
		}
	}
}

int GetMaxFields(TableData option)
{
	int maxFields = 0;
	switch (option)
	{
	case TableData::Sports:
		maxFields = 3;
		break;
	case TableData::Athletes:
		maxFields = 3;
		break;
	case TableData::Medals:
		maxFields = 2;
		break;
	case TableData::Stadiums:
		maxFields = 2;
		break;
	case TableData::Nations:
		maxFields = 2;
		break;
	default:
		break;
	}

	return maxFields;
}