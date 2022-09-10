////////////////////////////////////////////////////////////////////////////////
// A class for building geometry                                              //
// This class works in Cartesian Coords,                                      //
// the world range is (-1, -1, -1) -> (1, 1, 1)                               //
//                                                                            //
//        Xinzhan Bai, Sep 07, 2022                                           //
////////////////////////////////////////////////////////////////////////////////

#include "GeometryBuilder.h"
#include "APVMapping.h"
#include "Trapezoid.h"
#include "Sphere.h"
#include <iostream>
#include <QColor>

namespace base_cad
{
    GeometryBuilder::GeometryBuilder()
    {
    }

    GeometryBuilder::~GeometryBuilder()
    {
    }

    void GeometryBuilder::SetTextFile(const char* path)
    {
        map = apv_mapping::Mapping::Instance();
        map -> LoadMap(path);

        SetupVolume();
    }

    Module * GeometryBuilder::GetCompleteAssembly() const
    {
        return assembly;
    }

    void GeometryBuilder::SetWorldHalfW(float w)
    {
        world_halfw = w;
        unit = 1./w;
    }

    void GeometryBuilder::SetupVolume()
    {
        SetWorldHalfW(90);

        if(assembly == nullptr)
            assembly = new Module();
        else
            assembly->Clear();

        test_geometry();
    }

    Module* GeometryBuilder::build_chamber_test()
    {
        // an uva xy chamber
        Cube top_plane(50*unit/2., 40*unit/2., 5*unit/2, 0, -3*unit, 5*unit/2);
        top_plane.SetColor(QColor(0, 255, 255));
        top_plane.Init();

        Cube bottom_plane(65*unit/2., 48*unit/2., 1*unit/2., 0, 0, -1.*unit/2);
        bottom_plane.SetColor(QColor(0, 128, 12));
        bottom_plane.Init();

        Module *uvaxychamber = new Module();
        uvaxychamber -> AddModule(&top_plane); 
        uvaxychamber -> AddModule(&bottom_plane);

        return uvaxychamber;
    }

    Module *GeometryBuilder::build_apv_test()
    {
        Cube * apv = new Cube(3 * unit, 1.5 * unit, 0.5*unit);
        apv -> SetColor(QColor(51, 102, 255));
        apv -> Init();
        return apv;
    }

    Module *GeometryBuilder::build_chamber_apv_test()
    {
        Module *chamber = build_chamber_test();
        Module *apv = build_apv_test();

        Module *res = new Module();

        res -> AddModule(chamber);
        // 12-slot
        for(int i=0; i<12; i++) {
            Module tmp(*apv);
            tmp.Transform(-25*unit + 3*unit + i*4*unit, 20*unit, 2*unit, 0, 0, 90);
            res -> AddModule(&tmp);
        }
        // left 5-slot
        for(int i=0; i<5; i++) {
            Module tmp(*apv);
            tmp.Transform(-28*unit, -25*unit + 4*unit + i*4*unit, 2*unit);
            res -> AddModule(&tmp);
        }
        // right 5-slot
        for(int i=0; i<5; i++) {
            Module tmp(*apv);
            tmp.Transform(28*unit, i*4*unit, 2*unit);
            res -> AddModule(&tmp);
        }
 
        return res;
    }

    Module *GeometryBuilder::build_layer_test()
    {
        Module *uvaxychamber = build_chamber_apv_test();

        // an uva layer
        float dy = 56*unit;
        Module *l1m0 = new Module(*uvaxychamber);
        l1m0 -> Transform(0, -dy, 0, 0, 0, 180);
        Module *l1m1 = new Module(*uvaxychamber);
        l1m1 -> Transform(0, 0, 0, 20, 0, 180);
        Module *l1m2 = new Module(*uvaxychamber);
        l1m2 -> Transform(0, dy, 0);
        Module *l1m3 = new Module(*uvaxychamber);
        l1m3 -> Transform(0, 2*dy, 0);

        Module *layer = new Module();

        layer -> AddModule(l1m0);
        layer -> AddModule(l1m1);
        layer -> AddModule(l1m2);
        layer -> AddModule(l1m3);

        return layer;
    }

