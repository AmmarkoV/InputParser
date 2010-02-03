#include <stdio.h>
#include <stdlib.h>
#include "../InputParser_C.h"
#include <time.h>

#define max_ret_word 256

void ParseString(struct InputParserC * ipc,char * thestr)
{
    int i,z;
    char word_space[max_ret_word]={0};


    printf("\n\nParsing a string..  ( %s ) \n",thestr);
    time_t msec = time(NULL) * 1000;
    int res = InputParser_SeperateWords(ipc,thestr,0);
    time_t msec2 = time(NULL) * 1000;
    printf("Words Seperated ( %u ) at %u msec.. ",res,msec2-msec);

    printf("Int Check ");
    for (i=0; i<res; i++) {  z=InputParser_GetWordInt(ipc,i); printf(" %u = %u ",i,z); } printf("\n\n");

    printf("Length Check ");
    for (i=0; i<res; i++) { printf(" %u = %u ",i,InputParser_GetWordLength(ipc,i)); } printf("\n\n");


    printf("String Check ");
    for (i=0; i<res; i++) { InputParser_GetWord(ipc,i,word_space,max_ret_word);
                           printf(" %u = %s ",i,word_space); } printf("\n\n");

    printf("Upcase String Check ");
    for (i=0; i<res; i++) { InputParser_GetUpcaseWord(ipc,i,word_space,max_ret_word);
                           printf(" %u = %s ",i,word_space); } printf("\n\n");

    printf("Lowercase String Check ");
    for (i=0; i<res; i++) { InputParser_GetLowercaseWord(ipc,i,word_space,max_ret_word);
                           printf(" %u = %s ",i,word_space); } printf("\n\n");


}





int main()
{
    time_t startmsec = time(NULL) * 1000;

    printf("Testing InputParserC ");
    struct InputParserC * ipc=0;
    printf(", linked version is %s \n",InputParserC_Version());


    printf("Creating a new instance of the parser\n");
    printf("Starting memory point of IPC struct is %p , and afterwards",ipc);
    ipc = InputParser_Create(256,5);
    if ( ipc == 0 ) { fprintf(stderr,"\nError Commiting InputParser Context \n"); return(1); }
    printf(" %p \n",ipc);

    printf("SelfChecking\n");
    if ( InputParser_SelfCheck(ipc) == 0 ) { fprintf(stderr,"\nInputParser Self Check Returns erroneous state \n"); return(1); }

    printf("Checking if default delimiters work correctly\n");
    InputParser_DefaultDelimeters(ipc);


    char * parsemessage = "0,1,2,3,4,5,,6,7,8,9,10\0";
    ParseString(ipc,parsemessage);


    char * parsemessage2 = "miden,ena,dyo,tria,tessera,pente,eksi,epta,okto,ennea,deka\0";
    ParseString(ipc,parsemessage2);


    char * parsemessage3 = "010\0";
    ParseString(ipc,parsemessage3);

    char * parsemessage4 = "\0";
    ParseString(ipc,parsemessage4);


    char * parsemessage5 = ",,,,(),\0";
    ParseString(ipc,parsemessage5);

    char * parsemessage6 = "FORWARD(45)\0";
    ParseString(ipc,parsemessage6);

    printf("Deleting the new instance of the parser\n");
    InputParser_Destroy(ipc);

    printf("InputParser Instances destructed.. \n");

    time_t endmsec = time(NULL) * 1000;
    printf("\n%u total msec.. \n",endmsec-startmsec);

    return 0;
}
