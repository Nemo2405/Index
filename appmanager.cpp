#include "appmanager.h"
#include <QThread>

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
    Index::log ("init App Dispatcher...");

    WeatherApp *weather = new WeatherApp;
    appWrapper.add("Weather", weather);




    appWrapper.get<WeatherApp>("Weather")->__init(*this);
//    appWrapper.get<WeatherApp>("Weather")->get5DayForecast(56.04151, 37.855163);
}

template<typename T>
void AppManager::setAppInit(QString appName, bool isInit)
{
    appWrapper.get<T>(appName)->isInit = isInit;
}

void WeatherApp::__init(AppManager& src)
{
    connect(_helios, &Helios::testResult,
            &src, [&src] (bool result) {
       if (result) {
           Index::log("Helios init... OK");
       } else {
           Index::log("Helios init... ERROR");
       }
       src.setAppInit<WeatherApp>("Weather", result);
    });


    connect(_helios, &Helios::currentWeatherDataIsReady,
            &src, [](Helios::MomentWeather nowWeather) {
        Index::log("current " + QString::number(nowWeather.baseInfo.feelTemp));
    });

    connect(_helios, &Helios::forecastedWeatherDataIsReady,
            &src, [](Helios::ForecastWeather forecast) {
        Index::log("forecast");
        Index::log(forecast.city);
        foreach(auto e, forecast.moments) {
//            Index::log(QString::number(e.pop));
        }
        return;
    });

    _helios->doTest();
}

void WeatherApp::getCurrentWeather(double lat, double lon)
{
    _helios->getCurrentWeather(lat, lon);
}

void WeatherApp::get5DayForecast(double lat, double lon)
{
    _helios->get5ForecastWeather(lat, lon);
}

void AppWrapper::add(QString appName, IBaseApp *app)
{
    _wrapper.insert(appName, app);
}

template<typename T>
T *AppWrapper::get(QString key)
{
    return static_cast<T*>(_wrapper[key]);
}
