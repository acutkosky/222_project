/*
 *    ColorArray.hpp
 *implements an array where each element is m bits long.
 *m needs to divide the size of a word.
 *attempts to provide relatively seamless operation as a normal array
 */
#include<assert.h>
#include<iostream>
using std::cout;
using std::endl;

namespace Filters {
  typedef unsigned int word;


  const unsigned int CHAR_SIZE = 8;
  
  const unsigned int WORD_SIZE = sizeof(word)*8;

  class  ColorArray{

  public:
    ColorArray(word asize = 0,word acolorbits = 1) { 
      assert(acolorbits <= 8);
      colorbits = acolorbits;
      if(asize == 0) {
	bitarray = 0;
	size = 0;
      }else{
	size = asize;
	actual_size = (colorbits*size-1)/CHAR_SIZE+1;
	bitarray = new char[actual_size];
	for(unsigned int i=0;i<actual_size;i++) {
	  bitarray[i] = 0;
	}
      }
      colormask = (((word)(1))<<colorbits)-1;
    }
    
    ~ColorArray() {
      if(actual_size != 0) {
	delete [] bitarray;
      }
    }
    
    /* proxy class to simulate l-values of colorbits
     * inspired by similar structure in boost/dynamic_bitset
     */

    class reference {
      friend class ColorArray;
      
      /* there's a lot of redundancy here. It seems kind of hacky
       * and I'm not sure whether it's any faster.
       * but this is only used in filling the bloom filter, so it shouldn't
       * be a huge deal
       */
      
      
      reference(word & w, word apos, word acolormask):
	w_ref (w),
	pos(apos),
	colormask(acolormask),
	mask((~(acolormask << pos)))
	{}
 
    public:

      operator word() const { return ((~mask)&w_ref)>>pos;}

      reference& operator=(word val) {
	w_ref = (mask&w_ref)|((val&colormask)<<pos);
	return *this;
      }

      reference& operator=(const reference& aref) {
	w_ref = (mask&w_ref)|(((aref.w_ref&(~(aref.mask)))>>aref.pos)<<pos);
	return *this;
      }



    private:

      word& w_ref;
      const word pos;
      const word colormask;
      const word mask;


    };




    word operator[] (word pos) const {
      return (getword(getindex(pos))>>getoffset(pos))&colormask;
    }
      

    reference operator[](word pos) {
      return reference(getword(getindex(pos)),getoffset(pos),colormask);
    }
      
    word getsize() {
      return size;
    }

    word numcolors() {
      return colormask;
    }
    
  private:
    
    word& getword(word pos) const{
      return (*((word*)(bitarray+(pos))));
    }

    word getindex(word pos) const {return pos*colorbits/CHAR_SIZE;}
    word getoffset(word pos) const {return (pos*colorbits)% CHAR_SIZE;}



  private:
    char *bitarray;

    word size;
    
    word actual_size;

    word colorbits;

    //we'll just keep a set of colorbits 1s in a row around here
    //conveniently, it's also equal to the number of colors
    word colormask; 


  };

}
