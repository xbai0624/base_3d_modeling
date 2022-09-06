#include <QApplication>

#include "UnitTest.h"
#include "GeometryView.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    //base_cad::UnitTest unit_test;
    //unit_test.test();

    base_cad::GeometryView *geo_view = new base_cad::GeometryView();
    geo_view -> show();

    return app.exec();

    return 0;
}
