#include "GeometryView.h"
#include <QHBoxLayout>

#include "OpenGLView.h"
#include "GeometryManager.h"

namespace base_cad
{
    GeometryView::GeometryView(QWidget *parent) : QWidget(parent)
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
}
