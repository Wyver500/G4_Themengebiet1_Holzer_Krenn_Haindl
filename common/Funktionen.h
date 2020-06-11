
typedef struct HTS_221         // Values Temp und Press in Hex
{
    double timestamp; // Zeitstempel in Sekunden (LINUX)
    int Jahr;
    int Monat;
    int Tag;
    int Stunde;
    int Minute;
    int Sekunde;
    int TEMP_OUT_L;  // Temperatur LSB   (°F)
    int TEMP_OUT_H;     // Temperatur MSB
    float Temperatur;
    int HUM_OUT_L;   // Feuchtikeit LSB       (%)
    int HUM_OUT_H;   // Feuchtigkeit MSB
    float Feuchtigkeit;

}HTS_221;

typedef struct LPS25HP
{
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

void print_HTS_array(struct HTS_221 *, int, double ,double);
void print_LPS_array(struct LPS25HP*, int, double ,double);

struct HTS_221 *read_source(char*);
struct LPS25HP* read_LPS25HP(char*);

int count_LPS(struct LPS25HP*);
int count_HTS(struct HTS_221 *);

void UnixzeitNachDatum(unsigned long int,int *, int *, int *,int *, int *, int *);

void arraytimecalcHTS(struct HTS_221*, int);
void arraytimecalcLPS(struct LPS25HP*, int);


void HUM_CALCULATION(struct HTS_221 *, int);
void TEMP_CALCULATION(struct HTS_221 *, int);
void PRESS_CALC(struct LPS25HP*, int);
void TEMP_CALC(struct LPS25HP*, int);

double unixzeit_eingabe(int, int, int,int, int, int);
