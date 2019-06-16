#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <unistd.h>

int numberOfRound = 1; // The number of rounds played.
int numberToFlashPerRound = 2; // The number of colors to flash per round.
int speed, score = 0; // Store the speed and the score of the game.
bool runOnce = true; // A dummy variable to run the code only once.
int currColorToFlash; // Store the color from the randomly generated function.
int currNumOfColorHavedFlashed = 0; // Store the current number of flashes.
bool endOfEachRound = false; // An indication of each round's ending, and wait for the inputs.
std::vector<int> orderOfNumbers; // Storing the colors that have been flashed in order.
sf::Font font;
sf::Text text, numberText, simonSign;
sf::RectangleShape shapeGreen, shapeRed, shapeYellow, shapeBlue, ScoreBoard; // Store the definitions of the shapes.
sf::SoundBuffer greenBuffer, redBuffer, yellowBuffer, blueBuffer; // The buffers of each color, import the sound file.
sf::Sound greenSound, redSound, yellowSound, blueSound; // Sounds of each color.
sf::Event event;

void gameLogic();
void shapesDefinition();
void MenuScreen();
void sound();

int main() {

    shapesDefinition(); // Define The Default Colors Of The Shapes
    MenuScreen(); // Launch the menu screen.
    sound(); // Start the sound function.
    
    // Generate the main game screen.
    sf::RenderWindow gameScreen(sf::VideoMode(1080, 610), "Simon Game", sf::Style::Titlebar | sf::Style::Close);
    
    while (gameScreen.isOpen()) {
        
        while (gameScreen.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                gameScreen.close();
        }
        
        // Start the game logic after the first run.(Displaying the colors)
        if (!runOnce)
            gameLogic();
        
        // Displaying the number of rounds and score.
        text.setString("Round: " + std::to_string(numberOfRound) + "\nScore: " + std::to_string(score));
        
        while (currNumOfColorHavedFlashed <= numberToFlashPerRound){
            // update the game
            gameScreen.clear(sf::Color(33,47,60));
            gameScreen.draw(simonSign);
            gameScreen.draw(ScoreBoard);
            gameScreen.draw(text);
            gameScreen.draw(numberText);
            gameScreen.draw(shapeGreen);
            gameScreen.draw(shapeRed);
            gameScreen.draw(shapeYellow);
            gameScreen.draw(shapeBlue);
            gameScreen.display();
            gameScreen.setFramerateLimit(350);
            usleep(speed);
            
            if (runOnce){
                usleep(3000000);
                runOnce = false;
                std::cout << "GAME START" << std::endl;
            }else
                ++currNumOfColorHavedFlashed; // Increment The Number Of Flashes Per Round
            
            // Set Every Shape To Normal Colors
            if (currColorToFlash == 1) {
                shapeGreen.setFillColor(sf::Color::Green);
                greenSound.play();
            }else if (currColorToFlash == 2){
                shapeRed.setFillColor(sf::Color::Red);
                redSound.play();
            }else if (currColorToFlash == 3){
                shapeYellow.setFillColor(sf::Color::Yellow);
                yellowSound.play();
            }else if (currColorToFlash == 4){
                blueSound.play();
                shapeBlue.setFillColor(sf::Color::Blue);
            }
            
            usleep(speed);
            if (currColorToFlash != 0)
                orderOfNumbers.push_back(currColorToFlash);
            gameLogic();
            
            
        } // Exit Of Each Round
        
        // Change everything back to normal after each round.
        if (gameScreen.isOpen()){
            shapeGreen.setFillColor(sf::Color::Green);
            shapeRed.setFillColor(sf::Color::Red);
            shapeYellow.setFillColor(sf::Color::Yellow);
            shapeBlue.setFillColor(sf::Color::Blue);
            gameScreen.clear(sf::Color(33,47,60));
            gameScreen.draw(simonSign);
            gameScreen.draw(ScoreBoard);
            gameScreen.draw(text);
            gameScreen.draw(numberText);
            gameScreen.draw(shapeGreen);
            gameScreen.draw(shapeRed);
            gameScreen.draw(shapeYellow);
            gameScreen.draw(shapeBlue);
            gameScreen.display();
        }
        
        // Cheat Code
        for (auto c : orderOfNumbers)
            std::cout << c << " ";
        std::cout << std::endl;
        
        bool KeyAldPressed = false; // Indication that tell if the key is already pressed.
        int key = 0; // The key input(1,2,3,4).
        
        for (int i = 0; i <= numberToFlashPerRound; ++i){
            key= 0;
            KeyAldPressed = false;
            // Change The Color To Normal
            shapeGreen.setFillColor(sf::Color::Green);
            shapeRed.setFillColor(sf::Color::Red);
            shapeYellow.setFillColor(sf::Color::Yellow);
            shapeBlue.setFillColor(sf::Color::Blue);
            gameScreen.clear(sf::Color(33,47,60));
            gameScreen.draw(simonSign);
            gameScreen.draw(ScoreBoard);
            gameScreen.draw(text);
            gameScreen.draw(numberText);
            gameScreen.draw(shapeGreen);
            gameScreen.draw(shapeRed);
            gameScreen.draw(shapeYellow);
            gameScreen.draw(shapeBlue);
            gameScreen.display();
            
            while (!KeyAldPressed){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)){
                    key = 1;
                    shapeGreen.setFillColor(sf::Color::White);
                    gameScreen.draw(shapeGreen);
                    greenSound.play();
                    gameScreen.display();
                    usleep(200000);
                    shapeGreen.setFillColor(sf::Color::Green);
                    gameScreen.draw(shapeGreen);
                    gameScreen.display();
                    KeyAldPressed = true;
                }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)){
                    key = 2;
                    shapeRed.setFillColor(sf::Color::White);
                    gameScreen.draw(shapeRed);
                    redSound.play();
                    gameScreen.display();
                    usleep(200000);
                    shapeRed.setFillColor(sf::Color::Red);
                    gameScreen.draw(shapeRed);
                    gameScreen.display();
                    KeyAldPressed = true;
                }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)){
                    key = 3;
                    shapeYellow.setFillColor(sf::Color::White);
                    gameScreen.draw(shapeYellow);
                    yellowSound.play();
                    gameScreen.display();
                    usleep(200000);
                    shapeYellow.setFillColor(sf::Color::Yellow);
                    gameScreen.draw(shapeYellow);
                    gameScreen.display();
                    KeyAldPressed = true;
                }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)){
                    key = 4;
                    shapeBlue.setFillColor(sf::Color::White);
                    gameScreen.draw(shapeBlue);
                    blueSound.play();
                    gameScreen.display();
                    usleep(200000);
                    shapeBlue.setFillColor(sf::Color::Blue);
                    gameScreen.draw(shapeBlue);
                    gameScreen.display();
                    KeyAldPressed = true;
                }
                // If the Key is pressed, validate the input.
                if (KeyAldPressed){
                    if (key != orderOfNumbers[i]){
                        std::cout << "GAME OVER" << std::endl;
                        usleep(400000);
                        gameScreen.clear(sf::Color(33,47,60));
                        sf::Text gameOverText;
                        gameOverText.setFont(font);
                        gameOverText.setCharacterSize(150);
                        gameOverText.setString("GAME OVER");
                        gameOverText.setFillColor(sf::Color::White);
                        gameOverText.move(sf::Vector2f(130,330));
                        text.setCharacterSize(100);
                        text.move(sf::Vector2f(-370,-30));
                        gameScreen.draw(text);
                        gameScreen.draw(gameOverText);
                        gameScreen.display();
                        usleep(5000000);
                        gameScreen.close();
                        return 0;
                    }else
                        KeyAldPressed = true;
                } // Exit [if(keyAldPressed)]
                
            } // Exit [while(!notKeyPressed)]
            
            //  Change the colors back to normal
            shapeGreen.setFillColor(sf::Color::Green);
            shapeRed.setFillColor(sf::Color::Red);
            shapeYellow.setFillColor(sf::Color::Yellow);
            shapeBlue.setFillColor(sf::Color::Blue);
            gameScreen.draw(shapeGreen);
            gameScreen.draw(shapeRed);
            gameScreen.draw(shapeYellow);
            gameScreen.draw(shapeBlue);
            gameScreen.display();
            
        } // Exit For loop
        
        if (numberToFlashPerRound < 4) // Flashes Only 5 Times After A Number Of Rounds
            ++numberToFlashPerRound;
        score += currColorToFlash * 2;
        currNumOfColorHavedFlashed = 0;
        ++numberOfRound;
        orderOfNumbers.clear();
        usleep(500000);
        
    } // Exit of while the window is open.
    
} // Exit of main.

