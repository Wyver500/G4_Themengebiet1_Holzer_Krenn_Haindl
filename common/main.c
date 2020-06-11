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
    //Variablen/////////////////////////////////////////////////////////
    char filename_HTS[]= "Test_Data_10k_HTS221.csv";
    char filename_LPS[]= "Test_Data_45_LPS25_02.csv";
    struct LPS25HP *All_LPS;
    struct HTS_221 *All_HTS;

    int Sensor;
    char enter=0;

    char Sen1 []= "HTS221 (Luftfeuchtigkeit und Temperatur)";
    char Sen2 []=  "LPS25HB (Druck)";
//      char Sen3 []= "LSM9DS1 (XYZ-Koordinaten)";
    int time_start_j,SENSOR_start_j,SENSOR_end_j;
    int time_start_mon,SENSOR_start_mon,SENSOR_end_mon;
    int time_start_d,SENSOR_start_d,SENSOR_end_d;
    int time_start_h,SENSOR_start_h,SENSOR_end_h;
    int time_start_m,SENSOR_start_m,SENSOR_end_m;
    int time_start_s,SENSOR_start_s,SENSOR_end_s;
    int time_lengh_s;
    int jahr = 2020;
    int monat = 04;
    int tag = 15;

    while(1){


        //MAINMENUE/////////////////////////////////////////////////////////
        system("cls");
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
        if(Sensor == 2){
            system("cls");
            enter=0;
            time_start_h = 0;
			time_start_m = 0;
			time_start_s = 0;

            All_LPS = read_LPS25HP(filename_LPS);           // Einlesen der Daten
            int numb_LPS = count_LPS(All_LPS);      // Zählen der Records
            arraytimecalcLPS(All_LPS, numb_LPS);           //Umrechnung der Unix zeit in reguläres Zeitmaß
            PRESS_CALC(All_LPS, numb_LPS);              //BIT in hPa
            TEMP_CALC(All_LPS, numb_LPS);               //BIT in °C

            SENSOR_start_j=All_LPS[0].Jahr;
            SENSOR_start_mon=All_LPS[0].Monat;
            SENSOR_start_d=All_LPS[0].Tag;
            SENSOR_start_h=All_LPS[0].Stunde;
            SENSOR_start_m=All_LPS[0].Minute;
            SENSOR_start_s=All_LPS[0].Sekunde;

            SENSOR_end_j=All_LPS[numb_LPS-1].Jahr;
            SENSOR_end_mon=All_LPS[numb_LPS-1].Monat;
            SENSOR_end_d=All_LPS[numb_LPS-1].Tag;
            SENSOR_end_h=All_LPS[numb_LPS-1].Stunde;
            SENSOR_end_m=All_LPS[numb_LPS-1].Minute;
            SENSOR_end_s=All_LPS[numb_LPS-1].Sekunde;

            printf("Gewaehlter Sensor ist:\n%d. %s\n", Sensor, Sen1);
            printf("------------------------------\n");
            printf("Geben Sie einen Zeitraum an in dem Sie die Sensordaten haben wollen\n");
            printf("------------------------------\n");
            printf("Gemessener Zeitraum %d.%d.%d %d:%d:%d - %d.%d.%d %d:%d:%d\n",SENSOR_start_d,SENSOR_start_mon,SENSOR_start_j,SENSOR_start_h,SENSOR_start_m,SENSOR_start_s,SENSOR_end_d,SENSOR_end_mon,SENSOR_end_j,SENSOR_end_h,SENSOR_end_m,SENSOR_end_s);

            while (time_start_h < SENSOR_start_h || time_start_h > 23)
            {
				printf("------------------------------\n");
				printf("Anfang in Stunden:");
				scanf("%d", &time_start_h);
                if(time_start_h < SENSOR_start_h || time_start_h > 23){
					printf("Der eingegebene Wert ist Ungueltig!\n");
				}
			}
            while (time_start_m < SENSOR_start_m || time_start_m > 59)
            {
				printf("------------------------------\n");
				printf("Anfang in Minuten:");
				scanf("%d", &time_start_m);
                if(time_start_m < SENSOR_start_m || time_start_m > 59){
                    printf("Der eingegebene Wert ist Ungueltig!\n");				}
            }

            if(time_start_h == SENSOR_start_h && time_start_m == SENSOR_start_m){
				printf("------------------------------\n");
				printf("Anfang in Sekunden:");
				scanf("%d", &time_start_s);
                while (time_start_s < SENSOR_start_s || time_start_s > 59)
                {
                    if(time_start_s < SENSOR_start_s || time_start_s > 59)
                    {
					printf("Der eingegebene Wert ist Ungueltig!\n");
                    }
					printf("------------------------------\n");
					printf("Anfang in Sekunden:");
					scanf("%d", &time_start_s);
				}
			}
			else if (time_start_h == SENSOR_end_h && time_start_m == SENSOR_end_m)
            {
				printf("------------------------------\n");
				printf("Anfang in Sekunden:");
				scanf("%d", &time_start_s);
				while (time_start_s > SENSOR_end_s)
                {
                        if(time_start_s > SENSOR_end_s)
                        {
                        printf("Der eingegebene Wert ist Ungueltig!\n");
                        }
                        printf("------------------------------\n");
                        printf("Anfang in Sekunden:");
                        scanf("%d", &time_start_s);
                }
            }
            else
            {
				printf("------------------------------\n");
				printf("Anfang in Sekunden:");
				scanf("%d", &time_start_s);
				while (time_start_s > 59)
                    {
                        if(time_start_s > 59)
                        {
                        printf("Der eingegebene Wert ist Ungültig!\n");
                        }
                        printf("------------------------------\n");
                        printf("Anfang in Sekunden:");
                        scanf("%d", &time_start_s);
					}
			}

            printf("------------------------------\n");
            printf("Wie lange in Sekunden?:");
            scanf("%d", &time_lengh_s);
            printf("------------------------------\n");

            //timestamp berechnen//////////////////////////////////////////////////////////////////
            time_start_h = time_start_h - 2;

            double tbeginn = unixzeit_eingabe(jahr,monat,tag,time_start_h,time_start_m,time_start_s);

            int time_lengh_s1 = time_lengh_s + time_start_s;
            double tend = unixzeit_eingabe(jahr,monat,tag,time_start_h,time_start_m,time_lengh_s1);
            /////////////////////////////////////////////////////////////////////


            print_LPS_array(All_LPS, numb_LPS,tbeginn,tend);      //Daten Ausgeben
            free(All_LPS);

			printf("\n---------PRESS ENTER TO CONTINUE---------");
            fflush(stdin);
            while (enter != '\r' && enter != '\n') { enter = getchar(); }


            //////////////////////////////////////////////////////////////////////////////////



        //HTS-SENSOR//////////////////////////////////////////////////////////////////////

        }
		else if(Sensor == 1){
            system("cls");
            enter=0;
            time_start_h = 0;
			time_start_m = 0;
			time_start_s = 0;

            All_HTS = read_source(filename_HTS);
            int numb_HTS= count_HTS (All_HTS);    // Zählen der Records
            arraytimecalcHTS(All_HTS, numb_HTS);          //Umrechnung der Unix zeit in reguläres Zeitmaß
            HUM_CALCULATION(All_HTS, numb_HTS);         // Umrechnung Feuchtigkeit in %
            TEMP_CALCULATION(All_HTS, numb_HTS);        // Temperatur ausrechnen in °C

            SENSOR_start_j=All_HTS[0].Jahr;
            SENSOR_start_mon=All_HTS[0].Monat;
            SENSOR_start_d=All_HTS[0].Tag;
            SENSOR_start_h=All_HTS[0].Stunde;
            SENSOR_start_m=All_HTS[0].Minute;
            SENSOR_start_s=All_HTS[0].Sekunde;

            SENSOR_end_j=All_HTS[numb_HTS-1].Jahr;
            SENSOR_end_mon=All_HTS[numb_HTS-1].Monat;
            SENSOR_end_d=All_HTS[numb_HTS-1].Tag;
            SENSOR_end_h=All_HTS[numb_HTS-1].Stunde;
            SENSOR_end_m=All_HTS[numb_HTS-1].Minute;
            SENSOR_end_s=All_HTS[numb_HTS-1].Sekunde;




            printf("Gewaehlter Sensor ist:\n%d. %s\n", Sensor, Sen2);
            printf("------------------------------\n");
            printf("Geben Sie einen Zeitraum an in dem Sie die Sensordaten haben wollen\n");
            printf("------------------------------\n");
            printf("Gemessener Zeitraum %d.%d.%d %d:%d:%d - %d.%d.%d %d:%d:%d\n",SENSOR_start_d,SENSOR_start_mon,SENSOR_start_j,SENSOR_start_h,SENSOR_start_m,SENSOR_start_s,SENSOR_end_d,SENSOR_end_mon,SENSOR_end_j,SENSOR_end_h,SENSOR_end_m,SENSOR_end_s);

            while (time_start_h < SENSOR_start_h || time_start_h > 23)
            {
				printf("------------------------------\n");
				printf("Anfang in Stunden:");
				scanf("%d", &time_start_h);
                if(time_start_h < SENSOR_start_h || time_start_h > 23){
					printf("Der eingegebene Wert ist Ungueltig!\n");
				}
			}
            while (time_start_m < SENSOR_start_m || time_start_m > 59)
            {
				printf("------------------------------\n");
				printf("Anfang in Minuten:");
				scanf("%d", &time_start_m);
                if(time_start_m < SENSOR_start_m || time_start_m > 59)
                    {
                    printf("Der eingegebene Wert ist Ungueltig!\n");
                    }
            }

            if(time_start_h == SENSOR_start_h && time_start_m == SENSOR_start_m){
				printf("------------------------------\n");
				printf("Anfang in Sekunden:");
				scanf("%d", &time_start_s);
                while (time_start_s < SENSOR_start_s || time_start_s > 59)
                {
                    if(time_start_s < SENSOR_start_s || time_start_s > 59)
                    {
					printf("Der eingegebene Wert ist Ungueltig!\n");
                    }
					printf("------------------------------\n");
					printf("Anfang in Sekunden:");
					scanf("%d", &time_start_s);
				}
			}
			else if (time_start_h == SENSOR_end_h && time_start_m == SENSOR_end_m)
            {
				printf("------------------------------\n");
				printf("Anfang in Sekunden:");
				scanf("%d", &time_start_s);
				while (time_start_s > SENSOR_end_s)
                {
                        if(time_start_s > SENSOR_end_s)
                        {
                        printf("Der eingegebene Wert ist Ungueltig!\n");
                        }
                        printf("------------------------------\n");
                        printf("Anfang in Sekunden:");
                        scanf("%d", &time_start_s);
                }
            }
            else
            {
				printf("------------------------------\n");
				printf("Anfang in Sekunden:");
				scanf("%d", &time_start_s);
				while (time_start_s > 59)
                    {
                        if(time_start_s > 59)
                        {
                        printf("Der eingegebene Wert ist Ungueltig!\n");
                        }
                        printf("------------------------------\n");
                        printf("Anfang in Sekunden:");
                        scanf("%d", &time_start_s);
					}
			}

            printf("------------------------------\n");
            printf("Wie lange in Sekunden?:");
            scanf("%d", &time_lengh_s);
            printf("------------------------------\n");

            //timestamp berechnen//////////////////////////////////////////////////////////////////
            time_start_h = time_start_h - 2;

            double tbeginn = unixzeit_eingabe(jahr,monat,tag,time_start_h,time_start_m,time_start_s);

            int time_lengh_s1 = time_lengh_s + time_start_s;
            double tend = unixzeit_eingabe(jahr,monat,tag,time_start_h,time_start_m,time_lengh_s1);
            /////////////////////////////////////////////////////////////////////

            print_HTS_array(All_HTS,numb_HTS,tbeginn,tend);
            free(All_HTS);

            printf("\n---------PRESS ENTER TO CONTINUE---------");
            fflush(stdin);
            while (enter != '\r' && enter != '\n') { enter = getchar(); }

            //////////////////////////////////////////////////////////////////////////////////


        ////XYZ-SENSOR//////////////////////////////////////////////////////////////////////////////
        }
		else if(Sensor == 3){
            system("cls");
            printf("Gewaehlter Sensor ist:\n%d. %s\n", Sensor, Sen2);
        }
        //////////////////////////////////////////////////////////////////////////////////


        ////QUIT-PROGRAMM//////////////////////////////////////////////////////////////////////////////
        else if(Sensor == 4){
            system("cls");
            printf("PROGRAMM WIRD GESCHLOSSEN");
            break;
        }
        //////////////////////////////////////////////////////////////////////////////////
    }
    return 0;
}

