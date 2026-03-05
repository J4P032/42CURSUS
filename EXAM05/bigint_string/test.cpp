#include "bigint.hpp"

int main(){
    bigint a(1234);
  
    bigint b(2);
    std::string s = "00000000012c345678900";
    bigint c(b);
    
    std::cout << (a << b) << std::endl;
   
    
    return 0;
}