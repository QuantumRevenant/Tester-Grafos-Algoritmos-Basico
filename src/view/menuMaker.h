#ifndef MENUMAKER_H
#define MENUMAKER_H

#include "../model/General.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*

*/

class menuMaker
{
public:
    menuMaker(/* args */);
    ~menuMaker();
    static int createOptionMenu(vector<string> options, string title);
    static bool createYesNoQuestion(string q);
    static string createInputField(string str);
    static void createSeparator(string sep);
};

void menuMaker::createSeparator(string sep)
{
    sep=sep.length()==0?" ":sep;
    for (int i = 0; i < 100/(int)sep.length(); i++)
        cout << sep;

    cout << endl;
}

string menuMaker::createInputField(string str)
{
    string opt;
    cout << str << ": ";
    cin >> opt;

    return opt;
}

bool menuMaker::createYesNoQuestion(string q)
{
    char opt;
    cout << q << " (Y/n): ";
    cin >> opt;

    string x = (opt == 'y' || opt == 'Y') ? ">Se Introdujo SI" : ">Se Introdujo NO";
    cout << x << endl;

    return (opt == 'y' || opt == 'Y');
}
int menuMaker::createOptionMenu(vector<string> options, string title = "")
{
    int opt;
    do
    {
        system("cls");
        if (title != "")
        {
            cout << "\n\t" << title << endl;
            createSeparator("=");
        }
        for (size_t i = 0; i < options.size(); i++)
        {
            cout << "\t[" + to_string(i + 1) + "] " + options[i] << endl;
        }
        cout << "\t[0] Salir" << endl;
        cout << "\t> ";
        opt = General::inputInteger();
    } while (opt < 0 || opt > (int)options.size());

    return opt - 1;
}

#endif