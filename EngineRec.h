/* 
 * File:   EngineRec.h
 * Author: Monika
 *
 * Created on 3 czerwiec 2013, 11:44
 */

#ifndef ENGINEREC_H
#define	ENGINEREC_H
#ifdef WIN32
#include "stdafx.h"
#endif
#include "mpi.h" 
#include "Rec.h" 
#include <cstdlib> 
#include <iostream> 
#include <vector> 
#include "Timer.h"
using namespace std;

/**
 * Klasa konwertujca jednowymiarowa tabele int�w na tabele obiekt�w Rec
 * 
 * @author Monika
 */

class EngineRec {

   /**
     * schemat dzia�ania klasy EngineRec: 
     * - oczekiwanie na mo�liwo�� pobrania tabeli IDS z procesu 2
     * - odczyt z tre�ci wiadomo�ci tabeli IDS
     * - uruchomienie algorytmu klasy: przekonwertowanie tabeli int�w na tabele obiekt�w typu Rec
     * - wys�anie wyniku do procesu 0
     * 
     * @return void
    */

public:
    EngineRec();
    EngineRec(const EngineRec& orig);
    virtual ~EngineRec();
	   /**
     * schemat dzia�ania metody generateRec: 
     * - w petli od 0 do ilosci elementow w tabeli IDS nast�puje przepisanie tabeli int�w na tabele obiekt�w Rec
	 * - ID w obiekcie Rec to warto�� odpowiedniego elementu w IDS
	 * - note w obiekcie Rec to losowa warto�� z przedzia�u 0.0 - 5.0
     * 
     * @return RECS - wektor obiekt�w Rec
    */
    vector<Rec> generateRec(vector<int> IDS);

	 /**
     * schemat dzia�ania metody run: 
     * - oczekiwanie na mo�liwo�� pobrania tabeli IDS z procesu nr 2
     * - odczyt z tre�ci wiadomo�ci tabeli IDS
     * - uruchomienie algorytmu klasy: przekonwertowanie tabeli int�w na tabele obiekt�w typu Rec
     * - wys�anie wyniku do procesu 0
     * 
     * @return void
    */
	void run();

     /**
     * schemat dzia�ania metody Rand: 
     * - znalezienie losowej warto�ci
     * - wykonanie odpowiednich oblicze�, aby dostosowa� wylosowan� warto�� doodpowiedniego typu i odpowiedniego zakresu
     * 
     * @return double
    */

	int Rand(int min, int max);
private:

};

#endif	/* ENGINEREC_H */

