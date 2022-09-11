#ifndef __TUBE_H__
#define __TUBE_H__

#include "Module.h"
#include <vector>
#include <QVector3D>

namespace base_cad
{
    class Tube : public Module
    {
    public:
        Tube();
        Tube(float r_min, float r_max, float z_half, float angle);
        Tube(float r_min, float r_max, float z_half, float angle, QVector3D pos);
        Tube(float r_min, float r_max, float z_half, float angle, float x_pos, float y_pos, float z_pos);
        Tube(const Tube& m);
        Tube(Tube &&m);
        Tube operator=(const Tube& m);
        Tube operator=(Tube &&m);
        ~Tube();

        void SetLength(float r_min, float r_max, float z_half, float angle);
        void SetPosition(float x_pos, float y_pos, float z_pos);
        void SetRotation(float x_r, float y_r, float z_r);
        virtual void SetColor(QColor c) override;
        const std::vector<QVector3D> & GetTriangles() const;
        const std::vector<QVector3D> & GetCornerPoints() const;
        void Init();
        void UnitTest();

    protected:
        void Implement();
        void Transform();
        void Clear();

    private:
        void GenerateCornerCoords();
        void GenerateTriangles();
        void GenerateTriangleVertexIndex();
        void FillModule();

    private:
        QVector3D position;
        float r_min;
        float r_max;
        float z_half_width;
        float angle;

        float x_rot;
        float y_rot;
        float z_rot;

        std::vector<QVector3D> triangles; // stores vertices of all triangles
        std::vector<float> triangle_edge_config;
        std::vector<int> triangle_vertex_index;

        std::vector<QVector3D> corner_coords;
    };
}

#endif
