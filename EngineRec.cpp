/* 
 * File:   EngineRec.cpp
 * Author: Monkia
 * 
 * Created on 3 czerwiec 2013, 11:44
 */

#include "EngineRec.h"


EngineRec::EngineRec() {
   
}

EngineRec::EngineRec(const EngineRec& orig) {
}

EngineRec::~EngineRec() {
}
vector<Rec> EngineRec::generateRec(vector<int> IDS){
	/*
	 * tworzy tabelę, którą później zwróci
	*/
	vector<Rec> result;

	/*
	* pętla od 0 do ilości elementów w tabeli IDS
	* obiekt tymczasowy typu Rec
	*/
	Rec tmp;
	/*
	* rozpoczyna liczenie czasu
	*/
	Timer count_time; 
	count_time.start();
	for (int i=0;i<IDS.size();i++)
	{
		/*
		* wypełnia zawartość obiektu tmp (ID i note), a następnie dodaje ten obiekt do wektora obiektów Rec
	    */
		tmp.setID(IDS[i]);
		tmp.setNote(Rand(1, 10));
		result.push_back(tmp);
	}
	/*
	* zakończono liczenie czasu
	*/
	count_time.stop(); 
	cout << "EngineRec::generateRec() czas: " << count_time.getElapsedTimeInMicroSec() << " qs \n";
	/*
	* zwraca wypełniony wektor obiektów Rec
	*/
    return result;
}
void EngineRec::run(){
	int wymiary[2];
	/*
	* odbiera wymiary tablicy z wątku głównego
	*/
	MPI::COMM_WORLD.Recv(wymiary, 2, MPI::INT, 2, 1);
	int x=wymiary[0];
	vector<int> tmp;
	int* tmp_val=new int[x];
		/*
	* odbiera tablicę od wątku głównego
	*/
	MPI::COMM_WORLD.Recv(tmp_val, x, MPI::INT, 2, 2);
	for (int i=0;i<x;i++)
	{
		tmp.push_back(tmp_val[i]);
	}
	
	cout << "Proces 3 odebral IDS" <<endl;
	/*
	* wysyła odebraną tablicę do głównej metody klasy, która przekonwertuje elementy typu int na Rec
	*/
	vector<Rec> result=this->generateRec(tmp);

	/*
	* wysyła informację o wymiarach przerobionej tablicy do głównego wątku
	*/
	int wymiary_out[]={result.size(), 0};
    MPI::COMM_WORLD.Send(wymiary_out, 2, MPI::INT, 4, 3); // tabela, rozmiar, typ, adresat, tag
    
	int* tmp_ids=new int[result.size()];
	int* tmp_notes=new int[result.size()];
	for (int i=0;i<result.size();i++)
	{
		tmp_ids[i]=result[i].getID();
		tmp_notes[i]=result[i].getNote();
	}
    /*
	* wysyła tablice ID i note z tablicy elementów Rec do wątku głównego
	*/
    MPI::COMM_WORLD.Send(tmp_ids, wymiary_out[0], MPI::INT, 4, 3); // tabela, rozmiar, typ, adresat, tag
	MPI::COMM_WORLD.Send(tmp_notes, wymiary_out[0], MPI::INT, 4, 3);

}
int EngineRec::Rand(int min, int max)
{
	/*
	* zwraca losową wartość całkowitą z podanego przedziału
	*/
	//srand (time(NULL));
	int result=rand()%max+min;
    return result;
}
