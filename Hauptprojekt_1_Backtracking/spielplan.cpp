/**************************************************************************
* Dateiename	    : spielplan.cpp
* Projekt	        : Spielplanerstellung mittels Backtracking
* Autor	            : Nora Jungierek
* E-mail		    : nora@jungierek.de
* letzte Bearbeitung: 09.12.2020
\**************************************************************************/

#include "spielplan.hpp"



bool vollstaendig(const int& anzahl_m, const std::vector<TEAM_KONSTELLATION> &plan){
    return plan.size() == (anzahl_m * (anzahl_m - 1) / 3);
}

bool spielanzahl_erreicht(const TEAM_KONSTELLATION tk, int sta[BITS][BITS], const int anzahl_m){
    std::vector<int> teams = teams_in_konstellation(tk);

    if(DEBUG) std::cout << "Statistik: " << sta[teams[0]][teams[1]] << " " << sta[teams[0]][teams[2]] << " " << sta[teams[1]][teams[2]] << std::endl;
    if(DEBUG) std::cout << "Statistik: " << sta[teams[1]][teams[0]] << " " << sta[teams[2]][teams[0]] << " " << sta[teams[2]][teams[1]] << std::endl;
    //std::cout << teams[0] << " " << teams[1] << " " << teams[2] << std::endl;

    return  
        sta[teams[0]][teams[1]] > 1 ||  
        sta[teams[0]][teams[2]] > 1 ||
        sta[teams[1]][teams[2]] > 1;
}

void aktualisiere_statistik(int sta[BITS][BITS], const TEAM_KONSTELLATION tk, const int zaehler){  //zaehler: fuers addieren oder subtrahieren von der Statistik
    if(abs(zaehler) != 1){
        std::cout << "\nBOESER FEHLER, zaehler falsch z=" << zaehler << std::endl;
        exit(102);
    }
    std::vector<int> teams = teams_in_konstellation(tk);
    if(DEBUG) std::cout << "l=" << teams.size() << " " << teams[0] << " " << teams[1] << " " << teams[2] << std::endl;
    sta[teams[0]][teams[1]] += zaehler;
    sta[teams[0]][teams[2]] += zaehler;  
    sta[teams[1]][teams[2]] += zaehler;
}


bool erzeuge_spielplan(const int anzahl_m, std::vector<TEAM_KONSTELLATION> alle, std::vector<TEAM_KONSTELLATION> &plan, int sta[BITS][BITS], const int start_index){
    
    if(DEBUG) std::cout << "[" << plan.size() << "] ";

    if(vollstaendig(anzahl_m, plan)){                       //Abbruch, falls gueltiger Plan gefunden
        if(DEBUG) std::cout << "VOLLSTAENDIG" << std::endl;
        return true;
    }


    for(int i = start_index; i < alle.size(); i++){       //alle Konstellationen durchgehen
    /*
        if(ist_konstellation_in_vektor(alle[i], plan)){  //nur benutzen, falls noch nicht im plan
            if(DEBUG) std::cout << "i=" << i << " doppelt k=";
            if(DEBUG) drucke_konstellation(alle[i]);
            if(DEBUG) std::cout << std::endl;
        }
        else{ */
            TEAM_KONSTELLATION tk = alle[i];

            if(DEBUG) std::cout << "i=" << i << " KANDIDAT k=";
            if(DEBUG) drucke_konstellation(tk);
            if(DEBUG) std::cout << std::endl;

            if(spielanzahl_erreicht(tk, sta, anzahl_m)){ //testen der Statistik an allen stellen dieser teams < 2
                if(DEBUG) std::cout << " spielanzahl erreicht" << std::endl;
            }
            else{
                aktualisiere_statistik(sta, tk, +1);
                plan.push_back(tk);
                //std::cout << "[" << plan.size() << "] "; drucke_vektor("", plan, true); std::cout << std::endl;
                if(DEBUG) drucke_vektor("Plan", plan, false);

                if(erzeuge_spielplan(anzahl_m, alle, plan, sta, i + 1)){ //rekursiver aufruf
                    return true;  //hochreichen des gueltigen plans
                    
                }
                else{
                        aktualisiere_statistik(sta, tk, -1);
                        plan.pop_back();
                        if(DEBUG) std::cout << "!!!!LOESCHE k=";
                        if(DEBUG) drucke_konstellation(tk);
                        if(DEBUG) std::cout << std::endl;
                        if(DEBUG) std::cout << "[" << plan.size() << "] ";
                }
            }
        //}
       
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
    std::vector<TEAM_KONSTELLATION> spielplan;

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
  
    drucke_vektor("Konstellationen", alle_konstellationen, false);
    if(DEBUG) std::cout << "--------------------------------------------" << std::endl;

    if(erzeuge_spielplan(anzahl_m, alle_konstellationen, spielplan, statistik, 0)){
        drucke_vektor("Spielplan", spielplan, false);
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