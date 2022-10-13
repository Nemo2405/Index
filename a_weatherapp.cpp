#include <appmanager.h>
//#include <QException>
//#include <QString>
#include <cstring>


bool WeatherApp::init(double lat, double lon, QString api)
{
    log ("init " + _appName);
    latitude = lat;
    longitude = lon;
    apiKey = new char[api.size()];
    strcpy(apiKey, api.toStdString().c_str());

    std::cout << lat << lon << apiKey;
    return true;
}
