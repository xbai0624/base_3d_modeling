////////////////////////////////////////////////////////////////////////////////
// This is the Main Window Class, an Entrance class which contains            //
// both GeometryManager and OpenGLView class                                  //
//                                                                            //
//        Xinzhan Bai, Sep 06, 2022                                           //
////////////////////////////////////////////////////////////////////////////////

#include "GeometryView.h"
#include <QHBoxLayout>

#include "OpenGLView.h"
#include "GeometryManager.h"

namespace base_cad
{
    GeometryView::GeometryView(QWidget *parent) : QWidget(parent)
                                                  , input_path("")
    {
        setWindowTitle("geometry view");

        gl_view = new OpenGLView();
        geo_manager = new GeometryManager();
        geo_manager -> ReadGeometry();
        gl_view -> setGeometryManager(geo_manager);

        QHBoxLayout *layout = new QHBoxLayout(this);
        layout -> addWidget(gl_view);
    }

    GeometryView::~GeometryView()
    {
    }

    void GeometryView::SetPath(const char* path)
    {
        input_path = path;
    }
}
