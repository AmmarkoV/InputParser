/** @file InputParser_C.h
 *  @brief A very handy string tokenizer for C this basically a swiss army knife kind code segment that can be used wherever we get strings
 *         and we want to seperate them. This code is used in many of my projects including and not limited to
 *         https://github.com/AmmarkoV/RoboVision
 *         https://github.com/AmmarkoV/FlashySlideshows
 *         https://github.com/AmmarkoV/RGBDAcquisition
 *         https://github.com/AmmarkoV/AmmarServer
 * Basic usage is the following
 *
 *  struct InputParserC * ipc=0;
 *  ipc = InputParser_Create(512,5);     //We want to separte lines of Max 512 different strings seperated using 5 delimiters
 *  InputParser_SetDelimeter(ipc,0,' '); //We want to seperate spaces
 *
 *  char word[512];
 *  int numberOfWords = InputParser_SeperateWords(ipc,"zero,one,2,three(four)",1);
 *  for (int i=0; i<numberOfWords; i++)
 *    {
 *       InputParser_GetWord(ipc,i,word,512);
 *    }
 *  InputParser_Destroy(ipc);
 *
 *  @author Ammar Qammaz (AmmarkoV)
 */

#ifndef _INPUTPARSER_C_H_
#define _INPUTPARSER_C_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DELIM_MAX_MAX 6
#define CONTAINERS_MAX 1
#define MAX_COMPLICITY 4

#define MAX_MEMORY 256
#define MAX_STRING 2048

#define USE_SCANF 0



/**
 * @brief A struct that contains the token list
 */
struct tokens
{
  /* START MEANS THE FIRST CHARACTER TO READ..!
     LENGTH MEANS total characters to be read
     i.e.   a _ S _ A _ M _ P _ L _ E
            0   1   2   3   4   5   6
     this token starts from 0 and has 7 characters length*/
  unsigned int token_start;
  unsigned int length;
};

/**
 * @brief Guard Byte to make sure that there is no overflow
 */
struct guard_byte
{
  unsigned int checksum;
};

/**
 * @brief The structure that holds all of the Input Parsing Context
 */
struct InputParserC
{
    /* >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
    struct guard_byte guardbyte1;
    /* >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */

    unsigned int str_length;
    unsigned char local_allocation;
    char * str; /* String to process */

    /* >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
    struct guard_byte guardbyte2;
    /* >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
    unsigned short cur_container_count;
    unsigned short max_container_count;
    char *container_start;
    char *container_end;

    unsigned short cur_delimeter_count;
    unsigned short max_delimeter_count;
    char *delimeters;

    /* >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
    struct guard_byte guardbyte3;
    /* >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */

    /* RESULT */
    unsigned int tokens_max;
    unsigned int tokens_count;
    struct tokens* tokenlist;

