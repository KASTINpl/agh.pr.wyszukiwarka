/* 
 * File:   EngineSort.cpp
 * Author: Sylwia
 * 
 * Created on 3 czerwiec 2013, 21:27
 */

#include <iostream>
#include <vector>
#include "EngineSort.h"
#include "Rec.h"
#include "Timer.h"



vector<Rec> EngineSort::sort(vector<Rec> RECS) {
    Timer count_time; 
	count_time.start();
	int x = RECS.size();
	int* tmp_val1=new int[x];
	int* tmp_valsort=new int[x];
	for (int i=0;i<RECS.size();i++)
	{
		tmp_val1[i]=RECS[i].getID();
		tmp_valsort[i]=RECS[i].getNote();
	}
	Rec tempRec;
	vector<Rec> r;

	for( int i = 0; i < x; i++ )
    {
        for( int j = 0; j < x - 1; j++ )
        {
            if( tmp_valsort[ j ] > tmp_valsort[ j + 1 ] )
			{
                 swap( tmp_valsort[ j ], tmp_valsort[ j + 1 ] );
				 swap( tmp_val1[ j ], tmp_val1[ j + 1 ] );
			}
        }
    }


	for( int i = 0; i < x; i++ )
	{
		tempRec.setID(tmp_val1[i]); 
		tempRec.setNote(tmp_valsort[i]);
		r.push_back(tempRec);
	}


	r.push_back(tempRec);
	count_time.stop(); 
	cout << "EngineSort::sort() czas: " << count_time.getElapsedTimeInMicroSec() << " qs \n";

    return r;
}



void EngineSort::run(){
	int wymiary[2];
	/*
	* odbiera wymiary tablicy z procesu 3
	*/
	MPI::COMM_WORLD.Recv(wymiary, 2, MPI::INT, 3, 3);
	int x=wymiary[0];

	Rec tempRec;
	vector<Rec> tmp;
	int* tmp_val1=new int[x];
	int* tmp_val2=new int[x];
	/*
	* odbiera tablicę od procesu 3
	*/
	MPI::COMM_WORLD.Recv(tmp_val1, x, MPI::INT, 3, 3);
	MPI::COMM_WORLD.Recv(tmp_val2, x, MPI::INT, 3, 3);
	for (int i=0;i<x;i++)
	{
		tempRec.setID(tmp_val1[i]); 
		tempRec.setNote(tmp_val2[i]);
		tmp.push_back(tempRec);
	}
	
	/*
	* sortuje vector tmp i zapisuje do vectora result
	*/
	
	
	vector<Rec> result=this->sort(tmp);

	/*
	* wysyła informację o wymiarach przerobionej tablicy do głównego procesu
	*/
	int wymiary_out[]={result.size(), 0};
    MPI::COMM_WORLD.Send(wymiary_out, 2, MPI::INT, 0, 3); // tabela, rozmiar, typ, adresat, tag
    
	int* tmp_ids=new int[result.size()];
	int* tmp_notes=new int[result.size()];
	for (int i=0;i<result.size();i++)
	{
		tmp_ids[i]=result[i].getID();
		tmp_notes[i]=result[i].getNote();
	}
    /*
	* wysyła tablice ID i note z tablicy elementów Rec do procesu głównego
	*/
    MPI::COMM_WORLD.Send(tmp_ids, wymiary_out[0], MPI::INT, 0, 3); // tabela, rozmiar, typ, adresat, tag
	MPI::COMM_WORLD.Send(tmp_notes, wymiary_out[0], MPI::INT, 0, 3);

}
