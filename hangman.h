#include <iostream> //console input/output
#include <fstream>  //input stream
#include <string>   //string tools
#include <stdlib.h> //srand, rand
#include <time.h>   //time for rand function
#include <ctype.h>  //tolower()

using namespace std;

class hangman
{
public:
    hangman();         //initializes animal list array from input file
    ~hangman();        //deallocates dynamic array memory
    void intro();      //Introduces user to game
    void doubleSize(); //doubles size of dynamic array if full
    bool isFull();     //checks if array is full
    bool isPlaying();  //returns whether player wants to continue playing
    void setRound();
    void guessFilter(char guessList[], char &guess, int &guessCount); //Inputs and removes repeated guess from going through character matching
    int randPick();                                                   //Picks random index from array of animals
    void drawMan(const int lives);                                    //Draws status of hanging man depending on # of lives
    void charMatcher(char guess, int &unknown, int &lives);           //Checks if guess matches any letter in chosen word
    void displayWin();
    void displayLoss();
    void play(); //Inclues call to randPick(), setRound(), drawMan(), and has game logic;
    void outro();

private:
    int size;           //capacity of animalList array
    int count;          //# of animals in animalList array
    string *animalList; //array of animals
    char *placeholder;  //output for user to see progress on guessing word
    int spaces;         //# of spaces in chosen word
    int key;            //random chosen word index
};