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
        Cube top_plane(0.5/2., 0.417/2., 0.04/2, 0, -0.03, 0.04/2);
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
        float dy = 0.5;
        Module *l1m0 = new Module(uvaxychamber);
        l1m0 -> Transform(0, -2*dy, 0);
        Module *l1m1 = new Module(uvaxychamber);
        l1m1 -> Transform(0, -dy, 0);
        Module *l1m2 = new Module(uvaxychamber);
        l1m2 -> Transform(0, dy, 0);
        Module *l1m3 = new Module(uvaxychamber);
        l1m3 -> Transform(0, 2*dy, 0);

        assembly -> AddModule(l1m0);
        assembly -> AddModule(l1m1);
        assembly -> AddModule(l1m2);
        assembly -> AddModule(l1m3);
    }
}
