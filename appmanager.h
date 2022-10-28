#ifndef APPMANAGER_H
#define APPMANAGER_H

//#include <global.h>
#include <QProcess>
#include <QMap>
#include <a_helios.h>
#include <QObject>

class AppManager;

class IBaseApp : public QObject {
public:
    virtual void __init(AppManager&) = 0;
    bool isInit = false;
private:
};


class WeatherApp : public IBaseApp/*BaseApp<Helios>*/ {
public:
    virtual void __init(AppManager&) override;
    void getCurrentWeather(double lat, double lon);
    void get5DayForecast(double lat, double lon);
    WeatherApp()  {
        _helios = new Helios;
    }
private:
    Helios *_helios;
};

class AppWrapper {
public:
    void add(QString appName, IBaseApp* app);
    template<typename T>
    T* get(QString key);
private:
    QMap <QString, IBaseApp*> _wrapper;
};

class AppManager : public QObject
{
    Q_OBJECT
public:
    static AppManager* getAppMgr();
    template<typename T>
    void setAppInit(QString appName, bool isInit);

private:
    AppManager();
    AppManager(const AppManager& root) = delete;
    AppManager operator=(const AppManager&) = delete;

    static AppManager *_appMgr;

    AppWrapper appWrapper;
};

#endif // APPMANAGER_H
