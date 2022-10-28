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
    Index::log("starting mind...");
}

Mind::Mind()
{
    Index::log("init index core...");
    appMgr = AppManager::getAppMgr();

}

Mind::~Mind()
{
    std::cout << "closing mind..." << std::endl;
}
