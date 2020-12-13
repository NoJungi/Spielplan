/**************************************************************************
* Dateiename	    : spielplan.cpp
* Projekt	        : Spielplanerstellung mittels Backtracking
* Autor	            : Nora Jungierek
* E-mail		    : nora@jungierek.de
* letzte Bearbeitung: 09.12.2020
\**************************************************************************/

#include "spielplan.hpp"

int next = 0; // Index an der die nächste Teamkonstellation im Spielplan (am Ende) eingefügt wird

bool vollstaendig(const int anzahl_mannschaften, int laenge_spielplan){
    return laenge_spielplan == anzahl_mannschaften*(anzahl_mannschaften - 1) / 3;
}

bool spielanzahl_erreicht(const TEAM_KONSTELLATION tk, int sta[BITS][BITS]){
    int teams [3] = {0};
    teams_in_konstellation(tk, teams);

    return  
        sta[teams[0]][teams[1]] > 1 ||  
        sta[teams[0]][teams[2]] > 1 ||
        sta[teams[1]][teams[2]] > 1;
}

void drucke_statistik ( int anzahl_m, int statistik [BITS][BITS] ) {

    for ( int i = 0; i < anzahl_m - 1; i++ ) {
        for ( int j = 0; j <= i; j++ ) {
            std::cout << " ";
        }
        for ( int j = i + 1; j < anzahl_m; j++ ) {
            //std::cout << "[" << i << "," << j << "]=" << statistik [i] [j] << "|";
            std::cout << statistik [i] [j];
        }
        std::cout << std::endl;
    }
}

void aktualisiere_statistik(int sta[BITS][BITS], const TEAM_KONSTELLATION tk, const int zaehler){  //zaehler: fuers addieren oder subtrahieren von der Statistik
    if(abs(zaehler) != 1){
        std::cout << "\nBOESER FEHLER, zaehler falsch z=" << zaehler << std::endl;
        exit(102);
    }
    int teams [3] = {0};
    teams_in_konstellation(tk, teams);
    //if(DEBUG) std::cout << "l=" << teams.size() << " " << teams[0] << " " << teams[1] << " " << teams[2] << std::endl;
    sta[teams[0]][teams[1]] += zaehler;
    sta[teams[0]][teams[2]] += zaehler;  
    sta[teams[1]][teams[2]] += zaehler;
}

bool erzeuge_spielplan(const int anzahl_m, std::vector<TEAM_KONSTELLATION> alle, TEAM_KONSTELLATION* plan, int sta[BITS][BITS], const int start_index){
    
    if(DEBUG) std::cout << "[" << next << "] ";

    if(vollstaendig(anzahl_m, next)){                       //Abbruch, falls gueltiger Plan gefunden
        if(DEBUG) std::cout << "VOLLSTAENDIG" << std::endl;
        return true;
    }

    for(int i = start_index; i < alle.size(); i++){       //alle Konstellationen durchgehen
        TEAM_KONSTELLATION tk = alle[i];

        if(DEBUG) std::cout << "i=" << i << " KANDIDAT k=";
        if(DEBUG) drucke_konstellation(tk);
        if(DEBUG) std::cout << std::endl;

        if(spielanzahl_erreicht(tk, sta)){ //testen der Statistik an allen stellen dieser teams < 2
            if(DEBUG) std::cout << " spielanzahl erreicht" << std::endl;
            if (DEBUG) drucke_statistik(anzahl_m, sta);
        }
        else{
            aktualisiere_statistik(sta, tk, +1);
            if (DEBUG) drucke_statistik(anzahl_m, sta);
            plan [next++] = tk;
            if(DEBUG) { std::cout << "-->[" << next << "] "; drucke_vektor("", plan, next, true); std::cout << std::endl; }
            //if(DEBUG) drucke_vektor("Plan", plan, next, false);

            if(erzeuge_spielplan(anzahl_m, alle, plan, sta, i + 1)){ //rekursiver aufruf
                return true;  //hochreichen des gueltigen plans
            }
            else{
                aktualisiere_statistik(sta, tk, -1);
                if (DEBUG) drucke_statistik(anzahl_m, sta);
                plan [--next] = 0;
                if(DEBUG) std::cout << "!!!!LOESCHE k=";
                if(DEBUG) drucke_konstellation(tk);
                if(DEBUG) std::cout << std::endl;
                if(DEBUG) std::cout << "[" << next << "] ";
            }
        }
    }
    return false; //Falls keine Loesung gefunden wurde
}

//Alle funktionen in richtiger Reihenfolge ausfuehren und zeit stoppen
int spielplan(int anzahl_m){

    //Zeitmessung start
    Timer t = Timer();
    t.start();

    std::cout << "--------------------------------------------" << std::endl;

    int statistik[BITS][BITS] = {0};
    const int anzahl_spiele = anzahl_m*(anzahl_m-1)/3;
    TEAM_KONSTELLATION spielplan [anzahl_spiele] = { 0 };

    std::vector<TEAM_KONSTELLATION> alle_konstellationen = erzeuge_alle_konstellationen(anzahl_m);
    /*std::vector<TEAM_KONSTELLATION> perm_konstellationen;

    std::mt19937 gen;

    while(alle_konstellationen.size() > 0){
        std::uniform_int_distribution<int> dis(0,alle_konstellationen.size()-1);
        int random = dis(gen);
        TEAM_KONSTELLATION t = alle_konstellationen.at(random);
        perm_konstellationen.push_back(t);
        alle_konstellationen.erase(alle_konstellationen.begin() + (random));
    } */
  
    drucke_vektor("Konstellationen", alle_konstellationen.data(), alle_konstellationen.size(), false);
    if(DEBUG) std::cout << "--------------------------------------------" << std::endl;

    if(erzeuge_spielplan(anzahl_m, alle_konstellationen, spielplan, statistik, 0)){
        drucke_vektor("Spielplan", spielplan, anzahl_spiele, false);
    }
    else{
        std::cout << "Es gibt keine gueltige Loesung" << std::endl;
    }
    if(DEBUG) std::cout << "--------------------------------------------" << std::endl;
    if(DEBUG) std::cout << "\n--------------------------------------------" << std::endl;

    //Zeitmessung ende
    t.stop();
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "Zeit: " << t.secs() << "s" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;

    return 0;
}