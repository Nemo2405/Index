#ifndef INDEX_H
#define INDEX_H
#include <QString>
#include <iostream>
#include <string>
#include <QDebug>


class Index
{
public:
    Index();
    static void log(QString logText);
    static void log(QChar src);
    static void log(char src);
private:
    static bool isQdebug;
};

#endif // INDEX_H
