#ifndef __CUBE_H__
#define __CUBE_H__

#include "Module.h"
#include <vector>
#include <QVector3D>

namespace base_cad
{
    class Cube : public Module
    {
    public:
        Cube();
        Cube(float x_half, float y_half, float z_half);
        Cube(float x_half, float y_half, float z_half, QVector3D pos);
        Cube(float x_half, float y_half, float z_half, float x_pos, float y_pos, float z_pos);
        Cube(const Cube& m);
        Cube(Cube &&m);
        Cube operator=(const Cube& m);
        Cube operator=(Cube &&m);
        ~Cube();

        void SetLength(float x_half, float y_half, float z_half);
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
        float x_half_width;
        float y_half_width;
        float z_half_width;

        float x_rot;
        float y_rot;
        float z_rot;

        std::vector<QVector3D> triangles; // stores vertices of all triangles
        std::vector<float> triangle_edge_config;
        std::vector<int> triangle_vertex_index;

        std::vector<QVector3D> corner_coords;

        QColor color;
    };
}

#endif
