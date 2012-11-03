

#include<iostream>
using std::cout;
using std::endl;



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




int main(int argc, char* argv[] ) {

  testclass<int> testing(15,testfunct);

  
  cout<<testing.run()<<endl;
  return 0;
}
	    
