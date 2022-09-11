#ifndef GEOMETRY_VIEW_H
#define GEOMETRY_VIEW_H

#include <QWidget>
#include <string>

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

        void SetPath(const char *path);

    private:
        OpenGLView *gl_view;
        GeometryManager *geo_manager;

        std::string input_path;
    };
}

#endif
