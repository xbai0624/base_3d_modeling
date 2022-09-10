////////////////////////////////////////////////////////////////////////////////
// A class for describing sphere geometry                                     //
//                                                                            //
//        Xinzhan Bai, Sep 05, 2022                                           //
////////////////////////////////////////////////////////////////////////////////

#include "Sphere.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <QMatrix4x4>
#include <QVector4D>

namespace base_cad
{
    // control how smooth the ball is, larger number means finer surface
    #define Phi_Bins 40
    #define Theta_Bins 40
    #define PI 3.14159265358979323846264

    Sphere::Sphere() : r(0),
    x_rot(0), y_rot(0), z_rot(0)
    {
        position.setX(0);
        position.setY(0);
        position.setZ(0);
    }

    Sphere::~Sphere()
    {
        Clear();
    }

    Sphere::Sphere(float _r) :
        r(_r), x_rot(0), y_rot(0), z_rot(0)
    {
        position.setX(0), position.setY(0), position.setZ(0);
    }

    Sphere::Sphere(float _r, QVector3D pos) :
        position(pos), r(_r), x_rot(0), y_rot(0), z_rot(0)
    {
    }

    Sphere::Sphere(float _r, float x_pos, float y_pos, float z_pos)
        : r(_r), x_rot(0), y_rot(0), z_rot(0)
    {
        position.setX(x_pos), position.setY(y_pos), position.setZ(z_pos);
    }

    Sphere::Sphere(const Sphere &m) :
        Module(m),
        position(m.position),
        r(m.r),
        x_rot(0), y_rot(0), z_rot(0),
        triangles(m.triangles), triangle_edge_config(m.triangle_edge_config),
        triangle_vertex_index(m.triangle_vertex_index), corner_coords(m.corner_coords)
    {
    }

    Sphere::Sphere(Sphere &&m):
        Module(m),
        position(std::move(m.position)),
        r(m.r),
        x_rot(0), y_rot(0), z_rot(0),
        triangles(std::move(m.triangles)), triangle_edge_config(std::move(m.triangle_edge_config)),
        triangle_vertex_index(std::move(m.triangle_vertex_index)),
        corner_coords(std::move(m.corner_coords))
    {
    }

    Sphere Sphere::operator=(const Sphere &m)
    {
        if(this == &m)
            return *this;

        Sphere tmp(m);
        *this = std::move(m);

        return *this;
    }

    Sphere Sphere::operator=(Sphere &&m)
    {
        if(this == &m)
            return *this;

        Module::operator=(m);
        position = m.position;
        r = m.r;
        x_rot = m.x_rot, y_rot = m.y_rot, z_rot = m.z_rot;
        triangles = std::move(m.triangles);
        triangle_edge_config = std::move(m.triangle_edge_config);
        triangle_vertex_index = std::move(m.triangle_vertex_index);
        corner_coords = std::move(m.corner_coords);

        return *this;
    }

    void Sphere::Clear()
    {
        Module::Clear();

        triangles.clear();
        triangle_edge_config.clear();
        triangle_vertex_index.clear();
        corner_coords.clear();
    }

    void Sphere::SetRadius(float _r)
    {
        r = _r;
    }

    void Sphere::SetPosition(float x_pos, float y_pos, float z_pos)
    {
        position.setX(x_pos), position.setY(y_pos), position.setZ(z_pos);
    }

    void Sphere::SetRotation(float x_r, float y_r, float z_r)
    {
        x_rot = x_r, y_rot = y_r, z_rot = z_r;
    }

    void Sphere::SetColor(QColor c)
    {
        if(m_module_color.size() != 0)
        {
            std::cerr<<__PRETTY_FUNCTION__<<" Error: color list size() != 0,"<<std::endl
                <<"                color should be set at lowest level for primitive elements."
                <<std::endl;
            exit(0);
        }

        m_module_color[0] = c;
    }

    void Sphere::Init()
    {
        Implement();
    }

    ////////////////////////////////////////////////////////////////////////////////
    // generate coordinate for the mesh (in sphere-local coordinate)
    // right-hand coordinate,
    // Y axis pointing to the screen, X axis points to the right, Z axis points upward
    //
    // origin is sphere center
    //
    // mesh unit:
    //   (2)*---*(3)
    //      |   |
    //   (0)*---*(1)
    //
    void Sphere::GenerateCornerCoords()
    {
        float dTheta = 180./Theta_Bins;
        float dPhi = 360./Phi_Bins;
        float radian = PI / 180.;

        auto compute_xyz = [&](float theta, float phi, float &x, float &y, float &z)
        {
            z = r * cos(theta*radian);
            x = abs(r * sin(theta*radian)) * cos(phi*radian);
            y = abs(r * sin(theta*radian)) * sin(phi*radian);
            if(theta < 0.) {
                z = -z;
            }
        };

        for(int i=0; i<Theta_Bins; i++)
        {
            float theta_low = -90. + i*dTheta;
            float theta_high = theta_low + dTheta;

            for(int j=0; j<Phi_Bins; j++)
            {
                float phi_low = j*dPhi, phi_high = (j+1.0)*dPhi;

                float x, y, z;

                // point 0
                compute_xyz(theta_low, phi_low, x, y, z);
                corner_coords.push_back(QVector3D(x, y, z));
                // point 1
                compute_xyz(theta_low, phi_high, x, y, z);
                corner_coords.push_back(QVector3D(x, y, z));
                // point 2
                compute_xyz(theta_high, phi_low, x, y, z);
                corner_coords.push_back(QVector3D(x, y, z));
                // point 3
                compute_xyz(theta_high, phi_high, x, y, z);
                corner_coords.push_back(QVector3D(x, y, z));
            }
        }
    }

