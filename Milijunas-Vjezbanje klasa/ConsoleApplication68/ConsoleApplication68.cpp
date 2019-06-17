// ConsoleApplication68.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;
bool glob1 = 0;
bool glob2 = 0;
bool glob3 = 0;
class Odgovor {
private:
	string opis_o;
	bool tf;
public:
	static Odgovor *make_odgovor();
	void cin_opis_o();
	void cin_tf();
	void set_opis_o(string o);
	void set_tf(string t);
	string get_opis_o();
	bool get_tf();
};
class Pitanje
{
private:
	string opis_p;
	vector<Odgovor*>odg;
public:
	static Pitanje *make_pitanje();
	void set_opis(string o);
	void get_opis();
	void set_odg(vector<string>pom, vector<string>pom2);
	void get_odg();
	int izbor();
	bool odgovaranje();

	void publika();
	void polapola();
	void zovi();
};

//Funkcije Pitanje
Pitanje *Pitanje::make_pitanje()
{
	return new Pitanje;
}
void Pitanje::set_opis(string o) {
	opis_p = o;
}
void Pitanje::get_opis() {
	cout << "Pitanje: " << opis_p << endl;
}
void Pitanje::set_odg(vector<string>pom, vector<string>pom2)
{
	for (int i = 0; i < 4; i++) {
		odg.push_back(Odgovor::make_odgovor());
		odg[i]->set_opis_o(pom[i]);
		odg[i]->set_tf(pom2[i]);

	}
}
void Pitanje::get_odg() {
	for (int i = 0; i < odg.size(); i++)
	{
		cout << "\t\t" << "Odgovor " << i + 1 << " : " << odg[i]->get_opis_o() << "\t\t";
		cout << endl;
	}
}
int Pitanje::izbor() {
	cout << "Odaberite broj ispred odgovora za kojeg mislite da je tocan ili 0 za biranje jokera" << endl;
	int izbor;
	cin >> izbor;
	return izbor;
}
bool Pitanje::odgovaranje() {
	int i;
	i = izbor();
	if (i == 0) {
		do {
			cout << "Izaberite joker koji zelite iskoritit:\n1 - Publika\n2 - Zovi prijatelja\n3 - 50:50" << endl;
			int izbor_jokera;
			cin >> izbor_jokera;
			switch (izbor_jokera)
			{
			case 1:
				publika();
				i = izbor();
				break;
			case 2:
				zovi();
				i = izbor();
				break;
			case 3:
				polapola();
				i = izbor();
			default:
				break;
			}
		} while (i == 0);
	}

	if (odg[i - 1]->get_tf() == true) {
		cout << "*********************" << endl;
		cout << " VAS ODGOVOR JE TOCAN " << endl;
		cout << "*********************" << endl;
		system("pause");
		return true;
	}
	else if (odg[i - 1]->get_tf() == false) {
		cout << "**********************" << endl;
		cout << "VAS ODGOVOR JE NETOCAN " << endl;
		cout << "**********************" << endl;
		system("pause");
		return false;
	}

}
//Jokeri
void Pitanje::publika() {
	int y;
	y = rand() % 35 + 40;
	if (glob1 == false) {
		for (int i = 0; i < 4; i++) {
			if (odg[i]->get_tf() == true) {
				cout << "Publika misli da je tocan odgovor: " << i + 1 << " sa najvecim postotkom u iznosu  " << y << "%." << endl;
			}
		}
		glob1 = true;
	}
	else {
		cout << "Iskoristili ste taj joker!!" << endl;
		system("pause");
	}

}
void Pitanje::polapola() {
	int pom;
	if (glob2 == false) {
		cout << "ISKOISTILI STE JOKER POLA-POLA" << endl;
		pom = rand() % 4;
		for (int i = 0; i < 4; i++) {
			if (i == pom && odg[i]->get_tf() == false) {
				cout << "\t\t" << "Odgovor " << i + 1 << " : " << odg[i]->get_opis_o() << "\t\t";
				cout << endl;
			}
			if (odg[i]->get_tf() == true) {
				cout << "\t\t" << "Odgovor " << i + 1 << " : " << odg[i]->get_opis_o() << "\t\t";
				cout << endl;
			}
		}
		glob2 = true;
	}
	else {
		cout << "Iskoristili ste taj joker!!" << endl;
		system("pause");
	}

}
void Pitanje::zovi() {
	if (glob3 == false)
		for (int i = 0; i < 4; i++) {
			if (odg[i]->get_tf() == true) {
				cout << "Mislim da je toèan odgovor pod " << i + 1 << endl;
				cout << "Koliko si siguran?" << endl;
				cout << "70% sam siguran da sam 100% siguran " << endl;
			}
			glob3 = true;
		}
	else {
		cout << "Iskoristili ste taj joker!!" << endl;
		system("pause");
	}
}
//Funkcije Odgovori
Odgovor *Odgovor::make_odgovor() {
	return new Odgovor;
}
void Odgovor::set_opis_o(string o) {
	opis_o = o;
}
void Odgovor::set_tf(string t)
{
	if (t == "T") {
		tf = true;
	}
	else {
		tf = false;
	}
}
void Odgovor::cin_opis_o() {
	string opis;
	getline(cin, opis);
	/*cin.ignore();*/
	opis_o = opis;
}
void Odgovor::cin_tf()
{
	char odg;
	cin >> odg;
	if (odg == 'T') {
		tf = true;
	}
	else {
		tf = false;
	}
}
string Odgovor::get_opis_o() {
	return opis_o;
}
bool Odgovor::get_tf() {
	return tf;
}


