////////////////////////////////////////////////////////////////////////////////
// A Geometry Container class                                                 //
//                                                                            //
//        Xinzhan Bai, Sep 05, 2022                                           //
////////////////////////////////////////////////////////////////////////////////

#include "Module.h"
#include <cassert>
#include <QMatrix4x4>
#include <iostream>
#include <iomanip>

namespace base_cad
{
    // default ctor
    Module::Module()
    {
        name = "";
    }

    // copy ctor
    Module::Module(const Module& m)
        : m_module_triangles(m.m_module_triangles),
        m_module_triangle_vertex_index(m.m_module_triangle_vertex_index),
        m_module_triangle_edge_configs(m.m_module_triangle_edge_configs),
        m_module_color(m.m_module_color), m_module_name(m.m_module_name),
        name(m.name)
    {
        // copy all modules referenced by pointers
        if(m.HasChild())
        {
            for(auto &i: m.m_module)
            {
                m_module[i.first] = new Module(*i.second);
            }
        }
        else
        {
            m_module[0] = this; // if no child modules, then a module points to itself
        }
    }

    // move ctor
    Module::Module(Module &&m)
        : m_module(std::move(m.m_module)), m_module_triangles(std::move(m.m_module_triangles)),
        m_module_triangle_vertex_index(std::move(m.m_module_triangle_vertex_index)),
        m_module_triangle_edge_configs(m.m_module_triangle_edge_configs),
        m_module_color(std::move(m.m_module_color)), m_module_name(std::move(m.m_module_name)),
        name(std::move(m.name))
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
        m_module_triangle_vertex_index = std::move(m.m_module_triangle_vertex_index);
        m_module_triangle_edge_configs = std::move(m.m_module_triangle_edge_configs);
        m_module_color = std::move(m.m_module_color);
        m_module_name = std::move(m.m_module_name);
        name = std::move(m.name);

        return *this;
    }

    Module::~Module()
    {
        Clear();
    }

    void Module::Clear()
    {
        m_module_triangles.clear();
        m_module_triangle_vertex_index.clear();
        m_module_triangle_edge_configs.clear();
        m_module_color.clear();
        m_module_name.clear();
        name = "";

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
            assert(m_module_triangle_vertex_index.size() == index);
            assert(m_module_triangle_edge_configs.size() == index);
            assert(m_module_color.size() == index);
            assert(m_module_name.size() == index);

            // AddModule() will make a copy of the original moudle
            m_module[index] = new Module(*m);

            const std::unordered_map<int, std::vector<QVector3D>> & triangles =
                m -> GetModuleTriangles();
            const std::unordered_map<int, std::vector<int>> & elements =
                m -> GetModuleTriangleVertexIndex();
            const std::unordered_map<int, std::vector<float>> &edges =
                m -> GetModuleTriangleEdgeConfigs();
            const std::unordered_map<int, QColor> & colors =
                m -> GetModuleColors();
            const std::unordered_map<int, QString> &names =
                m -> GetModuleNameMap();

            assert(triangles.size() == 1);
            assert(elements.size() == 1);
            assert(colors.size() == 1);
            assert(edges.size() == 1);
            assert(names.size() == 1);

            m_module_triangles[index] =  triangles.at(0);
            m_module_triangle_vertex_index[index] = elements.at(0);
            m_module_triangle_edge_configs[index] = edges.at(0);
            m_module_color[index] = colors.at(0);
            m_module_name[index] = names.at(0);
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

    const std::unordered_map<int, std::vector<QVector3D>> & Module::GetModuleTriangles() const
    {
        return m_module_triangles;
    }

    const std::unordered_map<int, std::vector<int>> & Module::GetModuleTriangleVertexIndex() const
    {
        return m_module_triangle_vertex_index;
    }

    const std::unordered_map<int, Module*> & Module::GetModules() const
    {
        return m_module;
    }

    const std::unordered_map<int, QColor> & Module::GetModuleColors() const
    {
        return m_module_color;
    }

    const std::unordered_map<int, QString> & Module::GetModuleNameMap() const
    {
        return m_module_name;
    }

    const std::unordered_map<int, std::vector<float>> & Module::GetModuleTriangleEdgeConfigs() const
    {
        return m_module_triangle_edge_configs;
    }

    void Module::SetColor([[maybe_unused]] QColor c)
    {
        // place holder, this function should be implemented in subclass
    }

    void Module::SetPosition([[maybe_unused]] float x, [[maybe_unused]] float y, [[maybe_unused]] float z)
    {
        // place holder, this function should be implemented in subclass
    }

    void Module::SetRotation([[maybe_unused]] float x, [[maybe_unused]] float y, [[maybe_unused]] float z)
    {
        // place holder, this function should be implemented in subclass
    }

    void Module::Init()
    {
        // place holder, this function should be implemented in subclass
    }

    void Module::SetName(QString _n)
    {
        name = _n;
    }

    int Module::GetNumberOfVertices()
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

            std::vector<QVector3D> tmp;
            for(size_t index=0; index<unit_length; index++)
            {
                QVector4D v_tmp(i.second[index], 1);
                v_tmp = T * v_tmp;

                tmp.push_back(v_tmp.toVector3DAffine());
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

    void Module::DebugInfo()
    {
        std::cout<<"#####################################################"<<std::endl;
        std::cout<<"#################### Module #########################"<<std::endl;
        std::cout<<std::setprecision(6)<<std::setfill(' ')<<std::setw(10);
        for(auto &i: m_module_triangles) {
            std::cout<<std::endl;
            std::cout<<"triangles::Module index: "<<i.first<<std::endl;
            for(auto &j: i.second) {
                std::cout<<"("<<j.x()<<", "<<j.y()<<", "<<j.z()<<"), ";
            }
            std::cout<<std::endl;
        }
        for(auto &i: m_module_color){
            std::cout<<std::endl;
            std::cout<<"colors::Module index: "<<i.first<<std::endl;
            std::cout<<i.second.redF()<<", "<<i.second.greenF()<<", "<<i.second.blueF()
                     <<std::endl;
        }
        for(auto &i: m_module_triangle_edge_configs){
            std::cout<<std::endl;
            std::cout<<"triangle edge configs::Module Index: "<<i.first<<std::endl;
            for(auto &j: i.second) {
                std::cout<<"("<<j<<")";
            }
            std::cout<<std::endl;
        }
    }
}
