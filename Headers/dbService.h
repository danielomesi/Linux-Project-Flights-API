#include "libUtility.h"
#include <zip.h>

namespace fs=std::filesystem;

#define MAX_LEN_OF_ARG 7
#define FETCH_AIRPORTS_DATA 1
#define PRINT_ARRIVAL_FLIGHTS 2
#define PRINT_FULL_SCHEDULE 3
#define PRINT_AIRCRAFTS_FLIGHTS 4
#define ZIP_DB 5
#define EXIT 6

void extractDB();
int getPipeToRead(const char* readPath);
vector<string> readFromPipe(int pipeToRead, int *outChoice);
string readStringFromPipe(int pipefd);
