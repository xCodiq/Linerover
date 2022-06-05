//
// Created by elmar on 06/04/2022.
//

#include "Logger.h"

Logger::Logger(int serialPort) : m_serialPort(serialPort) {
    Serial.begin(m_serialPort);
}

Logger::~Logger() {
}

void Logger::configure(int serialPort) {
    if (serialPort != 0) {
        Logger newLogger{serialPort};
        return;
    }

    Logger::error("You are not allowed to configure the Logger twice!");
}

void Logger::info(const String &infoMessage) {
    Serial.print("[INFO] ");
    Serial.println(infoMessage);
}

void Logger::error(const String &errorMessage) {
    Serial.print("[ERROR] ");
    Serial.println(errorMessage);
}
