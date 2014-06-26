#ifndef MINDWAVE_HPP
#define MINDWAVE_HPP

#include <time.h>

#include <iostream>
#include <string>
#include <fstream>

#include <unistd.h>

#include "ThinkGearStreamParser.h"

class mindWave
{
public:

    mindWave() ;

    void refresh() ;
    int connect() ;
    int disconnect() ;

    void setTimeInterval(int) ;


    int getRawValue() ;
    int getAttention() ;
    int getMeditation() ;
    int getDelta() ;
    int getTheta() ;
    int getLowAlpha() ;
    int getHighAlpha() ;
    int getLowBeta() ;
    int getHighBeta() ;
    int getLowGamma() ;
    int getMidGamma() ;
    int getpoorSignal() ;
    int getBlinkStrength() ;

    void setLogFilename(std::string) ;
    std::string getLogFilename() ;

    bool isConnected() ;
    void setLogInFile(bool) ;
    bool getLogInFile() ;

    std::string getMessage() ;

private:

    int rawValue ;
    int attention ;
    int meditation ;

    int delta ;
    int theta ;
    int lowAlpha ;
    int highAlpha ;
    int lowBeta ;
    int highBeta ;
    int lowGamma ;
    int midGamma ;
    int poorSignal ;
    int blinkStrength ;

    bool connected ;
    bool logInFile ;

    int timeInterval ;

    std::string message ;
    std::string logFilename ;
    std::ofstream logFile ;
    std::ifstream btFlux ;

    int logMessage() ;
    void wait() ;
    void clear() ;

    ThinkGearStreamParser parser ;

    static void handlefunction(unsigned char, unsigned char, unsigned char, const unsigned char *, void *) ;

} ;



#endif // MINDWAVE_HPP
