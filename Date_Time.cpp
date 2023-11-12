#include"Date_Time.h"

std::string Date_Time::GenerateTime() {
    time_t t;
    tm* tmp;
    t = time(0);
    tmp = localtime(&t);

    std::string time_date = " " + std::to_string(tmp->tm_hour) + ":" + std::to_string(tmp->tm_min) +
        ":" + std::to_string(tmp->tm_sec);
    time_date = __DATE__ + time_date;
    return time_date;
}