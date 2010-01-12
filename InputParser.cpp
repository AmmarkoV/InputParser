#include "InputParser.h"
/* InputParser..
   A small generic library for parsing a string and tokenizing it!
   URLs: http://62.103.22.50
   Written by Ammar Qammaz a.k.a. AmmarkoV 2006

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


const char * ver=" VERSION 1.30 - 7/1/10 \0";

const char * Version()
{
 return ver;
}


inline int Str2Int_internal(char * inpt)
{
    int intresult=0,multiplier=1,curnum=0;
    bool error_flag=false;
    for (int i=strlen(inpt)-1; i>=0; i--)
    {
        curnum=inpt[i]-'0';
        if ((curnum>=0)&(curnum<=9))
        {
            intresult=intresult+(multiplier*curnum);
            multiplier=multiplier*10;
        }
        else
        {
            error_flag=true;
        }
    }
    return intresult;
}

void InputParser::DefaultDelimeterSetup()
{
    delim_cur=DELIM_MAX_MAX;
    delimeters[0]='\n';
    delimeters[1]=','; // keno by default alla dn theloume na kanoume tokenize sta kena
    delimeters[2]='=';
    delimeters[3]='(';
    delimeters[4]=',';
    delimeters[5]=')';
    cons[0]='"';
    cone[0]='"';
}

InputParser::InputParser()
{
    delim_cur=6;
    memory_string = new astring[MAX_MEMORY];

    for (unsigned int z=0; z<MAX_MEMORY; z++)
    {
        for (unsigned int i=0; i<MAX_STRING; i++)
        {
            memory_string[z].s[i]=0;
        }
    }
    delimeters = new char[delim_cur];
    cons = new char[CONTAINERS_MAX];
    cone = new char[CONTAINERS_MAX];
    DefaultDelimeterSetup();
}

InputParser::~InputParser()
{
    delete []memory_string;
    memory_string=0;
    delete []delimeters;
    delimeters=0;
    delete []cons;
    cons=0;
    delete []cone;
    cone=0;

}


void InputParser::SetDelimeter(int num,char tmp)
{
    delimeters[num]=tmp;
}

char InputParser::GetDelimeter(int num)
{
    return delimeters[num];
}


void InputParser::SetMemory(int num,char * tmp)
{
    memory_string[num].length=strlen(tmp);
    if ( memory_string[num].length > MAX_STRING )
    {
        return;
    }
    strncpy( memory_string[num].s,tmp,memory_string[num].length);
}

char * InputParser::GetMemory(int num)
{
    return memory_string[num].s;
}

char InputParser::GetMemoryChar(int num,int chr)
{
    return memory_string[num].s[chr];
}

void InputParser::MemoryToUpcase(int num) //Metatrepei String se Upcase
{
    for (unsigned int i=0; i<memory_string[num].length; i++)
    {
        memory_string[num].s[i]=toupper(memory_string[num].s[i]);
    }
}

unsigned short InputParser::GetMemoryLength(int num)
{
    return strlen(memory_string[num].s);
}

int InputParser::GetMemoryInt(int num)
{
    return Str2Int_internal(GetMemory(num));
}

int InputParser::SeperateWords(char * inpt)
{
    if ( inpt[0] == 0 )
    {
        return 0;
    }
    if ( strlen(inpt)<1 )
    {
        return 0;
    }

    const int INPUT_POS = 1;
    const int WORDS_SEPERATED = 2;
    const int STRING_END = 4;
    const int STACK_POS = 5;
    unsigned int loop;

    int containersstack[MAX_COMPLICITY];

    bool delimeterreached=false,tmpboo=false;
    unsigned int containerreaced=0;
    unsigned int bufs[6]={0,0,0,0,0,0}; // 1 string inpt position , 2 words seperated , 3 looping buffer , 4 string end , 5 stack position

    for (loop=0; loop<MAX_COMPLICITY; loop++)
    {
        containersstack[loop]=0;  //Clear containersstack[]
    }
    for (loop=0; loop<MAX_MEMORY; loop++)
    {
        memory_string[loop].s[0]=0;
        memory_string[loop].length=0;
    } //Clear memory_string[]
    strcpy(memory_string[0].s,inpt);  // Proccessed String is stored in memory_string[0]
    memory_string[0].length=strlen(inpt);

    bufs[STRING_END]=strlen(inpt); //BUFFER INPUT TO BUFFER

    const int MAX_STRINGPLUS1=MAX_STRING+1;
    char buffer[MAX_STRINGPLUS1]={0};

    if (bufs[STRING_END]>MAX_STRING-1)
    {
        bufs[STRING_END]=MAX_STRING-1;  //Overflow protection , MAX BUFFER IS MAX_STRING
    }
    for (loop=0; loop<bufs[STRING_END]; loop++)
    {
        buffer[loop]=inpt[loop];
    }


    bufs[INPUT_POS]=0;
    bufs[WORDS_SEPERATED]=1;
    bufs[STACK_POS]=0;
    do
    {
        containerreaced=-1;
        for (loop=0; loop<CONTAINERS_MAX; loop++)
        {
            if ((cons[loop]==buffer[bufs[INPUT_POS]])|(cone[loop]==buffer[bufs[INPUT_POS]]))
            {
                containerreaced=loop;
            }
        }
        if (containerreaced!=-1)
        {
            delimeterreached=(cons[containerreaced]==buffer[bufs[INPUT_POS]]); // Vrethike kapoio starting container symbol


            if (cons[containerreaced]!=cone[containerreaced])
            {
                tmpboo=(delimeterreached);
            }
            else // einai diaforetiko to cons apo to cone ( ) , { }
            {
                tmpboo=(delimeterreached)&(bufs[STACK_POS]==0);  // einai idia ta cons kai ta cone " " , ' ' xreiazetai epipleon elegxos.
            }
            if (tmpboo)
            {
                containersstack[bufs[STACK_POS]++]=containerreaced;
                if (memory_string[bufs[WORDS_SEPERATED]].length!=0)
                {
                    bufs[WORDS_SEPERATED]++;
                }
            }
            else //new memory place for string , new container
                if (cone[containerreaced]==buffer[bufs[INPUT_POS]])
                {
                    containersstack[bufs[STACK_POS]--]=0;
                    bufs[WORDS_SEPERATED]++;
                } //container end
        }
        else
        {

            delimeterreached=false;
            for (loop=0; loop<delim_cur; loop++)
            {
                if (delimeters[loop]==buffer[bufs[INPUT_POS]])
                {
                    delimeterreached=true;
                }
            }
            if ((containersstack[0]!=0)|(bufs[STACK_POS]>0))
            {
                delimeterreached=false;
            }
            if (!delimeterreached)
            {
                memory_string[bufs[WORDS_SEPERATED]].s[memory_string[bufs[WORDS_SEPERATED]].length]=buffer[bufs[INPUT_POS]];
                ++memory_string[bufs[WORDS_SEPERATED]].length;
                //strcat( memory_string[bufs[WORDS_SEPERATED]].s,&buffer[bufs[INPUT_POS]] );
                //memory_string[bufs[WORDS_SEPERATED]].length = strlen( memory_string[bufs[WORDS_SEPERATED]].s);
            }
            else
            {
                if (memory_string[bufs[WORDS_SEPERATED]].length!=0)
                {
                    memory_string[++bufs[WORDS_SEPERATED]].length=0;
                    memory_string[bufs[WORDS_SEPERATED]].s[0]=0;
                }
            }

        }

        bufs[INPUT_POS]++;
    }
    while (bufs[INPUT_POS]<bufs[STRING_END]);
    if (memory_string[bufs[WORDS_SEPERATED]].length==0)
    {
        --bufs[WORDS_SEPERATED];
    }
    return bufs[WORDS_SEPERATED];
}//END OF SEPERATE_WORDS

int InputParser::SeperateWordsCC(const char * inpt)
{
  return SeperateWords((char * )inpt);
}


int InputParser::SeperateWordsUC(unsigned char * inpt)
{
  return SeperateWords((char * )inpt);
}
