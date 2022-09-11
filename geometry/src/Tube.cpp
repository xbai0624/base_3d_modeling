////////////////////////////////////////////////////////////////////////////////
// A class for describing tube geometry                                       //
//                                                                            //
//        Xinzhan Bai, Sep 05, 2022                                           //
////////////////////////////////////////////////////////////////////////////////

#include "Tube.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <QMatrix4x4>
#include <QVector4D>

namespace base_cad
{
    #define Phi_Bins 40
    #define PI 3.14159265358979323846264
    #define radian (PI/180.)

    Tube::Tube() : r_min(0), r_max(0), z_half_width(0), angle(0),
    x_rot(0), y_rot(0), z_rot(0)
    {
        position.setX(0);
        position.setY(0);
        position.setZ(0);
    }

    Tube::~Tube()
    {
        Clear();
    }

    Tube::Tube(float rmin, float rmax, float zhalf, float agl) :
        r_min(rmin), r_max(rmax), z_half_width(zhalf), angle(agl),
        x_rot(0), y_rot(0), z_rot(0)
    {
        position.setX(0), position.setY(0), position.setZ(0);
    }

    Tube::Tube(float rmin, float rmax, float zhalf, float agl, QVector3D pos) :
        position(pos),
        r_min(rmin), r_max(rmax), z_half_width(zhalf), angle(agl),
        x_rot(0), y_rot(0), z_rot(0)
    {
    }

    Tube::Tube(float rmin, float rmax, float zhalf, float agl, float x_pos, float y_pos, float z_pos)
        : r_min(rmin), r_max(rmax), z_half_width(zhalf), angle(agl),
        x_rot(0), y_rot(0), z_rot(0)
    {
        position.setX(x_pos), position.setY(y_pos), position.setZ(z_pos);
    }

    Tube::Tube(const Tube &m) :
        Module(m),
        position(m.position),
        r_min(m.r_min), r_max(m.r_max), z_half_width(m.z_half_width),
        angle(m.angle), x_rot(m.x_rot), y_rot(m.y_rot), z_rot(m.z_rot),
        triangles(m.triangles), triangle_edge_config(m.triangle_edge_config),
        triangle_vertex_index(m.triangle_vertex_index), corner_coords(m.corner_coords)
    {
    }

    Tube::Tube(Tube &&m):
        Module(m),
        position(std::move(m.position)),
        r_min(m.r_min), r_max(m.r_max), z_half_width(m.z_half_width),
        angle(m.angle), x_rot(m.x_rot), y_rot(m.y_rot), z_rot(m.z_rot),
        triangles(std::move(m.triangles)), triangle_edge_config(std::move(m.triangle_edge_config)),
        triangle_vertex_index(std::move(m.triangle_vertex_index)),
        corner_coords(std::move(m.corner_coords))
    {
    }

    Tube Tube::operator=(const Tube &m)
    {
        if(this == &m)
            return *this;

        Tube tmp(m);
        *this = std::move(m);

        return *this;
    }

    Tube Tube::operator=(Tube &&m)
    {
        if(this == &m)
            return *this;

        Module::operator=(m);
        position = m.position;
        r_min = m.r_min, r_max = m.r_max, z_half_width = m.z_half_width;
        angle = m.angle, x_rot = m.x_rot, y_rot = m.y_rot, z_rot = m.z_rot;
        triangles = std::move(m.triangles);
        triangle_edge_config = std::move(m.triangle_edge_config);
        triangle_vertex_index = std::move(m.triangle_vertex_index);
        corner_coords = std::move(m.corner_coords);

        return *this;
    }

    void Tube::Clear()
    {
        Module::Clear();

        triangles.clear();
        triangle_edge_config.clear();
        triangle_vertex_index.clear();
        corner_coords.clear();
    }

    void Tube::SetLength(float rmin, float rmax, float z_half, float agl)
    {
        r_min = rmin, r_max = rmax, z_half_width = z_half, angle = agl;
    }

