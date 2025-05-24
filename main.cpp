#include "mainwindow.h"
#include "cloudflare.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    cloudflare obj("https://www.cloudflare.com/ips-v4/#");
    obj.run();
    //w.show();
    return a.exec();
}
