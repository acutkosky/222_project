
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
  //a big lookup table
  switch(str[0]) {
  case 't':
    return 3;
    break;
  case 'a':
  case 'c':
  case 'g':
    return 3;
    break;
    
  case 'h':
  case 'i':


  case 'o':
  case 's':
  case 'w':
    return 3;
    break;


  case 'n':
  case 'l':
  case 'd':
  case 'r':
    return 2;
    break;
  default:
    return 1;
  }
  
  cout<<"There was a fail in priority3 function on input "<<str<<endl;
  return 0;
}

word bloompriority(char* str) {
  return 1;
}

//here is our length function on strings. It is very hacky.
word length(char* str) {
  return (word)strlen(str);
}


void checkfile(PriorityFilter<char*>& filter, char* filename,char* outfile) {
  ifstream inputfile(filename);
  ofstream outputfile(outfile);

  char buffer[250];
  if(inputfile.is_open() && outputfile.is_open()) {
    while(inputfile.good()) {
      inputfile.getline(buffer,250);
      if(filter.check(buffer)) {
	outputfile<<buffer<<endl;
      }
    }
  } else {
    cout<<"File IO error!\n";
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
  if(argc<5) {
    cout<<"testbible.cpp biblefile testset priorityout bloomout\n";
    return 0;
  }

  char* bloomout = argv[4];
  char* priorityout = argv[3];
  char* testset = argv[2];
  char* biblefile = argv[1];
  

  PriorityFilter<char*> filter(FilterSize,2,NumHashes,priority3,length);

  int t0,t1; //used for timing


  t0 = clock();
  loadfilter(filter,testset);
  t1 = clock();
  cout<<"Loading the priority filter took "<<(float)(t1-t0)/CLOCKS_PER_SEC<<" seconds\n";

  t0 = clock();
  checkfile(filter,biblefile,priorityout);
  t1 = clock();
  cout<<"checking with the priority filter took "<<(float)(t1-t0)/CLOCKS_PER_SEC<<" seconds\n";

  cout<<"***\n"<<"CHECKING NORMAL BLOOM FILTER NOW!\n"<<"***\n";

  PriorityFilter<char*> bloomfilter(FilterSize*2,1,NumHashes,bloompriority,length);

  t0 = clock();
  loadfilter(bloomfilter,testset);
  t1 = clock();
  cout<<"Loading the Bloom filter took "<<(float)(t1-t0)/CLOCKS_PER_SEC<<" seconds\n";

  t0 = clock();
  checkfile(bloomfilter,biblefile,bloomout);
  t1 = clock();
  cout<<"Checking with the Bloom filter took "<<(float)(t1-t0)/CLOCKS_PER_SEC<<" seconds\n";

  return 0;
}
