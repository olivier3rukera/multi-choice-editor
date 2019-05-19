#include "display.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Display windows;
    windows.show();

    return app.exec();
}
