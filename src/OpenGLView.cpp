////////////////////////////////////////////////////////////////////////////////
// A class for setting up OpenGL enviroments                                  //
//                                                                            //
//        Xinzhan Bai, Sep 06, 2022                                           //
////////////////////////////////////////////////////////////////////////////////

#include "OpenGLView.h"
#include <QOpenGLShaderProgram>
#include <QMouseEvent>
#include <vector>
#include <iostream>
#include <iomanip>
#include "Module.h"
#include "GeometryManager.h"

namespace base_cad
{
    OpenGLView::OpenGLView(QWidget *parent) : QOpenGLWidget(parent)
    {
        content_data_length = 0;

        //draw a logo for start screen
        start_logo();

        // enable anti aliasing
        QSurfaceFormat fmt = format();
        fmt.setSamples(4);
        setFormat(fmt);
    }

    OpenGLView::~OpenGLView()
    {
        cleanup();
    }

    QSize OpenGLView::minimumSizeHint() const
    {
        return QSize(50, 50);
    }

    QSize OpenGLView::sizeHint() const
    {
        return QSize(1000, 900);
    }

    void OpenGLView::cleanup()
    {
        if(m_program == nullptr)
            return;

        makeCurrent();

        m_data.destroy();
        delete m_program;
        m_program = nullptr;

        doneCurrent();
    }

    void OpenGLView::initializeGL()
    {
        connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &OpenGLView::cleanup);

        initializeOpenGLFunctions();
        //glClearColor(1.0, 1.0, 1.0, 0);
        glClearColor(.0, .0, .0, 0);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // opengl wireframe mode
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // opengl normal/fill/default mode

        m_program = new QOpenGLShaderProgram;
        QString vertex_shader_file("./glsl/vertex_shader.glsl");
        QString geometry_shader_file("./glsl/geometry_shader.glsl");
        QString fragment_shader_file("./glsl/fragment_shader.glsl");
        m_program -> addShaderFromSourceFile(QOpenGLShader::Vertex, vertex_shader_file);
        m_program -> addShaderFromSourceFile(QOpenGLShader::Fragment, fragment_shader_file);
        m_program -> addShaderFromSourceFile(QOpenGLShader::Geometry, geometry_shader_file);
        m_program -> bindAttributeLocation("vertex", 0);
        m_program -> bindAttributeLocation("normal", 1);
        m_program -> bindAttributeLocation("color", 2);
        m_program -> bindAttributeLocation("edge_exclude", 3);
        m_program -> link();

        m_program -> bind();
        m_projMatrixLoc = m_program -> uniformLocation("projMatrix");
        m_mvMatrixLoc = m_program -> uniformLocation("mvMatrix");
        m_normalMatrixLoc = m_program -> uniformLocation("normalMatrix");
        m_lightPosLoc = m_program -> uniformLocation("lightPos");
        m_WinScaleLoc = m_program -> uniformLocation("WIN_SCALE");

        m_vao.create();
        QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

        m_data.create();
        m_data.bind();
        m_data.allocate(content_data, content_data_length * sizeof(GLfloat));

        setupVertexAttribs();

