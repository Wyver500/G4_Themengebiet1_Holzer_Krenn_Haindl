#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LPS25HP.h"


int main()
{

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
    }else if(Sensor == 3){
        printf("Gewaehlter Sensor ist:\n%d. %s\n", Sensor, Sen2);
    }



    //Variablen zur Datendatei Einlesen
    char filename_read[] = "Test_Data_45_LPS25_02.csv"; // Datei zum Einlesen

    struct LPS25HP *All_Records;                         // Pointer auf Startadresse des Arrays
    ////////////////////////////////////////////////

    All_Records = read_LPS25HP(filename_read);           // Einlesen der Daten

    int numb_Records = count_Records(All_Records);      // Zählen der Records

    arraytimecalc(All_Records, numb_Records);           //Umrechnung der Unix zeit in reguläres Zeitmaß

    PRESS_CALC(All_Records, numb_Records);              //BIT in hPa

    TEMP_CALC(All_Records, numb_Records);               //BIT in °C

    //write_struct_array(All_Records, filename_write, numb_Records);   // Schreiben der Daten in neue Datei
    //char filename_write[] = "write_test.txt";

    print_struct_array(All_Records, numb_Records);      //Daten Ausgeben

    free(All_Records);                                  // Speicher freigeben
    return 0;
}
