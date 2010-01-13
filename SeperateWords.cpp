#include "SeperateWords.h"

//SEPERATE_WORDS
const int MAX_MEMORY=256,MAX_STRING=2048;
string memory_string[MAX_MEMORY];
const int DELIM_MAX_MAX=6,CONTAINERS_MAX=1,MAX_COMPLICITY=4;
int delim_cur=6;
char delimeters[DELIM_MAX_MAX]={'\n',' ','=','(',',',')'}; //47=/ 92 = \ ,13 =CR , 11 = LF
char cons[CONTAINERS_MAX]={'"'};
char cone[CONTAINERS_MAX]={'"'};


void set_delimeter_num(int thenum)
{delim_cur=thenum;}

void default_delimeter_setup()
{ delim_cur=DELIM_MAX_MAX;
  delimeters[0]='\n';
  delimeters[1]=' ';
  delimeters[2]='=';
  delimeters[3]='(';
  delimeters[4]=',';
  delimeters[5]=')'; 
  cons[0]='"'; cone[0]='"';
 }

void set_delimeter(int num,char tmp)
{delimeters[num]=tmp;}

char get_delimeter(int num)
{return delimeters[num];}


void set_memory(int num,string tmp)
{memory_string[num]=tmp;}

string get_memory(int num)
{return memory_string[num];}


int seperate_words(string inpt)
{   
int containersstack[MAX_COMPLICITY];
 
  //cout<<"seperate_words("<<inpt<<")"<<endl;
  bool delimeterreached=false,tmpboo=false;
  int containerreaced=0;
  int bufs[5]={0,0,0,0,0}; // 1 string inpt position , 2 words seperated , 3 looping buffer , 4 string end , 5 stack position
  
  for (bufs[3]=0; bufs[3]<MAX_COMPLICITY; bufs[3]++) {containersstack[bufs[3]]=0;} //Clear containersstack[]
  for (bufs[3]=0; bufs[3]<MAX_MEMORY; bufs[3]++) {memory_string[bufs[3]]="";} //Clear memory_string[]
  memory_string[0]=inpt;  // Proccessed String is stored in memory_string[0]
  
  bufs[4]=strlen(inpt.c_str()); //BUFFER INPUT TO BUFFER 
  
 // bufs[4]=inpt.size(); //BUFFER INPUT TO BUFFER 
  char buffer[MAX_STRING+1];
  if (bufs[4]>MAX_STRING-1) {bufs[4]=MAX_STRING-1;} //Overflow protection , MAX BUFFER IS MAX_STRING
  for (bufs[3]=0; bufs[3]<bufs[4]; bufs[3]++) {buffer[bufs[3]]=inpt[bufs[3]];}  
  //cout<<"buffered string with success "<<bufs[1]<<" - "<<bufs[3]<<endl;
  
  
  bufs[1]=0; bufs[2]=1; bufs[5]=0;
  do
  { 
     containerreaced=-1;
     for (bufs[3]=0; bufs[3]<CONTAINERS_MAX; bufs[3]++) {if ((cons[bufs[3]]==buffer[bufs[1]])|(cone[bufs[3]]==buffer[bufs[1]]))  {containerreaced=bufs[3];}}  
     if (containerreaced!=-1)
     {
        delimeterreached=(cons[containerreaced]==buffer[bufs[1]]); // Vrethike kapoio starting container symbol
        if (cons[containerreaced]!=cone[containerreaced]) 
        {tmpboo=(delimeterreached);} else // einai diaforetiko to cons apo to cone ( ) , { }
        {tmpboo=(delimeterreached)&(bufs[5]==0);} // einai idia ta cons kai ta cone " " , ' ' xreiazetai epipleon elegxos.
        if (tmpboo) {containersstack[bufs[5]++]=containerreaced; 
                     if (memory_string[bufs[2]]!="") {bufs[2]++;}
                     /*cout<<"container reached start-> gone to "<<bufs[2]<<" "<<bufs[5]<<endl;*/ } else //new memory place for string , new container
        if (cone[containerreaced]==buffer[bufs[1]]) {containersstack[bufs[5]--]=0; 
                                                            bufs[2]++; 
                                                            /*cout<<"container reached end-> gone to "<<bufs[2]<<" "<<bufs[5]<<endl;*/} //container end 
     } else
     {
           
     delimeterreached=false;
     for (bufs[3]=0; bufs[3]<delim_cur; bufs[3]++) {  if (delimeters[bufs[3]]==buffer[bufs[1]]) {delimeterreached=true;} } 
     if ((containersstack[0]!=0)|(bufs[5]>0)) {delimeterreached=false;
                                               /*cout<<"."<<bufs[5];*/ } 
     if (!delimeterreached) {memory_string[bufs[2]]=memory_string[bufs[2]]+buffer[bufs[1]];} else
                            {if(memory_string[bufs[2]]!="") {memory_string[++bufs[2]]=""; } }
      
     }
    bufs[1]++;    
  } while(bufs[1]<bufs[4]); 
  if (memory_string[bufs[2]]=="") {--bufs[2];}
 // cout<<"done"<<endl; 
  return bufs[2];
}//END OF SEPERATE_WORDS
