#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LPS25HP.h"




int main() {

    int Sensor;
    char Sen1 []= "HTS221 (Luftfeuchtigkeit und Temperatur)";
    char Sen2 []=  "LPS25HB (Druck)";
//    char Sen3 []= "LSM9DS1 (XYZ-Koordinaten)";
    int time_start;
    int time_end;
    printf("------------------------------\n");
    printf("Alles Sensor Daten wurden am 15.04.2020 aufgezeichnet!\n");
    printf("------------------------------\n");
    printf("Welche Sensordaten sind gewuenscht?\n");
    printf("Zur Auswahl stehen:\n");
    printf("1. HTS221 (Luftfeuchtigkeit und Temperatur)\n");
    printf("2. LPS25HB (Druck)\n");
//    printf("3. LSM9DS1 (XYZ-Koordinaten)\n");
    printf("------------------------------\n");
    printf("Geben Sie gewuenschten Sensor ein:\n");
    scanf("%d", &Sensor);
    printf("------------------------------\n");
    if (Sensor == 1){
        printf("Gewaehlter Sensor ist:\n%d. %s\n", Sensor, Sen1);
        printf("------------------------------\n");
        printf("Geben Sie einen Zeitraum an in dem Sie die Sensordaten haben wollen\n");
        printf("------------------------------\n");
        printf("Gemessener Zeitraum 17:29:55 - 17:34:35\n");
        printf("------------------------------\n");
        printf("Anfang:");
        scanf("%d", &time_start);
        printf("------------------------------\n");
        printf("Ende:");
        scanf("%d", &time_end);
        printf("------------------------------\n");

    }else if(Sensor == 2){
        printf("Gewaehlter Sensor ist:\n%d. %s\n", Sensor, Sen2);
        printf("------------------------------\n");
        printf("Geben Sie einen Zeitraum an in dem Sie die Sensordaten haben wollen\n");
        printf("------------------------------\n");
        printf("Gemessener Zeitraum 19:44:32 - 19:49:48\n");
        printf("------------------------------\n");
        printf("Anfang:");
        scanf("%d", &time_start);
        printf("------------------------------\n");
        printf("Ende:");
        scanf("%d", &time_end);
        printf("------------------------------\n");
        /////////////////////////////////////////////////////
        //LPS25HP Funktionen
        //Ausgabe der Daten
        /////////////////////////////////////////////////////
        
    }else if(Sensor == 3){
        printf("Gewaehlter Sensor ist:\n%d. %s\n", Sensor, Sen2);
    }




    return 0;
}
