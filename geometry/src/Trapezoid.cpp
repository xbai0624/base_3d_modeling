////////////////////////////////////////////////////////////////////////////////
// A class for describing trapezoid geometry                                  //
//                                                                            //
//        Xinzhan Bai, Sep 05, 2022                                           //
////////////////////////////////////////////////////////////////////////////////

#include "Trapezoid.h"
#include <iostream>
#include <iomanip>
#include <QMatrix4x4>
#include <QVector4D>

namespace base_cad
{
    Trapezoid::Trapezoid() : top_x_half_width(0), top_y_half_width(0),
    btm_x_half_width(0), btm_y_half_width(0), z_half_width(0),
    x_rot(0), y_rot(0), z_rot(0)
    {
        position.setX(0);
        position.setY(0);
        position.setZ(0);

        color = DEFAULT_COLOR;
    }

    Trapezoid::~Trapezoid()
    {
        Clear();
    }

    Trapezoid::Trapezoid(float top_x_half, float top_y_half,
            float btm_x_half, float btm_y_half, float z_half) :
        top_x_half_width(top_x_half), top_y_half_width(top_y_half),
        btm_x_half_width(btm_x_half), btm_y_half_width(btm_y_half), z_half_width(z_half),
        x_rot(0), y_rot(0), z_rot(0)
    {
        position.setX(0), position.setY(0), position.setZ(0);
        color = DEFAULT_COLOR;
    }

    Trapezoid::Trapezoid(float top_x_half, float top_y_half,
            float btm_x_half, float btm_y_half, float z_half, QVector3D pos) :
        top_x_half_width(top_x_half), top_y_half_width(top_y_half),
        btm_x_half_width(btm_x_half), btm_y_half_width(btm_y_half), z_half_width(z_half),
        position(pos),
        x_rot(0), y_rot(0), z_rot(0), color(DEFAULT_COLOR)
    {
    }

    Trapezoid::Trapezoid(float top_x_half, float top_y_half,
            float btm_x_half, float btm_y_half, float z_half,
            float x_pos, float y_pos, float z_pos)
        : top_x_half_width(top_x_half), top_y_half_width(top_y_half),
        btm_x_half_width(btm_x_half), btm_y_half_width(btm_y_half), z_half_width(z_half),
        x_rot(0), y_rot(0), z_rot(0)
    {
        position.setX(x_pos), position.setY(y_pos), position.setZ(z_pos);
        color = DEFAULT_COLOR;
    }

    Trapezoid::Trapezoid(const Trapezoid &m) :
        Module(m),
        top_x_half_width(m.top_x_half_width), top_y_half_width(m.top_y_half_width),
        btm_x_half_width(m.btm_x_half_width), btm_y_half_width(m.btm_y_half_width),
        z_half_width(m.z_half_width),
        position(m.position),
        x_rot(m.x_rot), y_rot(m.y_rot), z_rot(m.z_rot),
        triangles(m.triangles), triangle_edge_config(m.triangle_edge_config),
        triangle_vertex_index(m.triangle_vertex_index), corner_coords(m.corner_coords),
        color(m.color)
    {
    }

    Trapezoid::Trapezoid(Trapezoid &&m):
        Module(m),
        top_x_half_width(m.top_x_half_width), top_y_half_width(m.top_y_half_width),
        btm_x_half_width(m.btm_x_half_width), btm_y_half_width(m.btm_y_half_width),
        z_half_width(m.z_half_width),
        position(std::move(m.position)),
        x_rot(m.x_rot), y_rot(m.y_rot), z_rot(m.z_rot),
        triangles(std::move(m.triangles)), triangle_edge_config(std::move(m.triangle_edge_config)),
        triangle_vertex_index(std::move(m.triangle_vertex_index)),
        corner_coords(std::move(m.corner_coords)),
        color(std::move(m.color))
    {
    }

    Trapezoid Trapezoid::operator=(const Trapezoid &m)
    {
        if(this == &m)
            return *this;

        Trapezoid tmp(m);
        *this = std::move(m);

        return *this;
    }

    Trapezoid Trapezoid::operator=(Trapezoid &&m)
    {
        if(this == &m)
            return *this;

        Module::operator=(m);
        top_x_half_width = m.top_x_half_width, top_y_half_width = m.top_y_half_width;
        btm_x_half_width = m.btm_x_half_width, btm_y_half_width = m.btm_y_half_width;
        z_half_width = m.z_half_width;
        position = m.position;
        x_rot = m.x_rot, y_rot = m.y_rot, z_rot = m.z_rot;
        triangles = std::move(m.triangles);
        triangle_edge_config = std::move(m.triangle_edge_config);
        triangle_vertex_index = std::move(m.triangle_vertex_index);
        corner_coords = std::move(m.corner_coords);
        color = std::move(m.color);

        return *this;
    }

    void Trapezoid::Clear()
    {
        Module::Clear();

        triangles.clear();
        triangle_edge_config.clear();
        triangle_vertex_index.clear();
        corner_coords.clear();
    }

    void Trapezoid::SetLength(float top_x_half, float top_y_half,
            float btm_x_half, float btm_y_half, float z_half)
    {
        top_x_half_width = top_x_half, top_y_half_width = top_y_half;
        btm_x_half_width = btm_x_half, btm_y_half_width = btm_y_half;
        z_half_width = z_half;
    }

    void Trapezoid::SetPosition(float x_pos, float y_pos, float z_pos)
    {
        position.setX(x_pos), position.setY(y_pos), position.setZ(z_pos);
    }

    void Trapezoid::SetRotation(float x_r, float y_r, float z_r)
    {
        x_rot = x_r, y_rot = y_r, z_rot = z_r;
    }

