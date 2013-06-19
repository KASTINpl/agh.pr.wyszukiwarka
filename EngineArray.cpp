/* 
 * File:   EngineArray.cpp
 * Author: Krzysiek
 * 
 * Created on 3 czerwiec 2013, 11:26
 */

#include "EngineArray.h"

void EngineArray::run() {
	
	/*
	 * pobierz wymiary tabeli MACIERZ_IDS
	*/
	//MPI::Status status;
	int r_buffer[2];
	MPI::COMM_WORLD.Recv ( r_buffer, 2, MPI::INT, 1, 1 ); // zmianna, rozmiar, typ, nadawca, tag, status
	
	int MACIERZ_IDS_SIZES_I = r_buffer[0]; // rozmiar tabeli z wymiarami MACIERZ_IDS
	
	//cout << "Proces 2 odebral r_buffer" <<endl;
	// tabela (1wymiar) z wymiarami MACIERZ_IDS
	int *MACIERZ_IDS_SIZES = new int[MACIERZ_IDS_SIZES_I];
	MPI::COMM_WORLD.Recv ( MACIERZ_IDS_SIZES, MACIERZ_IDS_SIZES_I, MPI::INT, 1, 1 ); // zmianna, rozmiar, typ, nadawca, tag, status
	
	/*
	 * pobierz zawartosc MACIERZ_IDS
	*/
 // printf( "MACIERZ_IDS[%d][%d]; \n", MACIERZ_IDS_I, MACIERZ_IDS_J );
	
	int *n_buff; vector<int> tmpv;
	for (int i=0;i<MACIERZ_IDS_SIZES_I;i++) { //i
		n_buff = new int[ MACIERZ_IDS_SIZES[i] ];
		MPI::COMM_WORLD.Recv ( n_buff, MACIERZ_IDS_SIZES[i], MPI::INT, 1, 2);
	
		// pobrany wiersz zapisz jako wektor
		tmpv.clear();
		for (int j=0;j<MACIERZ_IDS_SIZES[i]; j++) {//j
			tmpv.insert(tmpv.end(), n_buff[j]);
		}//j
		
		// dodaj wiersz=wektor do tabeli jako ostatni
		MACIERZ_IDS.insert(MACIERZ_IDS.end(), tmpv);
		delete[] n_buff;
	}//i
	//delete[] n_buff;
	delete[] MACIERZ_IDS_SIZES;
	
//	cout << "Proces 2 odebral MACIERZ_IDS" <<endl;
	/*
	 * algorytm klasy
	 * 
	*/
 
	vector<int> IDS;
	IDS = arrayUnique();
	
	/*
	 * wyslij wynik do procesu 3
	*/
	
	// ===== wysylaj IDS do procesu 3
	int i_buffer[] = {IDS.size(), 0};
    MPI::COMM_WORLD.Send ( i_buffer, 2, MPI::INT, 3, 1 ); // tabela, rozmiar, typ, adresat, tag
    
   
    int *IDS_A = &IDS[0]; // =(int*)vector<int>IDS
    MPI::COMM_WORLD.Send ( IDS_A, i_buffer[0], MPI::INT, 3, 2 ); // tabela, rozmiar, typ, adresat, tag
}

vector<int> EngineArray::arrayUnique() {
    vector<int> r;
    switch (MACIERZ_IDS.size()) {
        case 0:
            return r;
            break;
        case 1:
            return MACIERZ_IDS[0];
            break;
    }
    r = MACIERZ_IDS[0];
    
    
	Timer czas; 
	czas.start(); // uruchamiam stoper
		
    for (int i=1;i<MACIERZ_IDS.size();i++) {
        r = this->vectorUnique(&r, &MACIERZ_IDS[i]);
    }
    
	czas.stop(); // stoper zatrzymany
	cout << "EngineArray::arrayUnique() czas: " << czas.getElapsedTimeInMicroSec() << " qs \n"; // co tam sobie stoper nakrobal...
    
    return r;
}//--

vector<int> EngineArray::vectorUnique(vector<int> *v1, vector<int> *v2) {
    vector<int> r;
    bool vectorContain = false;
     
    #pragma omp parallel for private(vectorContain) 
    for (int i=0;i<v1->size();i++) {//i
		vectorContain = false;
		for (int ii=0;ii<v2->size();ii++) {
			if ((*v2)[ii]==(*v1)[i]) { vectorContain = true; break; }
		}
		
		if (!vectorContain) continue;
		
		#pragma omp critical
		r.insert(r.end(), (*v1)[i]);
    }//i
    
    return r;
}//--
