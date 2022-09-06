////////////////////////////////////////////////////////////////////////////////
// A class for locading geometry from text files                              //
//                                                                            //
//        Xinzhan Bai, Sep 06, 2022                                           //
////////////////////////////////////////////////////////////////////////////////

#include "GeometryManager.h"
#include "Module.h"
#include "Cube.h"
#include <iostream>

namespace base_cad
{
    GeometryManager::GeometryManager()
    {
    }

    GeometryManager::~GeometryManager()
    {
    }

    void GeometryManager::SetFile(const char* _path)
    {
        path = _path;
    }

    Module * GeometryManager::GetModule() const
    {
        return module;
    }

    void GeometryManager::ReadGeometry()
    {
        if(path.size() <= 0)
        {
            std::cerr<<__PRETTY_FUNCTION__<<" Error: empty path."
                <<std::endl;
            //exit(0); // debug
        }

        load_text_file();
        convert_to_module();
    }

    void GeometryManager::load_text_file()
    {
    }

    void GeometryManager::convert_to_module()
    {
        if(module == nullptr)
            module = new Module();

        module -> Clear();

        Cube *cube = new Cube(0.2, 0.1, 0.25, 0.5, 0.5, 0.);
        cube -> SetColor(QColor(0.5, 0.5, 0.5));
        cube -> Init();

        Cube *cube1 = new Cube(0.2, 0.1, 0.25, -0.5, -0.5, 0.);
        cube1 -> SetColor(QColor(0.5, 0.5, 0.5));
        cube1 -> Init();

        Cube *cube2 = new Cube(0.2, 0.1, 0.25, -0.5, 0.5, 0.);
        cube2 -> SetColor(QColor(0.5, 0.5, 0.5));
        cube2 -> Init();

        Cube *cube3 = new Cube(0.02, 0.1, 0.25, 0.5, -0.5, 0.);
        cube3 -> SetColor(QColor(0.5, 0.5, 0.5));
        cube3 -> Init();

        Cube *cube4 = new Cube(0.2, 0.01, 0.25, 0., 0., -0.5);
        cube4 -> SetColor(QColor(0.5, 0.5, 0.5));
        cube4 -> Init();

        Cube *cube5 = new Cube(0.2, 0.1, 0.025, 0., 0., 0.5);
        cube5 -> SetColor(QColor(0.5, 0.5, 0.5));
        cube5 -> SetRotation(45, 45, 45);
        cube5 -> Init();

        module -> AddModule(cube);
        module -> AddModule(cube1);
        module -> AddModule(cube2);
        module -> AddModule(cube3);
        module -> AddModule(cube4);
        module -> AddModule(cube5);

        module -> Transform(0., 0., 0.5, 90, 90, 0);
    }
}