    void Tube::SetPosition(float x_pos, float y_pos, float z_pos)
    {
        position.setX(x_pos), position.setY(y_pos), position.setZ(z_pos);
    }

    void Tube::SetRotation(float x_r, float y_r, float z_r)
    {
        x_rot = x_r, y_rot = y_r, z_rot = z_r;
    }

    void Tube::SetColor(QColor c)
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

    void Tube::Init()
    {
        Implement();
    }

    ////////////////////////////////////////////////////////////////////////////////
    // generate coordinate for the corners (in tube-local coordinate)
    // right-hand coordinate,
    // Y axis pointing to the screen, X axis points to the right, Z axis points upward
    //
    // The following diagram shows corner point index
    //
    //     (6)-*-------*(5)
    //       - -     - -
    //   (3)*-----(2)* -
    //      |  *(7)--|-*(4)
    //      | -      |-
    //   (0)*--------*(1)
    //
    void Tube::GenerateCornerCoords()
    {
        float dphi = angle / Phi_Bins;
        for(int i=0; i<Phi_Bins; i++)
        {
            float phi_low = i*dphi;
            float phi_max = phi_low + dphi;

            float x1 = r_max * cos(phi_low * radian);
            float y1 = r_max * sin(phi_low * radian);
            float x2 = r_max * cos(phi_max * radian);
            float y2 = r_max * sin(phi_max * radian);
 
            float x3 = r_min * cos(phi_low * radian);
            float y3 = r_min * sin(phi_low * radian);
            float x4 = r_min * cos(phi_max * radian);
            float y4 = r_min * sin(phi_max * radian);

            corner_coords.push_back(QVector3D(x1, y1, -z_half_width));
            corner_coords.push_back(QVector3D(x2, y2, -z_half_width));
            corner_coords.push_back(QVector3D(x2, y2,  z_half_width));
            corner_coords.push_back(QVector3D(x1, y1,  z_half_width));
            corner_coords.push_back(QVector3D(x4, y4, -z_half_width));
            corner_coords.push_back(QVector3D(x4, y4,  z_half_width));
            corner_coords.push_back(QVector3D(x3, y3,  z_half_width));
            corner_coords.push_back(QVector3D(x3, y3, -z_half_width));
        }
    }

    // transform to world coord
    void Tube::Transform()
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

