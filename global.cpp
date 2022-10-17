#include "global.h"

Index::Index()
{}

void Index::log(QString logText) {
    std::cout << logText.toStdString() << std::endl;
}
