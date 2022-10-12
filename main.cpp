#include <QCoreApplication>
#include <mind.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Mind *core = Mind::getMind();



    return a.exec();
}
