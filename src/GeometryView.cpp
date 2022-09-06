#include "GeometryView.h"
#include <QHBoxLayout>

namespace base_cad
{
    GeometryView::GeometryView(QWidget *parent) : QWidget(parent)
    {
        setWindowTitle("geometry view");

        gl_view = new OpenGLView();

        QHBoxLayout *layout = new QHBoxLayout(this);
        layout -> addWidget(gl_view);
    }

    GeometryView::~GeometryView()
    {
    }
}
