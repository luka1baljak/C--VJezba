// ConsoleApplication15.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;
//Klase
class Racun {
protected:
	int broj_racuna;
	float stanje_racuna;
	int vrijeme;
public:
	static Racun *make_racun(int izbor);

	virtual void set_broj_racuna(int brr);
	virtual int get_broj_racuna();

	virtual void set_vrijeme(int vri);

	virtual void set_stanje_racuna(float str);
	virtual float get_stanje_racuna();

	virtual void polaganje_novca();
	virtual void podizanje_novca();

	void stanje();
};

class Tekuci_racun :public Racun {
private:
	float mjesecna_kamata = 0.05;
	int vrijeme;
public:
	Tekuci_racun();
	Tekuci_racun(float kol);
	Tekuci_racun(int vr);
	void podizanje_novca();
	void set_vrijeme(int vri);
	int get_vrijeme();
};

class Stedni_racun :public Racun {
private:
	float godisnja_kamata = 5;
	int vrijeme;
public:
	Stedni_racun();
	Stedni_racun(float kol);
	Stedni_racun(int vr);
	void podizanje_novca();
	void set_vrijeme(int vri);
	int get_vrijeme();
};

//Funkcije
Racun *Racun::make_racun(int izbor)
{
	if (izbor == 1) {
		return new Tekuci_racun;
	}
	else if (izbor == 2) {
		return new Stedni_racun;
	}
	else {
		return new Tekuci_racun;
	}
}
void Racun::set_vrijeme(int vr) {
	vrijeme = vr;
}
void Racun::stanje() {
	cout << "Stanje racuna " << broj_racuna << " je:" << stanje_racuna << " kuna";
}
void Racun::polaganje_novca() {
	int kolicina;
	cout << "Koliko zelite uplatiti?" << endl << "Iznos: ";
	cin >> kolicina;
	stanje_racuna += kolicina;
}
void Racun::podizanje_novca() {
	int kolicina;
	cout << "Koliko zelite podigniti?" << endl << "Iznos: ";
	cin >> kolicina;
	stanje_racuna -= kolicina;
}
void Racun::set_broj_racuna(int brr) {
	broj_racuna = brr;
}
int Racun::get_broj_racuna() {
	return broj_racuna;
}
void Racun::set_stanje_racuna(float str) {
	stanje_racuna = str;
}
float Racun::get_stanje_racuna() {
	return stanje_racuna;
}
//Fukncije tekuci_racun
Tekuci_racun::Tekuci_racun() {
	stanje_racuna = 50.00;
	broj_racuna = 1025;
	mjesecna_kamata = 0.05;
	vrijeme = 0;
}
Tekuci_racun::Tekuci_racun(int vr) {
	vrijeme = vr;
}
Tekuci_racun::Tekuci_racun(float kolic) {
	stanje_racuna = kolic;
}

void Tekuci_racun::podizanje_novca() {
	stanje_racuna += stanje_racuna * (mjesecna_kamata / 100) *vrijeme;
	cout << "Podigli ste:" << stanje_racuna << " sa racuna " << broj_racuna << endl;
	stanje_racuna = 0;
}
void Tekuci_racun::set_vrijeme(int vri) {
	vrijeme = vri;
}
int Tekuci_racun::get_vrijeme() {
	return vrijeme;

}
//Funkcije stedni_racun
Stedni_racun::Stedni_racun() {
	broj_racuna = 1026;
	stanje_racuna = 250.00;
	float godisnja_kamata = 5;
	int vrijeme = 0;
}
Stedni_racun::Stedni_racun(float kol) {
	stanje_racuna = kol;
}
Stedni_racun::Stedni_racun(int vr) {
	vrijeme = vr;

}

void Stedni_racun::podizanje_novca() {
	stanje_racuna += stanje_racuna * (godisnja_kamata / 100)*vrijeme;
	cout << "Podigli ste:" << stanje_racuna << " sa racuna " << broj_racuna << endl;
	stanje_racuna = 0;
}
void Stedni_racun::set_vrijeme(int vri) {
	vrijeme = vri;
}
int Stedni_racun::get_vrijeme() {
	return vrijeme;
}


int main()
{

	srand(time(NULL));
	vector<Racun*>racuni;

	int odabir;
	do {
		system("cls");
		cout << "Odaberite koji racun zelite koristiti:\n1 - Tekuci\n2 - Stedni\n0 - Izlaz\n";
		cin >> odabir;
		racuni.push_back(Racun::make_racun(odabir));

		for (int i = 0; i < racuni.size(); i++) {
			int izbor;
			do {
				system("cls");
				if (odabir == 1) {
					cout << "***TEKUCI RACUN***" << endl << endl << endl;
				}
				else if (odabir == 2) {
					cout << "***STEDNI RACUN***" << endl << endl << endl;
				}
				cout << "1 - Stanje racuna " << endl;
				cout << "2 - Polaganje novca " << endl;
				cout << "3 - Podizanje novca " << endl;

				cout << "0 - Izlaz" << endl;
				cout << endl << "Vas izbor: ";
				cin >> izbor;
				switch (izbor) {
				case 1:racuni[i]->stanje();
					cout << endl;
					system("Pause");
					break;
				case 2:racuni[i]->polaganje_novca();
					break;
				case 3:
					int v;
					cout << "Koliko je vremena prošlo?:";
					cin >> v;
					racuni[i]->set_vrijeme(v);
					racuni[i]->podizanje_novca();
					system("Pause");
					break;
				case 4:
					break;
				case 5:
					break;
				case 0:
					break;
				}
			} while (izbor != 0);
		}
		for (int i = 0; i < racuni.size(); i++) {
			delete racuni[i];
		}
	} while (odabir != 0);
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
