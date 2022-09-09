#ifndef __MODULE_H__
#define __MODULE_H__

#include <unordered_map>
#include <vector>
#include <QColor>
#include <QVector3D>

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

        void AddModule(Module *m);
        const std::unordered_map<int, std::vector<QVector3D>> & GetModuleTriangles() const;
        const std::unordered_map<int, std::vector<int>> & GetModuleTriangleVertexIndex() const;
        const std::unordered_map<int, std::vector<float>> & GetModuleTriangleEdgeConfigs() const;
        const std::unordered_map<int, QColor> & GetModuleColors() const;
        void Clear();
        virtual void SetColor(QColor c);
        int GetNumberOfVertices();
        virtual void Transform(float x_pos, float y_pos, float z_pos,
                float x_rot=0., float y_rot = 0., float z_rot = 0.);
        void DebugInfo();

    protected:
        const std::unordered_map<int, Module*>& GetModules() const;
        bool IsEmpty() const;
        bool HasChild() const;

    protected:
        std::unordered_map<int, Module*> m_module;
        std::unordered_map<int, std::vector<QVector3D>> m_module_triangles;
        std::unordered_map<int, std::vector<int>> m_module_triangle_vertex_index;
        std::unordered_map<int, std::vector<float>> m_module_triangle_edge_configs;
        std::unordered_map<int, QColor> m_module_color;
    };
}

#endif
