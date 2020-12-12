/**************************************************************************
* Dateiename	    : main.cpp
* Projekt	        : Main zur Spielplanerstellung mittels Backtracking
* Autor	            : Nora Jungierek
* E-mail		    : nora@jungierek.de
* letzte Bearbeitung: 08.12.2020
\**************************************************************************/

/* ZEITMESSUNG

    - 4 Mannschaften ca.
    - 6 Mannschaften ca. 0.001s
    - 7 Mannschaften ca. 0.26s
    Spielplan anzahl=14
    {0,1,2}
    {0,1,3}
    {0,2,4}
    {0,3,5}
    {0,4,6}
    {0,5,6}
    {1,2,5}
    {1,3,6}
    {1,4,5}
    {1,4,6}
    {2,3,4}
    {2,3,6}
    {2,5,6}
    {3,4,5}

    - 9 Mannschaften ca. 1000s

    -vielleicht kann man noch die Mengen/Konstellationen vorher permutieren, so dass andere Reihenfolge der Pfade des Backtrackings hat
    -> hatte ich ausprobiert aber noch nichts wirklich gutes hinbekommen
*/

#include"spielplan.hpp"

int main(){

    int anzahl_mannschaften;


    // EINGABE ANZAHL MANNSCHAFTEN
    std::cout << "Wie viele Teams gibt es? ";
    std::cin >> anzahl_mannschaften;
    try {
        if(!std::cin || anzahl_mannschaften < 4){
            throw 1;
        }
        else if((anzahl_mannschaften * (anzahl_mannschaften - 1)) % 3 != 0){
            throw 1.0;
        } 
    }
    catch(int& e){
        std::cout << "FEHLER: Sie muessen eine natuerliche Zahl groesser 3 eingeben." << std::endl;
        exit(0);
    }
    catch(double& e){
        std::cout << "FEHLER: Fuer diese Mannschafts Anzahl gibt es keinen gueltigen Spielplan." << std::endl;
        exit(0);
    }
    catch(...){
        std::cout << "FEHLER: unbekannt" << std::endl;
        exit(0);
    }
    

    spielplan(anzahl_mannschaften); //in spielplan.cpp

    return 0;
}