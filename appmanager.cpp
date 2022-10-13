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


template<class C>
C *AppTemplate<C>::createApp(QString name)
{
    return static_cast<C*>(new AppTemplate(name));
}

//template<>
//WeatherApp *AppTemplate<WeatherApp>::createApp(QString name)
//{
//    WeatherApp *res = static_cast<WeatherApp*>(new AppTemplate(name));
//    //res->setApiKey("asd");
//    return res;
//}

template<class C>
void AppTemplate<C>::hello()
{
    log("hello " + _appName);
}

template<class C>
AppTemplate<C>::AppTemplate(QString name) : _appName(name), _isInit(false)
{
    log ("App   --- " + _appName + " ---");
}

template<class C>
void AppTemplate<C>::setIsInit(bool newIsInit)
{
    _isInit = newIsInit;
}


AppManager::AppManager()
{
//    std::cout << "init App Dispatcher..." << std::endl;
    log ("init App Dispatcher...");
    weather = WeatherApp::createApp("Weather App");
    music = MusicApp::createApp("Music App");

    weather->setIsInit(weather->init(21, 12, "ff428cee7af79fdf5be359b2ac8b17a9"));

}

//void WeatherApp::setApiKey(const QString &newApiKey)
//{
//    apiKey = newApiKey;
//}
