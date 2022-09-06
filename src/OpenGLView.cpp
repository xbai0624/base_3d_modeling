#include "OpenGLView.h"
#include <QOpenGLShaderProgram>
#include <QMouseEvent>
#include <vector>
#include <iostream>
#include <iomanip>
#include "Module.h"

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
        return QSize(500, 500);
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
        glClearColor(1.0, 1.0, 1.0, 0);

        m_program = new QOpenGLShaderProgram;
        QString vertex_shader_file("./glsl/vertex_shader.glsl");
        QString fragment_shader_file("./glsl/fragment_shader.glsl");
        m_program -> addShaderFromSourceFile(QOpenGLShader::Vertex, vertex_shader_file);
        m_program -> addShaderFromSourceFile(QOpenGLShader::Fragment, fragment_shader_file);
        m_program -> bindAttributeLocation("vertex", 0);
        m_program -> bindAttributeLocation("normal", 1);
        m_program -> link();

        m_program -> bind();
        m_projMatrixLoc = m_program -> uniformLocation("projMatrix");
        m_mvMatrixLoc = m_program -> uniformLocation("mvMatrix");
        m_normalMatrixLoc = m_program -> uniformLocation("normalMatrix");
        m_lightPosLoc = m_program -> uniformLocation("lightPos");

        m_vao.create();
        QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

        m_data.create();
        m_data.bind();
        m_data.allocate(content_data, content_data_length * sizeof(GLfloat));

        setupVertexAttribs();

        // set light position to a large value in case some part can't get light
        //m_program -> setUniformValue(m_lightPosLoc, QVector3D(0, 0, 7000));
        m_program -> setUniformValue(m_lightPosLoc, QVector3D(-90, 90, -90));
        m_program -> release();
    }

    void OpenGLView::setupVertexAttribs()
    {
        m_data.bind();
        QOpenGLFunctions *f = QOpenGLContext::currentContext() -> functions();
        f -> glEnableVertexAttribArray(0);
        f -> glEnableVertexAttribArray(1);

        f -> glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat),
                nullptr);
        f -> glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat),
                reinterpret_cast<void*>(0*sizeof(GLfloat)));

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

        glDrawArrays(GL_TRIANGLES, 0, content_data_length);

        m_program -> release();
    }

    void OpenGLView::resizeGL(int width, int height)
    {
        // project matrix
        m_proj.setToIdentity();
        m_proj.perspective(25.f, GLfloat(width)/height, 0.2f, 1000.0f);
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
            content_data[i] = fvec[i];
        }
    }
}