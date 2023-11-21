#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "../view/menuMaker.h"

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
    void exportG(const string &nombreArchivo) const;
    void printG(bool cls);
    void importG(const string &nombreArchivo);

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

Grafo Grafo::crearGrafo()
{
    Grafo g;
    char opt;
    bool isDirigido;
    bool isPesado;

    cout << "El grafo es Dirigido? (s/n): ";
    cin >> opt;

    isDirigido = (opt == 's' || opt == 'S');
    isDirigido ? cout << ">El grafo SI es dirigido\n" : cout << ">El grafo NO es dirigido\n";

    cout << "El grafo tiene pesos? (s/n): ";
    cin >> opt;

    isPesado = (opt == 's' || opt == 'S');
    isPesado ? cout << ">El grafo SI es pesado\n" : cout << ">El grafo NO es pesado\n";

    cout << "Ingrese el numero de vertices: ";
    cin >> g.V;

    // Inicializar la lista de adyacencia con pesos
    g.listaAdy.resize(g.V);

    // Permitir al usuario ingresar las aristaes y pesos entre vertices
    int origen, destino, peso;
    char continuar;
    int contador = 0;
    cout << "Recuerde que los vertices se comienzan a nombrar enumerando desde 0!\n";
    do
    {
        contador++;
        cout << ("Ingrese la arista #" + to_string(contador) + " (origen): ");
        cin >> origen;
        cout << ("Ingrese la arista #" + to_string(contador) + " (destino): ");
        cin >> destino;
        if (isPesado)
        {
            cout << ("Ingrese la arista #" + to_string(contador) + " (peso): ");
            cin >> peso;
        }
        else
            peso = 1;

        // Asumimos que los vertices estan numerados de 0 a V-1
        if (origen >= 0 && origen < g.V && destino >= 0 && destino < g.V)
        {
            g.listaAdy[origen].push_back({destino, peso});

            string endpart;
            isPesado ? endpart = " (peso: " + to_string(peso) + ")\n" : endpart = "\n";

            if (isDirigido)
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

        cout << "Desea agregar otra arista? (s/n): ";
        cin >> continuar;

    } while (continuar == 's' || continuar == 'S');

    return g;
}

void Grafo::exportG(const string &nombreArchivo) const
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
                archivo << arista.destino << "-" << arista.peso << " ";
            }
            archivo << "\n";
        }

        archivo.close();
        cout << "Grafo con pesos exportado exitosamente.\n";
    }
    else
    {
        cout << "No se pudo abrir el archivo para exportar el grafo con pesos.\n";
    }
}

void Grafo::printG(bool cls)
{
    cout<<endl;
    if(cls)
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

void Grafo::importG(const string &nombreArchivo)
{
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
    }
    else
    {
        cout << "No se pudo abrir el archivo para importar el grafo con pesos.\n";
    }
}

#endif // CLASS_H
