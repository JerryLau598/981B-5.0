#include "files.h"

#include <fstream>

using namespace std;

extern int CountLines(const char *filename)
{
    ifstream file;
    string line;
    int count=0;
    if(file.fail())
    {
        return -1;
    }
    else
    {
        while(getline(file,line))
        {
            count++;
        }
        return count;
    }

    file.close();
}
