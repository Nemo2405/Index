#include "appmanager.h"

AppManager *AppManager::_appMgr = 0;
//AppTemplate *AppTemplate::_app = 0;


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
    weather = static_cast<WeatherApp*>(AppTemplate::createApp("WeatherApp"));
    weather->init();
    music = static_cast<MusicApp*>(AppTemplate::createApp("Music App"));
//    weather->hello();
//    weather->foo();
}

////template <typename T>
//AppTemplate *AppTemplate::getApp()
//{
//    return _app;
//}

AppTemplate *AppTemplate::createApp(QString name)
{
    return new AppTemplate(name);
}

void AppTemplate::hello()
{
    std::cout  << "hello "<< _appName.toStdString() << std::endl;
}


void WeatherApp::foo()
{
    std::cout  << "foo "<< _appName.toStdString() << std::endl;

}

void WeatherApp::init()
{
    std::cout << "init pro " << std::endl;
}

AppTemplate::AppTemplate(QString name) :
    _appName(name)
{
    std::cout << "App   --- " << _appName.toStdString() << " ---" << std::endl;
}

void AppTemplate::init()
{
    std::cout << "init base " << _appName.toStdString() << " ..." << std::endl;
}


