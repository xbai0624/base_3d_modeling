#ifndef GEOMETRY_VIEW_H
#define GEOMETRY_VIEW_H

#include "OpenGLView.h"

namespace base_cad
{
    class GeometryView : public QWidget
    {
        Q_OBJECT

    public:
        GeometryView(QWidget *parent = nullptr);
        ~GeometryView();

    private:
        OpenGLView *gl_view;
    };
}

#endif
