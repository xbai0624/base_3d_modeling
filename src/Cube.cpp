////////////////////////////////////////////////////////////////////////////////
// A class for describing cube geometry                                       //
//                                                                            //
//        Xinzhan Bai, Sep 05, 2022                                           //
////////////////////////////////////////////////////////////////////////////////

#include "Cube.h"
#include <iostream>
#include <iomanip>
#include <QMatrix4x4>
#include <QVector4D>

namespace base_cad
{
    Cube::Cube() : x_half_width(0), y_half_width(0), z_half_width(0),
    x_rot(0), y_rot(0), z_rot(0)
    {
        position.setX(0);
        position.setY(0);
        position.setZ(0);
    }

    Cube::~Cube()
    {
        Clear();
    }

    Cube::Cube(float x_half, float y_half, float z_half) :
        x_half_width(x_half), y_half_width(y_half), z_half_width(z_half),
        x_rot(0), y_rot(0), z_rot(0)
    {
        position.setX(0), position.setY(0), position.setZ(0);
    }

    Cube::Cube(float x_half, float y_half, float z_half, QVector3D pos) :
        position(pos),
        x_half_width(x_half), y_half_width(y_half), z_half_width(z_half),
        x_rot(0), y_rot(0), z_rot(0)
    {
    }

    Cube::Cube(float x_half, float y_half, float z_half, float x_pos, float y_pos, float z_pos)
        : x_half_width(x_half), y_half_width(y_half), z_half_width(z_half),
        x_rot(0), y_rot(0), z_rot(0)
    {
        position.setX(x_pos), position.setY(y_pos), position.setZ(z_pos);
    }

    Cube::Cube(const Cube &m) :
        Module(m),
        position(m.position),
        x_half_width(m.x_half_width), y_half_width(m.y_half_width), z_half_width(m.z_half_width),
        x_rot(0), y_rot(0), z_rot(0),
        triangles(m.triangles), elements(m.elements)
    {
    }

    Cube::Cube(Cube &&m):
        Module(m),
        position(std::move(m.position)),
        x_half_width(m.x_half_width), y_half_width(m.y_half_width), z_half_width(m.z_half_width),
        x_rot(0), y_rot(0), z_rot(0),
        triangles(std::move(m.triangles)), elements(std::move(m.elements))
    {
    }

    Cube Cube::operator=(const Cube &m)
    {
        if(this == &m)
            return *this;

        Cube tmp(m);
        *this = std::move(m);

        return *this;
    }

    Cube Cube::operator=(Cube &&m)
    {
        if(this == &m)
            return *this;

        Module::operator=(m);
        position = m.position;
        x_half_width = m.x_half_width, y_half_width = m.y_half_width, z_half_width = m.z_half_width;
        x_rot = m.x_rot, y_rot = m.y_rot, z_rot = m.z_rot;
        triangles = m.triangles;
        elements = m.elements;

        return *this;
    }

    void Cube::Clear()
    {
        Module::Clear();

        triangles.clear();
        elements.clear();
        corner_coords.clear();
    }

    void Cube::SetLength(float x_half, float y_half, float z_half)
    {
        x_half_width = x_half, y_half_width = y_half, z_half_width = z_half;
    }

    void Cube::SetPosition(float x_pos, float y_pos, float z_pos)
    {
        position.setX(x_pos), position.setY(y_pos), position.setZ(z_pos);
    }

    void Cube::SetRotation(float x_r, float y_r, float z_r)
    {
        x_rot = x_r, y_rot = y_r, z_rot = z_r;
    }

    void Cube::SetColor(QColor c)
    {
        if(m_module_color.size() != 0)
        {
            std::cerr<<__func__<<" Error: color list size() != 0,"<<std::endl
                <<"                color should be set at lowest level for primitive elements."
                <<std::endl;
            exit(0);
        }

        m_module_color[0] = c;
    }

    void Cube::Init()
    {
        Implement();
    }

    ////////////////////////////////////////////////////////////////////////////////
    // generate coordinate for the 8 corners (in cube-local coordinate)
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
    void Cube::GenerateCornerCoords()
    {
        corner_coords.resize(8);
        corner_coords[0] = QVector3D(-x_half_width, -y_half_width, -z_half_width);
        corner_coords[1] = QVector3D( x_half_width, -y_half_width, -z_half_width);
        corner_coords[2] = QVector3D( x_half_width, -y_half_width,  z_half_width);
        corner_coords[3] = QVector3D(-x_half_width, -y_half_width,  z_half_width);
        corner_coords[4] = QVector3D( x_half_width,  y_half_width, -z_half_width);
        corner_coords[5] = QVector3D( x_half_width,  y_half_width,  z_half_width);
        corner_coords[6] = QVector3D(-x_half_width,  y_half_width,  z_half_width);
        corner_coords[7] = QVector3D(-x_half_width,  y_half_width, -z_half_width);
    }

