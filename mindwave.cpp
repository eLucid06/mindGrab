#include "mindwave.hpp"


mindWave::mindWave()
{
    std::cout << "Create Device" << std::endl ;

    rawValue = 0 ;
    attention = 0 ;
    meditation = 0 ;

    delta = 0 ;
    theta = 0 ;
    lowAlpha = 0 ;
    highAlpha = 0 ;
    lowBeta = 0 ;
    highBeta = 0 ;
    lowGamma = 0 ;
    midGamma = 0 ;
    poorSignal = 0 ;
    blinkStrength = 0 ;

    connected = false ;
    logInFile = true ;

    timeInterval = 10 ;

    logFilename = "myLog.log" ;

    THINKGEAR_initParser(&parser, PARSER_TYPE_PACKETS, mindWave::handlefunction, this) ;

    message = "no message" ;

    if(logInFile)
        logMessage() ;
}

int mindWave::connect()
{
    std::cout << "Connect Device" << std::endl ;
    message = "Connect Device" ;
    if(logInFile)
        logMessage() ;

    //system("rfcomm bind 2") ;
    sleep(1) ;

    btFlux.open("/dev/rfcomm0", std::ios::in | std::ios::binary) ;

    if(!btFlux.is_open())
    {
        std::cerr << "Impossible d'ouvrir le flux, consultez le fichier README.md" << std::endl ;
    }
    else
        std::cout << "Connection established\n" << std::endl ;

    connected = 0 ;

    return 0 ;
}

void mindWave::clear()
{
    std::cout << "Clear data" << std::endl ;
    message = "Clear Data" ;
    if(logInFile)
        logMessage() ;

    rawValue = 0 ;
    attention = 0 ;
    meditation = 0 ;

    delta = 0 ;
    theta = 0 ;
    lowAlpha = 0 ;
    highAlpha = 0 ;
    lowBeta = 0 ;
    highBeta = 0 ;
    lowGamma = 0 ;
    midGamma = 0 ;
    poorSignal = 0 ;
    blinkStrength = 0 ;
}

void mindWave::refresh()
{
    //std::cout << "Refresh Data" << std::endl ;
    message = "Refresh Data" ;
    if(logInFile)
        logMessage() ;

    char c ;
    btFlux.read((char *) &c, sizeof(char)) ;
    THINKGEAR_parseByte(&parser, c) ;
    wait() ;
}

void mindWave::handlefunction(unsigned char extendedCodeLevel,
                    unsigned char code,
                    unsigned char valueLength,
                    const unsigned char * value,
                    void * customData)
{
    int i ;
    mindWave * mW = (mindWave*) customData ;
    if(extendedCodeLevel == 00)
    {
        switch(code)
        {
        /* [CODE]: poorSignal */
        case(0x02):
            mW->poorSignal = value[0] & 0xFF ;
            break ;
        /* [CODE]: ATTENTION eSense */
        case(0x04):
            mW->attention = value[0] & 0xFF ;
            break ;
        /* [CODE]: MEDITATION eSense */
        case( 0x05 ):
            mW->meditation = value[0] & 0xFF ;
            break ;

        /* [CODE]: Blink Strength */
        case( 0x16 ):
            mW->blinkStrength = value[0] & 0xFF ;
            break ;
        /* [CODE]: raw Value */
        case( 0x80 ):
            mW->rawValue = (value[0] & 0xFF)*256 + (value[1] & 0xFF) ;
            if (mW->rawValue > 32768)
                mW->rawValue = mW->rawValue - 65536 ;
            break ;
        case( 0x83 ):
            /* delta */
            mW->delta = (value[0] & 0xFF)*65536 + (value[1] & 0xFF)*256 + (value[2] & 0xFF) ;
            mW->theta = (value[3] & 0xFF)*65536 + (value[4] & 0xFF)*256 + (value[5] & 0xFF) ;
            mW->lowAlpha = (value[6] & 0xFF)*65536 + (value[7] & 0xFF)*256 + (value[8] & 0xFF) ;
            mW->highAlpha = (value[9] & 0xFF)*65536 + (value[10] & 0xFF)*256 + (value[11] & 0xFF) ;
            mW->lowBeta = (value[12] & 0xFF)*65536 + (value[13] & 0xFF)*256 + (value[14] & 0xFF) ;
            mW->highBeta = (value[15] & 0xFF)*65536 + (value[16] & 0xFF)*256 + (value[17] & 0xFF) ;
            mW->lowGamma = (value[18] & 0xFF)*65536 + (value[19] & 0xFF)*256 + (value[20] & 0xFF) ;
            mW->midGamma = (value[21] & 0xFF)*65536 + (value[22] & 0xFF)*256 + (value[23] & 0xFF) ;
            break ;

            default:
                printf("EXCODE level: %d CODE: 0x%02X vLength: %d\n", extendedCodeLevel, code, valueLength) ;
                printf("Data value(s):") ;
                for(i = 0 ; i < valueLength ; i++)
                    printf(" %02X", value[i] & 0xFF) ;
                printf("\n") ;
                break ;
        }
    }

}

int mindWave::disconnect()
{
    std::cout << "Disconnect device" << std::endl ;
    message = "Disconnect device" ;
    if(logInFile)
        logMessage() ;

    btFlux.close() ;

    connected = false ;

    return 0 ;
}

void mindWave::setTimeInterval(int millis)
{
    timeInterval = millis ;
    if(logInFile)
        logMessage() ;
}

void mindWave::wait()
{
    usleep(timeInterval*1000) ;
}

int mindWave::getRawValue()
{
    return rawValue ;
}

int mindWave::getAttention()
{
    return attention ;
}

int mindWave::getMeditation()
{
    return meditation ;
}

int mindWave::getDelta()
{
    return delta ;
}

int mindWave::getTheta()
{
    return theta ;
}

int mindWave::getLowAlpha()
{
    return lowAlpha ;
}

int mindWave::getHighAlpha()
{
    return highAlpha ;
}

int mindWave::getLowBeta()
{
    return lowBeta ;
}

int mindWave::getHighBeta()
{
    return highBeta ;
}

int mindWave::getLowGamma()
{
    return lowGamma ;
}

int mindWave::getMidGamma()
{
    return midGamma ;
}

int mindWave::getpoorSignal()
{
    return poorSignal ;
}

int mindWave::getBlinkStrength()
{
    return blinkStrength ;
}

void mindWave::setLogFilename(std::string logFilename)
{
    this->logFilename = logFilename ;
}

std::string mindWave::getLogFilename()
{
    return logFilename ;
}

bool mindWave::isConnected()
{
    return connected ;
}

void mindWave::setLogInFile(bool logInFile)
{
    this->logInFile = logInFile ;
}

bool mindWave::getLogInFile()
{
    return logInFile ;
}

std::string mindWave::getMessage()
{
    return message ;
}

int mindWave::logMessage()
{

    return 0 ;
}
