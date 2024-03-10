#include "button.hpp"

#pragma once


class Calculator{
private:
    RenderWindow * win;
    Button ** buttons;
    Font font;
    float buttonSize = 0;
    Vector2u winSize;
    string screenText = "0";
    Text screen;
    int mode = 0;
    int operation = 0;
    int visualOperation = 0;
    double firstNumber = 0.0f;
    double secondNumber = 0.0f;
    bool enteredOperation = false;

public:
    Calculator(){
        win = new RenderWindow(VideoMode(400, 650), "Calculator");
        winSize = win->getSize();

        if (!font.loadFromFile("arial.ttf")) {
            // Error handling if the font fails to load
            cout << "Unable to load font\n";
            exit(0);
        }

        //create buttons
        buttons = new Button*[19];

        if(winSize.x > winSize.y){
            buttonSize = winSize.y / 4;
        } else {
            buttonSize = winSize.x / 4;
        }

        int delay = 250;

        //0 button
        buttons[0] = new Button(0, buttonSize * 5.5, (buttonSize * 2) - 1, buttonSize - 1, Color(127, 127, 125), "0", font, Color::White, Color(218, 218, 218), delay);

        //make grid number buttons
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                buttons[(i*3) + j + 1] = new Button(j * buttonSize, (2-i + 2.5) * buttonSize, buttonSize - 1, buttonSize - 1, Color(127, 127, 125), std::to_string((i*3)+j + 1), font, Color::White, Color(218, 218, 218), delay);
            }
        }

        //button .
        buttons[10] = new Button(buttonSize * 2, buttonSize * 5.5, buttonSize - 1, buttonSize - 1, Color(127, 127, 125), ".", font, Color::White, Color(218, 218, 218), delay);

        //top row buttons
        buttons[11] = new Button(0, buttonSize * 1.5, buttonSize - 1, buttonSize - 1, Color(127, 127, 125), "c", font, Color::White, Color(218, 218, 218), delay);
        buttons[12] = new Button(buttonSize, buttonSize * 1.5, buttonSize - 1, buttonSize - 1, Color(127, 127, 125), "+/-", font, Color::White, Color(218, 218, 218), delay);
        buttons[13] = new Button(buttonSize * 2, buttonSize * 1.5, buttonSize - 1, buttonSize - 1, Color(127, 127, 125), "%", font, Color::White, Color(218, 218, 218), delay);

        //side operator buttons
        buttons[14] = new Button(buttonSize * 3, buttonSize * 1.5, buttonSize - 1, buttonSize - 1, Color(231, 160, 61), "\u00F7", font, Color::White, Color(241, 191, 121), 0);
        buttons[15] = new Button(buttonSize * 3, buttonSize * 2.5, buttonSize - 1, buttonSize - 1, Color(231, 160, 61), "\u02DF", font, Color::White, Color(241, 191, 121), 0);
        buttons[16] = new Button(buttonSize * 3, buttonSize * 3.5, buttonSize - 1, buttonSize - 1, Color(231, 160, 61), "\u2212", font, Color::White, Color(241, 191, 121), 0);
        buttons[17] = new Button(buttonSize * 3, buttonSize * 4.5, buttonSize - 1, buttonSize - 1, Color(231, 160, 61), "+", font, Color::White, Color(241, 191, 121), 0);
        buttons[18] = new Button(buttonSize * 3, buttonSize * 5.5, buttonSize - 1, buttonSize - 1, Color(231, 160, 61), "=", font, Color::White, Color(241, 191, 121), delay);

        //screen   
        screen = Text();
        screen.setFont(font);
        screen.setOrigin(Vector2f(0, 0));
        screen.setPosition(Vector2f(0, 0));
        screen.setFillColor(Color::White);
        screen.setCharacterSize(80);
        screen.setString("0");

    }


    void enterNumber(int num){
        buttons[num]->click();

        //check screen text.length
        //check if just did visualOperation and clear screen
        if(enteredOperation == true){
            enteredOperation = false;
            visualOperation = 0;
            screenText = "0";
        }
        
        //size <= 10
        if(screenText.length() <= 10){
            //dont add if already 0 and entering 0
            if(!(num == 0 && screenText == "0")){
                //check if 0
                if(screenText == "0") screenText = std::to_string(num);
                else screenText += std::to_string(num);
            }
        }
        
        
    }

    void enterDecimal(){
        buttons[10]->click();

        if(enteredOperation == true){
            enteredOperation = false;
            visualOperation = 0;
            screenText = "0";
        }

        if(screenText.find('.') == std::string::npos){
            if(screenText.length() <= 10) screenText += ".";
        }
    }

    void enterClear(){
        buttons[11]->click();
        screenText = "0";
        visualOperation = 0;
        enteredOperation = false;
        mode = 0;
        operation = 0;
    }

    void enterNegator(){
        buttons[12]->click();
        if(std::stod(screenText) != 0){        
            float a = std::stod(screenText);
            a = a * - 1;
            std::stringstream ss;
            ss << a;
            screenText = ss.str();
            //enteredOperation = true;
        }
    }

    void enterPercentage(){
        if(std::stod(screenText) != 0){ 
            buttons[13]->click();
            float a = std::stod(screenText);
            a = a / 100;
            std::stringstream ss;
            ss << a;
            screenText = ss.str();
            enteredOperation = true;
        }
    }

    void enterOperation(int type){
        switch(type){
            case 0:
            break;
            case 1:
                buttons[14]->click();
                visualOperation = 1;
                if(!enteredOperation){
                    enteredOperation = true;
                    processOp();
                } else {
                    operation = visualOperation;
                }
                
                break;
            case 2:
                buttons[15]->click();
                visualOperation = 2;
                if(!enteredOperation){
                    enteredOperation = true;
                    processOp();
                } else {
                    operation = visualOperation;
                }
                
                break;
            case 3:
                buttons[16]->click();
                visualOperation = 3;
                if(!enteredOperation){
                    enteredOperation = true;
                    processOp();
                } else {
                    operation = visualOperation;
                }
                            
                break;
            case 4:
                buttons[17]->click();
                visualOperation = 4;
                if(!enteredOperation){
                    enteredOperation = true;
                    processOp();
                } else {
                    operation = visualOperation;
                }
                
                break;
        }
    }

    void enterEqual(){
        buttons[18]->click();
        visualOperation = 0;
        enteredOperation = true;

        //calculate
        //save second number and complete operation
        secondNumber = std::stod(screenText);

        //complete calculation
        float temp;
        std::stringstream ss;
        switch(operation){
            case 1:
                temp = firstNumber / secondNumber;
                ss << temp;
                screenText = ss.str();
                break;
            case 2:
                temp = firstNumber * secondNumber;
                ss << temp;
                screenText = ss.str();
                break;
            case 3:
                temp = firstNumber - secondNumber;
                ss << temp;
                screenText = ss.str();
                break;
            case 4:
                temp = firstNumber + secondNumber;
                ss << temp;
                screenText = ss.str();
                break;
        }
        mode = 0;
        firstNumber = std::stod(screenText);
        secondNumber = 0.0f;
        operation = 0;
    }

    void processOp(){
        if(mode == 0){
            //save first number
            firstNumber = std::stod(screenText);
            operation = visualOperation;

            mode = 1;
        } else if(mode == 1){
            //save second number and complete operation
            secondNumber = std::stod(screenText);

            //complete calculation
            float temp;
            std::stringstream ss;
            switch(operation){
                case 1:
                    temp = firstNumber / secondNumber;
                    ss << temp;
                    screenText = ss.str();
                    break;
                case 2:
                    temp = firstNumber * secondNumber;
                    ss << temp;
                    screenText = ss.str();
                    break;
                case 3:
                    temp = firstNumber - secondNumber;
                    ss << temp;
                    screenText = ss.str();
                    break;
                case 4:
                    temp = firstNumber + secondNumber;
                    ss << temp;
                    screenText = ss.str();
                    break;
            }

            firstNumber = std::stod(screenText);
            
        }
    }


    void run(){
        while(win->isOpen()){
            Event e;
            while(win->pollEvent(e)){
                if(e.type == Event::Closed){
                    win->close();
                }

                //click
                if (e.type == sf::Event::MouseButtonPressed){
                    Vector2i mousePosition = Mouse::getPosition(*win);

                    for(int i = 0; i < 10; i++){
                        if(buttons[i]->isClicked(mousePosition)){
                            enterNumber(i);
                        }
                    }
                    
                    //.
                    if(buttons[10]->isClicked(mousePosition)) enterDecimal();

                    //c
                    if(buttons[11]->isClicked(mousePosition)) enterClear();
                    
                    //+/-
                    if(buttons[12]->isClicked(mousePosition)) enterNegator();                        

                    //%
                    if(buttons[13]->isClicked(mousePosition)) enterPercentage();

                    // /
                    if(buttons[14]->isClicked(mousePosition)) enterOperation(1);

                    // *
                    if(buttons[15]->isClicked(mousePosition)) enterOperation(2);

                    // -
                    if(buttons[16]->isClicked(mousePosition)) enterOperation(3);

                    // +
                    if(buttons[17]->isClicked(mousePosition)) enterOperation(4);

                    // =
                    if(buttons[18]->isClicked(mousePosition)) enterEqual();


                    //copy when clicked
                    if(e.mouseButton.y < (buttonSize * 1.5) && e.mouseButton.y > 0 && e.mouseButton.x > 0 && e.mouseButton.x < (int) winSize.x){
                        // Use SFML-Network to copy the text to the clipboard
                        Clipboard::setString(screen.getString());
                    }

                }

                //few different options for next line
                if (e.type == sf::Event::KeyPressed) {
                    //numbers
                    if(e.key.code >= 26 && e.key.code <= 35 && !e.key.shift){
                        char key = (char) (e.key.code - 26 + 48);
                        enterNumber((int) key - 48);
                    }

                    //.
                    if(e.key.code == 50) enterDecimal();

                    //+
                    if(e.key.code == 55) enterOperation(4);

                    //-
                    if(e.key.code == 56) enterOperation(3);

                    //*
                    if(e.key.shift && e.key.code == 34) enterOperation(2);

                    // / 
                    if(e.key.code == 52) enterOperation(1);

                    // c
                    if(e.key.code == 2) enterClear();

                    // =
                    if(e.key.code == 58) enterEqual();

                    //backspace
                    if(e.key.code == 59){
                        //check string > 0
                        if(screenText.length() > 0){
                            screenText.pop_back();
                            //set to 0 if need be
                            if(screenText == "") screenText = "0";
                        }
                    }

                }


                if (e.type == sf::Event::Resized){
                    // update the view to the new size of the window
                    sf::FloatRect visibleArea(0, 0, e.size.width, e.size.height);
                    win->setView(sf::View(visibleArea));

                    // Enforce the minimum size
                    if (e.size.width < 200 || e.size.height < 325) {
                        win->setSize(sf::Vector2u(std::max(e.size.width, 200u), std::max(e.size.height, 325u)));
                    }

                    // Enforce aspect ratio
                    if((float) e.size.height / (float) e.size.width != 1.625){
                        win->setSize(sf::Vector2u(e.size.width, (int)((float) (e.size.width) * 1.625)));
                    }
                }
            }

            //update buttons
            for(int i = 0; i < 19; i++){
                buttons[i]->update();
            }

            //visualOperation buttons
            if(visualOperation != 0){
                buttons[((int) visualOperation) + 13]->click();
            }

            //screen text display
            screen.setString(screenText);
            if(screenText.length() <= 6){
                screen.setCharacterSize(80);
            } else {
                screen.setCharacterSize(60);
            }

            sf::FloatRect textBounds = screen.getLocalBounds();
            float textX = winSize.x - textBounds.width - 20;
            float textY = (buttonSize * 1.5) - 20 - textBounds.top - textBounds.height;
            
            screen.setPosition(textX, textY);

            


            //clear
            win->clear(Color::Black);
            
            //draw entities
            for(int i = 0; i < 19; i++){
                buttons[i]->draw(win);
            }

            win->draw(screen);

            

            //display
            win->display();
        }

        return;
    }


};