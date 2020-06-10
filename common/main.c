#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LPS25HP.h"


int main()
{
    //Variablen zur Datendatei Einlesen
    char filename_read[] = "Test_Data_45_LPS25_02.csv"; // Datei zum Einlesen
    double tbeginn =1586964605.396500;
    double tend =1586964605.631000;

    struct LPS25HP *All_Records;                         // Pointer auf Startadresse des Arrays
    ////////////////////////////////////////////////

    All_Records = read_LPS25HP(filename_read);           // Einlesen der Daten

    int numb_Records = count_Records(All_Records);      // Z‰hlen der Records

    arraytimecalc(All_Records, numb_Records);           //Umrechnung der Unix zeit in regul‰res Zeitmaﬂ

    PRESS_CALC(All_Records, numb_Records);              //BIT in hPa

    TEMP_CALC(All_Records, numb_Records);               //BIT in ∞C

    print_struct_array(All_Records, numb_Records,tbeginn,tend);      //Daten Ausgeben

    free(All_Records);                                  // Speicher freigeben

    return 0;
}


