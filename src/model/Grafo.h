#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "../view/menuMaker.h"
#include "General.h"

using namespace std;

struct Arista
{
    int destino;
    int peso;
};

class Grafo
{
public:
    Grafo();
    Grafo(int vectores, vector<vector<Arista>> listaAdyacencias);
    static Grafo crearGrafo();
    bool exportG(const string &nombreArchivo) const;
    void printG(bool cls);
    bool importG(const string &nombreArchivo);

    void setEmptyDefault();
    int getV() { return V; };
    vector<vector<Arista>> getlistaAdy() { return listaAdy; };

    int size() { return listaAdy.size(); };
    vector<Arista> getAristas(int i) { return listaAdy[i]; };

private:
    int V;
    vector<vector<Arista>> listaAdy;
};

Grafo::Grafo()
{
}

Grafo::Grafo(int vectores, vector<vector<Arista>> listaAdyacencias)
{
    V = vectores;
    listaAdy = listaAdyacencias;
}

void Grafo::setEmptyDefault()
{
    Arista a;
    a.peso = 1;
    a.destino = 1;
    vector<Arista> vc;
    vc.push_back(a);

    listaAdy.clear();
    listaAdy.push_back(vc);

    vc.clear();
    a.destino = 0;
    vc.push_back(a);
    listaAdy.push_back(vc);

    V = 2;
}

Grafo Grafo::crearGrafo()
{
    Grafo g;
    bool isDirigido;
    bool isPesado;

    isDirigido = menuMaker::createYesNoQuestion("El grafo es Dirigido?");

    isPesado = menuMaker::createYesNoQuestion("El grafo tiene Pesos?");

    cout << "Ingrese el numero de vertices: ";
    int value = General::inputInteger();
    if (value <= -1)
    {
        Grafo error;
        error.setEmptyDefault();
        cout << "Se introdujo un valor inválido, se cancela la creación" << endl;
        return error;
    }
    else
        g.V = value;

    // Inicializar la lista de adyacencia con pesos
    g.listaAdy.resize(g.V);

    // Permitir al usuario ingresar las aristaes y pesos entre vertices
    int origen, destino, peso;
    int contador = 0;
    cout << "Recuerde que los vertices se comienzan a nombrar enumerando desde 0!\n";
    do
    {
        contador++;
        cout << ("Ingrese la arista #" + to_string(contador) + " (origen): ");

        int value = General::inputInteger();
        if (value <= -1 || value >= g.getV())
        {
            Grafo error;
            error.setEmptyDefault();
            cout << "Se introdujo un valor inválido, se cancela la creación" << endl;
            system("pause");
            return error;
        }
        else
            origen = value;

        cout << ("Ingrese la arista #" + to_string(contador) + " (destino): ");

        value = General::inputInteger();
        if (value <= -1)
        {
            Grafo error;
            error.setEmptyDefault();
            cout << "Se introdujo un valor inválido, se cancela la creación" << endl;
            system("pause");
            return error;
        }
        else
            destino = value;

        if (isPesado || value >= g.getV())
        {
            cout << ("Ingrese la arista #" + to_string(contador) + " (peso): ");

            value = General::inputInteger();
            peso = value;
        }
        else
            peso = 1;

        // Asumimos que los vertices estan numerados de 0 a V-1
        if (origen >= 0 && origen < g.V && destino >= 0 && destino < g.V)
        {
            g.listaAdy[origen].push_back({destino, peso});

            string endpart;
            isPesado ? endpart = " (peso: " + to_string(peso) + ")\n" : endpart = "\n";

            if (isDirigido && origen!=destino)
                cout << ">Se añadio la arista V" + to_string(origen) + "->V" + to_string(destino) + endpart;
            else
            {
                g.listaAdy[destino].push_back({origen, peso}); // Para grafos no dirigidos
                cout << ">Se añadio la arista V" + to_string(origen) + "<->V" + to_string(destino) + endpart;

                // Otras opciones:
                /*
                1)
                cout << ">Se añadio la arista V" + to_string(origen) + "-V" + to_string(destino) + endpart;
                2)
                cout << ">Se añadio la arista V" + to_string(origen) + "->V" + to_string(destino) + endpart;
                cout << ">Se añadio la arista V" + to_string(destino) + "->V" + to_string(origen) + endpart;
                */
            }
        }
        else
        {
            cout << "Vertices no validos. Intentelo de nuevo.\n";
        }

    } while (menuMaker::createYesNoQuestion("Desea agregar otra arista?"));

    return g;
}

bool Grafo::exportG(const string &nombreArchivo) const
{
    ofstream archivo(nombreArchivo);

    if (archivo.is_open())
    {
        archivo << V << "\n";

        for (int i = 0; i < V; ++i)
        {
            archivo << i << ": ";
            for (const Arista &arista : listaAdy[i])
            {
                archivo << arista.destino << "p" << arista.peso << " ";
            }
            archivo << "\n";
        }

        archivo.close();
        cout << "Grafo con pesos exportado exitosamente.\n";
        return true;
    }
    cout << "No se pudo abrir el archivo para exportar el grafo con pesos.\n";
    return false;
}

void Grafo::printG(bool cls)
{
    cout << endl;
    if (cls)
        system("cls");
    menuMaker::createSeparator("#");
    cout << endl;
    cout << "Cantidad de Nodos: " << V << "\n";

    for (int i = 0; i < V; ++i)
    {
        cout << i << ": ";
        for (const Arista &arista : listaAdy[i])
        {
            cout << arista.destino << "(p:" << arista.peso << ") ";
        }
        cout << "\n";
    }

    cout << endl;
    menuMaker::createSeparator("#");
}

bool Grafo::importG(const string &nombreArchivo)
{
    V = 0;
    listaAdy.clear();
    ifstream archivo(nombreArchivo);

    if (archivo.is_open())
    {
        archivo >> V;
        listaAdy.resize(V);

        string linea;

        getline(archivo, linea); // Consumir la linea en blanco despues de V

        while (getline(archivo, linea))
        {
            stringstream ss(linea);
            int vertice;
            char separador;

            ss >> vertice >> separador; // Leer el numero de vertice y el separador ":"

            Arista arista;
            while (ss >> arista.destino >> separador >> arista.peso)
            {
                listaAdy[vertice].push_back(arista);
            }
        }

        archivo.close();
        cout << "Grafo con pesos importado exitosamente.\n";
        return true;
    }
    cout << "No se pudo abrir el archivo para importar el grafo con pesos.\n";
    return false;
}

#endif // CLASS_H
