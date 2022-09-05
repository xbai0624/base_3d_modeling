#ifndef __UNIT_TEST_H__
#define __UNIT_TEST_H__

#include "Module.h"

namespace base_cad
{
    class UnitTest
    {
    public:
        UnitTest();
        ~UnitTest();

        void test();

    private:
        Module *m;
    };
}

#endif