    Module *GeometryBuilder::build_assembly_test()
    {
        Module *layer = build_layer_test();

        // entire assembly
        float x_rot = 0., y_rot = -90., z_rot = 0.;
        Module *layer1 = new Module(*layer);
        z_rot = 20;
        layer1 -> Transform(0., 0, 0, x_rot, y_rot, z_rot);
        z_rot = 0.;

        Module *layer2 = new Module(*layer);
        y_rot += 25;
        layer2 -> Transform(50*unit, 0, 0, x_rot, y_rot, z_rot);
        y_rot = -90.;

        Module *layer3 = new Module(*layer);
        layer3 -> Transform(100*unit, 0, 0, x_rot, y_rot, z_rot);

        Module *layer4 = new Module(*layer);
        x_rot = 45.;
        layer4 -> Transform(150*unit, 0, 0, x_rot, y_rot, z_rot);
        x_rot = 0.;

        Module *layer5 = new Module(*layer);
        layer5 -> Transform(-50*unit, 0, 0, x_rot, y_rot, z_rot);

        Module *layer6 = new Module(*layer);
        x_rot = 70.;
        layer6 -> Transform(-100*unit, 0, 0, x_rot, y_rot, z_rot);
        x_rot = 0.;

        Module *layer7 = new Module(*layer);
        z_rot = -25.;
        layer7 -> Transform(-150*unit, 0, 0, x_rot, y_rot, z_rot);
        z_rot = 0.;

        Module *layer8 = new Module(*layer);
        x_rot = -30;
        layer8 -> Transform(-200*unit, 0, 0, x_rot, y_rot, z_rot);

        Module * as = new Module();
        as -> AddModule(layer1);
        as -> AddModule(layer2);
        as -> AddModule(layer3);
        as -> AddModule(layer4);
        as -> AddModule(layer5);
        as -> AddModule(layer6);
        as -> AddModule(layer7);
        as -> AddModule(layer8);

        as -> Transform(25*unit, -25*unit, 0);

        return as;
    }

    void GeometryBuilder::test_geometry()
    {
        auto test_assembly = [&]()
        {
            assembly = build_assembly_test();
        };

        auto test_cube = [&]()
        {
            Cube cube(0.5, 0.5, 0.5, 6, -6, 0);
            cube.SetColor(QColor(255, 255, 0));
            cube.SetName("cube1");
            cube.Init();

            assembly -> AddModule(&cube);
        };

        auto test_trapezoid = [&]()
        {
            Trapezoid trapezoid1(1, 1, 4, 4, 3);
            trapezoid1.SetColor(QColor(255, 0, 0));
            trapezoid1.SetRotation(45, 45, 45);
            trapezoid1.SetName("trape1");
            trapezoid1.Init();

            Trapezoid trapezoid2(0.05, 0.05, 4, 4, 3, 6, 6, 6);
            trapezoid2.SetColor(QColor(0, 255, 0));
            trapezoid2.SetName("trape2");
            trapezoid2.Init();

            Trapezoid trapezoid3(0.2, 1, 0.2, 4, 3, -6, -6, -6);
            trapezoid3.SetColor(QColor(0, 0, 255));
            trapezoid3.SetName("trape3");
            trapezoid3.Init();

            assembly->AddModule(&trapezoid1);
            assembly->AddModule(&trapezoid2);
            assembly->AddModule(&trapezoid3);
        };

        auto test_sphere = [&]()
        {
            Sphere ball1(3, -10, 6, 0);
            ball1.SetColor(QColor(0,0,255));
            ball1.SetName("ball1");
            ball1.Init();

            assembly -> AddModule(&ball1);
        };

        test_assembly();
        //test_cube();
        //test_trapezoid();
        //test_sphere();
    }
}
