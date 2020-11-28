#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <vector>

//TYPE DEFINITIONS
typedef uint32_t TEAM_TUPEL;

//FUNKTIONEN

TEAM_TUPEL erzeuge_tupel ( int team1, int team2, int team3 );
void drucke_tupel ( TEAM_TUPEL t );
int ist_team_im_tupel ( int team, TEAM_TUPEL tupel );
int ist_bereits_gespielt ( TEAM_TUPEL tupel );
void erzuege_alle_tupel ();
void drucke_alle_tupel ();
void drucke_spielplan ();
int anzahl_spiele ( int t1, int t2 );


//GLOBALE VARIABLEN
int anzahl_Mannschaften = 0;
int anzahl_Tupel = 0;
int anzahl_Spieltage = 1;
int spiele = 2;

std::vector<TEAM_TUPEL> alle_tupel;
std::vector<TEAM_TUPEL> spielplan;

int aktuelles_spiel = 1;

const int BITS = 8 * sizeof ( TEAM_TUPEL );



int main () {
    std::cout << "Wie viele Mannschaften? ";
    std::cin >> anzahl_Mannschaften;
    anzahl_Tupel = (anzahl_Mannschaften * (anzahl_Mannschaften - 1) * (anzahl_Mannschaften - 2) / 6);
    //std::cout << "Wie oft soll jeder gegen jeden Spielen? ";
    //std::cin >> spiele;
    anzahl_Spieltage = anzahl_Mannschaften * (anzahl_Mannschaften - 1) / 2 * spiele / 3;

    std::cout << anzahl_Mannschaften << "\t" << anzahl_Tupel << "\t" << anzahl_Spieltage << std::endl;

    erzuege_alle_tupel ();



    bool fertig = 0;
    TEAM_TUPEL aktuelles_tupel;


    int index_tupel_fuer_spiel[anzahl_Spieltage] = {0};
    index_tupel_fuer_spiel[0] = 1;
    spielplan.push_back ( alle_tupel[0] );

    while ( fertig == 0 )

    {   int n = 0;
        bool geaendert = 0;

        for ( int i = index_tupel_fuer_spiel[aktuelles_spiel]; i < alle_tupel.size(); i++ ) {
            if ( ist_bereits_gespielt ( alle_tupel[n] ) ) {
                n++;
            }else {
                geaendert = 1;
                break;
            }
        }
        if(geaendert == 0){
            aktuelles_spiel--;
            continue;
        }

        aktuelles_tupel = alle_tupel[n];
        index_tupel_fuer_spiel[aktuelles_spiel] = n+1;
        
        drucke_tupel(aktuelles_tupel);
        




        aktuelles_spiel++;
        fertig = 1;
    }
    

    return 0;
}


//FUNKTIONEEN
TEAM_TUPEL erzeuge_tupel ( int team1, int team2, int team3 ) {

    return (TEAM_TUPEL) 0 | (1 << team1) | (1 << team2) | (1 << team3);
}

void drucke_tupel ( TEAM_TUPEL t ) {

    char delimiter = '(';
    for ( int b = 0; b < BITS; b++ ) {
        if ( ist_team_im_tupel ( b, t ) ) {
            printf ( "%c%d", delimiter, b + 1 );
            delimiter = ',';
        }
    }
    printf ( ")" );
}

int ist_team_im_tupel ( int team, TEAM_TUPEL tupel ) {

    return tupel & (1 << team);
}

int ist_bereits_gespielt ( TEAM_TUPEL tupel ) {

    for ( int i = 0; i < spielplan.size(); i++ ) {
        if ( tupel == spielplan [i] ) return 1;
    }
    return 0;
}

int ist_bereits_in_alle_tupel ( TEAM_TUPEL tupel ) {
    for ( int i = 0; i < alle_tupel.size(); i++ ) {
        if ( tupel == alle_tupel [i] ) return 1;
    }
    return 0;
}

void erzuege_alle_tupel () {

    int n = 0;

    for ( int i = 0; i < anzahl_Mannschaften; i++ ) {
        for ( int j = 0; j < anzahl_Mannschaften; j++ ) {
            if ( j == i ) continue;
            for ( int k = 0; k < anzahl_Mannschaften; k++ ) {
                if ( k == j || k == i ) continue;
                TEAM_TUPEL t =  erzeuge_tupel ( i, j, k );
                    //printf ( "i=%d j=%d k=%d n=%d t=0x%04x\n", i, j, k, n, t );
                if(ist_bereits_in_alle_tupel ( t ) == 0) {
                    alle_tupel.push_back ( t );
                    std::cout << std::endl << "Erzeuge Tupel: \t" << ++n << "\t" << std::endl;
                    drucke_tupel(t);
                }
            }
        }
    }
    std::cout << "Anzahl TUPEL: \t " << n << std::endl;
}

void drucke_alle_tupel () {

    std::cout << "ANZAHL_TUPEL: \t" << alle_tupel.size() << std::endl;
    for ( int i = 0; i < alle_tupel.size(); i++ ) {
        drucke_tupel ( alle_tupel [i] );
        printf ( "\n" );
    }
}

void drucke_spielplan () {

    for(int i = 0; i < spielplan.size(); i++) {
        drucke_tupel ( spielplan [i] );
        printf ( "\n" );
    }
}

int anzahl_spiele ( int t1, int t2 ) {

    //printf ( "anzahl_spiele: %d %d\n", t1, t2 );

    int n = 0;

    for ( int i = 0; i < aktuelles_spiel; i++ ) {
        if ( ( spielplan [i] & (1 << t1) ) && ( spielplan [i] & (1<< t2) ) ) n++;
    }

    //printf ( "anzahl_spiele: %d %d -> %d\n", t1, t2, n );

    return n;
}