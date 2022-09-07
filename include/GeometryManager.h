#ifndef __GEOMETRY_MANAGER_H__
#define __GEOMETRY_MANAGER_H__

#include <string>
#include "GeometryBuilder.h"

namespace base_cad
{
    class Module;

    class GeometryManager
    {
    public:
        GeometryManager();
        ~GeometryManager();

        void SetFile(const char* path);
        Module * GetModule() const;

        void ReadGeometry();

    protected:
        void load_text_file();
        void convert_to_module();
        void convert_to_module_test();

    private:
        std::string path;
        Module *module = nullptr;

        GeometryBuilder *geo_builder = nullptr;
    };
}

#endif