    void Tube::Implement()
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
    void Tube::GenerateTriangles()
    {
        int N = (int)corner_coords.size();
        assert(N % 8 == 0);
        N /= 8;
        for(int i=0; i<N; i++)
        {
            int offset = i * 8;
            // front face - two triangles compose one face
            triangles.push_back(corner_coords[offset + 0]);
            HIDE_EDGE;
            triangles.push_back(corner_coords[offset + 1]);
            if(i == 0 && angle < 360.)
                SHOW_EDGE;
            else
                HIDE_EDGE;
            triangles.push_back(corner_coords[offset + 3]);
            SHOW_EDGE;

            triangles.push_back(corner_coords[offset + 1]);
            SHOW_EDGE;
            triangles.push_back(corner_coords[offset + 2]);
            HIDE_EDGE;
            triangles.push_back(corner_coords[offset + 3]);
            if(i == (N-1) && angle < 360.)
                SHOW_EDGE;
            else
                HIDE_EDGE;

            if(i == (N-1)){
                // right face, only draw for the last one
                triangles.push_back(corner_coords[offset + 1]);
                HIDE_EDGE;
                triangles.push_back(corner_coords[offset + 4]);
                SHOW_EDGE;
                triangles.push_back(corner_coords[offset + 2]);
                SHOW_EDGE;

                triangles.push_back(corner_coords[offset + 4]);
                SHOW_EDGE;
                triangles.push_back(corner_coords[offset + 5]);
                HIDE_EDGE;
                triangles.push_back(corner_coords[offset + 2]);
                SHOW_EDGE;
            }

            // back face
            triangles.push_back(corner_coords[offset + 4]);
            SHOW_EDGE;
            triangles.push_back(corner_coords[offset + 6]);
            if(i == (N-1) && angle < 360.)
                SHOW_EDGE;
            else
                HIDE_EDGE;
            triangles.push_back(corner_coords[offset + 5]);
            HIDE_EDGE;

            triangles.push_back(corner_coords[offset + 4]);
            if(i == 0 && angle < 360.)
                SHOW_EDGE;
            else
                HIDE_EDGE;
            triangles.push_back(corner_coords[offset + 7]);
            HIDE_EDGE;
            triangles.push_back(corner_coords[offset + 6]);
            SHOW_EDGE;

            if(i == 0) {
                // left face, only draw for the first one
                triangles.push_back(corner_coords[offset + 0]);
                HIDE_EDGE;
                triangles.push_back(corner_coords[offset + 3]);
                SHOW_EDGE;
                triangles.push_back(corner_coords[offset + 7]);
                SHOW_EDGE;

                triangles.push_back(corner_coords[offset + 3]);
                SHOW_EDGE;
                triangles.push_back(corner_coords[offset + 6]);
                HIDE_EDGE;
                triangles.push_back(corner_coords[offset + 7]);
                SHOW_EDGE;
            }

            // top face
            triangles.push_back(corner_coords[offset + 2]);
            if(i == 0 && angle < 360.)
                SHOW_EDGE;
            else
                HIDE_EDGE;
            triangles.push_back(corner_coords[offset + 6]);
            SHOW_EDGE;
            triangles.push_back(corner_coords[offset + 3]);
            HIDE_EDGE;

            triangles.push_back(corner_coords[offset + 2]);
            SHOW_EDGE;
            triangles.push_back(corner_coords[offset + 5]);
            HIDE_EDGE;
            triangles.push_back(corner_coords[offset + 6]);
            if(i == (N-1) && angle < 360.)
                SHOW_EDGE;
            else
                HIDE_EDGE;

            // bottom face
            triangles.push_back(corner_coords[offset + 1]);
            if(i == 0 && angle < 360.)
                SHOW_EDGE;
            else
                HIDE_EDGE;
            triangles.push_back(corner_coords[offset + 0]);
            HIDE_EDGE;
            triangles.push_back(corner_coords[offset + 7]);
            SHOW_EDGE;

            triangles.push_back(corner_coords[offset + 1]);
            SHOW_EDGE;
            triangles.push_back(corner_coords[offset + 7]);
            if(i == (N-1) && angle < 360.)
                SHOW_EDGE;
            else 
                HIDE_EDGE;
            triangles.push_back(corner_coords[offset + 4]);
            HIDE_EDGE;
        }
    }

    void Tube::GenerateTriangleVertexIndex()
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

    const std::vector<QVector3D> & Tube::GetTriangles() const
    {
        return triangles;
    }

    const std::vector<QVector3D> & Tube::GetCornerPoints() const
    {
        return corner_coords;
    }

    // fill members of module class
    void Tube::FillModule()
    {
        if(!IsEmpty()) {
            std::cerr<<__PRETTY_FUNCTION__<<" Error: implementing a primitive tube, but its base class is not empty."
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

    void Tube::UnitTest()
    {
        std::cout<<"Tube class unit test..."<<std::endl;
        Tube tube(1, 2, 1, 10, 10, 10, 10);
        tube.Init();

        const auto & eles = tube.GetCornerPoints();
        std::cout<<"corner size: "<<eles.size()<<std::endl;

        for(auto &i: eles) {
            std::cout<<std::setfill(' ')<<std::setw(5)<<i.x();
            std::cout<<std::setfill(' ')<<std::setw(5)<<i.y();
            std::cout<<std::setfill(' ')<<std::setw(5)<<i.z();
            std::cout<<std::endl;
        }
    }
}
