/* 
 * File:   Rec.cpp
 * Author: kastin
 * 
 * Created on 28 maj 2013, 12:58
 */

#include "Rec.h"

Rec::Rec(int ID, int note) {
    this->ID=ID;
    this->note=note;
}

Rec::Rec(const Rec& orig) {
    this->ID=orig.ID;
    this->note=orig.note;
}
void Rec::setID(int ID){
	this->ID=ID;
}
void Rec::setNote(int note){
	this->note=note;
}
int Rec::getID(){
	return ID;
}
int Rec::getNote(){
	return note;
}
