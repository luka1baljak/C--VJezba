// ConsoleApplication53.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

struct pacijent {
	int MBO;
	string ime;
	string prezime;
	vector<string>popis_lijekova;
};
//DEKLARACIJE!!
vector<pacijent>popis;
queue<string>red;
queue<string>prez;
//Cekaonica
void shell_sortiranje();
void prijava_pacijenata();
void stanje();
//Menu
void unos_lijekova();
void citanje_filea();
void zapis_ufile(vector<pacijent>popis);
pacijent unos_pacijenata();
void prikaz_pacijenata(vector<pacijent> popis);
int pretrazivanje(vector<pacijent> popis, int start, int kraj, int trazeni_broj);

int main()
{
	citanje_filea();
	int odabir;
	do {
		system("cls");
		cout << "Odaberite opciju:" << endl;
		cout << "1. Unos novih pacijenata" << endl;
		cout << "2. Prikaz pacijenata" << endl;
		cout << "3. Pretrazivanje" << endl;
		cout << "4. Unos lijekova za pacijenta" << endl;
		cout << "   ***Cekaonica*** " << endl;
		cout << "5. Prijava pacijenata" << endl;
		cout << "6. Stanje u cekaonici" << endl;
		cout << "   ***Izlaz*** " << endl;
		cout << "0. Izlaz" << endl;
		cin >> odabir;
		switch (odabir) {
		case 1:popis.push_back(unos_pacijenata());
			break;
		case 2:prikaz_pacijenata(popis);
			system("Pause");
			break;
		case 3:int trazeni;
			cout << "Unesite MBO koji zelite pronaci: " << endl;
			cin >> trazeni;
			shell_sortiranje();
			int y;
			y = pretrazivanje(popis, 0, popis.size(), trazeni);
			/*if (y == -1) {
				cout << "Prob";
			}*/
			system("pause");
			break;
		case 4:unos_lijekova();
			break;
		case 5:prijava_pacijenata();
			break;
		case 6:stanje();
			system("pause");
			break;
		case 0:shell_sortiranje();
			zapis_ufile(popis);
			break;
		default:cout << "Neispravan unos!!" << endl;
			system("Pause");
			break;
		}
	} while (odabir != 0);

	system("pause");
	return 0;
}

//FUNKCIJE!!
//void cekaonica() {
	//  /*int opcija;
	//  do {
	//      system("cls");
	//
	//      cout << "           !!!CEKAONICA!!!             ";
	//      cout << "Izaberite opciju (ili 0 za izlaz): " << endl;
	//      cout << "1.Prijava pacijenata" << endl;
	//      cout << "2.Odjava pacijenata" << endl << "3.Stanje" << endl;
	//      cin >> opcija;
	//      switch (opcija) {
	//      case 1:prijava_pacijenata();
	//          break;
	//      case 2:odjava_pacijenata();
	//          system("Pause");
	//          break;
	//      case 3:stanje();
	//          system("pause");
	//          break;
	//      case 0:
	//          break;
	//      }
	//  } while (opcija != 0);*/
	//}
	//void odjava_pacijenata() {
		//system("cls");
		//for (int i = 0; i < 1; i++,red.pop()) {
		//  cout << red.front() << " se odjavio" << endl;
		//}
	//}

void prijava_pacijenata() {
	system("cls");
	cout << "Koliko pacijenata zelite prijaviti?: " << endl;
	int kol;
	cin >> kol;
	for (int i = 0; i < kol; i++) {
		string unos;
		string prezime;
		cout << "Unesite ime: " << endl;
		cin >> unos;
		cout << "Unesite prezime: " << endl;
		cin >> prezime;
		red.push(unos);
		prez.push(prezime);
	}
}

void stanje() {
	system("cls");
	if (red.size() > 1) {
		for (int i = 0; i < 1; i++, red.pop(),prez.pop()) {
			cout << red.front() << " " << prez.front() << " je trenutno kod doktora" << endl;
		}
		cout << red.front() << " " << prez.front() << " je sljedeci na redu" << endl;
		cout << red.size() << " ceka u cekaonici!!";
	}
	else if (red.size() == 1) {
		for (int i = 0; i < 1; i++, red.pop(), prez.pop()) {
			if (i == 0) {
				cout << red.front() << " " << prez.front() << " je trenutno kod doktora" << endl;
			}
			cout << "Nema nitko u cekaonici";
		}
	}
	else {
		cout << "Nema pacijenata!!";
	}
}

