#include "MyWidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MyWidget window;
    window.setGeometry(0, 0, 800, 600);
    window.show();

    return app.exec();
}
