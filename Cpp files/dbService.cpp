#include <dbService.h>

int main()
{
    int choice, pipeToRead;
    fs::path cwd = fs::current_path();
    fs::path readPathFS=cwd/"sharedFolder"/"userInput";
    const char* readPath = readPathFS.c_str();
    string res;
    vector<string> inputNames;

    while (true)
    {
        sleep(2);
        extractDB();
        pipeToRead=getPipeToRead(readPath);
        res=readStringFromPipe(pipeToRead);
        //inputNames=readFromPipe(pipeToRead,&choice);
        cout<<res<<endl;
    }
}

void extractDB()
{
    const char *zipFileName = "Api Data.zip";
    const char *destinationFolder = "Api Data";

    // Check if the zip file exists
    struct stat zipFileStat;
    if (stat(zipFileName, &zipFileStat) != 0)
    {
        return;
    }

    // Remove the existing destination folder if it exists
    struct stat destinationFolderStat;
    if (stat(destinationFolder, &destinationFolderStat) == 0 && S_ISDIR(destinationFolderStat.st_mode))
    {
        std::string removeCommand = "rm -rf '";
        removeCommand = removeCommand + destinationFolder + "'";
        if (system(removeCommand.c_str()) != 0)
        {
            std::cout << "Failed to remove the existing destination folder." << std::endl;
            return;
        }
    }

    // Extract the zip file to the destination folder
    std::string extractCommand = "unzip -q -o ";
    extractCommand = extractCommand + "'" + zipFileName + "'";
    extractCommand += " -d '";
    extractCommand = extractCommand + destinationFolder + "'";
    if (system(extractCommand.c_str()) != 0)
    {
        std::cout << "Failed to extract the zip file." << std::endl;
        return;
    }
}

int getPipeToRead(const char* readPath)
{
    int pipe;

    pipe=open(readPath, O_RDONLY | O_NONBLOCK);

    if (pipe==-1)
    {
        errno=ENOENT;
        PrintError();
        exit(errno);
    }
    
    return pipe;
}

string readStringFromPipe(int pipefd)
{
    const int sizeToRead = 1024;
    char *buffer = new char[sizeToRead];
    int bufferSize = sizeToRead;

    string receivedString;

    ssize_t bytesRead;
    while ((bytesRead = read(pipefd, buffer, sizeToRead)) > 0)
    {
        receivedString.append(buffer, bytesRead);
        if (bytesRead == bufferSize)
        {
            bufferSize *= 2;
            char *resizedBuffer = new char[bufferSize];
            memcpy(resizedBuffer, buffer, bytesRead);
            delete[] buffer;
            buffer = resizedBuffer;
        }
    }

    delete[] buffer;

    close(pipefd);

    return receivedString;
}

vector<string> readFromPipe(int pipeToRead, int *outChoice)
{
    vector<string> inputNames;
    char arg[MAX_LEN_OF_ARG];
    int sizeOfArg, numOfArgs;

    read(pipeToRead, outChoice, sizeof(int));
    read(pipeToRead, &numOfArgs, sizeof(int));
    for (int i = 0; i < numOfArgs; ++i)
    {
        read(pipeToRead, &sizeOfArg, sizeof(int));
        read(pipeToRead, arg, sizeOfArg);
        arg[sizeOfArg] = '\0';
        inputNames.push_back((string)arg);
    }
    return inputNames;
    close(pipeToRead);
}