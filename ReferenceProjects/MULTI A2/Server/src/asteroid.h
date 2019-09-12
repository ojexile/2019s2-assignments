#ifndef _ASTEROID_H
#define _ASTEROID_H


class _Asteroid {
    private:
        int ID;
        float x;
        float y;
        float velocity_x;
        float velocity_y;
        float velocity_angular;
		
        // Lab 12. Part 1. Step 1.2 Add collision checking codes in the server
        int image_size;

    public:
        _Asteroid( int ID, float x, float y, float velocity_angular );
        ~_Asteroid();

    public:
        void SetID( int ID ) { this->ID = ID; }
        void SetX( float x ) { this->x = x; }
        void SetY( float y ) { this->y = y; }
        void SetVelocityX( float velocity_x ) { this->velocity_x = velocity_x; }
        void SetVelocityY( float velocity_y ) { this->velocity_y = velocity_y; }
        void SetVelocityAngular( float velocity_angular ) { this->velocity_angular = velocity_angular; }
        void SetImageSize( int size ) { this->image_size = size; }

        int   GetID( void ) { return ID; }
        float GetX( void ) { return x; }
        float GetY( void ) { return y; }
        float GetVelocityX( void ) { return velocity_x; }
        float GetVelocityY( void ) { return velocity_y; }
        float GetVelocityAngular( void ) { return velocity_angular; }
        int   GetImageSize( void ) { return image_size; }
		float lastnetworkupdate;

    public:
        void Update( float timedelta, float sprite_width, float sprite_height );

};


#endif