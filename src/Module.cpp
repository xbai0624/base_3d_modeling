////////////////////////////////////////////////////////////////////////////////
// A Geometry Container class                                                 //
//                                                                            //
//        Xinzhan Bai, Sep 05, 2022                                           //
////////////////////////////////////////////////////////////////////////////////

#include "Module.h"
#include <cassert>
#include <QMatrix4x4>
#include <iostream>
namespace base_cad
{
    // default ctor
    Module::Module()
    {
        // place holder
    }

    // copy ctor
    Module::Module(const Module& m)
        : m_module_triangles(m.m_module_triangles),
        m_module_triangle_elements(m.m_module_triangle_elements),
        m_module_color(m.m_module_color)
    {
        // copy module
        if(m.HasChild())
        {
            for(auto &i: m.m_module)
            {
                m_module[i.first] = new Module(*i.second);
            }
        }
        else
        {
            m_module[0] = this;
        }
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
        m_module_triangles.clear();
        m_module_triangle_elements.clear();
        m_module_color.clear();

        if(HasChild())
        {
            for(auto &i: m_module)
                i.second -> Clear();
        }

        m_module.clear();
    }

    bool Module::HasChild() const
    {
        if(m_module.size() <= 1)
            return false;
        return true;
    }

    bool Module::IsEmpty() const
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

            // AddModule will make a copy of the original moudle
            m_module[index] = new Module(*m);

            const std::unordered_map<int, std::vector<float>> & triangles =
                m -> GetModuleTriangles();
            const std::unordered_map<int, std::vector<int>> & elements =
                m -> GetModuleTriangleElements();
            const std::unordered_map<int, QColor> & colors =
                m -> GetModuleColors();

            assert(triangles.size() == 1);
            assert(elements.size() == 1);
            assert(colors.size() == 1);

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

    // transform the assembly as a whole
    void Module::Transform(float x_pos, float y_pos, float z_pos,
                float x_rot, float y_rot, float z_rot)
    {
        QMatrix4x4 T;
        T.setToIdentity();
        T.translate(x_pos, y_pos, z_pos);
        T.rotate(x_rot, 1, 0, 0);
        T.rotate(y_rot, 0, 1, 0);
        T.rotate(z_rot, 0, 0, 1);

        // transform triangles
        for(auto &i: m_module_triangles)
        {
            size_t unit_length = i.second.size();
            if(unit_length <= 0)
                continue;

            assert(unit_length % 3 == 0);
            size_t n = unit_length / 3;

            std::vector<float> tmp;
            for(size_t index=0; index<n; index++)
            {
                QVector4D v_tmp(i.second[3*index], i.second[3*index+1], i.second[3*index+2], 1);
                v_tmp = T * v_tmp;

                tmp.push_back(v_tmp.x()), tmp.push_back(v_tmp.y()), tmp.push_back(v_tmp.z());
            }

            m_module_triangles[i.first].clear();
            m_module_triangles[i.first] = tmp;
        }

        // transform submodules
        if(HasChild())
        {
            for(auto &i: m_module)
                i.second -> Transform(x_pos, y_pos, z_pos, x_rot, y_rot, z_rot);
        }
    }
}
