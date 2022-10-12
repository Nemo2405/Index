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
    weather = WeatherApp::createApp("Weather App");
    music = MusicApp::createApp("Music App");

}

template<class C>
C *AppTemplate<C>::createApp(QString name)
{
    return static_cast<C*>(new AppTemplate(name));
}

template<class C>
void AppTemplate<C>::hello()
{
    std::cout  << "hello "<< _appName.toStdString() << std::endl;
}

template<class C>
AppTemplate<C>::AppTemplate(QString name) : _appName(name)
{
    std::cout << "App   --- " << _appName.toStdString() << " ---" << std::endl;
}


void WeatherApp::init(double lat, double lon)
{
    std::cout << "init " << _appName.toStdString() << std::endl;
}
