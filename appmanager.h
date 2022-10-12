#ifndef APPMANAGER_H
#define APPMANAGER_H
#include <iostream>
#include <QString>


class AppManager
{
public:
    static AppManager* getAppMgr();


private:
    AppManager();
    AppManager(const AppManager& root) = delete;
    AppManager operator=(const AppManager&) = delete;

    static AppManager *_appMgr;
};


class AppTemplate {
public:
    static AppTemplate *getApp();
    virtual void initApp(QString name);
protected:
    AppTemplate();
    AppTemplate(const AppTemplate& root) = delete;
    AppTemplate operator=(const AppTemplate&) = delete;

    static AppTemplate *_app;

private:
    QString _appName;

};

#endif // APPMANAGER_H
