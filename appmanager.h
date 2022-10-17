#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <global.h>
#include <QProcess>


template <class C>
class AppTemplate;
class WeatherApp;
class MusicApp;

class AppManager
{
public:
    static AppManager* getAppMgr();

private:
    AppManager();
    AppManager(const AppManager& root) = delete;
    AppManager operator=(const AppManager&) = delete;

    static AppManager *_appMgr;

    WeatherApp *weather;
    MusicApp *music;
};



//template <class C>
//class AppTemplate {
//public:
//   static C *createApp(QString name);
//   void hello();
//   void setIsInit(bool newIsInit);

//protected:
//    AppTemplate(QString name);
//    AppTemplate(const AppTemplate& root) = delete;
//    const QString _appName;
//    bool _isInit;
//private:
//};



//class WeatherApp : public AppTemplate<WeatherApp>{
//public:
//    bool init(double lat, double lon, QString api);

//private:
//    double latitude;
//    double longitude;
//    char *apiKey;
//};

class BaseApp //: public QObject
{
public:
    BaseApp(QString appName, QString appPath);
    void start();

protected:
    const QString _appName;
    const QString _appPath;
    bool init();
};

class HeliosApp : public BaseApp {
public:
    HeliosApp(QString appName, QString appPath);
};

#endif // APPMANAGER_H