    /* >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
    struct guard_byte guardbyte4;
    /* >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
};


/**
 * @brief Get Back a String containing the version of the InputParser
 * @retval Pointer to a C String that contains the version of InputParser
 */
char * InputParserC_Version();

/**
 * @brief Clear any non-character characters from string
 * @ingroup InputParser
 * @param String Input/Output
 * @param Length of String
 * @retval 1 if success , 0 if not
 */
int InputParser_ClearNonCharacters(char * inpt , unsigned int length);

/**
 * @brief Trim Starting Characters preceeding string
 * @ingroup InputParser
 * @param String Input/Output
 * @param Length of String
 * @param Character to Trim
 * @retval 1 if success , 0 if not
 */
int InputParser_TrimCharactersStart(char * inpt , unsigned int length,char what2trim);


/**
 * @brief Trim Starting Characters after string
 * @ingroup InputParser
 * @param String Input/Output
 * @param Length of String
 * @param Character to Trim
 * @retval 1 if success , 0 if not
 */
int InputParser_TrimCharactersEnd(char * inpt , unsigned int length,char what2trim);


/**
 * @brief This call will remove all characters specified from the string
 * @ingroup InputParser
 * @param String Input/Output
 * @param Length of String
 * @param Character to Trim
 * @retval 1 if success , 0 if not
 */
int InputParser_TrimCharacters(char * inpt , unsigned int length,char what2trim);


/**
 * @brief This call will setup the default delimiters that are typically used , these are '\n' ',' '=' '(' and ')'
 *        these can be also read by InputParser_GetDelimeter or changed at any time using InputParser_SetDelimeter
 * @ingroup InputParser
 * @param InputParser Context ( needs to be created using InputParser_Create )
 */
void InputParser_DefaultDelimeters(struct InputParserC * ipc);


/**
 * @brief This call will change the value of a delimiter so that it will also act as a tokenization split character
 * @ingroup InputParser
 * @param InputParser Context ( needs to be created using InputParser_Create )
 * @param Number of delimiter we want to set ( has to be less than the max_delimiter_count value we gave in InputParser_Create )
 * @param New Value for the delimiter we want to set
 */
void InputParser_SetDelimeter(struct InputParserC * ipc,int num,char tmp);

/**
 * @brief Get Back the characters that are used as delimiters
 * @ingroup InputParser
 * @param InputParser Context ( needs to be created using InputParser_Create )
 * @param Number of delimiter we want to set ( has to be less than the max_delimiter_count value we gave in InputParser_Create )
 * @retval Character used as delimiter , or Null if incorrect delimter number requested
 */
char InputParser_GetDelimeter(struct InputParserC * ipc,int num);



/**
 * @brief Create an InputParser Structure and Context that can be used to tokenize strings
 * @ingroup InputParser
 * @param  The maximum number of strings/tokens to be returned as output from a SeperateWords command
 * @param  The maximum number of delimters used typically 5 for the defaults '\n' ',' '=' '(' and ')'
 * @retval InputParser Context , or Null if there is an error
 */
struct InputParserC * InputParser_Create(unsigned int max_string_count,unsigned int max_delimiter_count);


/**
 * @brief Destroy an InputParser Structure and Context and safely free all of the memory it might have allocated
 * @ingroup InputParser
 * @param InputParser Context ( needs to be created using InputParser_Create )
 */
void InputParser_Destroy(struct InputParserC * ipc);


unsigned char InputParser_SelfCheck(struct InputParserC * ipc);


unsigned int InputParser_IsEmptyWord(struct InputParserC * ipc,unsigned int num);
unsigned char CheckWordNumOk(struct InputParserC * ipc,unsigned int num);

char InputParser_GetWordChar(struct InputParserC * ipc,unsigned int num,unsigned int pos);

/* WordCompare and WordCompareNoCase return 1 when strings match , 0 otherwise..*/
unsigned char InputParser_WordCompareNoCase(struct InputParserC * ipc,unsigned int num,const char * word,unsigned int wordsize);
unsigned char InputParser_WordCompareNoCaseAuto(struct InputParserC * ipc,unsigned int num,const char * word);
unsigned char InputParser_WordCompare(struct InputParserC * ipc,unsigned int num,const char * word,unsigned int wordsize);
unsigned char InputParser_WordCompareAuto(struct InputParserC * ipc,unsigned int num,const char * word);

unsigned int InputParser_GetWord(struct InputParserC * ipc,unsigned int num,char * wheretostore,unsigned int storagesize);
unsigned int InputParser_GetUpcaseWord(struct InputParserC * ipc,unsigned int num,char * wheretostore,unsigned int storagesize);
unsigned int InputParser_GetLowercaseWord(struct InputParserC * ipc,unsigned int num,char * wheretostore,unsigned int storagesize);
signed int InputParser_GetWordInt(struct InputParserC * ipc,unsigned int num);
float InputParser_GetWordFloat(struct InputParserC * ipc,unsigned int num);
unsigned int InputParser_GetWordLength(struct InputParserC * ipc,unsigned int num);

int InputParser_SeperateWords(struct InputParserC * ipc,char * inpt,char keepcopy);
int InputParser_SeperateWordsCC(struct InputParserC * ipc,const char * inpt,char keepcopy);
int InputParser_SeperateWordsUC(struct InputParserC * ipc,unsigned char * inpt,char keepcopy);


#ifdef __cplusplus
}
#endif


#endif

