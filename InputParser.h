#ifndef _INPUTPARSER_H_
#define _INPUTPARSER_H_

#include <stdio.h>
#include <string.h>
#include <ctype.h>

using namespace std;

const unsigned int DELIM_MAX_MAX=6,CONTAINERS_MAX=1,MAX_COMPLICITY=4;
const unsigned int MAX_MEMORY=256,MAX_STRING=2048;


struct astring
{
  char s[MAX_STRING];
  unsigned int length;
};

class InputParser
{
  private:

    astring *memory_string;
    char *delimeters;
    int delim_cur;
    char *cons;
    char *cone;


    public:

    const char * Version();
    void DefaultDelimeterSetup();

    InputParser();
    ~InputParser();

    void SetDelimeter(int num,char tmp);
    char GetDelimeter(int num);

    void SetMemory(int num,char * tmp);
    char * GetMemory(int num);
    char GetMemoryChar(int num,int chr);

    unsigned short GetMemoryLength(int num);
    void MemoryToUpcase(int num);
    int GetMemoryInt(int num);

    int SeperateWords(char * inpt);
    int SeperateWordsCC(const char * inpt);
    int SeperateWordsUC(unsigned char * inpt);
};

#endif
