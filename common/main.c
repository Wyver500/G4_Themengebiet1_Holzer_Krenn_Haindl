#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LPS25HP.h"

/** Konvertiert gegliederte UTC-Angaben in Unix-Zeit.
* Parameter und ihre Werte-Bereiche:
* - jahr [1970..2038]
* - monat [1..12]
* - tag [1..31]
* - stunde [0..23]
* - minute [0..59]
* - sekunde [0..59]
*/
double unixzeit_eingabe(int jahr, int monat, int tag,
                           int stunde, int minute, int sekunde)
{
    const short tage_seit_jahresanfang[12] = /* Anzahl der Tage seit Jahresanfang ohne Tage des aktuellen Monats und ohne Schalttag */
            {0,31,59,90,120,151,181,212,243,273,304,334};

    int schaltjahre = ((jahr-1)-1968)/4 /* Anzahl der Schaltjahre seit 1970 (ohne das evtl. laufende Schaltjahr) */
                      - ((jahr-1)-1900)/100
                      + ((jahr-1)-1600)/400;

    long long tage_seit_1970 = (jahr-1970)*365 + schaltjahre
                               + tage_seit_jahresanfang[monat-1] + tag-1;

    if ( (monat>2) && (jahr%4==0 && (jahr%100!=0 || jahr%400==0)) )
        tage_seit_1970 += 1; /* +Schalttag, wenn jahr Schaltjahr ist */

    return sekunde + 60 * ( minute + 60 * (stunde + 24*tage_seit_1970) );
}

