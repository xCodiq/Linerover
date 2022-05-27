//
// Created by elmar on 06/04/2022.
//

#include "Logger.h"

Logger::Logger(int serialPort) : m_serialPort(serialPort) {
    instance = this;
    Serial.begin(m_serialPort);
}

Logger::~Logger() {
    delete Logger::instance;
}

void Logger::configure(int serialPort) {
    if (instance == nullptr) {
        Logger newLogger{serialPort};
        return;
    }

    Logger::error("You are not allowed to configure the Logger twice!");
}

void Logger::info(const String &infoMessage) {
    if (instance->m_serialPort == -1) return;

    Serial.print("[INFO] ");
    Serial.println(infoMessage);
}

void Logger::error(const String &errorMessage) {
    Serial.print("[ERROR] ");
    Serial.println(errorMessage);
}
