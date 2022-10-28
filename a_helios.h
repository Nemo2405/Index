#ifndef A_HELIOS_H
#define A_HELIOS_H


#include <QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QObject>
#include <iostream>
#include <string>
#include <QString>
#include <QDebug>

#include <global.h>

class Helios : public QObject
{
    Q_OBJECT
public:
    typedef struct {
        double WindSpeed;
        int WindDirection;
        double WindGust;
    } WindInfo;

    typedef struct {
        QString shortName;
        QString longName;
        int cloudPercent;
    } CloudInfo;

    typedef struct {
        double temperature;
        double feelTemp;
        int humidity;
    } BaseWeatherInfo;

    typedef struct {
        QDateTime SunriseTime;
        QDateTime SunsetTime;
    } SunInfo;

    typedef struct {
        BaseWeatherInfo baseInfo;
        CloudInfo cloud;
        WindInfo wind;
        SunInfo sun;
        int visibility;
        QString city;
        QDateTime dataTime;
    } MomentWeather;

    typedef struct {
        BaseWeatherInfo baseInfo;
        CloudInfo cloud;
        WindInfo wind;
        int visibility;
        double pop; //probability of precipitation
        QDateTime dataTime;
    } ForecastMomentWeather; //without sun & city data

    typedef struct {
        QVector <ForecastMomentWeather> moments;
        SunInfo sun; // common for all
        QString city;
    } ForecastWeather;

    Helios();

    void getCurrentWeather(double lat, double lon, QString Api = ApiKey);

    void get5ForecastWeather(double lat, double lon, QString Api = ApiKey);

    void doTest(QString Api = ApiKey);

signals:
    void currentWeatherDataIsReady(MomentWeather);

    void forecastedWeatherDataIsReady(ForecastWeather);

    void testResult(bool success);

private:
    QNetworkAccessManager *netManager;
    QNetworkRequest request;
    static QString ApiKey;
};
#endif // A_HELIOS_H
