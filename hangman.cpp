#include "hangman.h"

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
        for (int i = 0; i < animalList[count].length(); i++)
            animalList[count][i] = tolower(animalList[count][i]);
        count++;
    }
    in.close();
}

void hangman::intro()
{
    cout << endl
         << "-----------------------------------------" << endl
         << "Welcome to my hangman game." << endl
         << "The possible answers will all be animals." << endl
         << "Good luck!" << endl
         << "-----------------------------------------" << endl;
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
    char choice;
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
    for (int i = 0; i < animalList[key].length(); i++)
    {
        if (static_cast<int>(animalList[key][i]) == 32) //Ascii value for [SPACE]
        {
            placeholder[i] = ' ';
            spaces++;
        }
        else
        {
            placeholder[i] = '_';
        }
    }
}

int hangman::randPick()
{
    return rand() / ((RAND_MAX / count) + 1);
}

void hangman::guessFilter(char guessList[], char &guess, int &guessCount)
{
    bool guessFound = true;

    while (guessFound)
    {
        cout << endl
             << endl
             << "Please enter your guess: ";
        cin >> guess;
        guess = tolower(guess);
        guessFound = false;

        for (int i = 0; i < guessCount; i++)
        {
            if (guess == guessList[i])
            {
                cout << endl
                     << "----------------------------------"
                     << endl
                     << "Letter already guessed. Try again."
                     << endl
                     << "----------------------------------"
                     << endl;
                guessFound = true;
                break;
            }
        }
    }
    guessList[guessCount] = guess;
    guessCount++;
}

void hangman::drawMan(int lives)
{
    /*
    Drawings/code from:
    http://www.cplusplus.com/forum/beginner/2439/
    User: "chosen1"
    */
    switch (lives)
    {
    case 1:
        cout << " ___________" << endl;
        cout << " |         }" << endl;
        cout << " |       \\  " << endl;
        cout << "_|______________" << endl;
        break;
    case 2:
        cout << " ___________" << endl;
        cout << " |         }" << endl;
        cout << " |       \\ 0 " << endl;
        cout << "_|______________" << endl;
        break;
    case 3:
        cout << " ___________" << endl;
        cout << " |         }" << endl;
        cout << " |       \\ 0 /" << endl;
        cout << "_|______________" << endl;
        break;
    case 4:
        cout << " ___________" << endl;
        cout << " |         }" << endl;
        cout << " |       \\ 0 /" << endl;
        cout << " |         |" << endl;
        cout << "_|______________" << endl;
        break;
    case 5:
        cout << " ___________" << endl;
        cout << " |         }" << endl;
        cout << " |       \\ 0 /" << endl;
        cout << " |         |" << endl;
        cout << " |        /  " << endl;
        cout << "_|______________" << endl;
        break;
    case 6:
        cout << " ___________" << endl;
        cout << " |         }" << endl;
        cout << " |       \\ 0 /" << endl;
        cout << " |         |" << endl;
        cout << " |        / \\ " << endl;
        cout << "_|______________" << endl;
    }
}

void hangman::charMatcher(char guess, int &unknown, int &lives)
{
    bool found = false;
    for (int i = 0; i < animalList[key].length(); i++)
    {
        if (guess == animalList[key][i])
        {
            placeholder[i] = animalList[key][i];
            found = true;
            unknown--;
        }
    }
    if (!found)
        lives--;
}

void hangman::displayWin()
{
    cout << endl
         << "************************"
         << endl
         << "Congradulations! You win"
         << endl
         << "************************"
         << endl;
}

void hangman::displayLoss()
{
    cout << endl
         << "Answer: " << animalList[key] << endl
         << endl
         << ":( :( :( :( :("
         << endl
         << "Sucks to suck"
         << endl
         << ":( :( :( :( :("
         << endl;
}

void hangman::play()
{
    setRound();
    char guess;
    char guessList[26];
    int guessCount = 0;

    int unknown = animalList[key].length() - spaces;
    int lives = 6;

    while (unknown > 0 && lives > 0)
    {
        drawMan(lives);

        for (int i = 0; i < animalList[key].length(); i++)
            cout << placeholder[i] << ' ';

        guessFilter(guessList, guess, guessCount); //also inputs guess

        charMatcher(guess, unknown, lives);
    }

    if (unknown == 0)
        displayWin();
    else
        displayLoss();
}

void hangman::outro()
{
    cout << endl
         << "##################"
         << endl
         << "Thanks for playing"
         << endl
         << "##################"
         << endl;
}

hangman::~hangman()
{
    delete[] animalList;
}