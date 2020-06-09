#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LPS25HP.h"


int main()
{
    //Variablen zur Datendatei Einlesen
    char filename_read[] = "Test_Data_45_LPS25_02.csv"; // Datei zum Einlesen

    struct LPS25HP *All_Records;                         // Pointer auf Startadresse des Arrays
    ////////////////////////////////////////////////

    All_Records = read_LPS25HP(filename_read);           // Einlesen der Daten

    int numb_Records = count_Records(All_Records);      // Zählen der Records

    arraytimecalc(All_Records, numb_Records);           //Umrechnung der Unix zeit in reguläres Zeitmaß

    PRESS_CALC(All_Records, numb_Records);              //BIT in hPa

    TEMP_CALC(All_Records, numb_Records);               //BIT in °C

    //char filename_write[] = "write_test.txt";
    //write_struct_array(All_Records, filename_write, numb_Records);   // Schreiben der Daten in neue Datei

    print_struct_array(All_Records, numb_Records);      //Daten Ausgeben

    free(All_Records);                                  // Speicher freigeben
    return 0;
}
