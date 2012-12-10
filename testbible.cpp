#include"priorityfilter.hpp"
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
using Filters::PriorityFilter;
using Filters::word;
using Filters::ColorArray;

#define FilterSize 500
#define NumHashes 5
#define NumBits 2

//here is our priority function on strings. It is a big switch statement
word priority_3bits(char* str) {
  //a big lookup table
  switch(str[0]) {
  case 't':
    return 7;
    break;
  case 'a':
    return 6;
    break;
  case 'o':
    return 5;
    break;
  case 's':
  case 'h':
    return 4;
    break;
  case 'w':
  case 'i':
  case 'b':
    return 3;
    break;
  case 'f':
  case 'x':
  case 'm':
  case 'q':
  case 'c':
  case 'z':
  case 'v':
    return 2;
    break;
  default:
    return 1;
  }


  
  cout<<"There was a fail in priority_3bits function on input "<<str<<endl;
  return 0;
}
 
//here is our priority function on strings. It is a big switch statement
word priority3(char* str) {
  //a big lookup table
  switch(str[0]) {
  case 't':
    return 15;
    break;
  case 'a':
    return 14;
    break;
  case 'o':
    return 13;
    break;
  case 's':
    return 12;
    break;
  case 'h':
    return 11;
    break;
  case 'w':
    return 10;
    break;
  case 'i':
    return 9;
    break;
  case 'b':
    return 8;
    break;
  case 'f':
  case 'x':
    return 7;
    break;
  case 'm':
  case 'q':
    return 6;
    break;
  case 'c':
  case 'z':
  case 'v':
    return 5;
    break;
  case 'l':
  case 'j':
  case 'k':
    return 4;
    break;
  case 'n':
  case 'r':
  case 'e':
    return 3;
    break;
  case 'd':
  case 'y':
    return 2;
    break;
  default:
    return 1;
  }


  
  cout<<"There was a fail in priority3 function on input "<<str<<endl;
  return 0;
}

word priority_2bits(char* str) {
  //a big lookup table
  switch(str[0]) {
  case 't':
  case 'w':
  case 'n':
  case 'y':
  case 'o':
  case 'z':
  case 'x':
  case 'q':
    return 3;
    break;
  case 'a':
  case 'i':
  case 'e':
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
  /*  
//SOME DEBUGGING CODE  

  int testnums[] = {0,2,5,4,43,46,432,94,54,204,103,206,409};
  
  ColorArray testcolors(FilterSize,4);
  
  for(int i=0;i<12;i++) {
    testcolors[testnums[i]] = (i%15)+1;
  }

  for(int i=0;i<FilterSize;i++) {
    if(testcolors[i] != 0)
      cout<<i<<" "<<testcolors[i]<<endl;
  }
  
  //  testcolors[0] = 1;
  //  testcolors[2] = 2;
  cout<<testcolors[0]<<endl;
  return 0;
  */

  word hashvals[] = {10,10,10,10,10,9,9,7,6,6,5,3,2,2,2,2,2};
  word bloomhashvals[] = {10,10};

  PriorityFilter<char*> filter(FilterSize,NumBits,hashvals,priority_2bits,length);

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

  PriorityFilter<char*> bloomfilter(FilterSize*NumBits,1,bloomhashvals,bloompriority,length);

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

