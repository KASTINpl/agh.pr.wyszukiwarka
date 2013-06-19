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
 * Klasa konwertujca jednowymiarowa tabele intów na tabele obiektów Rec
 * 
 * @author Monika
 */

class EngineRec {

   /**
     * schemat dzia³ania klasy EngineRec: 
     * - oczekiwanie na mo¿liwoœæ pobrania tabeli IDS z procesu 2
     * - odczyt z treœci wiadomoœci tabeli IDS
     * - uruchomienie algorytmu klasy: przekonwertowanie tabeli intów na tabele obiektów typu Rec
     * - wys³anie wyniku do procesu 0
     * 
     * @return void
    */

public:
    EngineRec();
    EngineRec(const EngineRec& orig);
    virtual ~EngineRec();
	   /**
     * schemat dzia³ania metody generateRec: 
     * - w petli od 0 do ilosci elementow w tabeli IDS nastêpuje przepisanie tabeli intów na tabele obiektów Rec
	 * - ID w obiekcie Rec to wartoœæ odpowiedniego elementu w IDS
	 * - note w obiekcie Rec to losowa wartoœæ z przedzia³u 0.0 - 5.0
     * 
     * @return RECS - wektor obiektów Rec
    */
    vector<Rec> generateRec(vector<int> IDS);

	 /**
     * schemat dzia³ania metody run: 
     * - oczekiwanie na mo¿liwoœæ pobrania tabeli IDS z procesu nr 2
     * - odczyt z treœci wiadomoœci tabeli IDS
     * - uruchomienie algorytmu klasy: przekonwertowanie tabeli intów na tabele obiektów typu Rec
     * - wys³anie wyniku do procesu 0
     * 
     * @return void
    */
	void run();

     /**
     * schemat dzia³ania metody Rand: 
     * - znalezienie losowej wartoœci
     * - wykonanie odpowiednich obliczeñ, aby dostosowaæ wylosowan¹ wartoœæ doodpowiedniego typu i odpowiedniego zakresu
     * 
     * @return double
    */

	int Rand(int min, int max);
private:

};

#endif	/* ENGINEREC_H */

