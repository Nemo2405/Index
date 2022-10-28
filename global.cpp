#include "global.h"

bool Index::isQdebug = true;

Index::Index()
{}

void Index::log(QString src)
{
    if (isQdebug){
        qDebug() << src;
    } else {
        std::cout << src.toStdString()<< std::endl;
    }
}

void Index::log(QChar src)
{
    if (isQdebug){
        qDebug() << src;
    } else {
        std::cout << src.toLatin1()<< std::endl;
    }
}

void Index::log(char src)
{
    if (isQdebug){
        qDebug() << src;
    } else {
        std::cout << src<< std::endl;
    }
}
