#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>
#include "Funktionen.h"

/** Konvertiert gegliederte UTC-Angaben in Unix-Zeit.
* Parameter und ihre Werte-Bereiche:
* - jahr [1970..2038]
* - monat [1..12]
* - tag [1..31]
* - stunde [0..23]
* - minute [0..59]
* - sekunde [0..59]
*/

int main()
{
    int fortfahren=0;
    char filename_HTS[]= "Test_Data_10k_HTS221.csv";
    char filename_LPS[]= "Test_Data_45_LPS25_02.csv";
    struct LPS25HP *All_LPS;
    struct HTS_221 *All_HTS;

    while(1){


        //MAINMENUE/////////////////////////////////////////////////////////
        system("cls");
        int Sensor;
        char enter=0;

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
        printf("Geben Sie gewuenschten Sensor ein:");
        fflush(stdin);
        scanf("%d", &Sensor);
        printf("------------------------------\n");

        //////////////////////////////////////////////////////////////////////////


        //LPS-SENSOR//////////////////////////////////////////////////////////////////////
        if (Sensor == 2){
            system("cls");
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

            //timestamp berechnen//////////////////////////////////////////////////////////////////
            time_start_h = time_start_h - 2;

            double tbeginn = unixzeit_eingabe(jahr,monat,tag,time_start_h,time_start_m,time_start_s);

            int time_lengh_s1 = time_lengh_s + time_start_s;
            double tend = unixzeit_eingabe(jahr,monat,tag,time_start_h,time_start_m,time_lengh_s1);
            //////////////////////////////////////////////////////////////////////

            All_LPS = read_LPS25HP(filename_LPS);           // Einlesen der Daten
            int numb_LPS = count_LPS(All_LPS);      // Zählen der Records
            arraytimecalcLPS(All_LPS, numb_LPS);           //Umrechnung der Unix zeit in reguläres Zeitmaß
            PRESS_CALC(All_LPS, numb_LPS);              //BIT in hPa
            TEMP_CALC(All_LPS, numb_LPS);               //BIT in °C
            print_LPS_array(All_LPS, numb_LPS,tbeginn,tend);      //Daten Ausgeben
            free(All_LPS);

            printf("\n---------PRESS ENTER TO CONTINUE---------");
            fflush(stdin);
            while (enter != '\r' && enter != '\n') { enter = getchar(); }


            //////////////////////////////////////////////////////////////////////////////////



        //HTS-SENSOR//////////////////////////////////////////////////////////////////////

        }else if(Sensor == 1){
            system("cls");
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
            //timestamp berechnen//////////////////////////////////////////////////////////////////
            time_start_h = time_start_h - 2;

            double tbeginn = unixzeit_eingabe(jahr,monat,tag,time_start_h,time_start_m,time_start_s);

            int time_lengh_s1 = time_lengh_s + time_start_s;
            double tend = unixzeit_eingabe(jahr,monat,tag,time_start_h,time_start_m,time_lengh_s1);
            //////////////////////////////////////////////////////////////////////

            All_HTS = read_source(filename_HTS);
            int numb_HTS= count_HTS (All_HTS);    // Zählen der Records
            arraytimecalcHTS(All_HTS, numb_HTS);          //Umrechnung der Unix zeit in reguläres Zeitmaß
            HUM_CALCULATION(All_HTS, numb_HTS);         // Umrechnung Feuchtigkeit in %
            TEMP_CALCULATION(All_HTS, numb_HTS);        // Temperatur ausrechnen in °C
            print_HTS_array(All_HTS,numb_HTS,tbeginn,tend);
            free(All_HTS);

            printf("\n---------PRESS ENTER TO CONTINUE---------");
            fflush(stdin);
            while (enter != '\r' && enter != '\n') { enter = getchar(); }

            //////////////////////////////////////////////////////////////////////////////////


        ////XYZ-SENSOR//////////////////////////////////////////////////////////////////////////////
        }else if(Sensor == 3){
            system("cls");
            printf("Gewaehlter Sensor ist:\n%d. %s\n", Sensor, Sen2);
        }
        //////////////////////////////////////////////////////////////////////////////////


        ////QUIT-PROGRAMM//////////////////////////////////////////////////////////////////////////////
        else if(Sensor == 4){
            system("cls");
            printf("PROGRAMM WIRD GESCHLOSSEN");
            for(int i=0;i<3000000;i++){}
            break;
        }
        //////////////////////////////////////////////////////////////////////////////////
    }
    return 0;
}

