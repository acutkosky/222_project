

#include<iostream>
#include"priorityfilter.hpp"
#include<stdio.h>
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
  return ((word)str[0])%4;
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
  

  return 0;
}
	    