        // set light position to a large value in case some part can't get light
        m_program -> setUniformValue(m_lightPosLoc, QVector3D(-900, 900, 7000));
        //m_program -> setUniformValue(m_lightPosLoc, QVector3D(-90, 90, -90));
        m_program -> release();
    }

    void OpenGLView::setupVertexAttribs()
    {
        m_data.bind();
        QOpenGLFunctions *f = QOpenGLContext::currentContext() -> functions();
        f -> glEnableVertexAttribArray(0);
        f -> glEnableVertexAttribArray(1);
        f -> glEnableVertexAttribArray(2);
        f -> glEnableVertexAttribArray(3);

        // data array organization: (x, y, z, r, g, b, edge_property)
        f -> glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat),
                nullptr);
        f -> glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat),
                reinterpret_cast<void*>(0*sizeof(GLfloat)));
        f -> glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat),
                reinterpret_cast<void*>(3*sizeof(GLfloat)));
        f -> glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat),
                reinterpret_cast<void*>(6*sizeof(GLfloat)));

        m_data.release();
    }

    void OpenGLView::paintGL()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

        m_program -> bind();

        // model matrix
        m_world.setToIdentity();
        m_world.scale(scale);
        m_world.rotate(m_xRot / 16., 1, 0, 0);
        m_world.rotate(m_yRot / 16., 0, 1, 0);
        m_world.rotate(m_zRot / 16., 0, 0, 1);

        // view matrix
        m_camera.setToIdentity();
        m_camera.translate(0, 0, -10.); // place camera at (0, 0, -10);

        m_program -> setUniformValue(m_projMatrixLoc, m_proj);
        m_program -> setUniformValue(m_mvMatrixLoc, m_camera * m_world);

        // color
        QMatrix3x3 normalMatrix = m_world.normalMatrix();
        m_program -> setUniformValue(m_normalMatrixLoc, normalMatrix);

        // window size
        m_program -> setUniformValue(m_WinScaleLoc, QVector2D(1000, 900));

        glDrawArrays(GL_TRIANGLES, 0, content_data_length);
        //glDrawArrays(GL_LINES, 0, content_data_length);
        //glDrawArrays(GL_POINTS, 0, content_data_length);

        m_program -> release();
    }

    void OpenGLView::resizeGL(int width, int height)
    {
        // project matrix
        m_proj.setToIdentity();
        m_proj.perspective(20.f, GLfloat(width)/height, 0.05, 1000.0f);
    }

    void OpenGLView::mousePressEvent(QMouseEvent *event)
    {
        m_lastPos = event -> pos();
    }

    void OpenGLView::mouseMoveEvent(QMouseEvent *event)
    {
        int dx = event->x() - m_lastPos.x();
        int dy = event->y() - m_lastPos.y();

        if(event->buttons() & Qt::LeftButton)
        {
            setXRotation(m_xRot + 8*dy);
            setYRotation(m_yRot + 8*dx);
        }
        else if(event -> buttons() & Qt::RightButton)
        {
            setXRotation(m_xRot + 8*dy);
            setZRotation(m_yRot + 8*dx);
        }

        m_lastPos = event->pos();
    }

    void OpenGLView::wheelEvent(QWheelEvent *event)
    {
        m_lastPos = event -> position().toPoint();
        QPoint numDegrees = event -> angleDelta();
        float y_rot = numDegrees.y()/8.;

        if(y_rot < 0)
            scale/=1.1;
        if(y_rot > 0)
            scale *= 1.1;

        update();
    }

    static void normalize_angle(int &angle)
    {
        while(angle < 0)
            angle += 360 * 16;
        while(angle > 360*16)
            angle -= 360 * 16;
    }

    void OpenGLView::setXRotation(int angle)
    {
        normalize_angle(angle);
        if(angle != m_xRot)
        {
            m_xRot = angle;
            emit xRotationChanged(angle);
            update();
        }
    }

    void OpenGLView::setYRotation(int angle)
    {
        normalize_angle(angle);
        if(angle != m_yRot)
        {
            m_yRot = angle;
            emit yRotationChanged(angle);
            update();
        }
    }

    void OpenGLView::setZRotation(int angle)
    {
        normalize_angle(angle);
        if(angle != m_zRot)
        {
            m_zRot = angle;
            emit zRotationChanged(angle);
            update();
        }
    }

    void OpenGLView::setModule(Module *m)
    {
        module = m;
    }

    void OpenGLView::setGeometryManager(GeometryManager *m)
    {
        geo_manager = m;

        Module *tmp_module = geo_manager -> GetModule();
        setModule(tmp_module);

        copyContentDataFromModule();
    }

    void OpenGLView::copyContentDataFromModule()
    {
        if(module == nullptr) {
            std::cerr<<__PRETTY_FUNCTION__<<" Error: Module is empty."
                <<std::endl;
            exit(0);
        }

        const std::unordered_map<int, std::vector<QVector3D>> & triangles =
            module -> GetModuleTriangles();
        const std::unordered_map<int, QColor> & colors =
            module -> GetModuleColors();
        const std::unordered_map<int, std::vector<float>> &triangle_edge_configs =
            module -> GetModuleTriangleEdgeConfigs();

        if(content_data_length > 0)
            delete[] content_data;

        content_data_length = module -> GetNumberOfVertices();
        // each triangle has 3 vertices
        std::cout<<"INFO:: "<<__PRETTY_FUNCTION__<<": total triangle primitives to draw: "
            <<content_data_length / 3 <<std::endl;

        if(content_data_length <= 0) {
            std::cerr<<__PRETTY_FUNCTION__<<" Error: module has empty triangle array."
                <<std::endl;
            exit(0);
        }

        // content data array is arranged in this way:
        // x_coord, y_coord, z_coord, r_color, g_color, b_color, edge_config
        // so total length of array should be 7 * content_data_length
        content_data = new float[7 * content_data_length];
        content_data_length = 7 * content_data_length;

        // copy vertex, color & edge config
        size_t index = 0;
        for(auto &i: triangles)
        {
            float r = colors.at(i.first).redF();
            float g = colors.at(i.first).greenF();
            float b = colors.at(i.first).blueF();

            const std::vector<float> &edge_vector = triangle_edge_configs.at(i.first);
            int edge_index = 0;

            for(auto &j: i.second)
            {
                content_data[index++] = j.x();
                content_data[index++] = j.y();
                content_data[index++] = j.z();
                content_data[index++] = r;
                content_data[index++] = g;
                content_data[index++] = b;
                content_data[index] = edge_vector[edge_index];
                edge_index++;
                index++;
            }
        }
    }

    void OpenGLView::start_logo()
    {
        // clear buffer
        if(content_data_length > 0)
            delete[] content_data;
        content_data_length = 0;

        std::vector<float> fvec =
        {
              -1, -1, 0,
            -0.5, -1, 0,
               1,  1, 0,
              -1, -1, 0,
               1,  1, 0,
             0.5,  1, 0,

             0.5, -1, 0,
               1, -1, 0,
              -1,  1, 0,
               1, -1, 0,
              -1,  1, 0,
            -0.5,  1, 0
        };

        content_data_length = (int)fvec.size();
        content_data = new float[content_data_length];

        for(int i=0; i<content_data_length; i++)
        {
            content_data[i] = fvec[i] * 0.5;
        }
    }
}
