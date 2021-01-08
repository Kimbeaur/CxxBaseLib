#include <iostream>
#include "fileutil.h"
int main(void)
{
    bool ret = File::Isfile("test.txt");
    if(ret == true)
        std::cout<<" test.txt is file"<<std::endl;
    else
         std::cout<<" test.txt is not file"<<std::endl;
    
    return 0;
}