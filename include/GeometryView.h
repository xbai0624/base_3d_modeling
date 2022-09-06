#ifndef GEOMETRY_VIEW_H
#define GEOMETRY_VIEW_H

#include <QWidget>

namespace base_cad
{
    class OpenGLView;
    class GeometryManager;

    class GeometryView : public QWidget
    {
        Q_OBJECT

    public:
        GeometryView(QWidget *parent = nullptr);
        ~GeometryView();

    private:
        OpenGLView *gl_view;
        GeometryManager *geo_manager;
    };
}

#endif
