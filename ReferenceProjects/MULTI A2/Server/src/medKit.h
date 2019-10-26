#ifndef _MEDKIT_H
#define _MEDKIT_H


class _Medkit {
    private:
        int TakenShipID;
        float x;
        float y;

    public:
		_Medkit( int TakenShipID, float x, float y);
        ~_Medkit();

    public:
        void SetID( int ID ) { this->TakenShipID = TakenShipID; }
        void SetX( float x ) { this->x = x; }
        void SetY( float y ) { this->y = y; }

        int   GetID( void ) { return TakenShipID; }
        float GetX( void ) { return x; }
        float GetY( void ) { return y; }

};


#endif