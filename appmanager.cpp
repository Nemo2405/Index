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


//template<class C>
//C *AppTemplate<C>::createApp(QString name)
//{
//    return static_cast<C*>(new AppTemplate(name));
//}

//template<class C>
//void AppTemplate<C>::hello()
//{
//    Index::log("hello " + _appName);
//}

//template<class C>
//AppTemplate<C>::AppTemplate(QString name) : _appName(name), _isInit(false)
//{
//    Index::log ("App   --- " + _appName + " ---");
//}

//template<class C>
//void AppTemplate<C>::setIsInit(bool newIsInit)
//{
//    _isInit = newIsInit;
//}


AppManager::AppManager()
{
    Index::log ("init App Dispatcher...");
    HeliosApp helios("Helios", "/home/eddyneshton/QT_PROJECTS/_INDEX/index/microApps/Helios");
    helios.start();


//    weather = WeatherApp::createApp("Weather App");
//    weather->setIsInit(weather->init(21, 12, "ff428cee7af79fdf5be359b2ac8b17a9"));

    //music = MusicApp::createApp("Music App");
}


BaseApp::BaseApp(QString appName, QString appPath) :
    _appName(appName), _appPath(appPath)
{

}

void BaseApp::start()
{
    Index::log("init " + this->_appName + "...");
    if (this->init()) {
        Index::log("success\n");
        return;
    }
    Index::log("error while init " + this->_appName + "\n");
}

bool BaseApp::init()
{
    QProcess initProcess;
    initProcess.start(_appPath);
    initProcess.waitForFinished();
    QString output(initProcess.readAllStandardOutput());
//    QString output1(initProcess.readAllStandardError()); //////????????????????????????? WHY ERROR
//    Index::log("12313" + output);
    if (output.trimmed() == "ok") {
        return true;
    }
    return false;
}

HeliosApp::HeliosApp(QString appName, QString appPath) :
    BaseApp(appName, appPath)
{}

