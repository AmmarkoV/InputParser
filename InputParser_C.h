#ifndef _INPUTPARSER_C_H_
#define _INPUTPARSER_C_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DELIM_MAX_MAX 6
#define CONTAINERS_MAX 1
#define MAX_COMPLICITY 4

#define MAX_MEMORY 256
#define MAX_STRING 2048





struct tokens
{
  // START MEANS THE FIRST CHARACTER TO READ..!
  // LENGTH MEANS total characters to be read
  // i.e.   a _ S _ A _ M _ P _ L _ E
  //        0   1   2   3   4   5   6
  // this token starts from 0 and has 7 characters length
  unsigned int token_start;
  unsigned int length;
};

struct guard_byte
{
  unsigned int checksum;
};

struct InputParserC
{
    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    struct guard_byte guardbyte1;
    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    unsigned int str_length;
    unsigned char local_allocation;
    char * str; // String to process

    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    struct guard_byte guardbyte2;
    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    unsigned short cur_container_count;
    unsigned short max_container_count;
    char *container_start;
    char *container_end;

    unsigned short cur_delimeter_count;
    unsigned short max_delimeter_count;
    char *delimeters;

    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    struct guard_byte guardbyte3;
    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    // RESULT
    unsigned int tokens_max;
    unsigned int tokens_count;
    struct tokens* tokenlist;

    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    struct guard_byte guardbyte4;
    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
};

char * InputParserC_Version();

void InputParser_DefaultDelimeters(struct InputParserC * ipc);

struct InputParserC * InputParser_Create(unsigned int max_string_count,unsigned int max_delimiter_count);
//unsigned char InputParser_Create( struct InputParserC * ipc,unsigned int max_string_count,unsigned int max_delimiter_count);
void InputParser_Destroy(struct InputParserC * ipc);
unsigned char InputParser_SelfCheck(struct InputParserC * ipc);

char InputParser_GetChar(struct InputParserC * ipc,int num,int pos);
unsigned int InputParser_GetWord(struct InputParserC * ipc,int num,char * wheretostore,unsigned storagesize);
unsigned int InputParser_GetUpcaseWord(struct InputParserC * ipc,int num,char * wheretostore,unsigned storagesize);
unsigned int InputParser_GetLowercaseWord(struct InputParserC * ipc,int num,char * wheretostore,unsigned storagesize);
signed int InputParser_GetWordInt(struct InputParserC * ipc,int num);
unsigned int InputParser_GetWordLength(struct InputParserC * ipc,int num);

int InputParser_SeperateWords(struct InputParserC * ipc,char * inpt,char keepcopy);
int InputParser_SeperateWordsCC(struct InputParserC * ipc,const char * inpt,char keepcopy);
int InputParser_SeperateWordsUC(struct InputParserC * ipc,unsigned char * inpt,char keepcopy);
/*

void SetDelimeter(struct InputParserC * ipc,int num,char tmp);
char GetDelimeter(struct InputParserC * ipc,int num);

void SetMemory(struct InputParserC * ipc,int num,char * tmp);
char * GetMemory(struct InputParserC * ipc,int num);
char GetMemoryChar(struct InputParserC * ipc,int num,int chr);

unsigned short GetMemoryLength(struct InputParserC * ipc,int num);
void MemoryToUpcase(struct InputParserC * ipc,int num);
int GetMemoryInt(struct InputParserC * ipc,int num);

int SeperateWords(struct InputParserC * ipc,char * inpt);
int SeperateWordsCC(struct InputParserC * ipc,const char * inpt);
int SeperateWordsUC(struct InputParserC * ipc,unsigned char * inpt);
*/
#endif
