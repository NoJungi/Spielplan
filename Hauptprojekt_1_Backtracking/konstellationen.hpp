/**************************************************************************
* Dateiename	    : konstellationen.hpp
* Projekt	        : Spielplanerstellung mittels Backtracking
* Autor	            : Nora Jungierek
* E-mail		    : nora@jungierek.de
* letzte Bearbeitung: 08.12.2020
\**************************************************************************/

#ifndef __KONSTELLATIONEN_HEADER_
#define __KONSTELLATIONEN_HEADER_

#include <iostream>
#include <vector>

// Typ Definition
typedef uint32_t TEAM_KONSTELLATION; // 32 Bit Integer um Mengen moeglichst effizient zu vergleichen

// KONSTANTEN
const int BITS = 8 * sizeof ( TEAM_KONSTELLATION );  // Anzahl von Bits, die TEAM_KONSTELLATION hat, also 32 

// FUNKTIONEN
bool ist_team_in_konstellation(const int &team, const TEAM_KONSTELLATION &t); //Rueckgabe, ob Team in einer Konstellatio/Menge ist
bool ist_konstellation_in_vektor(const TEAM_KONSTELLATION &t, const std::vector<TEAM_KONSTELLATION> &v); //Rueckgabe, ob bereits Konstellation im Vektor vorhanden

TEAM_KONSTELLATION erzeuge_konstellation(int team1, int team2, int team3); // erstellt aus drei Zahlen eine Menge als 32 Bit Integer
std::vector<TEAM_KONSTELLATION> erzeuge_alle_konstellationen(int anzahl); //erzeugt vektor mit allen 3elemtigen mengen

std::vector<int> teams_in_konstellation(const TEAM_KONSTELLATION &tk); //gibt teams als int aus TEAM_KONSTELLATION wieder

void drucke_konstellation(TEAM_KONSTELLATION t); // Gibt aus, welche Teams sich treffen
void drucke_vektor(const char* bezeichnung, std::vector<TEAM_KONSTELLATION> v, bool in_einer_zeile); // Gibt alle Konstellationen aus Vektoer wieder


#endif //__KONSTELLATIONEN_HEADER_