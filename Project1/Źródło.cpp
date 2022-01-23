#include<iostream>
#include<iomanip>
#include<cstring>
#include<fstream>
#include<sstream>

using namespace std;

struct pomiar {
	char id[6];
	float x;
	float y;
	int liczba;
	char data[11];
};

//string s("napis probny");

string miasto_pomiaru(string id)
{
	fstream ifs("Punkty_w_Miastach.txt", ios::in);

	string ident;
	string line;
	string miasto;
	stringstream s;

	while (getline(ifs, line))
	{
		s << line;
		s >> miasto;
		while (s)
		{
			s >> ident;
			if (id == ident) return(miasto);
		}
		s.clear();
	}
	return("");
}


void sprawdz(fstream& ofs, char id_pom[], long int& licznik)
{
	fstream ifs("Pomiary.txt", ios::in);
	pomiar p;

	while (ifs >> p.id >> p.x >> p.y >> p.liczba >> p.data)
	{
		if (!strcmp(p.id, id_pom))
		{
			ofs << p.id << ' ' << p.liczba << ' ' << p.data << ' ' << miasto_pomiaru(p.id) << endl;
			licznik++;
		}
	}
	ifs.close();
}



void filtruj(fstream& ofs, long int& licznik)		//strumienie przesylamy przez refernecje
{
	fstream wybranefs("WybranePunkty.txt", ios::in);
	char id_pom[6];

	while (wybranefs >> id_pom)
	{
		sprawdz(ofs, id_pom, licznik);
	}
	wybranefs.close();
}


int main()
{
	fstream ofs("Output.txt", ios::out);

	long int licznik = 0;

	filtruj(ofs, licznik);

	ofs << "Zapisano dane " << licznik << " pomiarow";
	ofs.close();

}
