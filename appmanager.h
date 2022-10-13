#ifndef APPMANAGER_H
#define APPMANAGER_H
#include <iostream>
#include <QString>
#include <string>

inline void log(QString logData) {
    std::cout << logData.toStdString() << std::endl;
}

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

//    QVector <AppTemplate*> a;
    WeatherApp *weather;
    MusicApp *music;
};



template <class C>
class AppTemplate {
public:
   static C *createApp(QString name);
   void hello();
   void setIsInit(bool newIsInit);

protected:
    AppTemplate(QString name);
    AppTemplate(const AppTemplate& root) = delete;
    //AppTemplate operator=(const AppTemplate&) = delete;
    const QString _appName;
    bool _isInit;
    //static AppTemplate *_app;
private:
};



class WeatherApp : public AppTemplate<WeatherApp>{
public:
    bool init(double lat, double lon, QString api);
//    void setApiKey(const QString &newApiKey);

private:
    //QString apiKey;
    double latitude;
    double longitude;
    char *apiKey;
};

class MusicApp : public AppTemplate<MusicApp> {

};

#endif // APPMANAGER_H
