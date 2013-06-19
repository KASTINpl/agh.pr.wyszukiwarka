/* 
 * File:   EngineArray.h
 * Author: Krzysiek
 *
 * Created on 3 czerwiec 2013, 11:26
 */

#ifndef ENGINEARRAY_H
#define	ENGINEARRAY_H

using namespace std;
#include <iostream>
#include <vector>
#include "Timer.h"
#include "mpi.h"
#include <omp.h>

/**
 * Klasa przetwarzająca tabele dwuwymiarową na wektor jednowymiarowy zawierający duplikaty wybrane z całej otrzymanej tabeli
 * 
 * @author Krzysiek
 */
class EngineArray {
	/**
	 * tabela 2d gdzie każdy wiersz to wektor liczb (ID rekordów). 
	 * Wektor odpowiada ciągowi rekordów będących wynikami wyszukiwania danego słowa.
	 */
	vector< vector<int> > MACIERZ_IDS;
	
public:
    EngineArray(){};
    virtual ~EngineArray(){};
    
    /**
     * schemat działania klasy: 
     * - oczekiwanie na możliwość pobrania tabeli MACIERZ_IDS z procesu ID=1
     * - odczyt z treści wiadomości tabeli MACIERZ_IDS
     * - uruchomienie algorytmu klasy : znajdywanie duplikatów i wygenerowanie tabeli IDS (wynik)
     * - wysłanie wyniku do procesu 0
     * 
     * @return void
    */
    void run();
    
    /**
     * na podstawie MACIERZ_IDS wygeneruj wynik w postaci wektora liczb, które będą się powtarzać w całej tabeli
     * 
     * @return IDS - wektor z liczbami
     */
    vector<int> arrayUnique();
    
private:
	/**
	 * wybierz duplikaty z wektorów podanych jako argumenty
	 * 
	 * @return wektor unikalnych liczb
	 * @param v1 wektor liczb
	 * @param v2 wektor liczb
	 */
    vector<int> vectorUnique(vector<int> *v1, vector<int> *v2);
};

#endif	/* ENGINEARRAY_H */
