#include "ConfigReader.h"
#include "APVMapping.h"
#include <iostream>
#include <QColor>

namespace base_cad
{
    ConfigReader::ConfigReader()
    {
    }

    ConfigReader::~ConfigReader()
    {
    }

    void ConfigReader::ReadAPVMapping(const char* path)
    {
        map = apv_mapping::Mapping::Instance();
        map -> LoadMap(path);

        SetupVolume();
    }

    Module * ConfigReader::GetCompleteAssembly() const
    {
        return assembly;
    }

    void ConfigReader::SetupVolume()
    {
        if(assembly == nullptr)
            assembly = new Module();
        else
            assembly->Clear();

        // an infn xy chamber
        Cube an_infnchamber; 

        // an uva xy chamber
        Cube top_plane(0.5/2., 0.417/2., 0.08/2, 0, -0.03, 0.04/2);
        top_plane.SetColor(QColor(1, 1, 1));
        top_plane.Init();
        Cube bottom_plane(0.65/2., 0.48/2., 0.01/2., 0, 0, -0.01/2);
        bottom_plane.SetColor(QColor(1, 1, 1));
        bottom_plane.Init();

        Module uvaxychamber;
        uvaxychamber.AddModule(&top_plane); 
        uvaxychamber.AddModule(&bottom_plane);

        // an apv volume unit
        float df = 0.01;
        Cube an_apv((0.05-df)/2., (0.04-df)/2., 0.005);

        // an uva layer
        float dy = 0.56;
        Module *l1m0 = new Module(uvaxychamber);
        l1m0 -> Transform(0, -dy, 0, 0, 0, 180);
        Module *l1m1 = new Module(uvaxychamber);
        l1m1 -> Transform(0, 0, 0, 0, 0, 180);
        Module *l1m2 = new Module(uvaxychamber);
        l1m2 -> Transform(0, dy, 0);
        Module *l1m3 = new Module(uvaxychamber);
        l1m3 -> Transform(0, 2*dy, 0);

        Module *layer = new Module();

        layer -> AddModule(l1m0);
        layer -> AddModule(l1m1);
        layer -> AddModule(l1m2);
        layer -> AddModule(l1m3);

        // entire assembly
        float x_rot = 10., y_rot = -65., z_rot = -5.;
        Module *layer1 = new Module(*layer);
        layer1 -> Transform(0., 0, 0, x_rot, y_rot, z_rot);
        Module *layer2 = new Module(*layer);
        layer2 -> Transform(0.5, 0, 0, x_rot, y_rot, z_rot);
        Module *layer3 = new Module(*layer);
        layer3 -> Transform(1.0, 0, 0, x_rot, y_rot, z_rot);
        Module *layer4 = new Module(*layer);
        layer4 -> Transform(1.5, 0, 0, x_rot, y_rot, z_rot);
        Module *layer5 = new Module(*layer);
        layer5 -> Transform(-0.5, 0, 0, x_rot, y_rot, z_rot);
        Module *layer6 = new Module(*layer);
        layer6 -> Transform(-1.0, 0, 0, x_rot, y_rot, z_rot);
        Module *layer7 = new Module(*layer);
        layer7 -> Transform(-1.5, 0, 0, x_rot, y_rot, z_rot);
        Module *layer8 = new Module(*layer);
        layer8 -> Transform(-2.0, 0, 0, x_rot, y_rot, z_rot);

        assembly -> AddModule(layer1);
        assembly -> AddModule(layer2);
        assembly -> AddModule(layer3);
        assembly -> AddModule(layer4);
        assembly -> AddModule(layer5);
        assembly -> AddModule(layer6);
        assembly -> AddModule(layer7);
        assembly -> AddModule(layer8);

        assembly -> Transform(0.25, -0.25, 0);
    }
}
