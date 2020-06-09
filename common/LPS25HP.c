#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Offset 45
#define BUFLEN 1024
#include "LPS25HP.h"


void print_struct_array(struct LPS25HP *temp_Record, int numb_Records) //3     // Ausgabe von numb_Records
{
    int numb;
    for (numb = 1; numb<=numb_Records; numb++)
    {
        printf("TIME:%02d.%02d.%4d %02d:%02d:%02d TEMPERATURE: %4d Celsius PRESSURE:%5d hPa\n",temp_Record[numb-1].Tag,temp_Record[numb-1].Monat,temp_Record[numb-1].Jahr,temp_Record[numb-1].Stunde,temp_Record[numb-1].Minute,temp_Record[numb-1].Sekunde,temp_Record[numb-1].TEMP,temp_Record[numb-1].PRESS);
    }

}

struct LPS25HP *read_LPS25HP(char *filename_read) //1         // Einlesen der Daten und Speichern in struct Array
{

    char line[BUFLEN];

    char field_delim[] = ";";
    char *p_field_search;                               // pointer für die Funktion strtok

    int numb = 1;                                       // number of Record

    struct LPS25HP *temp_Record = malloc(sizeof(struct LPS25HP));    // Speicher für das erste Feld im Array
    if (temp_Record == NULL)
    {
        printf("No memory available");
        exit(-1);
    }

    FILE *open_file = fopen(filename_read, "r");
    if (NULL==open_file)
    {
        printf("could not open %s",open_file);
        exit(-1);
    }


    while (fgets(line, BUFLEN, open_file)!=NULL)                       // zeilenweises Einlesen - ACHTUNG auf line Delimiter im Source File
    {
        //printf("%s",line);
        temp_Record = realloc(temp_Record,numb*sizeof(struct LPS25HP));      // vergrößern des Speichers bei jedem Record
        if (temp_Record == NULL)
        {
            printf("No memory available");
            exit(-1);
        }

        p_field_search = strtok(line,field_delim);                           // 1. Feld in line
        temp_Record[numb-1].timestamp = atof(p_field_search);

        p_field_search = strtok(NULL,field_delim);
        temp_Record[numb-1].TEMP_OUT_L = (int)strtol(p_field_search, NULL, 16);

        p_field_search = strtok(NULL,field_delim);
        temp_Record[numb-1].TEMP_OUT_H = (int)strtol(p_field_search, NULL, 16);

        p_field_search = strtok(NULL,field_delim);
        temp_Record[numb-1].PRESS_OUT_XL = (int)strtol(p_field_search, NULL, 16);

        p_field_search = strtok(NULL,field_delim);
        temp_Record[numb-1].PRESS_OUT_L = (int)strtol(p_field_search, NULL, 16);

        p_field_search = strtok(NULL,field_delim);
        temp_Record[numb-1].PRESS_OUT_H = (int)strtol(p_field_search, NULL, 16);

        numb++;
    }


    fclose(open_file);

    temp_Record = realloc(temp_Record,numb*sizeof(struct LPS25HP));
    temp_Record[numb-1].timestamp = EOF;                            // sicherstellen, dass am Ende des Arrays 0.0 im timestamp steht

    //print_struct_array(temp_Record, numb);
    return(temp_Record);
}


void write_struct_array(struct LPS25HP *temp_Record, char *filename_write, int numb_Records)//4
{
    FILE *open_file = fopen(filename_write, "w+");
    if (NULL==open_file)
    {
        printf("could not open %s",open_file);
        exit(-1);
    }
    int numb;
    for (numb = 1; numb<=numb_Records; numb++)
    {
        fprintf(open_file,"TIME:%d.%d.%d %d:%d:%d TEMPERATURE: %d°C PRESSURE:%d hPa\n",temp_Record[numb-1].Tag,temp_Record[numb-1].Monat,temp_Record[numb-1].Jahr,temp_Record[numb-1].Stunde,temp_Record[numb-1].Minute,temp_Record[numb-1].Sekunde,temp_Record[numb-1].TEMP,temp_Record[numb-1].PRESS);
    }
    fclose(open_file);
}

int count_Records(struct LPS25HP *All_Records) //2
{
    int i = 0;
    while(All_Records[i].timestamp!=EOF)       // ACHTUNG!! setzt voraus, dass wirklich 0.0 im letzten timestamp steht
    {
        i++;
    }
    return i-1;
}

