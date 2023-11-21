#ifndef GENERAL_H
#define GENERAL_H

#include <iostream>
#include <string>
#include <iostream>
#include <sstream>
#include <limits>

using namespace std;

/*

*/

class General
{
public:
    General(/* args */);
    ~General();
    static bool isInteger(string str);
    static bool isDouble(string str);
    static int inputInteger();
};
int General::inputInteger()
{
    string opt;
    cin >> opt;
    if(isInteger(opt))
    {
        return std::stoi(opt);
    }

    cout<<">El valor introducido no es Entero. Tomamos por defecto '-1'"<<endl;//menu Error
    system("pause");
    return -1;
}

bool General::isInteger(std::string str) {
    try {
        size_t pos;
        int valor = std::stoi(str, &pos);

        // Verificar si se consumieron todos los caracteres y no hay caracteres adicionales
        return pos == str.length()+valor-valor;
    } catch (const std::out_of_range& e) {
        return false;  // El valor es demasiado grande para ser representado como int
    } catch (const std::invalid_argument& e) {
        return false;  // No se pudo convertir a int
    }
}

bool General::isDouble(std::string str){
    try {
        size_t pos;
        double valor = std::stod(str, &pos);
        // Verificar si se consumieron todos los caracteres y no hay caracteres adicionales
        return pos == str.length()+valor-valor;
    } catch (const std::out_of_range& e) {
        return false;  // El valor es demasiado grande para ser representado como double
    } catch (const std::invalid_argument& e) {
        return false;  // No se pudo convertir a double
    }
}

General::General(/* args */)
{
}

General::~General()
{
}

#endif