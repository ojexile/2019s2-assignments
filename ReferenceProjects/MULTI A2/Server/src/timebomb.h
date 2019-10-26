#ifndef _TIMEBOMB_H
#define _TIMEBOMB_H


class _Timebomb {
    private:
        int ID;
        float x;
        float y;
		float timer;

    public:
		_Timebomb( int ID, float x, float y);
        ~_Timebomb();

    public:
        void SetID( int ID ) { this->ID = ID; }
        void SetX( float x ) { this->x = x; }
        void SetY( float y ) { this->y = y; }
		void SetTimer(float timer) { this->timer = timer; }

		float GetTimer(void) { return timer; }
        int   GetID( void ) { return ID; }
        float GetX( void ) { return x; }
        float GetY( void ) { return y; }
		float lastnetworkupdate;

    public:
        void Update(float timedelta);

};


#endif