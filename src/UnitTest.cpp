#include "UnitTest.h"

#include <iostream>

namespace base_cad
{
    UnitTest::UnitTest()
    {
    }

    UnitTest::~UnitTest()
    {
    }

    void UnitTest::test()
    {
        std::cout<<"testing module..."<<std::endl;
        m = new Module();
    }
}
