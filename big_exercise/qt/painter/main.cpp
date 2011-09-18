#include "myform.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    myForm window;
    window.setGeometry(0, 0, 900, 500); 
    window.show();

    return app.exec();
}