void shapesDefinition()
{
    // Load the font.
    font.loadFromFile("res/fonts/FontFile.ttf");
    // Score Board
    ScoreBoard.setSize(sf::Vector2f(400, 500));
    ScoreBoard.setFillColor(sf::Color(93,109,126));
    ScoreBoard.setOutlineThickness(7);
    ScoreBoard.setOutlineColor(sf::Color::Black);
    ScoreBoard.move(sf::Vector2f(650,50));
    // Text in score board
    text.setFont(font);
    text.setCharacterSize(60);
    text.setFillColor(sf::Color::White);
    text.move(sf::Vector2f(690,100));
    // Numbers under each shape
    numberText.setFont(font);
    numberText.setCharacterSize(40);
    numberText.setFillColor(sf::Color::White);
    numberText.move(sf::Vector2f(70,510));
    numberText.setString("1         2         3        4");
    // Simon word above the colors
    simonSign.setString("Simon Game");
    simonSign.setFont(font);
    simonSign.setCharacterSize(80);
    simonSign.move(sf::Vector2f(60,45));
    simonSign.setStyle(sf::Text::Bold);
    simonSign.setFillColor(sf::Color::White);
    // Shape Green
    shapeGreen.setSize(sf::Vector2f(110,300));
    shapeGreen.move(sf::Vector2f(30,200));
    shapeGreen.setFillColor(sf::Color::Green);
    // Shape Red
    shapeRed.setSize(sf::Vector2f(110,300));
    shapeRed.move(sf::Vector2f(170,200));
    shapeRed.setFillColor(sf::Color::Red);
    // Shape Yellow
    shapeYellow.setSize(sf::Vector2f(110,300));
    shapeYellow.move(sf::Vector2f(310,200));
    shapeYellow.setFillColor(sf::Color::Yellow);
    // Shape Blue
    shapeBlue.setSize(sf::Vector2f(110,300));
    shapeBlue.move(sf::Vector2f(450,200));
    shapeBlue.setFillColor(sf::Color::Blue);
    
}


