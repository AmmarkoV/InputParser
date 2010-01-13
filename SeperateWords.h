#ifndef _SEPERATEWORDS_H_
#define _SEPERATEWORDS_H_
#include <string>
using namespace std;

void set_delimeter_num(int thenum);
void default_delimeter_setup();
void set_delimeter(int num,char tmp);
char get_delimeter(int num);
void set_memory(int num,string tmp);
string get_memory(int num);
int seperate_words(string inpt);

#endif
