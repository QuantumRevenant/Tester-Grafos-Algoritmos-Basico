#include "menuMaker.h"
#include "../model/Grafo.h"
#include "../model/Timer.h"
#include "../model/ShortestPath.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*

*/

#define CARPETAEXPORT "../data/export/"
#define CARPETAIMPORT "../data/import/"

int main()
{
    Grafo grafo;
    int opt;
    bool grafoExist = false;
    do
    {
        opt=-1;
        string x = grafoExist ? "Existe" : "No Existe";
        opt = menuMaker::createOptionMenu({"Crear Grafo", "Consultar Grafo", "Evaluar Camino mas Rapido", "Importar Grafo", "Exportar Grafo"}, "Menu Principal\t-Grafo: " + x);
        Grafo tempGrafo;

        switch (opt)
        {
        case -1:
            cout << "Muchas Gracias por usar el programa <3" << endl;
            system("pause");
            break;
        case 0:
            do
            {
                tempGrafo = Grafo::crearGrafo();
                system("cls");
                cout<<"Grafo ingresado:"<<endl;
                tempGrafo.printG(false);
                if (menuMaker::createYesNoQuestion("Desea guardar ese grafo?, si ya existe uno en la memoria este lo reemplazara (es irreversible)"))
                {
                    grafo = tempGrafo;
                    grafoExist = true;
                    break;
                }
            } while (menuMaker::createYesNoQuestion("Desea crear otro grafo?"));
            system("pause");
            break;

        case 1:
            if(grafoExist)
                grafo.printG(true);
            system("pause");
            break;

        case 2:
            // Escoger el subPrograma
            system("pause");
            break;

        case 3:
            if (menuMaker::createYesNoQuestion("Seguro que deseas importar al grafo actual?,\nsi ya existe uno en la memoria este lo reemplazara (es irreversible)"))
            {
                string x = CARPETAIMPORT;
                x.erase(0, 2);
                cout << endl;
                menuMaker::createSeparator("-");
                cout << endl;
                cout << "[?]\tNo te olvides que el archivo se importara desde la direccion:" << endl
                     << "~/[Ruta al WORKSPACE]" + x + "." << endl;
                cout << "[!]\tRecuerda que si pones el nombre de un archivo con formato invalido el programa puede fallar." << endl
                     << endl;
                bool yaExiste=grafoExist;
                grafoExist=grafo.importG(CARPETAIMPORT + menuMaker::createInputField("Introduce el nombre del archivo de destino") + ".txt");
                grafoExist=yaExiste?true:grafoExist;
            }
            system("pause");
            break;

        case 4:
            if (menuMaker::createYesNoQuestion("Seguro que deseas exportar el grafo actual?"))
            {
                string x = CARPETAEXPORT;
                x.erase(0, 2);
                cout << endl;
                menuMaker::createSeparator("-");
                cout << endl;
                cout << "[?]\tNo te olvides que el archivo se exportara a la direccion:" << endl
                     << "~/[Ruta al WORKSPACE]" + x + "." << endl;
                cout << "[!]\tRecuerda que si pones el nombre de un archivo existente este se sobreescribira (no puede revertirse)." << endl
                     << endl;
                grafo.exportG(CARPETAEXPORT + menuMaker::createInputField("Introduce el nombre del archivo de destino") + ".txt");
            }
            system("pause");
            break;

        default:
            cout << "Error... Valor inválido";
            system("pause");
            break;
        }
    } while (opt != -1);
    // Grafo g;
    // Timer timer;
    // timer.saveStart();

    // // g=Grafo::crearGrafo();
    // // g.exportG(CARPETAEXPORT"export.txt");
    // g.importG(CARPETAEXPORT"export.txt");
    // g.exportG(CARPETAEXPORT"exportimp.txt");

    // Timer::printTime(timer.getElapsedSecondsNow());

    // int origen=0;
    // int destino=5;

    // Camino result = ShortestPath::dijkstra(g, origen, destino);

    // ShortestPath::printResultado(result,origen,destino);

    // system("pause");

    return 0;
}