int main()
{
	srand(time(NULL));
	vector<Pitanje*>pit;
	bool toc = true;
	vector<string>novceki;
	{
		novceki.push_back("100 kuna");
		novceki.push_back("200 kuna");
		novceki.push_back("300 kuna");
		novceki.push_back("500 kuna");
		novceki.push_back("1 000 kuna");
		novceki.push_back("2 000 kuna");
		novceki.push_back("4 000 kuna");
		novceki.push_back("8 000 kuna");
		novceki.push_back("16 000 kuna");
		novceki.push_back("32 000 kuna");
		novceki.push_back("64 000 kuna");
		novceki.push_back("125 000 kuna");
		novceki.push_back("250 000 kuna");
		novceki.push_back("500 000 kuna");
		novceki.push_back("1 000 000 kuna");

	}
	ifstream input;
	input.open("Milpit.txt");
	string pitanje;
	vector<string>pitanja;

	vector<string>odgovori;
	vector<string>tfovi;
	string odg;
	string tfov;

	while (input) {
		getline(input, pitanje);
		pitanja.push_back(pitanje);
		do {
			getline(input, odg);
			if (odg != "-") {
				odgovori.push_back(odg);
			}
		} while (odg != "-");

		do {
			getline(input, tfov);
			if (tfov != "+") {
				tfovi.push_back(tfov);
			}
		} while (tfov != "+");


		if (input.eof()) {
			break;
		}
	}
	input.close();
	//Pravi kalupe za pitanja
	for (int i = 0; i < 15; i++) {
		pit.push_back(Pitanje::make_pitanje());
	}

	//Opis pitanja i odgovore
	for (int i = 0; i < pitanja.size(); i++) {
		vector<string>pom;
		vector<string>pom2;
		pit[i]->set_opis(pitanja[i]);
		for (int j = i * 4; j < (i + 1) * 4; j++) {
			pom.push_back(odgovori[j]);
			pom2.push_back(tfovi[j]);
		}
		pit[i]->set_odg(pom, pom2);
	}
	for (int i = 0; i < pit.size(); i++)
	{
		//Ovdje pratiti pitanja i novèeke
		system("cls");
		cout << "**************					**************" << endl;
		cout << "   PITANJE  " << i + 1 << "					  " << novceki[i] << endl;
		cout << "**************					**************" << endl;

		pit[i]->get_opis();
		pit[i]->get_odg();
		toc = pit[i]->odgovaranje();
		//Zaustavlja igru ako se netocno odgovori
		if (toc == false) {
			break;
		}
		else {
			continue;
		}
		cout << endl;
		system("pause");
	}
	return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
