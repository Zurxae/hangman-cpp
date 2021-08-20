#include <iostream> //console input/output
#include <fstream>  //input stream
#include <string>   //string tools
#include <stdlib.h> //srand, rand
#include <time.h>   //time
#include <ctype.h>  //tolower()

using namespace std;

class hangman
{
public:
    hangman();         //initializes animal list array from input file
    ~hangman();        //deallocates dynamic array memory
    void doubleSize(); //doubles size of dynamic array if full
    bool isFull();     //checks if array is full
    bool isPlaying();  //returns whether player wants to continue playing
    void setRound();
    int randPick();
    void play();

private:
    int size;
    int count;
    string *animalList;
    char choice;
    char *placeholder;
    int spaces;
    int key;
};

hangman::hangman()
{
    size = 1;
    count = 0;
    animalList = new string[size];

    ifstream in;
    in.open("animals.txt");

    while (!in.eof())
    {
        if (isFull())
            doubleSize();
        getline(in, animalList[count]);
        for (char i : animalList[count])
            animalList[count] = tolower(animalList[count][i]);
        count++;
    }
    in.close();
}

void hangman::doubleSize()
{
    size *= 2;
    string *temp = new string[size];
    for (int i = 0; i < count; i++)
    {
        temp[i] = animalList[i];
    }
    animalList = temp;
}

bool hangman::isFull()
{
    return size == count;
}

bool hangman::isPlaying()
{
    cout << endl
         << "-----------------------------------" << endl
         << "Would you like to play again (Y/N)?" << endl
         << "-----------------------------------" << endl;
    cin >> choice;
    if (choice == 'y' || choice == 'Y')
        return true;
    return false;
}

void hangman::setRound()
{
    key = randPick();
    spaces = 0;
    placeholder = new char[animalList[key].length()];
    for (char i : animalList[key])
    {
        if (animalList[key][i] == ' ')
        {
            placeholder[i] = ' ';
            spaces++;
        }
        placeholder[i] = '_';
    }
}

int hangman::randPick()
{
    return rand() / ((RAND_MAX / count) + 1);
}

void hangman::play()
{
    setRound();
    char guess;
    int unknown = animalList[key].length() - spaces;
    while (unknown > 0)
    {
        cout << animalList[key] << endl;
        for (char i : animalList[key])
            cout << placeholder[i] << ' ';
        cout << endl
             << "Please enter your guess: ";
        cin >> guess;
        for (char i : animalList[key])
        {
            if (guess == animalList[key][i])
            {
                placeholder[i] = animalList[key][i];
                unknown--;
            }
        }
    }
}

hangman::~hangman()
{
    delete[] animalList;
}

int main()
{
    hangman game;

    //Initialize random seed
    srand(time(NULL));

    cout << endl
         << "-----------------------------------------" << endl
         << "Welcome to my hangman game and good luck!" << endl
         << "-----------------------------------------" << endl;
    do
    {
        //cout << endl
        //     << "currently playing" << endl;
        game.play();
    } while (game.isPlaying());

    cout << endl
         << "Thanks for playing" << endl;
    return 0;
}