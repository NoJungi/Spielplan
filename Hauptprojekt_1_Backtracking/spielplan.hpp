/**************************************************************************
* Dateiename	    : spielplan.hpp
* Projekt	        : Spielplanerstellung mittels Backtracking
* Autor	            : Nora Jungierek
* E-mail		    : nora@jungierek.de
* letzte Bearbeitung: 08.12.2020
\**************************************************************************/

#ifndef __SPIELPLAN_HEADER_
#define __SPIELPLAN_HEADER_

#include "Timer.hpp"
#include "konstellationen.hpp"
#include <random>

const bool DEBUG = false;

bool vollstaendig(const int& anzahl_m, const std::vector<TEAM_KONSTELLATION> &plan);  //teste, ob bereits ein gueltiger Plan
bool spielanzahl_erreicht(const TEAM_KONSTELLATION tk, int sta[BITS][BITS]);  //testet, ob die teams schon 2 mal gegeneinander gespielt haben
void aktualisiere_statistik(int sta[BITS][BITS], const TEAM_KONSTELLATION tk, const int zaehler); 
bool erzeuge_spielplan(const int anzahl_m, std::vector<TEAM_KONSTELLATION> alle, TEAM_KONSTELLATION* plan, int sta[BITS][BITS], const int start_index);

int spielplan(int anzahl_m);



#endif //__SPIELPLAN_HEADER_