    // transform to world coord
    void Cube::Transform()
    {
        QMatrix4x4 T;
        T.setToIdentity();
        T.translate(position);
        T.rotate(x_rot, 1, 0, 0);
        T.rotate(y_rot, 0, 1, 0);
        T.rotate(z_rot, 0, 0, 1);

        for(size_t i=0; i<8; i++) {
            QVector4D v(corner_coords[i], 1);
            v = T * v;
            QVector3D tmp = v.toVector3DAffine();
            corner_coords[i] = tmp;
        }
    }

    void Cube::Implement()
    {
        GenerateCornerCoords();
        Transform();

        GenerateTriangles();
        GenerateTriangleElements();

        FillModule();
    }

    // generate triangles for OpenGL to render
    void Cube::GenerateTriangles()
    {
        // front face - two triangles compose one face
        triangles.push_back(corner_coords[0]);
        triangles.push_back(corner_coords[1]);
        triangles.push_back(corner_coords[3]);
        triangles.push_back(corner_coords[1]);
        triangles.push_back(corner_coords[2]);
        triangles.push_back(corner_coords[3]);
        // right face
        triangles.push_back(corner_coords[1]);
        triangles.push_back(corner_coords[2]);
        triangles.push_back(corner_coords[4]);
        triangles.push_back(corner_coords[2]);
        triangles.push_back(corner_coords[4]);
        triangles.push_back(corner_coords[5]);
        // back face
        triangles.push_back(corner_coords[4]);
        triangles.push_back(corner_coords[5]);
        triangles.push_back(corner_coords[6]);
        triangles.push_back(corner_coords[4]);
        triangles.push_back(corner_coords[6]);
        triangles.push_back(corner_coords[7]);
        // left face
        triangles.push_back(corner_coords[0]);
        triangles.push_back(corner_coords[3]);
        triangles.push_back(corner_coords[7]);
        triangles.push_back(corner_coords[3]);
        triangles.push_back(corner_coords[6]);
        triangles.push_back(corner_coords[7]);
        // top face
        triangles.push_back(corner_coords[2]);
        triangles.push_back(corner_coords[3]);
        triangles.push_back(corner_coords[6]);
        triangles.push_back(corner_coords[2]);
        triangles.push_back(corner_coords[5]);
        triangles.push_back(corner_coords[6]);
        // bottom face
        triangles.push_back(corner_coords[0]);
        triangles.push_back(corner_coords[1]);
        triangles.push_back(corner_coords[7]);
        triangles.push_back(corner_coords[1]);
        triangles.push_back(corner_coords[4]);
        triangles.push_back(corner_coords[7]);
    }

    void Cube::GenerateTriangleElements()
    {
        // reserved for future implementation
        //
        // this function should work in cooperation with triangles array
        // it is intended to use glDrawElement() function of OpenGL,
        // but it needs a reimplementation of triangles array, which I 
        // don't want to do at present, so fill 0 to avoid assersion failure

        if(m_module_triangle_elements.size() != 0)
        {
            std::cerr<<__func__<<" Error: triangle element array size() != 0,"<<std::endl
                <<"                element array should be filled at lowest level only for primitive elements."
                <<std::endl;
            exit(0);
        }
        m_module_triangle_elements[0] = std::vector<int>{0, 0, 0};
    }

    const std::vector<QVector3D> & Cube::GetTriangles() const
    {
        return triangles;
    }

    const std::vector<QVector3D> & Cube::GetCornerPoints() const
    {
        return corner_coords;
    }

    // fill members of module class
    void Cube::FillModule()
    {
        if(!IsEmpty()) {
            std::cerr<<__func__<<" Error: implementing a primitive cube, but its base class is not empty."
                <<std::endl;
            exit(0);
        }

        m_module[0] = this;

        // triangles
        std::vector<float> tmp_triangle;
        for(auto &i: triangles)
        {
            tmp_triangle.push_back(i.x());
            tmp_triangle.push_back(i.y());
            tmp_triangle.push_back(i.z());
        }
        m_module_triangles[0] = tmp_triangle;
        // elements
        m_module_triangle_elements[0] = elements;
    }

    void Cube::UnitTest()
    {
        std::cout<<"Cube class unit test..."<<std::endl;
        Cube cube(1, 1, 1, 10, 10, 10);
        cube.Init();

        const auto & eles = cube.GetCornerPoints();
        std::cout<<"corner size: "<<eles.size()<<std::endl;

        for(auto &i: eles) {
            std::cout<<std::setfill(' ')<<std::setw(5)<<i.x();
            std::cout<<std::setfill(' ')<<std::setw(5)<<i.y();
            std::cout<<std::setfill(' ')<<std::setw(5)<<i.z();
            std::cout<<std::endl;
        }
    }
}
