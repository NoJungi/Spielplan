/**************************************************************************
* Dateiename	    : konstellationen.cpp
* Projekt	        : Spielplanerstellung mittels Backtracking
* Autor	            : Nora Jungierek
* E-mail		    : nora@jungierek.de
* letzte Bearbeitung: 08.12.2020
\**************************************************************************/

#include"konstellationen.hpp"


TEAM_KONSTELLATION erzeuge_konstellation(int team1, int team2, int team3){

    return(TEAM_KONSTELLATION) 0 | (1 << team1) | (1 << team2) | (1 << team3);  //Leftshift im 32 bit Integer mittels bitweisem oder verknuepft
}

bool ist_team_in_konstellation(const int team, const TEAM_KONSTELLATION t){

    return t & (1 << team);  // Bitweises und
}

bool ist_konstellation_in_vektor(const TEAM_KONSTELLATION t, const std::vector<TEAM_KONSTELLATION> v){

    for(int i = 0; i < v.size(); i++){
        if(t == v[i]) return true;
    }
    return false;
}

std::vector<TEAM_KONSTELLATION> erzeuge_alle_konstellationen(int anzahl){

    //int n = 0;

    std::vector<TEAM_KONSTELLATION> alle;
    for(int i = 0; i < anzahl; i++){ //alle durchgehen und gegebenenfalls einfuegen
        for(int j = i+1; j < anzahl; j++){
            for(int k = j+1; k < anzahl; k++){
                TEAM_KONSTELLATION t =  erzeuge_konstellation(i, j, k);
                alle.push_back(t);
            }
        }
    }
    //std::cout << "Anzahl Konstellationen: " << n << std::endl;
    return alle;
}

void teams_in_konstellation(const TEAM_KONSTELLATION tk, int* teams){

    int t = 0;

    for(int b = 0; b < BITS; b++){ //alle durchghen und in teams speichern
        if(ist_team_in_konstellation(b, tk)){
            teams [t++] = b;
        }
    }

}

void drucke_konstellation(TEAM_KONSTELLATION t){

    char trenner = '{';
    for(int b = 0; b < BITS; b++){
        if(ist_team_in_konstellation(b, t)){
            std::cout << trenner << b;
            trenner = ',';
        }
    }
    printf ( "}" );
}

void drucke_vektor(const char* bezeichnung, TEAM_KONSTELLATION* v, int laenge, bool in_einer_zeile){

    if(!in_einer_zeile) std::cout << bezeichnung << " anzahl=" << laenge << std::endl;
    for ( int i = 0; i < laenge; i++ ) {
        drucke_konstellation(v[i]);
        if(!in_einer_zeile) std::cout << std::endl;
    }
    if(!in_einer_zeile) std::cout << std::endl;
}