#include "Module.h"

namespace base_cad
{
    Module::Module()
    {
        // place holder
    }

    Module::Module(const Module& m)
    {
    }

    Module::~Module()
    {
        m_module.clear();
        m_module_triangles.clear();
        m_module_triangle_elements.clear();
    }

    const std::unordered_map<int, std::vector<float>> & Module::GetModuleTriangles() const
    {
        return m_module_triangles;
    }

    const std::unordered_map<int, std::vector<int>> & Module::GetModuleTriangleElements() const
    {
        return m_module_triangle_elements;
    }

    const std::unordered_map<int, Module*> & Module::GetModules() const
    {
        return m_module;
    }
}
