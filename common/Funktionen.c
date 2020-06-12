#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFLEN 1024
#include "Funktionen.h"



void print_HTS_array(struct HTS_221 *temp_HTS, int numb_HTS, double timebeginn,double timeend) //3     // Ausgabe von numb_Records
{
    for (int numb = 1; numb<=numb_HTS; numb++)
    {
        if(timebeginn<=temp_HTS[numb-1].timestamp&&timeend>=temp_HTS[numb-1].timestamp)
        {
            printf("%4d.%02d.%02d %02d:%02d:%02d  HUMIDITY:%.2f%%  TEMPERATURE:%.2fCelsius\n",temp_HTS[numb-1].Jahr,temp_HTS[numb-1].Monat,temp_HTS[numb-1].Tag,temp_HTS[numb-1].Stunde,temp_HTS[numb-1].Minute,temp_HTS[numb-1].Sekunde,temp_HTS[numb-1].Feuchtigkeit,temp_HTS[numb-1].Temperatur);
        }
    }
}

struct HTS_221 *read_source(char *filename_read) //1         // Einlesen der Daten und Speichern in struct Array
{

    char line[BUFLEN];

    char field_delim[] = ";";
    char *p_field_search;                               // pointer für die Funktion strtok

    int numb = 1;                                       // number of Record

    struct HTS_221 *temp_HTS = malloc(sizeof(struct HTS_221));    // Speicher für das erste Feld im Array
    if (temp_HTS == NULL)
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
        temp_HTS = realloc(temp_HTS,numb*sizeof(struct HTS_221));      // vergrößern des Speichers bei jedem Record
        if (temp_HTS == NULL)
        {
            printf("No memory available");
            exit(-1);
        }

        p_field_search = strtok(line,field_delim);                           // 1. Feld in line
        temp_HTS[numb-1].timestamp = atof(p_field_search);

        p_field_search = strtok(NULL,field_delim);
        temp_HTS[numb-1].TEMP_OUT_L = (int)strtol(p_field_search, NULL, 16);

        p_field_search = strtok(NULL,field_delim);
        temp_HTS[numb-1].TEMP_OUT_H = (int)strtol(p_field_search, NULL, 16);

        p_field_search = strtok(NULL,field_delim);
        temp_HTS[numb-1].HUM_OUT_L = (int)strtol(p_field_search, NULL, 16);

        p_field_search = strtok(NULL,field_delim);
        temp_HTS[numb-1].HUM_OUT_H = (int)strtol(p_field_search, NULL, 16);


        numb++;
    }


    fclose(open_file);

    temp_HTS = realloc(temp_HTS,numb*sizeof(struct HTS_221));
    temp_HTS[numb-1].timestamp = 0.0;                            // sicherstellen, dass am Ende des Arrays 0.0 im timestamp steht

    //print_struct_array(temp_Record, numb);
    return(temp_HTS);
}

