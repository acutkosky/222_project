
/*
 * implements priority bloom filters
 */

#include"MurmurHash3.cpp"
#include"colorarray.hpp"
#include <iostream>

using namespace std;

namespace Filters {


  template <typename datatype>
  class PriorityFilter {
    
  public:
    
    PriorityFilter(word size, word bits, word* ak,word (*prioritypointer)(datatype), unsigned int (* alength) (datatype)):
      filter(size,bits),
      Priority(prioritypointer),
      k(ak),
      length(alength)
    {}

    int insert(datatype toinsert) {
      word priority = Priority(toinsert);
      for(word i=0;i<k[priority];i++) {
	word hashval = hash(toinsert,i,filter.getsize());
	word curpriority = filter[hashval];
	if(curpriority<priority)
	  filter[hashval]=priority;
      }
      return 0;
    }


    int check(datatype tocheck) {
      word priority = Priority(tocheck);

      for(word i=0;i<k[priority];i++) {
	word hashval = hash(tocheck,i,filter.getsize());
	word curpriority = filter[hashval];
	//cout << hashval << ' ' << curpriority << ' ';
	if(curpriority<priority){
	  return 0;
	}
      }
      return 1;
    }

    
    ColorArray filter;
    word (*Priority)(datatype);
    word* k;
   

  private:
    unsigned int (* length) (datatype);

    word hash(datatype key, int i, int size){
      unsigned int x;
      unsigned int * p = &x;
      MurmurHash3_x86_32(key, length(key) , i, p);
      *p = (*p) % size;
      return *p;				     
    }

  };
}
