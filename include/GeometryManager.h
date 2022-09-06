#ifndef __GEOMETRY_MANAGER_H__
#define __GEOMETRY_MANAGER_H__

#include <string>

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

    private:
        std::string path;
        Module *module = nullptr;
    };
}

#endif