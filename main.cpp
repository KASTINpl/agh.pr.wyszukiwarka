/*
 * File:   main.cpp
 * Author: studentN2
 *
 * Created on 23 maj 2013, 17:45
 * 
 * reczne kompilowanie programu (po zainstalowaniu openMPI):
 * mpiCC main.cpp Rec.cpp EngineArray.cpp EngineSort.cpp EngineRec.cpp Parser.cpp Timer.cpp -o main && mpirun -np 5 ./main
 */
using namespace std;

#include <cstdlib>
#include <iostream>
#include <vector>

#include "mpi.h"

#include "Timer.h"
#include "Rec.h"
#include "Parser.h"
#include "EngineArray.h"
#include "EngineRec.h"
#include "EngineSort.h"

/*
 * 
 * main.cpp - plik główny - wspólny dla wszystkich
 * 
 */
#define DESC  1
#define ASC  0

/**
 * Podział zadań na procesy:
 * 0 => main.cpp
 * 1 => Parser
 * 2 => EngineArray
 * 3 => EngineRec
 * 4 => EngineSort
 * 
 */
int main(int argc, char** argv) {
	
	/* open MPI */
  MPI::Init ( argc, argv );
  int id = MPI::COMM_WORLD.Get_rank ( ); // ID procesu
  int p_all = MPI::COMM_WORLD.Get_size ( ); // liczba wszystkich procesow
  
	//----------------------------------
	
/*
    vector< vector<int> > MACIERZ_IDS;
    vector<int> IDS;
    vector<Rec> RECS;
    */
    
  cout << "Prace zaczyna proces: " << id << " (wszystkich "<<p_all<<") " <<endl;
  
		Parser p;                           // Mateusz
		EngineArray eArray; 			// Krzysiek
		EngineRec eRec;                  // Monika
		EngineSort eSort;               // Sylwia
		
  switch (id) {//id procesu
	  case 1:
		p.run("dane_wejsciowe.txt");
	  break;//1
	  case 2:
		eArray.run();
	  break; // 2
	  case 3:
		eRec.run();
	  break; // 3
	  case 4:
		eSort.run();
	  break; // 4
	  default: // proces 0 - main
	  
		 // =====  czekaj na wynik z procesu 4
	int r_buffer[2];
	MPI::COMM_WORLD.Recv ( r_buffer, 2, MPI::INT, 4, 3 ); // zmianna, rozmiar, typ, nadawca, tag, status
	
	if (r_buffer[1] != 0) { cout << "dopuszczalna tabela tylko 1 wymiarowa!"; return 1; }
	
	int* tmp_ids=new int[r_buffer[0]];
	int* tmp_notes=new int[r_buffer[0]];
	
	vector<Rec> RECS;
	// odczyt liczb
    MPI::COMM_WORLD.Recv(tmp_ids, r_buffer[0], MPI::INT, 4, 3); // tabela, rozmiar, typ, adresat, tag
	MPI::COMM_WORLD.Recv(tmp_notes, r_buffer[0], MPI::INT, 4, 3);
	
	// generuj RECS z otrzymanych wiadomosci
	for (int i=0;i<r_buffer[0];i++) {//i
		Rec r(tmp_ids[i], tmp_notes[i]);
		RECS.insert(RECS.end(), r);
	}//i
	
	// wyswietl RECS
	
	p.display(RECS);
	
    // ======= ---
		
	  break;//0
  }//id procesu

    // koniec MPI
    MPI::Finalize ( );
    
    return 0;
}