int count_HTS(struct HTS_221 *All_HTS) //2
{
    int i = 0;
    while(All_HTS[i].timestamp > 0.0)       // ACHTUNG!! setzt voraus, dass wirklich 0.0 im letzten timestamp steht
    {
        i++;
    }
    return i;
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

void arraytimecalcHTS(struct HTS_221 *temp_HTS, int numb_HTS) // Array zeitstempel umrechnung
{
    for (int numb = 0; numb<numb_HTS; numb++)
    {
        //Variablen für Unixzeit///////////////////////
        unsigned long int unixtime=temp_HTS[numb].timestamp+7200;  //Timestamp + 2 Stunden für EU Zeit
        int *pJahr = &temp_HTS[numb].Jahr;                         //Pointer auf Struckt variablen
        int *pMonat= &temp_HTS[numb].Monat;                        //
        int *pTag= &temp_HTS[numb].Tag;                            //
        int *pStunde= &temp_HTS[numb].Stunde;                      //
        int *pMinute= &temp_HTS[numb].Minute;                      //
        int *pSekunde= &temp_HTS[numb].Sekunde;                    //
        ///////////////////////////////////////////////
        UnixzeitNachDatum(unixtime,pJahr, pMonat, pTag, pStunde, pMinute, pSekunde);    // Zeit umrechnen und in Array schreiben
    }

}

void HUM_CALCULATION(struct HTS_221 *temp_HTS, int numb_HTS){
    //Parameter
    float h0_out_rh = 0x44;
    float h1_out_rh = 0x86;
    int H0_T_out= 0x0005;
    long H1_T_out= 0xd9aa; //2s von d9aa

    H1_T_out = ~H1_T_out & 0x0000ffff;
    H1_T_out++;
    H1_T_out = -H1_T_out;

    int numb;
    for (numb = 0; numb<numb_HTS; numb++){

        int H_T_out = (temp_HTS[numb].HUM_OUT_H<<8) | temp_HTS[numb].HUM_OUT_L;
        //printf("%x",H_T_out);

        if(((H_T_out & 0x8000)>>15) == 1 ){
            H_T_out = ~H_T_out;
            H_T_out++;
        }

        temp_HTS[numb].Feuchtigkeit=(float)((((h1_out_rh-h0_out_rh)/2)*(H_T_out-H0_T_out)/(H1_T_out-H0_T_out))+(h0_out_rh/2)); //formel laut Datenblatt

    }
}


void TEMP_CALCULATION(struct HTS_221 *temp_HTS, int numb_HTS){

    //Parameter
    int T1_deg_cx8 = 0x09  ;
    int T0_deg_cx8 = 0x9e ;
    float T1_deg;
    float T0_deg;
    int T1_out = 0x02d5;
    int T0_out = 0xfffb;//2s von fffb
    T0_out = ~T0_out& 0x0000ffff;
    T0_out++;
    T0_out = -T0_out;

    T1_deg_cx8 = ((0x4 & 0xc)<<6) | T1_deg_cx8;   //Umrechnung un kombination von msb und deg x8
    T0_deg_cx8 = ((0x4 & 0x3)<<8) | T0_deg_cx8;
    T1_deg = (float)T1_deg_cx8 /8;
    T0_deg = (float)T0_deg_cx8 /8;
    int numb;
    for (numb = 0; numb<numb_HTS; numb++){

        int T_out = (temp_HTS[numb].TEMP_OUT_H<<8)|temp_HTS[numb].TEMP_OUT_L;
        //printf("%x",T_out);

        if(((T_out & 0x8000)>>15) == 1 ){
            T_out = ~T_out;
            T_out++;

        }

        temp_HTS[numb].Temperatur =(float)((((T1_deg-T0_deg)*(T_out-T0_out))/(T1_out-T0_out))+(T0_deg)); //formel laut Datenblatt

    }
}




void print_LPS_array(struct LPS25HP *temp_Record, int numb_Records, double timebeginn,double timeend) //3     // Ausgabe von numb_Records
{
    int numb;
    for (numb = 1; numb<=numb_Records; numb++)
    {
        if(timebeginn<=temp_Record[numb-1].timestamp&&timeend>=temp_Record[numb-1].timestamp)
        {
            printf("TIME:%02d.%02d.%4d %02d:%02d:%02d   TEMPERATURE: %4.2f Celsius   PRESSURE:%5.2f hPa\n",temp_Record[numb-1].Tag,temp_Record[numb-1].Monat,temp_Record[numb-1].Jahr,temp_Record[numb-1].Stunde,temp_Record[numb-1].Minute,temp_Record[numb-1].Sekunde,temp_Record[numb-1].TEMP,temp_Record[numb-1].PRESS);
        }
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
    temp_Record[numb].timestamp =0.0;                            // sicherstellen, dass am Ende des Arrays 0.0 im timestamp steht

    //print_struct_array(temp_Record, numb);
    return(temp_Record);
}

int count_LPS(struct LPS25HP *All_Records) //2
{
    int i = 0;
    while(All_Records[i].timestamp!=0.0)       // ACHTUNG!! setzt voraus, dass wirklich 0.0 im letzten timestamp steht
    {
        i++;
    }
    return i-1;
}


void arraytimecalcLPS(struct LPS25HP *temp_Record, int numb_Records) // Array zeitstempel umrechnung
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
    int help;
    for (numb = 0; numb<numb_Records; numb++)
    {
        help=temp_Record[numb].PRESS_OUT_H;
        help=help<<8;
        help=help|temp_Record[numb].PRESS_OUT_L;
        help=help<<8;
        help=help|temp_Record[numb].PRESS_OUT_XL;

        temp_Record[numb].PRESS=help;
        temp_Record[numb].PRESS=temp_Record[numb].PRESS/4096;
    }
}

void TEMP_CALC(struct LPS25HP *temp_Record, int numb_Records)
{
    int VZ=1;
    float offset = 42.5;
    int numb;
    for (numb = 0; numb<numb_Records; numb++)
    {
        int help=0;
        if(temp_Record[numb].TEMP_OUT_H>>7==1){VZ=-1;}        //Vorzeichenberechnung
        else{VZ=1;}
        help=temp_Record[numb].TEMP_OUT_H;   //übernahme mit -1
        help=help<<8;
        if(VZ==-1){help=help|temp_Record[numb].TEMP_OUT_L&0xFE;help=~help&0xFFFF;}                      //invertieren falls 2s kompliment
        else{help=help|temp_Record[numb].TEMP_OUT_L;}      //Übernahme von Temp_L}
        temp_Record[numb].TEMP=help*VZ;
        temp_Record[numb].TEMP=(temp_Record[numb].TEMP/480)+offset;
    }
}


double unixzeit_eingabe(int jahr, int monat, int tag,int stunde, int minute, int sekunde)
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


void print_LSM_array(struct LSM9DS *temp_LSM, int numb_LSM9DS, double timebeginn,double timeend)
{
    printf("GYRx,y,z in [mdps]\n");
    printf("ACCx,y,z in [mg]\n");
    printf("MAGx,y,z in [mgauss]\n\n");
    printf("|  TIME  |  GYR_x |  GYR_y |  GYR_z |  ACC_x |  ACC_y |  ACC_z |  MAG_x |  MAG_y |  MAG_z |\n");
    printf("|-----------------------------------------------------------------------------------------|\n");
    for (int numb = 1; numb<=numb_LSM9DS; numb++)
    {
        if(timebeginn<=temp_LSM[numb-1].timestamp&&timeend>=temp_LSM[numb-1].timestamp)
        {
            printf("|%7d |", temp_LSM[numb-1].timestamp);
            printf("%7ld |", temp_LSM[numb-1].GYR_x);
            printf("%7ld |", temp_LSM[numb-1].GYR_y);
            printf("%7ld |", temp_LSM[numb-1].GYR_z);
            printf("%7ld |", temp_LSM[numb-1].ACC_x);
            printf("%7ld |", temp_LSM[numb-1].ACC_y);
            printf("%7ld |", temp_LSM[numb-1].ACC_z);
            printf("%7ld |", temp_LSM[numb-1].MAG_x);
            printf("%7ld |", temp_LSM[numb-1].MAG_y);
            printf("%7ld |\n", temp_LSM[numb-1].MAG_z);
        }
    }
}

struct LSM9DS *read_LSM9DS1(char *filename_read)
{


    char line[BUFLEN];

    char field_delim[] = ";";
    char *p_field_search;                               // pointer für die Funktion strtok

    int numb = 1;                                       // number of Record

    struct LSM9DS *temp_Record = malloc(sizeof(struct LSM9DS));    // Speicher für das erste Feld im Array
    if (temp_Record == NULL)
    {
        printf("No memory available");
        exit(-1);
    }

    FILE *open_file = fopen(filename_read, "r");
    if (NULL == open_file)
    {
        printf("could not open %s",open_file);
        exit(-1);
    }


    while (fgets(line, BUFLEN, open_file)!=NULL)                       // zeilenweises Einlesen - ACHTUNG auf line Delimiter im Source File
    {
        //printf("%s",line);
        temp_Record = realloc(temp_Record,numb*sizeof(struct LSM9DS));      // vergrößern des Speichers bei jedem Record
        if (temp_Record == NULL)
        {
            printf("No memory available");
            exit(-1);
        }

        p_field_search = strtok(line,field_delim);                           // 1. Feld in line
        temp_Record[numb-1].timestamp = (int)strtol(p_field_search, NULL, 10);

        p_field_search = strtok(NULL,field_delim);
        temp_Record[numb-1].ACC_x = (long long)strtoul(p_field_search, NULL, 16);

        p_field_search = strtok(NULL,field_delim);
        temp_Record[numb-1].ACC_y = (long long)strtoul(p_field_search, NULL, 16);

        p_field_search = strtok(NULL,field_delim);
        temp_Record[numb-1].ACC_z = (long long)strtoul(p_field_search, NULL, 16);

        p_field_search = strtok(NULL,field_delim);
        temp_Record[numb-1].GYR_x = (long long)strtoul(p_field_search, NULL, 16);

        p_field_search = strtok(NULL,field_delim);
        temp_Record[numb-1].GYR_y = (long long)strtoul(p_field_search, NULL, 16);

        p_field_search = strtok(NULL,field_delim);
        temp_Record[numb-1].GYR_z = (long long)strtoul(p_field_search, NULL, 16);

        p_field_search = strtok(NULL,field_delim);
        temp_Record[numb-1].MAG_x = (long long)strtoul(p_field_search, NULL, 16);

        p_field_search = strtok(NULL,field_delim);
        temp_Record[numb-1].MAG_y = (long long)strtoul(p_field_search, NULL, 16);

        p_field_search = strtok(NULL,field_delim);
        temp_Record[numb-1].MAG_z = (long long)strtoul(p_field_search, NULL, 16);
        numb++;
    }


    fclose(open_file);

    temp_Record = realloc(temp_Record,numb*sizeof(struct LSM9DS));
    temp_Record[numb].timestamp = 0.0;                            // sicherstellen, dass am Ende des Arrays 0.0 im timestamp steht

    //print_struct_array(temp_Record, numb);
    return(temp_Record);
}

int count_LSM9DS(struct LSM9DS *All_Records)
{
    int i = 0;
    while(All_Records[i].timestamp!=0.0)       // ACHTUNG!! setzt voraus, dass wirklich 0.0 im letzten timestamp steht
    {
        i++;
    }
    return i-1;
}

long long MASK (long long GYR)
{
    if(GYR>>31== 1){
        GYR = GYR-1;
        GYR = ~(GYR);
    }
    return GYR;
}

