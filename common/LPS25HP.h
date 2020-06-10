
typedef struct LPS25HP{
    double timestamp; // Zeitstempel in Sekunden (LINUX)

    int Jahr;
    int Monat;
    int Tag;
    int Stunde;
    int Minute;
    int Sekunde;

    int TEMP_OUT_L;  // Temperatur LSB
    int TEMP_OUT_H;  // Temperatur MSB
    float TEMP;

    int PRESS_OUT_XL;// Druck LSB       (hPa)
    int PRESS_OUT_L; // Druck Mid Part
    int PRESS_OUT_H; // Druck MSB
    float PRESS;

}LPS25HP;


void print_struct_array(struct LPS25HP*, int, double ,double);
struct LPS25HP* read_LPS25HP(char*);
int count_Records(struct LPS25HP*);
void UnixzeitNachDatum(unsigned long int,int*, int*, int*,int*, int*, int*);
void arraytimecalc(struct LPS25HP*, int);
void PRESS_CALC(struct LPS25HP*, int);
void TEMP_CALC(struct LPS25HP*, int);



