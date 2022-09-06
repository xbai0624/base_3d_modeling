#ifndef __UNIT_TEST_H__
#define __UNIT_TEST_H__

#include "Module.h"
#include "Cube.h"

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
        Cube *cube;
    };
}

#endif
