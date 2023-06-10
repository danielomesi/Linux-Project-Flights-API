#include "flightsService.h"

int main()
{
    int choice,pipeToWrite;
    fs::path cwd = fs::current_path();
    fs::path writePathFS=cwd/"sharedFolder"/"userInput";
    const char* writePath = writePathFS.c_str();
    vector<string> inputNames;

    std::ofstream pipeToWrite(writePath);

    if (!pipeToWrite.is_open())
    {
        cout<<"Can't open file"<<endl;
    }
    else
    {
        PrintMenu();
        choice = GetChoice();

        if (choice >= 1 && choice <= 4)
        {
            inputNames = GetData(choice); // put in if in case no need for data
            cout << "In cases where some of the data is stored on the server, the process could take a few moments." << endl;
            cout << "Please wait..." << endl;
        }

        pipeToWrite<<choice<<endl;
    }

    
}

void PrintMenu()
{
    cout << "Please choose one of the following commands" << endl;
    cout << "1 - Fetch airports incoming flights." << endl;
    cout << "2 - Fetch airports full flights schedule." << endl;
    cout << "3 - Fetch aircraft incoming flights." << endl;
    cout << "4 - Update DB" << endl;
    cout << "5 - Zip DB Files." << endl;
    cout << "6 - Get child process Pid." << endl;
    cout << "7 - Exit." << endl;
    cout << "Please type your choice <1,2,3,4,5,6,7>" << endl;
}

int GetChoice()
{
    string choiceStr;
    getline(cin, choiceStr);

    while (!isValidChoice(choiceStr))
    {
        errno = EINVAL;
        PrintError();
        getline(cin, choiceStr);
    }

    return atoi(choiceStr.c_str());
}

vector<string> GetData(int choice)
{
    vector<string> inputNames;
    bool isAirport = true;

    if (choice >= 1 && choice <= 3)
    {
        inputNames = GetNames(isAirport);
    }
    else if (choice == 4)
    {
        isAirport = false;
        inputNames = GetNames(isAirport);
    }
    return inputNames;
}

vector<string> GetNames(bool isAirport)
{
    string arg;
    bool isFinish = false;
    vector<string> allValidNames;
    cout << "Note: the data you request will be fetched from the local database if possible,\nIf you wish to get updated data, use the 'Update Database' option in main menu.\n"
         << endl;
    cout << "Please write the arguments seperated by enter, to finish type 'E' (end)" << endl;
    getline(cin, arg);
    while (!(isFinish && !allValidNames.empty()))
    {
        if (arg == "E")
        {
            isFinish = true;
        }
        else
        {
            if (isAirport)
            {
                if (isValidAirport(arg))
                {
                    allValidNames.push_back(arg);
                }
                else
                {
                    PrintError();
                }
            }
            else
            {
                if (isValidIcao24(arg))
                {
                    allValidNames.push_back(arg);
                }
                else
                {
                    PrintError();
                }
            }
            getline(cin, arg);
        }
    }

    return allValidNames;
}

bool isValidChoice(const string &str)
{
    if (str == "1" || str == "2" || str == "3" || str == "4" || str == "5" || str == "6" || str == "7")
        return true;
    return false;
}

void PrintError()
{
    cout << "Error: " << strerror(errno) << " (error number: " << errno << ")" << endl;
}

void WriteToPipe(int pipeToWrite, int choice, vector<string> &inputNames)
{
    int size = inputNames.size(), sizeOfArg;
    char *str;
    write(pipeToWrite, &choice, sizeof(int));
    write(pipeToWrite, &size, sizeof(int));
    for (auto arg : inputNames)
    {
        sizeOfArg = arg.size();
        write(pipeToWrite, &sizeOfArg, sizeof(int));
        write(pipeToWrite, arg.c_str(), arg.size());
    }
    close(pipeToWrite);
}