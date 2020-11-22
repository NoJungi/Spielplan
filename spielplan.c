/*
 * 21.11.2020 junand
 *  
 * Die ersten Schritte im Spielplan für Nora
 * 
 */

#include <stdint.h>
#include <stdio.h>

#define ANZAHL_MANNSCHAFTEN 6

typedef uint32_t TEAM_TUPEL;

TEAM_TUPEL erzeuge_tupel ( int team1, int team2, int team3 ) {

    return (TEAM_TUPEL) 0 | (1 << team1) | (1 << team2) | (1 << team3);

}
;
#define ANZAHL_TUPEL (ANZAHL_MANNSCHAFTEN * (ANZAHL_MANNSCHAFTEN - 1) * (ANZAHL_MANNSCHAFTEN - 2) )

TEAM_TUPEL alle_tupel [ANZAHL_TUPEL] = { 0 };

int ist_team_im_tupel ( int team, TEAM_TUPEL tupel ) {

    return tupel & (1 << team);

}

int ist_bereits_gespielt (TEAM_TUPEL tupel ) {

    for ( int i = 0; i < ANZAHL_TUPEL; i++ ) {
        if ( tupel == alle_tupel [i] ) return 1;
    }

    return 0;
    
}

void erzuege_alle_tupel () {

    int n = 0;

    for ( int i = 0; i < ANZAHL_MANNSCHAFTEN; i++ ) {
        for ( int j = 0; j < ANZAHL_MANNSCHAFTEN; j++ ) {
            if ( j == i ) continue;
            for ( int k = 0; k < ANZAHL_MANNSCHAFTEN; k++ ) {
                if ( k == j || k == i ) continue;
                TEAM_TUPEL t =  erzeuge_tupel ( i, j, k );
                if(ist_bereits_gespielt( t ) == 0) {
                    printf ( "i=%d j=%d k=%d n=%d t=0x%04x\n", i, j, k, n, t );
                    alle_tupel [n++] = t;
                }
            }
        }
    }
}

void drucke_alle_tupel () {

    for ( int i = 0; i < ANZAHL_TUPEL; i++ ) {
        TEAM_TUPEL t = alle_tupel [i];
        char delimiter = '(';
        for ( int b = 0; b < 8 * sizeof ( TEAM_TUPEL ); b++ ) {
            if ( ist_team_im_tupel ( b, t ) ) {
                printf ( "%c%d", delimiter, b + 1 );
                delimiter = ',';
            }
        }
        printf ( ")\n" );
    }
}

int main () {

    printf ( "Start\n" );
    printf ( "Anzahl Tupel=%d\n", ANZAHL_TUPEL );
    printf ( "sizeof tupel=%d\n", sizeof ( TEAM_TUPEL ) );

    erzuege_alle_tupel ();
    printf ( "Tupel erzeugt\n" );

    drucke_alle_tupel ();

    printf ( "Schluss\n" );

    return 0;

}
