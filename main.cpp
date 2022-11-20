#include <iostream>
#include "my_memory.h"
#include <utility>
#include <string>

using Unique = my_unique_ptr<std::string>;
using Shared = my_shared_ptr<std::string>;

int main()
{
    Unique u1{ new std::string("some string of significant length\n") };
    Unique u2{ std::move(u1) };
    Unique u3{new std::string};;
    
    std::cout << *u2;
    
    u3 = std::move(u2);
    
    std::cout << "the size of the string is " << u3->size() << std::endl;
    
    ///////////////////////////////////////////////////////////////////////
    
    Shared s1{ new std::string("another string of significant length\n") };
    Shared s2{ std::move(s1) };
    Shared s3;
    Shared s4{ s3 };
    
    std::cout << *s2;
    
    s3 = std::move(s2);
    s4 = s3;
    
    std::cout << "the size of the string is " << s4->size() << std::endl;
    
    return 0;

}
