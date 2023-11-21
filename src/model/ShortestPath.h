#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include "Grafo.h"
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

/*

*/

typedef pair<int, vector<int>> Camino;

class ShortestPath
{
private:
    /*private data*/
public:
    ShortestPath();
    ~ShortestPath();

    static void printResultado(Camino camino, int origen, int destino);
    static Camino dijkstra(Grafo &grafo, int origen, int destino);
    static Camino bellmanFord(Grafo &grafo, int origen, int destino);
};

void ShortestPath::printResultado(Camino camino, int origen, int destino)
{
     int distancia = camino.first;
    vector<int> caminoCorto = camino.second;

    cout << "camino mas corto desde el nodo " << origen << " al nodo " << destino << ": ";
    for (size_t i = 0; i < caminoCorto.size(); ++i) {
        cout << caminoCorto[i];
        if (i != caminoCorto.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;

    cout << "Distancia recorrida: " << distancia << endl;
}

Camino ShortestPath::dijkstra(Grafo &grafo, int origen, int destino)
{
    int numNodos = grafo.size();
    vector<int> distancias(numNodos, numeric_limits<int>::max());
    vector<int> previos(numNodos, -1); // Almacena el nodo previo en el Camino mas corto

    distancias[origen] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(distancias[origen], origen));

    while (!pq.empty())
    {
        int nodoActual = pq.top().second;
        pq.pop();

        if (nodoActual == destino)
        {
            break; // Llegamos al nodo destino, terminamos el algoritmo
        }

        for (const Arista &arista : grafo.getAristas(nodoActual))
        {
            int newdistancia = distancias[nodoActual] + arista.peso;
            if (newdistancia < distancias[arista.destino])
            {
                distancias[arista.destino] = newdistancia;
                previos[arista.destino] = nodoActual;
                pq.push(make_pair(distancias[arista.destino], arista.destino));
            }
        }
    }

    // Verificar si se llego al destino
    if (previos[destino] == -1)
    {
        // No hay camino valido
        return make_pair(-1, vector<int>());
    }

    vector<int> caminoCorto;
    int actual = destino;
    while (actual != -1)
    {
        caminoCorto.push_back(actual);
        actual = previos[actual];
    }

    reverse(caminoCorto.begin(), caminoCorto.end()); // Invertimos el vector para que quede en orden

    return make_pair(distancias[destino], caminoCorto);
}

Camino ShortestPath::bellmanFord(Grafo &grafo, int origen, int destino)
{
    int numNodos = grafo.size();
    vector<int> distancias(numNodos, numeric_limits<int>::max());
    vector<int> previos(numNodos, -1); // Almacena el nodo previo en el Camino mas corto

    distancias[origen] = 0;

    // Relajacion de las aristas repetidas veces
    for (int i = 0; i < numNodos - 1; ++i)
    {
        for (int u = 0; u < numNodos; ++u)
        {
            for (const Arista &arista : grafo.getAristas(u))
            {
                int v = arista.destino;
                int peso = arista.peso;
                if (distancias[u] != numeric_limits<int>::max() && distancias[u] + peso < distancias[v])
                {
                    distancias[v] = distancias[u] + peso;
                    previos[v] = u;
                }
            }
        }
    }

    // Verificar la existencia de ciclos negativos
    for (int u = 0; u < numNodos; ++u)
    {
        for (const Arista &arista : grafo.getAristas(u))
        {
            int v = arista.destino;
            int peso = arista.peso;
            if (distancias[u] != numeric_limits<int>::max() && distancias[u] + peso < distancias[v])
            {
                // Ciclo negativo encontrado, no se puede garantizar el resultado correcto
                return Camino(-1, vector<int>());
            }
        }
    }

    // Construir el camino
    vector<int> caminoCorto;
    int actual = destino;
    while (actual != -1)
    {
        caminoCorto.push_back(actual);
        actual = previos[actual];
    }

    reverse(caminoCorto.begin(), caminoCorto.end()); // Invertimos el vector para que quede en orden

    return Camino(distancias[destino], caminoCorto);
}
#endif