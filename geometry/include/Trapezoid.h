#ifndef __TRAPEZOID_H__
#define __TRAPEZOID_H__

#include "Module.h"
#include <vector>
#include <QVector3D>

namespace base_cad
{
    class Trapezoid : public Module
    {
    public:
        Trapezoid();
        Trapezoid(float top_x_half, float top_y_half, float btm_x_half, float btm_y_half, float z_half);
        Trapezoid(float top_x_half, float top_y_half, float btm_x_half, float btm_y_half, float z_half, QVector3D pos);
        Trapezoid(float top_x_half, float top_y_half, float btm_x_half, float btm_y_half, float z_half, float x_pos, float y_pos, float z_pos);
        Trapezoid(const Trapezoid& m);
        Trapezoid(Trapezoid &&m);
        Trapezoid operator=(const Trapezoid& m);
        Trapezoid operator=(Trapezoid &&m);
        ~Trapezoid();

        void SetLength(float top_x_half, float top_y_half, float btm_x_half, float btm_y_half, float z_half);
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
        float top_x_half_width;
        float top_y_half_width;
        float btm_x_half_width;
        float btm_y_half_width;
        float z_half_width;

        QVector3D position;

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
