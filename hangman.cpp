#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    int size = 1;
    int count = 0;
    string *animalList = new string[size];
    ifstream in;
    in.open("animals.txt");
    while (!in.eof())
    {
        if (size == count)
        {
            size *= 2;
            string *temp = new string[size];
            for (int i = 0; i < count; i++)
            {
                temp[i] = animalList[i];
            }
            animalList = temp;
            delete[] temp;
        }
        getline(in, animalList[count]);
        cout << animalList[count] << endl;
        count++;
    }
    in.close();
    //for (int i = 0; i < 20; i++)
    //{
    //    cout << animalList[i] << endl;
    //}

    return 0;
}