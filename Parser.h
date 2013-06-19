/* 
 * File:   Parser.h
 * Author: Matt
 *  
 * Created on 3 czerwiec 2013, 20:57
 */

#ifndef PARSER_H
#define	PARSER_H

using namespace std;
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "mpi.h"
#include "Rec.h"

/**
 * Klasa wczytujaca wartosci z podanego pliku i zapisujaca je do vektora dwuwymiarowego
 * 
 * @author Mateusz
 */
 
class Parser {

public:
    Parser(){};
    virtual ~Parser(){};

    /**
     * schemat dzia³ania klasy: 
     * - uruchomienie algorytmu klasy : wczytywanie pliku i wygenerowanie dwuwymiarowego wektora MACIERZ_IDS (wynik)
	 * - wyswietlenie wyniku
     * - wys³anie wyniku do procesu 0
     * 
     * @return vector <vector<int>>
    */
	void run (string nazwa);
	
    vector < vector<int> > loadFile (string nazwa);
	
    void display(vector<Rec> v);
	
};



#endif	/* PARSER_H  */

