// ConsoleApplication55.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

using namespace std;

// definiranje klasa

class Node {
private:
	int podatak;
	Node *next;
	static int broj_nodeova;

public:
	Node();
	~Node();
	void set_podatak(int vrijednost);
	int get_podatak();
	void set_next(Node *nnn);
	Node *get_next();
	static int get_broj_nodeova();
};

class PovezanaLista {
private:
	Node *head;
public:
	PovezanaLista();
	void unos_pocetak(int vrijednost);
	void brisanje_pocetak();
	void unos_kraj(int vrijednost);
	void brisanje_kraj();
	void ispis();
	void brisanje_s_indeksa(int unos);
	void dodavanje_na_indeks(int unos, int vrijednost);
};

// Definicije klase Node

int Node::broj_nodeova = 0; // inicijaliziranje statickog clana broj_nodeova na 0

Node::Node() {
	broj_nodeova++;
}

Node::~Node() {
	broj_nodeova--;
}

void Node::set_podatak(int vrijednost) {
	podatak = vrijednost;
}

int Node::get_podatak() {
	return podatak;
}

void Node::set_next(Node *nnn) {
	next = nnn;
}

Node* Node::get_next() {
	return next;
}

int Node::get_broj_nodeova() {
	return broj_nodeova;
}

// Definicije klase PovezanaLista

PovezanaLista::PovezanaLista() {
	head = nullptr;
}

void PovezanaLista::unos_pocetak(int vrijednost) {
	Node *temp = new Node;
	temp->set_podatak(vrijednost);
	temp->set_next(head);
	head = temp;
}

void PovezanaLista::brisanje_pocetak() {
	Node *temp = head;
	head = temp->get_next();
	delete temp;
}

void PovezanaLista::unos_kraj(int vrijednost) {
	Node *n = new Node;
	n->set_podatak(vrijednost);
	n->set_next(nullptr);
	if (head == nullptr) {
		head = n;
	}
	else {
		Node *temp = head;
		while (temp->get_next() != nullptr) {
			temp = temp->get_next();
		}
		temp->set_next(n);
	}
}

void PovezanaLista::brisanje_kraj() {
	Node *temp = head;
	Node *prev = temp;
	while (temp->get_next() != nullptr) {
		prev = temp;
		temp = temp->get_next();
	}
	prev->set_next(nullptr);
	delete temp;
}

void PovezanaLista::ispis() {
	Node *temp = head;
	while (temp != nullptr) {
		cout << temp->get_podatak() << "\t";
		temp = temp->get_next();
	}
	cout << endl;
}

void PovezanaLista::brisanje_s_indeksa(int unos) {
	Node *temp0 = head;
	Node *temp1 = head;
	Node *temp2 = head;

	if (temp0->get_next() == NULL)
	{
		delete(temp0);
		head = NULL;
	}
	else
	{
		for (int i = -1; i < unos; i++) {
			temp2 = temp1;
			temp1 = temp0;
			temp0 = temp0->get_next();

		}
		delete(temp1);
		temp2->set_next(temp0);

	}
}

void PovezanaLista::dodavanje_na_indeks(int unos,int vrijednost) {
	Node *temp0 = head;
	Node *temp1 = head;

	Node *n = new Node;

	for (int i = 0; i < unos; i++) {
		temp1 = temp0;
		temp0 = temp0->get_next();
	}
	n->set_podatak(vrijednost);
	temp1->set_next(n);
	n->set_next(temp0);
}
int main()
{
	PovezanaLista lista;
	int x;
	do {
		system("cls");
		cout << "Povezana lista - koristeci klase\n\n";
		cout << "1 - Unos na pocetak\n2 - Brisanje s pocetka\n3 - Unos na kraj\n";
		cout << "4 - Brisanje s kraja\n5 - Ispis\n6 - Broj nodeova\n7 - Brisanje elementa sa indeksa\n";
		cout << "8 - Dodavanje elementa na indeks\n0 - Izlaz\n";
		cout << "Vas izbor: ";
		cin >> x;
		switch (x) {

			int broj;
		case 1:
			cout << "Unesite broj: ";
			cin >> broj;
			lista.unos_pocetak(broj);
			cout << endl;
			break;
		case 2:
			lista.brisanje_pocetak();
			break;
		case 3:
			cout << "Unesite broj: ";
			cin >> broj;
			lista.unos_kraj(broj);
			cout << endl;
			break;
		case 4:
			lista.brisanje_kraj();
			break;
		case 5:
			cout << endl;
			lista.ispis();
			cout << endl;
			system("pause");
			break;
		case 6:
			cout << endl << Node::get_broj_nodeova() << endl;
			system("pause");
			break;
		case 7:
			int unos1;
			cout << "Indeks elementa za brisanje: " << endl;
			cin >> unos1;
			if (unos1 == 0) {
				lista.brisanje_pocetak();
			}
			else {
				lista.brisanje_s_indeksa(unos1);
			}
			break;
		case 8:
			int unos, vrijednost;
			cout << "Na kojem indeksu: " << endl;
			cin >> unos;
			cout << "Koju vrijednost: " << endl;
			cin >> vrijednost;
			if (unos == 0) {
				lista.unos_pocetak(vrijednost);
			}
			else {
				lista.dodavanje_na_indeks(unos, vrijednost);
			}
			break;
		case 0:
			break;
		default:
			cout << "Molim ispravan unos!\n";
			break;
		}
	} while (x != 0);

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