void sound()
{
    /// Load the sounds from files.
    greenBuffer.loadFromFile("res/sound/green.wav");
    redBuffer.loadFromFile("res/sound/red.wav");
    yellowBuffer.loadFromFile("res/sound/yellow.wav");
    blueBuffer.loadFromFile("res/sound/blue.wav");
    // Set the sounds from the buffers.
    greenSound.setBuffer(greenBuffer);
    redSound.setBuffer(redBuffer);
    yellowSound.setBuffer(yellowBuffer);
    blueSound.setBuffer(blueBuffer);
}


void gameLogic(){
    /// Generate a random number
    currColorToFlash = (rand() % 4) + 1;
    /// Change the color shape to white for selected shape.
    switch (currColorToFlash) {
        case 1:
            shapeGreen.setFillColor(sf::Color::White);
            break;
        case 2:
            shapeRed.setFillColor(sf::Color::White);
            break;
        case 3:
            shapeYellow.setFillColor(sf::Color::White);
            break;
        case 4:
            shapeBlue.setFillColor(sf::Color::White);
            break;
    }
}


void MenuScreen(){
    
    // Menu screen.
    sf::RenderWindow startScreen(sf::VideoMode(640, 360), "Simon Game", sf::Style::Titlebar | sf::Style::Close);
    
    sf::Text welcomeWord;
    welcomeWord.setFont(font);
    welcomeWord.setCharacterSize(45);
    welcomeWord.setFillColor(sf::Color::Black);
    welcomeWord.setString("Welcome To Simon Game\n\nSelect The Level:\n[1] Easy\n[2] Medium\n[3] Hard");
    
    while (startScreen.isOpen()) {
        sf::Event event;
        while (startScreen.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    startScreen.close();
            }
        }
        startScreen.clear(sf::Color::White);
        startScreen.draw(welcomeWord);
        startScreen.display();
        // Wait for the key press
        while (true) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
                speed = 400000;
                break;
            }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
                speed = 300000;
                break;
            }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
                speed = 250000; //(miliseconds)
                break;
            }
        }
        startScreen.close();
    }
}

