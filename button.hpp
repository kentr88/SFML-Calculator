#include "entity.hpp"

#pragma once

class Button : public Entity {
private:
    Text * text;
    Font font;
    Color color;
    Color clickColor;
    bool clicked = false;
    std::chrono::_V2::system_clock::time_point startClick;
    int delay;
public:
    Button(float _x, float _y, float _length, float _width, Color _color, string _character, Font _font, Color _textColor, Color _clickColor, int _delay): Entity(_x, _y, _length, _width){
        font = _font;
        color = _color;
        clickColor = _clickColor;
        delay = _delay;

        body = new RectangleShape(Vector2f(length, width));
        body->setFillColor(color);
        body->setPosition(Vector2f(x, y));
        body->setOrigin(Vector2f(0, 0));
        

        text = new Text();
        text->setFont(font);
        text->setOrigin(Vector2f(0, 0));
        text->setPosition(Vector2f(x, y));
        text->setFillColor(_textColor);
        text->setCharacterSize(30);
        if(_character == "\u00F7"){
            text->setString(L"\u00F7");
            text->setCharacterSize(35);            
        } else if(_character == "\u2212"){
            text->setString(L"\u2212");
        } else if(_character == "\u02DF"){
            text->setString(L"\u02DF");
            text->setCharacterSize(40);
        } else {
            text->setString(_character);
        }
        

        // Calculate the position to center the text inside the rectangle
        sf::FloatRect textBounds = text->getLocalBounds();
        text->setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
        text->setPosition(body->getPosition().x + length / 2, body->getPosition().y + width / 2);
    }

    ~Button(){
        delete body;
        delete text;
    }


    string getString(){ return text->getString(); }
    void setString(string _character){ text->setString(_character); }


    void setX(float _x){
        x = _x;
        body->setPosition(Vector2f(x, y));
        text->setPosition(Vector2f(x, y));
    }
    void setY(float _y){
        y = _y;
        body->setPosition(Vector2f(x, y));
        text->setPosition(Vector2f(x, y));
    }


    void setSize(float _length, float _width){
        length = _length;
        width = _width;
        delete body;

        body = new RectangleShape(Vector2f(length, width));
        body->setFillColor(color);
        body->setPosition(Vector2f(x, y));
        body->setOrigin(Vector2f(0, 0));
    }

    void draw(RenderWindow * win){
        win->draw(*body);
        win->draw(*text);         
    }

    bool isClicked(Vector2f mouse){
        if(mouse.x >= x && mouse.x <= x + length){
            if(mouse.y >= y && mouse.y <= y + width){
                return true;
            }
        }
        return false;
    }

    bool isClicked(Vector2i mouse){
        if(mouse.x >= x && mouse.x <= x + length){
            if(mouse.y >= y && mouse.y <= y + width){
                return true;
            }
        }
        return false;
    }

    void update(){
        if(clicked){
            if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startClick).count() > delay){
                body->setFillColor(color);
            }
        }
    }

    void click(){
        clicked = true;
        startClick = std::chrono::high_resolution_clock::now();

        //change button appearance
        body->setFillColor(clickColor);
    }


};
