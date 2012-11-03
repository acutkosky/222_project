
/*
 * implements priority bloom filters
 */

#include"MurmerHash3.cpp"
#include"colorarray.hpp"


namespace Filter {


  template <typename datatype>
  class PriorityFilter {

  public:
    PriorityFilter(word size, word bits, word ak,word (*prioritypointer)(datatype)):
      filter(size,bits),
      k(ak)
      Priority(prioritypointer);
    {}

    int insert(datatype toinsert) {
      for(word i=0;i<k;i++) {
	word hashval = hash(toinsert,i)
	  word curpriority = filter[hashval];
	word priority = Priority(toinsert);
	if(curpriority<priority)
	  filter[hashval]=priority;
      }
      return 0;
    }


    int check(datatype tocheck) {
      word priority = Priority(tocheck);

      for(word i=0;i<k;i++) {
	word hashval = hash(tocheck,i);
	word curpriority = filter[hashval];
	if(curpriority<priority)
	  return 0;
      }
      return 1;
    }

    
    ColorArray filter;
    word (*Priority)(datatype);
    word k;
  };

}
