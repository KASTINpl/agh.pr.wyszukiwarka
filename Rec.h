/* 
 * File:   Rec.h
 * Author: kastin
 *
 * Created on 28 maj 2013, 12:58
 */

#ifndef REC_H
#define REC_H

#ifdef WIN32
#include "stdafx.h"
#endif

class Rec {
    int ID;
    int note;
public:
    Rec() {};
    Rec(int ID, int note);
    Rec(const Rec& orig);
    virtual ~Rec() {};
	void setID(int ID);
	void setNote(int note);
	int getID();
	int getNote();

private:

};

#endif  /* REC_H */
