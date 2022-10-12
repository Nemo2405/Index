#include "appmanager.h"

AppManager *AppManager::_appMgr = 0;


AppManager *AppManager::getAppMgr()
{
    if (!_appMgr) {
        _appMgr = new AppManager();
    }
    return _appMgr;
}

AppManager::AppManager()
{
    std::cout << "init App Dispatcher..." << std::endl;
}

AppTemplate *AppTemplate::getApp()
{
    if (!_app) {
        _app = new AppTemplate();
    }
    return _app;
}

void AppTemplate::initApp(QString name)
{
    this->_appName = name;
    std::cout << "init App --- " << name.toStdString() << " --- " << std::endl;
}
