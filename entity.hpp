#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <time.h>
#include <chrono>
#include <sstream>

using namespace sf;
using std::cout;
using std::endl;
using std::string;


#pragma once

class Entity {
protected:
    float x, y;
    float length, width;
    Shape * body;

public:
    Entity(float _x, float _y, float _length, float _width) : x(_x), y (_y), length(_length), width(_width) {}

    float getX(){return x;}
    float getY(){return y;}
    float getLength(){return length;}
    float getWidth(){return width;}

    virtual void setX(float _x){x = _x;}
    virtual void setY(float _y){y = _y;}
    virtual void setSize(float _length, float _width){ length = _length; width = _width; }

};