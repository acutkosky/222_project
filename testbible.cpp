
#include"priorityfilter.hpp"
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
using Filters::PriorityFilter;
using Filters::word;


#define FilterSize 1000
#define NumHashes 10


//here is our priority function on strings. It is a big switch statement
word priority3(char* str) {
  //  switch on first letter of string
  return 1;
}


//here is our length function on strings. It is very hacky.
word length(char* str) {
  return (word)strlen(str);
}


void checkfile(PriorityFilter<char*>& filter, char* filename) {
  ifstream inputfile(filename);
  
  char buffer[250];
  if(inputfile.is_open()) {
    while(inputfile.good()) {
      inputfile.getline(buffer,250);
      if(filter.check(buffer)) {
	cout<<buffer<<endl;
      }
    }
  }
  inputfile.close();
}

void loadfilter(PriorityFilter<char*>& filter, char* filename) {
  ifstream inputfile(filename);
  char buffer[250];
  if(inputfile.is_open()) {
    while(inputfile.good()) {
      inputfile.getline(buffer,250);
      filter.insert(buffer);
    }
  }
  inputfile.close();
}


int main(int argc, char* argv []) {
  if(argc<3) {
    cout<<"testbible.cpp biblefile testset\n";
    return 0;
  }

  char* testset = argv[2];
  char* biblefile = argv[1];

  PriorityFilter<char*> filter(FilterSize,3,NumHashes,priority3,length);
  

  loadfilter(filter,testset);
  

  checkfile(filter,biblefile);

  return 0;
}
