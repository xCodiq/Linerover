//
// Created by elmar on 06/04/2022.
//

#ifndef LINEROVER_LOGGER_H
#define LINEROVER_LOGGER_H

#include <HardwareSerial.h>
#include <WString.h>

class Logger {
private:
    // The instance pointer of the Logger
//    static inline Logger *instance = nullptr;

    // The serial port of the logger
    int m_serialPort = -1;

    explicit Logger(int serialPort);

    ~Logger();

public:

    /**
     * Configure the Logger which will create a new singleton instance
     *
     * @param serialPort the serial port used for the logger
     */
    static void configure(int serialPort);

    /**
     * Send an INFO message to the serial monitor console
     *
     * @param infoMessage the info message to send
     */
    static void info(const String &infoMessage);

    /**
     * Send an ERROR message to the serial monitor console
     *
     * @param errormessage the error message to send
     */
    static void error(const String &errormessage);
};


#endif //LINEROVER_LOGGER_H
