#include <iostream>
#include <string.h>
#include <time.h>
#include "mindwave.hpp"
#include <QString>
#include <QDate>
#include <QTime>

const std::string currentDateTime()
{
    time_t     now = time(0) ;
    struct tm  tstruct ;
    char       buf[80] ;
    tstruct = *localtime(&now) ;
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct) ;

    return buf ;
}


int main()
{

    mindWave mindWave ;
    mindWave.setTimeInterval(2) ;

    mindWave.connect() ;

    std::cout << QDate::currentDate().toString(QString("yyyy_MM_dd")).simplified().toStdString() << std::endl ;

    //for (int i = 0 ; i < 1000000 ; i++)
    while(1)
    {
        mindWave.refresh() ;

//        if (i%20 == 0)
        {
	    std::cout << QTime::currentTime().toString(QString("hh_mm_ss_zzz")).simplified().toStdString() ;
	    //std::cout << currentDateTime() << std::endl ;
            //std::cout << "Att : " << mindWave.getAttention() << std::endl ;
            //std::cout << "Meditation : " << mindWave.getMeditation() << std::endl ;
            //std::cout << "Poor Signal : " << mindWave.getpoorSignal() << std::endl ;
            //std::cout << "Blink Strength : " << mindWave.getBlinkStrength() << std::endl ;
            std::cout << " Raw " << mindWave.getRawValue() << std::endl ;
            //std::cout << "Theta Data : " << mindWave.getTheta() << std::endl ;
            //std::cout << "Delta Data : " << mindWave.getDelta() << std::endl ;
            //std::cout << "Low Alpha Data : " << mindWave.getLowAlpha() << std::endl ;
            //std::cout << "High Alpha Data : " << mindWave.getHighAlpha() << std::endl ;
            //std::cout << "Low Beta Data : " << mindWave.getLowBeta() << std::endl ;
            //std::cout << "High Beta Data : " << mindWave.getHighBeta() << std::endl ;
            //std::cout << "Low Gamma Data : " << mindWave.getLowGamma() << std::endl ;
            //std::cout << "Mid Gamma Data : " << mindWave.getMidGamma() << std::endl ;
        }
    }

    mindWave.disconnect() ;

    return 0 ;
}

