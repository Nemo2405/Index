#include "a_helios.h"

QString Helios::ApiKey ="ff428cee7af79fdf5be359b2ac8b17a9";


Helios::Helios()
{
    netManager = new QNetworkAccessManager();
}

void Helios::getCurrentWeather(double lat, double lon, QString Api)
{
    request.setUrl(QUrl("https://api.openweathermap.org/data/2.5/weather?"
                        "units=metric&"
                        "lat="+QString::number(lat)+"&"
                        "lon="+QString::number(lon)+"&"
                        "appid=" + Api));


    connect(netManager, &QNetworkAccessManager::finished,
            this, [this](QNetworkReply *reply) {
        if (reply->error()) {
            std::cout << reply->errorString().toStdString();
            return;
        }
        QString strReply = reply->readAll();

        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonObject mainObj = jsonObject["main"].toObject();
        QJsonObject weathObj = jsonObject["weather"].toObject()[0].toObject();
        QJsonObject cloudObj = jsonObject["clouds"].toObject();
        QJsonObject windObj = jsonObject["wind"].toObject();
        QJsonObject sysObj = jsonObject["sys"].toObject();

        MomentWeather momentWeather= MomentWeather({
                                         BaseWeatherInfo({
                                             mainObj["temp"].toDouble(),
                                             mainObj["feels_like"].toDouble(),
                                             mainObj["humidity"].toInt()
                                         }),
                                         CloudInfo({
                                             weathObj["main"].toString(),
                                             weathObj["description"].toString(),
                                             cloudObj["all"].toInt()
                                         }),
                                         WindInfo({
                                             windObj["speed"].toDouble(),
                                             windObj["deg"].toInt(),
                                             windObj["gust"].toDouble()
                                         }),
                                         SunInfo({
                                             QDateTime::fromSecsSinceEpoch(sysObj["sunrise"].toInt()),
                                             QDateTime::fromSecsSinceEpoch(sysObj["sunset"].toInt())
                                         }),
                                         jsonObject["visibility"].toInt(),
                                         jsonObject["name"].toString(),
                                         QDateTime::fromSecsSinceEpoch(jsonObject["dt"].toInt())
                                     });

        emit currentWeatherDataIsReady(momentWeather);
    });

    netManager->get(request);
}

void Helios::get5ForecastWeather(double lat, double lon, QString Api)
{
//    Index::log(QUrl("https://api.openweathermap.org/data/2.5/forecast?"
//                    "units=metric&"
//                    "lat="+QString::number(lat)+"&"
//                    "lon="+QString::number(lon)+"&"
//                    "appid=" + Api).toString());
    request.setUrl(QUrl("https://api.openweathermap.org/data/2.5/forecast?"
                        "units=metric&"
                        "lat="+QString::number(lat)+"&"
                        "lon="+QString::number(lon)+"&"
                        "appid=" + Api));

    connect(netManager, &QNetworkAccessManager::finished,
            this, [this](QNetworkReply *reply) {
        if (reply->error()) {
            Index::log(reply->errorString());
            return;
        }
        QString strReply = reply->readAll();

        Index::log("123" + strReply);

        ForecastWeather result;

        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonObject cityObj = jsonObject["city"].toObject();
        QJsonArray list = jsonObject["list"].toArray();

        int momentsCnt = jsonObject["cnt"].toInt();
        for (quint8 nowMoment = 0; nowMoment < momentsCnt; nowMoment++) {
            QJsonObject momentObject = list[nowMoment].toObject();
            QJsonObject mainObj      = momentObject["main"].toObject();
            QJsonObject weathObj     = momentObject["weather"].toObject()[0].toObject();
            QJsonObject cloudObj     = momentObject["clouds"].toObject();
            QJsonObject windObj      = momentObject["wind"].toObject();

            ForecastMomentWeather forecastedMomentWeather = ForecastMomentWeather({
                                                           BaseWeatherInfo({
                                                               mainObj["temp"].toDouble(),
                                                               mainObj["feels_like"].toDouble(),
                                                               mainObj["humidity"].toInt()
                                                           }),
                                                           CloudInfo({
                                                               weathObj["main"].toString(),
                                                               weathObj["description"].toString(),
                                                               cloudObj["all"].toInt()
                                                           }),
                                                           WindInfo({
                                                               windObj["speed"].toDouble(),
                                                               windObj["deg"].toInt(),
                                                               windObj["gust"].toDouble()
                                                           }),
                                                           momentObject["visibility"].toInt(),
                                                           momentObject["pop"].toDouble(),
                                                           QDateTime::fromSecsSinceEpoch(jsonObject["dt"].toInt())
                                                       });
            result.moments.append(forecastedMomentWeather);
        }

        result.sun = SunInfo({
                                QDateTime::fromSecsSinceEpoch(cityObj["sunrise"].toInt()),
                                QDateTime::fromSecsSinceEpoch(cityObj["sunset"].toInt()),
                             });
        result.city = cityObj["name"].toString();


        emit forecastedWeatherDataIsReady(result);
    });

    netManager->get(request);
}

void Helios::doTest(QString Api)
{
    request.setUrl(QUrl("https://api.openweathermap.org/data/2.5/weather?"
                        "units=metric&"
                        "lat=44.34&lon=10.99&"
                        "appid=" + Api)); // NEW YORK

    connect(netManager, &QNetworkAccessManager::finished,
            this, [this](QNetworkReply *reply) {
        if (reply->error()) {
            std::cout << reply->errorString().toStdString();
            emit testResult(false);
            return;
        }
        QString strReply = reply->readAll();
        if (QJsonDocument::fromJson(strReply.toUtf8()).object()["cod"].toInt() == 200) {
            emit testResult(true);
            return;
        }
        emit testResult(false);
        return;
    });

    netManager->get(request);
}
