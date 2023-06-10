#include "libUtility.h"

namespace fs=std::filesystem;

#define FETCH_AIRPORTS_DATA 1
#define PRINT_ARRIVAL_FLIGHTS 2
#define PRINT_FULL_SCHEDULE 3
#define PRINT_AIRCRAFTS_FLIGHTS 4
#define ZIP_DB 5
#define EXIT 6

void PrintMenu();
int GetChoice();
vector<string> GetData(int choice);
vector<string> GetNames(bool isAirport);
bool isValidChoice(const string &str);
void PrintError();
void WriteToPipe(int pipeToWrite, int choice, vector<string> &inputNames);

