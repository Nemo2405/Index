#include "mind.h"

Mind* Mind::_mind = 0;

Mind *Mind::getMind()
{
   if (!_mind) {
       _mind = new Mind();
   }
   return _mind;
}

void Mind::start()
{
    std::cout << "starting mind..." << std::endl;
}

Mind::Mind()
{
    std::cout << "init index core..." << std::endl;
    appMgr = AppManager::getAppMgr();

}

Mind::~Mind()
{
    std::cout << "closing mind..." << std::endl;
}
