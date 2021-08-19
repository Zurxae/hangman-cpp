#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class hangman
{
public:
    hangman();
    ~hangman();
    void doubleSize();
    bool isFull();

private:
    int size;
    int count;
    string *animalList;
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
        cout << animalList[count] << endl;
        count++;
    }
    in.close();
    for (int i = 0; i < 20; i++)
    {
        cout << animalList[i] << endl;
    }
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

int main()
{

    return 0;
}