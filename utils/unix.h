#ifndef UNIX_H
#define UNIX_H

#include <iostream>
#include <chrono>
#include <string>
#include <iomanip>

std::string unixToDate(std::string dateUnix) {
    std::time_t unixTimestamp(std::stol(dateUnix));
    std::string formattedDate = std::asctime(std::localtime(&unixTimestamp));
    return formattedDate.substr(0, 24);
}

int dateToUnix(std::string date) {
    std::tm tm = {};
    std::istringstream ss(date);
    ss >> std::get_time(&tm, "%d/%m/%y");
    std::time_t tiempo_unix = std::mktime(&tm);
    return static_cast<int>(tiempo_unix);
}

#endif