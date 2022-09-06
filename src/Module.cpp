////////////////////////////////////////////////////////////////////////////////
// A Geometry Container class                                                 //
//                                                                            //
//        Xinzhan Bai, Sep 05, 2022                                           //
////////////////////////////////////////////////////////////////////////////////

#include "Module.h"
#include <cassert>

namespace base_cad
{
    // default ctor
    Module::Module()
    {
        // place holder
    }

    // copy ctor
    Module::Module(const Module& m)
        : m_module(m.m_module), m_module_triangles(m.m_module_triangles),
        m_module_triangle_elements(m.m_module_triangle_elements),
        m_module_color(m.m_module_color)
    {
    }

    // move ctor
    Module::Module(Module &&m)
        : m_module(std::move(m.m_module)), m_module_triangles(std::move(m.m_module_triangles)),
        m_module_triangle_elements(std::move(m.m_module_triangle_elements)),
        m_module_color(std::move(m.m_module_color))
    {
    }

    // copy assignment
    Module Module::operator=(const Module &m)
    {
        if(&m == this)
            return *this;

        Module tmp(m);
        *this = std::move(tmp);

        return *this;
    }

    // move assignment
    Module Module::operator=(Module &&m)
    {
        if(this == &m)
            return *this;

        m_module = std::move(m.m_module);
        m_module_triangles = std::move(m.m_module_triangles);
        m_module_triangle_elements = std::move(m.m_module_triangle_elements);
        m_module_color = std::move(m.m_module_color);

        return *this;
    }

    Module::~Module()
    {
        Clear();
    }

    void Module::Clear()
    {
        m_module.clear();
        m_module_triangles.clear();
        m_module_triangle_elements.clear();
        m_module_color.clear();
    }

    bool Module::HasChild()
    {
        if(m_module.size() <= 1)
            return false;
        return true;
    }

    bool Module::IsEmpty()
    {
        if(m_module.size() < 1)
            return true;
        return false;
    }

    void Module::AddModule(Module *m)
    {
        if(m -> IsEmpty())
            return;

        if(!(m -> HasChild()))
        {
            size_t index = m_module.size();
            assert(m_module_triangles.size() == index);
            assert(m_module_triangle_elements.size() == index);
            assert(m_module_color.size() == index);

            m_module[index] = m;

            const std::unordered_map<int, std::vector<float>> & triangles =
                m -> GetModuleTriangles();
            const std::unordered_map<int, std::vector<int>> & elements =
                m -> GetModuleTriangleElements();
            const std::unordered_map<int, QColor> & colors =
                m -> GetModuleColors();

            m_module_triangles[index] =  triangles.at(0);
            m_module_triangle_elements[index] = elements.at(0);
            m_module_color[index] = colors.at(0);
        }
        else
        {
            const std::unordered_map<int, Module*> & module_list = m -> GetModules();
            for(auto &i: module_list)
            {
                AddModule(i.second);
            }
        }
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

    const std::unordered_map<int, QColor> & Module::GetModuleColors() const
    {
        return m_module_color;
    }

    void Module::SetColor([[maybe_unused]] QColor c)
    {
        // place holder, this function should be implemented in subclass
    }

    int Module::GetTriangleLength()
    {
        int length = 0;
        for(auto &i: m_module_triangles)
            length += (int)i.second.size();
        return length;
    }
}
