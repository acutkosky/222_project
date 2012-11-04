

#include<iostream>
#include"priorityfilter.hpp"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
using namespace std;
using namespace Filters;


template <typename datatype>
class testclass {


public:
  datatype a;
  int (*afunc)(datatype);
  testclass(datatype blah,int(*func)(datatype)):a(blah),afunc(func){}

  int run(void) {
    return afunc(a);
  }

};



int testfunct(int ha) {
  return ha*ha;
}



word priority(char* str) {
  return ((word)str[0])%3 + 1;
}

word length(char* str) {
  return (word)strlen(str);
}


int main(int argc, char* argv[] ) {

  testclass<int> testing(15,testfunct);

  
  cout<<testing.run()<<endl;


  PriorityFilter<char*> afilter(100,4,10,priority,length);



  char* strings[] = {"string1","string2","string4","astring","bstring"};
  for(int i=0;i<5;i++) {
    cout<<strings[i]<<endl;
  }

  for (int i=0;i<5;i++) {
    afilter.insert(strings[i]);
  }

  if(afilter.check("string")) {
    cout<<"oh no it's a false positive. Probably things are broken\n";
  } else {
    cout<<"yay it wsn't there\n";
  }

  for(int i=0;i<5;i++) {
    if(afilter.check(strings[i]))
      cout<<"success on "<<strings[i]<<endl;
  }
  

  char ** randstrings = new char*[1000];
  srand(0);
  int arraysize = 1000;
  for(int i = 0; i < arraysize; i ++){
    int randNum = rand() % 10 + 11;
    char * astring = new char[randNum];
    
    for(int j=0; j < randNum - 1; j ++){
      astring[j] = rand() % 26 + 'a';
    }
    astring[randNum-1] = '\0';
    //cout << astring << endl;
    randstrings[i] = astring;
  }

  PriorityFilter<char*> myfilter(10000,4, 2, priority, length);  

  for(int i = 0; i < arraysize; i ++){
    myfilter.insert(randstrings[i]);
  }

  cout << "checking our strings" << endl;
  for(int i = 0; i < arraysize; i ++){
    if(!myfilter.check(randstrings[i]))
      cout << "fail on " << randstrings[i] << endl;
  }

  cout<< "checking other strings" << endl;
  srand(23434);
  for(int i = 0; i < 10; i ++){
    int randNum = rand() % 10 + 11;
    char * astring = new char[randNum];
    
    for(int j=0; j < randNum - 1; j ++){
      astring[j] = rand() % 26 + 'a';
    }
    astring[randNum-1] = '\0';
    //cout << " checking " << astring << ": " ;
    if(myfilter.check(astring))
      cout<<" false positive " << astring << endl;
    //cout << endl;
  }

  
  return 0;
}
	    