void citanje_filea()
{

	pacijent p;
	ifstream input;
	input.open("pacijenti.txt");
	string MBO, ime, prezime, lijek;

	while (input) {
		getline(input, MBO);
		p.MBO = stoi(MBO);
		getline(input, p.ime);
		getline(input, p.prezime);
		vector <string> medicina;
		do {
			getline(input, lijek);
			if (lijek != "-") {
				medicina.push_back(lijek);
			}
		} while (lijek != "-");
		p.popis_lijekova = medicina;
		popis.push_back(p);
		if (input.eof()) {
			break;
		}
	}
}



void zapis_ufile(vector<pacijent>popis) {
	ofstream output;
	output.open("pacijenti.txt", ios::out);
	for (int i = 0; i < popis.size(); i++) {
		output << popis[i].MBO << endl << popis[i].ime << endl << popis[i].prezime << endl;
		for (int j = 0; j < popis[i].popis_lijekova.size(); j++) {
			output << popis[i].popis_lijekova[j] << endl;
		}
		if (i == popis.size()- 1) {
			output << "-";
		}
		else {
			output << "-" << endl;
		}
	}
	output.close();

	//ofstream output2;
	//output2.open("pacijenti.txt", ios::out);
	//for (int i = 0; i < popis.size(); i++) {
	//  output2 << popis[i].MBO << " " << popis[i].ime << " " << popis[i].prezime;
	//}
	//output2.close();
}

pacijent unos_pacijenata() {
	int a;
	pacijent novi;
	bool isti = false;
	do {
		cout << "Unesite MBO: ";
		cin >> a;
		for (int i = 0; i < popis.size(); i++) {
			if (a == popis[i].MBO) {
				cout << "Vec postoji pacijent s tim MBO\n";
				isti = true;
				break;
			}
			else {
				isti = false;
			}
		}
	} while (isti);
	novi.MBO = a;

	cout << "\nUnesite ime: ";
	cin >> novi.ime;

	cout << "\nUnesite Prezime: ";
	cin >> novi.prezime;

	return novi;
}

void unos_lijekova() {
	//Unos lijekova
	string lijek;
	cout << "Ime pacijenta: " << endl;
	string ime;
	cin >> ime;
	int indeks;
	for (int i = 0; i < popis.size(); i++) {
		if (popis[i].ime == ime) {
			indeks = i;
		}
	}
	do {
		cout << "\nUnesite lijek (ili 0 za izlaz): " << endl;
		cin >> lijek;
		if (lijek == "0") {
			break;
		}
		popis[indeks].popis_lijekova.push_back(lijek);
	} while (lijek != "0");
}

void prikaz_pacijenata(vector<pacijent> popis) {
	cout << "MBO" << "\t" << "IME" << "\t" << "PREZIME" << "\t\t" << "LIJEKOVI" << endl;
	for (int i = 0; i < popis.size(); i++) {
		cout << popis[i].MBO << "\t" << popis[i].ime << "\t" << popis[i].prezime << "\t\t";
		for (int j = 0; j < popis[i].popis_lijekova.size(); j++) {
			if (j < popis[i].popis_lijekova.size() - 1) {
				cout << popis[i].popis_lijekova[j] << ", ";
			}
			else {
				cout << popis[i].popis_lijekova[j];
			}
		}
		cout << endl;
	}
	/*for (int i = 0; i < popis.size(); i++) {
		cout << "MBO:" << popis[i].MBO << "\t" << "Ime:" << popis[i].ime << "\t" << "Prezime:" << popis[i].prezime << endl;
		cout << "Lijekovi:" << endl;
		for (int j = 0; j < popis[i].popis_lijekova.size(); j++) {
			cout << popis[i].popis_lijekova[j] << endl;
		}
	}*/
}

int pretrazivanje(vector<pacijent> popis, int start, int kraj, int trazeni_broj) {
	int sredina = (start + kraj) / 2;

	if (popis[sredina].MBO == trazeni_broj) {
		cout << popis[sredina].ime << " " << popis[sredina].prezime;
		return 0;
	}
	else if (start == kraj && popis[sredina].MBO != trazeni_broj) {
		cout << "Ne postoji taj MBO" << endl;
		return -1;
	}
	else {
		if (popis[sredina].MBO < trazeni_broj) {
			pretrazivanje(popis, sredina + 1, kraj, trazeni_broj);
		}
		else if (popis[sredina].MBO > trazeni_broj) {
			pretrazivanje(popis, start, sredina - 1, trazeni_broj);
		}
	}
}

void shell_sortiranje() {
	int n = popis.size();
	for (int k = n / 2; k > 0; k /= 2) {
		for (int i = k; i < n; i++) {
			pacijent pom1 = popis[i];
			int pom = popis[i].MBO;
			int j;
			for (j = i; j >= k && popis[j - k].MBO > pom; j -= k) {
				popis[j] = popis[j - k];

			}
			popis[j] = pom1;
		}
	}
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
