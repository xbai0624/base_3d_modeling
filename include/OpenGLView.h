#ifndef __OPENGL_VIEW_H__
#define __OPENGL_VIEW_H__

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

class QOpenGLShaderProgram; // this is a global class

namespace base_cad
{
    class Module; // only use Module the one from base_cad namespace
    class GeometryManager;

    class OpenGLView : public QOpenGLWidget, protected QOpenGLFunctions
    {
        Q_OBJECT

    public:
        OpenGLView(QWidget *parent = nullptr);
        ~OpenGLView();

        QSize minimumSizeHint() const override;
        QSize sizeHint() const override;

        void setModule(Module *m);
        void setGeometryManager(GeometryManager* manager);

    public slots:
        void setXRotation(int angle);
        void setYRotation(int angle);
        void setZRotation(int angle);
        void cleanup();
    signals:
        void xRotationChanged(int angle);
        void yRotationChanged(int angle);
        void zRotationChanged(int angle);

    protected:
        void initializeGL() override;
        void paintGL() override;
        void resizeGL(int height, int width) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void wheelEvent(QWheelEvent *event) override;

    private:
        void setupVertexAttribs();
        void copyContentDataFromModule();
        void start_logo();

    private:
        QOpenGLVertexArrayObject m_vao;
        QOpenGLBuffer m_data;
        QOpenGLBuffer m_data_index;
        QOpenGLShaderProgram *m_program = nullptr;

        int m_projMatrixLoc = 0;
        int m_mvMatrixLoc = 0;
        int m_normalMatrixLoc = 0;
        int m_lightPosLoc = 0;
        int m_WinScaleLoc = 0;

        // transformation
        QMatrix4x4 m_proj;
        QMatrix4x4 m_camera;
        QMatrix4x4 m_world;
        int m_xRot = 0;
        int m_yRot = 0;
        int m_zRot = 0;
        QPoint m_lastPos;

        float *content_data;
        int content_data_length;

        int *content_data_index; // reserved
        int content_data_index_length; // reserved

        Module *module = nullptr;
        GeometryManager *geo_manager = nullptr;

        float scale = 1.0;
    };
}

#endif
