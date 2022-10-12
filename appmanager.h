#ifndef APPMANAGER_H
#define APPMANAGER_H
#include <iostream>
#include <QString>


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
class AppTemplate {
public:
   static AppTemplate *createApp(QString name);
   void hello();
protected:
    AppTemplate(QString name);
    AppTemplate(const AppTemplate& root) = delete;
    //AppTemplate operator=(const AppTemplate&) = delete;
    const QString _appName;
    //static AppTemplate *_app;

    virtual void init();
private:
};



class WeatherApp : public AppTemplate{
public:
    void foo();
    virtual void init() override;
private:
};

class MusicApp : public AppTemplate {

};

#endif // APPMANAGER_H
