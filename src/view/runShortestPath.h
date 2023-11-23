#ifndef RUNSHORTESTPATH_H
#define RUNSHORTESTPATH_H

#include <iostream>
#include <string>
#include "menuMaker.h"
#include "../model/Grafo.h"
#include "../model/Timer.h"
#include "../model/ShortestPath.h"

using namespace std;

/*

*/

void runShortestPath(Grafo grafo)
{
    int opt;
    do
    {
        system("cls");
        Timer timer;
        opt = -1;
        opt = menuMaker::createOptionMenu({"Ejecutar todos los Algoritmos", "Dijsktra", "Bellman-Ford", "Agrega otra Funcion Aqui!"}, "Evaluar camino mas rapido");
        pair<int, int> nodos;
        switch (opt)
        {
        case -1:
            cout << "Volviendo al menu principal..." << endl;
            system("pause");
            break;
        case 0:
            nodos = Grafo::introducirOrigenDestinoSPP(grafo);
            cout << nodos.first << "-" << nodos.second << endl;
            timer.saveStart();
            ShortestPath::printResultado(ShortestPath::dijkstra(grafo, nodos.first, nodos.second), nodos.first, nodos.second);
            Timer::printTime(timer.getElapsedSecondsNow());
            timer.saveStart();
            ShortestPath::printResultado(ShortestPath::bellmanFord(grafo, nodos.first, nodos.second), nodos.first, nodos.second);
            Timer::printTime(timer.getElapsedSecondsNow());
            system("pause");
            break;
        case 1:
            nodos = Grafo::introducirOrigenDestinoSPP(grafo);
            timer.saveStart();
            ShortestPath::dijkstra(grafo, nodos.first, nodos.second);
            Timer::printTime(timer.getElapsedSecondsNow());
            system("pause");
            break;
        case 2:
            nodos = Grafo::introducirOrigenDestinoSPP(grafo);
            timer.saveStart();
            ShortestPath::bellmanFord(grafo, nodos.first, nodos.second);
            Timer::printTime(timer.getElapsedSecondsNow());
            system("pause");
            break;

        case 3:
            cout << "Hola! Reemplaza esta funcion con una nueva! Recuerda agregarla en 'ShortestPath.h' y utilizar el mismo formato que las otras!" << endl;
            system("pause");
            break;

        default:
            cout << "Error... Valor inválido";
            system("pause");
            break;
            break;
        }
    } while (opt != -1);
}

#endif