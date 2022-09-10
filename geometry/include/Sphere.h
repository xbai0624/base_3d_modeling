#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Module.h"
#include <vector>
#include <QVector3D>

namespace base_cad
{
    class Sphere : public Module
    {
    public:
        Sphere();
        Sphere(float r);
        Sphere(float r, QVector3D pos);
        Sphere(float r, float x_pos, float y_pos, float z_pos);
        Sphere(const Sphere& m);
        Sphere(Sphere &&m);
        Sphere operator=(const Sphere& m);
        Sphere operator=(Sphere &&m);
        ~Sphere();

        void SetRadius(float r);
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
        float r;

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