    // transform to world coord
    void Sphere::Transform()
    {
        QMatrix4x4 T;
        T.setToIdentity();
        T.translate(position);
        T.rotate(x_rot, 1, 0, 0);
        T.rotate(y_rot, 0, 1, 0);
        T.rotate(z_rot, 0, 0, 1);

        for(size_t i=0; i<corner_coords.size(); i++) {
            QVector4D v(corner_coords[i], 1);
            v = T * v;
            QVector3D tmp = v.toVector3DAffine();
            corner_coords[i] = tmp;
        }
    }

    void Sphere::Implement()
    {
        GenerateCornerCoords();
        Transform();

        GenerateTriangles();
        GenerateTriangleVertexIndex();

        FillModule();
    }

    ////////////////////////////////////////////////////////////////////////////////
    // generate triangles for OpenGL to render
    //
    // edge config:
    //    0: show this edge
    //    1: hide this edge, never show it. This means that
    //       this edge joins two triangles which are in the same surface
    //
    //    reference: https://developer.download.nvidia.com/whitepapers/2007/SDK10/SolidWireframe.pdf
    // 
    // edge index convention:
    //    OpenGL use default anti-clock wise order,
    //    edge index follow the vertex index: 
    //    edge0 is the one p0 points to, it has no intersection with p0,
    //    and so on: edge 1 is ...
    //
    //    reference: https://stackoverflow.com/questions/8142388/in-what-order-should-i-send-my-vertices-to-opengl-for-culling
    //
    void Sphere::GenerateTriangles()
    {
        int N = (int)corner_coords.size();
        assert(N % 4 == 0);
        N/=4;

        for(int i=0; i<N; i++)
        {
            int idx = 4 * i;

            triangles.push_back(corner_coords[idx]);
            triangle_edge_config.push_back(1); // for sphere, edge should always be hidden
            triangles.push_back(corner_coords[idx+1]);
            triangle_edge_config.push_back(1);
            triangles.push_back(corner_coords[idx+2]);
            triangle_edge_config.push_back(1);

            triangles.push_back(corner_coords[idx+1]);
            triangle_edge_config.push_back(1);
            triangles.push_back(corner_coords[idx+2]);
            triangle_edge_config.push_back(1);
            triangles.push_back(corner_coords[idx+3]);
            triangle_edge_config.push_back(1);
        }
    }

    void Sphere::GenerateTriangleVertexIndex()
    {
        // reserved for future implementation
        //
        // this function should work in cooperation with triangles array
        // it is intended to use glDrawElement() function of OpenGL,
        // but it needs a reimplementation of triangles array, which I 
        // don't want to do at present, so fill 0 to avoid assersion failure

        if(m_module_triangle_vertex_index.size() != 0)
        {
            std::cerr<<__PRETTY_FUNCTION__<<" Error: triangle element array size() != 0,"<<std::endl
                <<"                element array should be filled at lowest level only for primitive elements."
                <<std::endl;
            exit(0);
        }
        m_module_triangle_vertex_index[0] = std::vector<int>{0, 0, 0};
    }

    const std::vector<QVector3D> & Sphere::GetTriangles() const
    {
        return triangles;
    }

    const std::vector<QVector3D> & Sphere::GetCornerPoints() const
    {
        return corner_coords;
    }

    // fill members of module class
    void Sphere::FillModule()
    {
        if(!IsEmpty()) {
            std::cerr<<__PRETTY_FUNCTION__<<" Error: implementing a primitive sphere, but its base class is not empty."
                <<std::endl;
            exit(0);
        }

        m_module[0] = this;

        // triangles
        m_module_triangles[0] = triangles;
        // edges
        m_module_triangle_edge_configs[0] = triangle_edge_config;
        // elements
        m_module_triangle_vertex_index[0] = triangle_vertex_index;
        // names
        m_module_name[0] = name;
    }

    void Sphere::UnitTest()
    {
        std::cout<<"Sphere class unit test..."<<std::endl;
        Sphere sphere(1, 10, 10, 10);
        sphere.Init();

        const auto & eles = sphere.GetCornerPoints();
        std::cout<<"corner size: "<<eles.size()<<std::endl;

        for(auto &i: eles) {
            std::cout<<std::setfill(' ')<<std::setw(5)<<i.x();
            std::cout<<std::setfill(' ')<<std::setw(5)<<i.y();
            std::cout<<std::setfill(' ')<<std::setw(5)<<i.z();
            std::cout<<std::endl;
        }
    }
}
