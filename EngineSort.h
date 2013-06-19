/* 
 * File:   EngineSort.h
 * Author: kastin
 *
 * Created on 3 czerwiec 2013, 21:27
 */

#ifndef ENGINESORT_H
#define	ENGINESORT_H

using namespace std;
#include <iostream>
#include <vector>
#include "Rec.h"
#include "mpi.h"

/**
* Klasa wczytująca wartosci z poprzedniego procesu i sortująca je
* 
* @author Sylwia Firszt
*
* schemat działania klasy: 
* - wczytywanie wartosci z poprzedniego procesu
* - przeksztalcanie wartości na vector<Rec>
* - sortowanie wartości
* - przeksztalcanie wyniku na tablicę
* - wysylanie wyniku do procesu 0
* 
* @return void
*/

class EngineSort {
public:

/**
* Metdoda sort sortuje podany wektor typu Rec utworzony z odebranych wartości z poprzedniego procesu
*
* @return vector<Rec>
*/
    vector<Rec> sort(vector<Rec> RECS);
	
	
	
/**
* Metoda run:		
* - wczytywanie wartosci z poprzedniego procesu
* - przeksztalcanie wartości na vector<Rec>
* - sortowanie wartości (wywołanie metody sort)
* - przeksztalcanie wyniku na tablicę
* - wysylanie wyniku do procesu 0
* 
* @return void
*/		
	void run();
		
private:


};

#endif	/* ENGINESORT_H */
