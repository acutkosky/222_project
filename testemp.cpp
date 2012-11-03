

#include<iostream>
using std::cout;
using std::endl;



template <class afunc>
class testclass {
public:
  int a;
  testclass(int blah):a(blah){}

  int run(void) {
    return afunc(a);
  }

};



int testfunct(int ha) {
  return ha*ha;
}



int main(int argc, char* argv[] ) {

  testclass<testfunct> testing(15);

  
  cout<<testing.run()<<endl;
  return 0;
}
	    