    void Trapezoid::SetColor(QColor c)
    {
        if(m_module_color.size() != 0)
        {
            std::cerr<<__PRETTY_FUNCTION__<<" Error: color list size() != 0,"<<std::endl
                <<"                color should be set at lowest level for primitive elements."
                <<std::endl;
            exit(0);
        }

        color = c;
    }

    void Trapezoid::Init()
    {
        Implement();
    }

    ////////////////////////////////////////////////////////////////////////////////
    // generate coordinate for the 8 corners (in trapezoid-local coordinate)
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
    void Trapezoid::GenerateCornerCoords()
    {
        corner_coords.resize(8);
        corner_coords[0] = QVector3D(-btm_x_half_width, -btm_y_half_width, -z_half_width);
        corner_coords[1] = QVector3D( btm_x_half_width, -btm_y_half_width, -z_half_width);
        corner_coords[2] = QVector3D( top_x_half_width, -top_y_half_width,  z_half_width);
        corner_coords[3] = QVector3D(-top_x_half_width, -top_y_half_width,  z_half_width);
        corner_coords[4] = QVector3D( btm_x_half_width,  btm_y_half_width, -z_half_width);
        corner_coords[5] = QVector3D( top_x_half_width,  top_y_half_width,  z_half_width);
        corner_coords[6] = QVector3D(-top_x_half_width,  top_y_half_width,  z_half_width);
        corner_coords[7] = QVector3D(-btm_x_half_width,  btm_y_half_width, -z_half_width);
    }

    // transform to world coord
    void Trapezoid::Transform()
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

    void Trapezoid::Implement()
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
    void Trapezoid::GenerateTriangles()
    {
        // front face - two triangles compose one face
        triangles.push_back(corner_coords[0]);
        HIDE_EDGE;
        triangles.push_back(corner_coords[1]);
        SHOW_EDGE;
        triangles.push_back(corner_coords[3]);
        SHOW_EDGE;

        triangles.push_back(corner_coords[1]);
        SHOW_EDGE;
        triangles.push_back(corner_coords[2]);
        HIDE_EDGE;
        triangles.push_back(corner_coords[3]);
        SHOW_EDGE;

        // right face
        triangles.push_back(corner_coords[1]);
        HIDE_EDGE;
        triangles.push_back(corner_coords[4]);
        SHOW_EDGE;
        triangles.push_back(corner_coords[2]);
        SHOW_EDGE;

        triangles.push_back(corner_coords[4]);
        SHOW_EDGE;
        triangles.push_back(corner_coords[5]);
        HIDE_EDGE;
        triangles.push_back(corner_coords[2]);
        SHOW_EDGE;

        // back face
        triangles.push_back(corner_coords[4]);
        SHOW_EDGE;
        triangles.push_back(corner_coords[6]);
        SHOW_EDGE;
        triangles.push_back(corner_coords[5]);
        HIDE_EDGE;

        triangles.push_back(corner_coords[4]);
        SHOW_EDGE;
        triangles.push_back(corner_coords[7]);
        HIDE_EDGE;
        triangles.push_back(corner_coords[6]);
        SHOW_EDGE;

        // left face
        triangles.push_back(corner_coords[0]);
        HIDE_EDGE;
        triangles.push_back(corner_coords[3]);
        SHOW_EDGE;
        triangles.push_back(corner_coords[7]);
        SHOW_EDGE;

        triangles.push_back(corner_coords[3]);
        SHOW_EDGE;
        triangles.push_back(corner_coords[6]);
        HIDE_EDGE;
        triangles.push_back(corner_coords[7]);
        SHOW_EDGE;

        // top face
        triangles.push_back(corner_coords[2]);
        SHOW_EDGE;
        triangles.push_back(corner_coords[6]);
        SHOW_EDGE;
        triangles.push_back(corner_coords[3]);
        HIDE_EDGE;

        triangles.push_back(corner_coords[2]);
        SHOW_EDGE;
        triangles.push_back(corner_coords[5]);
        HIDE_EDGE;
        triangles.push_back(corner_coords[6]);
        SHOW_EDGE;

        // bottom face
        triangles.push_back(corner_coords[1]);
        SHOW_EDGE;
        triangles.push_back(corner_coords[0]);
        HIDE_EDGE;
        triangles.push_back(corner_coords[7]);
        SHOW_EDGE;

        triangles.push_back(corner_coords[1]);
        SHOW_EDGE;
        triangles.push_back(corner_coords[7]);
        SHOW_EDGE;
        triangles.push_back(corner_coords[4]);
        HIDE_EDGE;
    }

    void Trapezoid::GenerateTriangleVertexIndex()
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

    const std::vector<QVector3D> & Trapezoid::GetTriangles() const
    {
        return triangles;
    }

    const std::vector<QVector3D> & Trapezoid::GetCornerPoints() const
    {
        return corner_coords;
    }

    // fill members of module class
    void Trapezoid::FillModule()
    {
        if(!IsEmpty()) {
            std::cerr<<__PRETTY_FUNCTION__<<" Error: implementing a primitive trapezoid, but its base class is not empty."
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
        // color
        m_module_color[0] = color;
    }

    void Trapezoid::UnitTest()
    {
        std::cout<<"Trapezoid class unit test..."<<std::endl;
        Trapezoid trapezoid(1, 1, 4, 4, 1, 10, 10, 10);
        trapezoid.Init();

        const auto & eles = trapezoid.GetCornerPoints();
        std::cout<<"corner size: "<<eles.size()<<std::endl;

        for(auto &i: eles) {
            std::cout<<std::setfill(' ')<<std::setw(5)<<i.x();
            std::cout<<std::setfill(' ')<<std::setw(5)<<i.y();
            std::cout<<std::setfill(' ')<<std::setw(5)<<i.z();
            std::cout<<std::endl;
        }
    }
}
