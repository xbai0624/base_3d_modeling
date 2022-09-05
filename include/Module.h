#ifndef __MODULE_H__
#define __MODULE_H__

#include <unordered_map>
#include <vector>

namespace base_cad
{
    class Module
    {
    public:
        Module();
        Module(const Module &m);
        Module(Module &&m);
        Module operator=(const Module& m);
        Module operator=(Module &&m);

        ~Module();

        const std::unordered_map<int, std::vector<float>>& GetModuleTriangles() const;
        const std::unordered_map<int, std::vector<int>>& GetModuleTriangleElements() const;

    protected:
        const std::unordered_map<int, Module*>& GetModules() const;

    private:
        std::unordered_map<int, Module*> m_module;
        std::unordered_map<int, std::vector<float>> m_module_triangles;
        std::unordered_map<int, std::vector<int>> m_module_triangle_elements;
    };
}

#endif
