/* 
 * File:   Parser.cpp
 * Author: Matt
 * 
 * Created on 3 czerwiec 2013, 21:01 
 */

#include "Parser.h"
#include "Rec.h"

void Parser::run(string nazwa) {
	
	/*
	 * algorytm klasy
	*/
	vector< vector<int> > MACIERZ_IDS;
	MACIERZ_IDS=loadFile(nazwa);
	
	int m_rozmiar[2];
	int m_ymax=0;
	int licz=0;
	
	/*
	 * okreslanie rozmiaru MACEIRZ_IDS
	*/
	for (unsigned int i=0; i<MACIERZ_IDS.size(); i++) {
		for (unsigned int j=0; j<MACIERZ_IDS[i].size(); j++) {
			licz++;
		}
		if (licz>m_ymax) { m_ymax=licz; licz=0; }
	}
	
	m_rozmiar[0]=MACIERZ_IDS.size();
	m_rozmiar[1]=m_ymax-1;
	
	/*
	 * utworzenie tablicy dwuwymiarowej z MACIERZY_IDS i przygotowanie jej do wyslania
	*/
	int ** tablica = new int * [m_rozmiar[0]];
    for (int i = 0; i<m_rozmiar[1]; i++)
        tablica[i] = new int [m_rozmiar[1]];

	for (unsigned int i=0; i<m_rozmiar[0]; i++)
		for (unsigned int j=0; j<m_rozmiar[1]; j++)
			tablica[i][j]=0;

	for (unsigned int i=0; i<MACIERZ_IDS.size(); i++)
		for (unsigned int j=0; j<MACIERZ_IDS[i].size(); j++)
			tablica[i][j]=MACIERZ_IDS[i][j];
	
	/*
	 * utworzenie tablicy jednowymiarowej okreslajacej ile liczb jest w kazdej kolumnie MACIERZ_IDS
	*/
	int * ile_liczb = new int [m_rozmiar[0]];
	licz=0;
	for (unsigned int i=0; i<MACIERZ_IDS.size(); i++) {
		for (unsigned int j=0; j<MACIERZ_IDS[i].size(); j++) {
			licz++;
		}
		ile_liczb[i]=licz;
		licz=0;
	}
	/*
	 * wysylanie tablicy do nastepnej klasy
	*/
    MPI::COMM_WORLD.Send ( m_rozmiar, 2, MPI::INT, 2, 1 ); // przesylanie rozmiarow tablicy dwuwymiarowej
    MPI::COMM_WORLD.Send ( ile_liczb, m_rozmiar[0], MPI::INT, 2, 1 ); // przesylanie tablicy okreslajacej ilosc liczb do wczytania z kazdego wiersza
		
	for (unsigned int i=0; i<m_rozmiar[0]; i++) {
		MPI::COMM_WORLD.Send ( tablica[i], ile_liczb[i], MPI::INT, 2, 2 ); // przesylanie tablicy dwuwymiarowej
	}
	
	delete []ile_liczb;
	delete []tablica;
}

vector < vector<int> >  Parser::loadFile (string nazwa) { //wcztaj plik i wygeneruj MACIERZ_IDS
   
	fstream plik;

	vector <int> IDS;
	vector < vector<int> > MACIERZ_IDS;

	plik.open(nazwa.c_str()); //otwieranie pliku
	
	cout << "Watek 1 otwiera plik " << nazwa << endl;
	if( plik.good() == true ) { //sprawdzanie pliku
		//cout << "Uzyskano dostep do pliku" << endl;
	} 
	else {
		cout << "Brak pliku" << endl;
		IDS.insert(IDS.begin(),0);
		MACIERZ_IDS.insert(MACIERZ_IDS.begin(), IDS);
		plik.close();
		return MACIERZ_IDS;
	}

	string linia;
	while (getline(plik, linia)) { //generowanie MACIERZ_IDS
		istringstream pom(linia);
		int liczba;
		while (pom >> liczba)
			IDS.push_back(liczba);
		if (IDS.size()>0)
			MACIERZ_IDS.push_back(IDS);
		IDS.clear();
	}

	plik.close();
	return MACIERZ_IDS;

}

void Parser::display (vector<Rec> v) { // wyswietl MACIERZ_IDS
	cout << endl << "Tabela RECS:" << endl;
	for (unsigned int i=0; i<v.size(); i++) {
		cout << "ID " << v[i].getID() << " ocena " << v[i].getNote() << endl;
	}

}
