#ifndef UNIX_H
#define UNIX_H

#include <iostream>
#include <chrono>
#include <string>
#include <iomanip>

std::string unixToDate(std::string date) {
    std::time_t unixTimestamp(std::stol(date));
    std::string formattedDate = std::asctime(std::localtime(&unixTimestamp));
    return formattedDate.substr(0, 24);
}

int dateToUnix(std::string date) {
    std::string fecha_con_formato = "20" + date.substr(0, 2) + "/" + date.substr(3, 2) + "/" + date.substr(6, 2);

    std::tm tm = {};

    std::chrono::system_clock::time_point tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    std::chrono::seconds duration = std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch());

    return static_cast<int>(duration.count());
}

#endif