int main()
{
    while(1){

        int Sensor;

        char Sen1 []= "HTS221 (Luftfeuchtigkeit und Temperatur)";
        char Sen2 []=  "LPS25HB (Druck)";
//      char Sen3 []= "LSM9DS1 (XYZ-Koordinaten)";
        int time_start_h;
        int time_start_m;
        int time_start_s;
        int time_lengh_s;
        int jahr = 2020;
        int monat = 04;
        int tag = 15;
        printf("------------------------------\n");
        printf("Alles Sensor Daten wurden am 15.04.2020 aufgezeichnet!\n");
        printf("------------------------------\n");
        printf("Welche Sensordaten sind gewuenscht?\n");
        printf("Zur Auswahl stehen:\n");
        printf("1. HTS221 (Luftfeuchtigkeit und Temperatur)\n");
        printf("2. LPS25HB (Druck)\n");
    //  printf("3. LSM9DS1 (XYZ-Koordinaten)\n");
        printf("4. EXIT\n");
        printf("------------------------------\n");
        printf("Geben Sie gewuenschten Sensor ein:\n");
        scanf("%d", &Sensor);
        printf("------------------------------\n");
        if (Sensor == 2){
            printf("Gewaehlter Sensor ist:\n%d. %s\n", Sensor, Sen1);
            printf("------------------------------\n");
            printf("Geben Sie einen Zeitraum an in dem Sie die Sensordaten haben wollen\n");
            printf("------------------------------\n");
            printf("Gemessener Zeitraum 17:29:55 - 17:34:35\n");
            printf("------------------------------\n");
            printf("Anfang in Stunden:");
            scanf("%d", &time_start_h);
            if (time_start_h != 17){
                printf("Der eingegebene Wert befindet sich nicht im Zeitraum der Messung!");
                exit(-1);
            }
            printf("------------------------------\n");
            printf("Anfang in Minuten:");
            scanf("%d", &time_start_m);
            if (time_start_m <29 || time_start_m > 34){
                printf("Der eingegebene Wert befindet sich nicht im Zeitraum der Messung!");
                exit(-1);
            }
            printf("------------------------------\n");
            printf("Anfang in Sekunden:");
            scanf("%d", &time_start_s);
            if (time_start_h == 17 && time_start_m == 29){
                if (time_start_s < 55){
                    printf("Der eingegebene Wert befindet sich nicht im Zeitraum der Messung!");
                    exit(-1);
                }
            }
            if (time_start_h == 17 && time_start_m == 34){
                if (time_start_s < 35){
                    printf("Der eingegebene Wert befindet sich nicht im Zeitraum der Messung!");
                    exit(-1);
                }
            }
            printf("------------------------------\n");
            printf("Wie lange in Millisekunden?(max. 280s):");
            scanf("%d", &time_lengh_s);
            if(time_lengh_s >= 280){
                printf("Der eingegebene Wert befindet sich nicht im Zeitraum der Messung!");
                exit(-1);
            }
            printf("------------------------------\n");

        }else if(Sensor == 1){
            printf("Gewaehlter Sensor ist:\n%d. %s\n", Sensor, Sen2);
            printf("------------------------------\n");
            printf("Geben Sie einen Zeitraum an in dem Sie die Sensordaten haben wollen\n");
            printf("------------------------------\n");
            printf("Gemessener Zeitraum 19:44:32 - 19:49:48\n");
            printf("------------------------------\n");
            printf("Anfang in Stunden:");
            scanf("%d", &time_start_h);
            if (time_start_h != 19){
                printf("Der eingegebene Wert befindet sich nicht im Zeitraum der Messung!");
                exit(-1);
            }
            printf("------------------------------\n");
            printf("Anfang in Minuten:");
            scanf("%d", &time_start_m);
            if (time_start_m <44 || time_start_m > 49){
                printf("Der eingegebene Wert befindet sich nicht im Zeitraum der Messung!");
                exit(-1);
            }
            printf("------------------------------\n");
            printf("Anfang in Sekunden:");
            scanf("%d", &time_start_s);
            if (time_start_h == 19 && time_start_m == 44){
                if (time_start_s < 32){
                    printf("Der eingegebene Wert befindet sich nicht im Zeitraum der Messung!");
                    exit(-1);
                }
            }
            if (time_start_h == 19 && time_start_m == 49){
                if (time_start_s < 48){
                    printf("Der eingegebene Wert befindet sich nicht im Zeitraum der Messung!");
                    exit(-1);
                }
            }
            printf("------------------------------\n");
            printf("Wie lange in Millisekunden?(max. 316s):");
            scanf("%d", &time_lengh_s);
            if(time_lengh_s >= 316){
                printf("Der eingegebene Wert befindet sich nicht im Zeitraum der Messung!");
                exit(-1);
            }
            printf("------------------------------\n");
        }else if(Sensor == 3){
            printf("Gewaehlter Sensor ist:\n%d. %s\n", Sensor, Sen2);
        }else if(Sensor == 4){
            break;
        }

        time_start_h = time_start_h - 2;

        double u_input = unixzeit_eingabe(jahr,monat,tag,time_start_h,time_start_m,time_start_s);
        printf("%f\n", u_input);

        int time_lengh_s1 = time_lengh_s + time_start_s;
        double u_input_l = unixzeit_eingabe(jahr,monat,tag,time_start_h,time_start_m,time_lengh_s1);
        printf("%f\n", u_input_l);

        //Variablen zur Datendatei Einlesen
        char filename_read[] = "Test_Data_45_LPS25_02.csv"; // Datei zum Einlesen

        struct LPS25HP *All_Records;                         // Pointer auf Startadresse des Arrays
        ////////////////////////////////////////////////

        All_Records = read_LPS25HP(filename_read);           // Einlesen der Daten

        int numb_Records = count_Records(All_Records);      // Zählen der Records

        printf("%d", numb_Records);

        arraytimecalc(All_Records, numb_Records);           //Umrechnung der Unix zeit in reguläres Zeitmaß

        PRESS_CALC(All_Records, numb_Records);              //BIT in hPa

        TEMP_CALC(All_Records, numb_Records);               //BIT in °C

        //write_struct_array(All_Records, filename_write, numb_Records);   // Schreiben der Daten in neue Datei
        //char filename_write[] = "write_test.txt";

        print_struct_array(All_Records, numb_Records,u_input,u_input_l);      //Daten Ausgeben

        free(All_Records);                                  // Speicher freigeben

    }
    return 0;
}