void UnixzeitNachDatum(unsigned long int unixtime,int *pJahr, int *pMonat, int *pTag,int *pStunde, int *pMinute, int *pSekunde)
{
    const unsigned long int SEKUNDEN_PRO_TAG   =  86400ul; /*  24* 60 * 60 */
    const unsigned long int TAGE_IM_GEMEINJAHR =    365ul; /* kein Schaltjahr */
    const unsigned long int TAGE_IN_4_JAHREN   =   1461ul; /*   4*365 +   1 */
    const unsigned long int TAGE_IN_100_JAHREN =  36524ul; /* 100*365 +  25 - 1 */
    const unsigned long int TAGE_IN_400_JAHREN = 146097ul; /* 400*365 + 100 - 4 + 1 */
    const unsigned long int TAGN_AD_1970_01_01 = 719468ul; /* Tagnummer bezogen auf den 1. Maerz des Jahres "Null" */

    unsigned long int TagN = TAGN_AD_1970_01_01 + unixtime/SEKUNDEN_PRO_TAG;
    unsigned long int Sekunden_seit_Mitternacht = unixtime%SEKUNDEN_PRO_TAG;
    unsigned long int temp;

    /* Schaltjahrregel des Gregorianischen Kalenders:
       Jedes durch 100 teilbare Jahr ist kein Schaltjahr, es sei denn, es ist durch 400 teilbar. */
    temp = 4 * (TagN + TAGE_IN_100_JAHREN + 1) / TAGE_IN_400_JAHREN - 1;
    *pJahr = 100 * temp;
    TagN -= TAGE_IN_100_JAHREN * temp + temp / 4;

    /* Schaltjahrregel des Julianischen Kalenders:
       Jedes durch 4 teilbare Jahr ist ein Schaltjahr. */
    temp = 4 * (TagN + TAGE_IM_GEMEINJAHR + 1) / TAGE_IN_4_JAHREN - 1;
    *pJahr += temp;
    TagN -= TAGE_IM_GEMEINJAHR * temp + temp / 4;

    /* TagN enthaelt jetzt nur noch die Tage des errechneten Jahres bezogen auf den 1. Maerz. */
    *pMonat = (5 * TagN + 2) / 153;
    *pTag = TagN - (*pMonat * 153 + 2) / 5 + 1;


    *pMonat += 3;
    if (*pMonat > 12)
    {
        *pMonat -= 12;
        ++*pJahr;
    }

    *pStunde  = Sekunden_seit_Mitternacht / 3600;
    *pMinute  = Sekunden_seit_Mitternacht % 3600 / 60;
    *pSekunde = Sekunden_seit_Mitternacht % 60;
}

void arraytimecalc(struct LPS25HP *temp_Record, int numb_Records) // Array zeitstempel umrechnung
{
    int numb;
    for (numb = 0; numb<numb_Records; numb++)
    {
        //Variablen für Unixzeit///////////////////////
        unsigned long int unixtime=temp_Record[numb].timestamp+7200;  //Timestamp + 2 Stunden für EU Zeit
        int *pJahr = &temp_Record[numb].Jahr;                         //Pointer auf Struckt variablen
        int *pMonat= &temp_Record[numb].Monat;                        //
        int *pTag= &temp_Record[numb].Tag;                            //
        int *pStunde= &temp_Record[numb].Stunde;                      //
        int *pMinute= &temp_Record[numb].Minute;                      //
        int *pSekunde= &temp_Record[numb].Sekunde;                    //
        ///////////////////////////////////////////////
        UnixzeitNachDatum(unixtime,pJahr, pMonat, pTag, pStunde, pMinute, pSekunde);    // Zeit umrechnen und in Array schreiben
    }

}

void PRESS_CALC(struct LPS25HP *temp_Record, int numb_Records) // Druck berechnung
{
    int numb;
    for (numb = 0; numb<numb_Records; numb++)
    {
        temp_Record[numb].PRESS=temp_Record[numb].PRESS_OUT_H;
        temp_Record[numb].PRESS=temp_Record[numb].PRESS<<8;
        temp_Record[numb].PRESS=temp_Record[numb].PRESS|temp_Record[numb].PRESS_OUT_L;
        temp_Record[numb].PRESS=temp_Record[numb].PRESS<<8;
        temp_Record[numb].PRESS=temp_Record[numb].PRESS|temp_Record[numb].PRESS_OUT_XL;

        temp_Record[numb].PRESS=temp_Record[numb].PRESS/4096;
    }
}

void TEMP_CALC(struct LPS25HP *temp_Record, int numb_Records)
{
    int VZ=1;
    int numb;
    for (numb = 0; numb<numb_Records; numb++)
    {
        if(temp_Record[numb].TEMP_OUT_H>>7==1){VZ=-1;}        //Vorzeichenberechnung
        else{VZ=1;}
        temp_Record[numb].TEMP=temp_Record[numb].TEMP_OUT_H&0x7F;   //übernahme von  Temp_H ohne vorzeichen
        temp_Record[numb].TEMP=temp_Record[numb].TEMP<<8;
        temp_Record[numb].TEMP=temp_Record[numb].TEMP|temp_Record[numb].TEMP_OUT_L;        //Übernahme von Temp_L
        temp_Record[numb].TEMP=((temp_Record[numb].TEMP/480)*VZ)+Offset;

    }
}
