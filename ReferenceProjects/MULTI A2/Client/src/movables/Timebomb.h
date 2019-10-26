#ifndef _TIMEBOMB_H_
#define _TIMEBOMB_H_
#pragma once


#include "movables.h"

class Timebomb : public Movables
{
    private:
		int ownerid;
		float timer;
		std::unique_ptr<hgeFont> font_;
    public:
		Timebomb( float startx,
                  float starty,
				  int shipID); 
        ~Timebomb();

    public:
		void SetTimer(float _timer) { timer = _timer; }
		int  GetTimer(void) { return timer; }
		void SetOwnerID(int _ownerid) { ownerid = _ownerid; }
		int  GetOwnerID(void) { return ownerid; }

		bool isDone;

    public:
        void Render();
};


#endif
