#include <iostream>
#include "time.h"

Time::Time(){
    hour = 0 ;
    minute = 0;
    second = 0;
}

Time::Time(int Hour , int Minute, int Second){
    hour = Hour;
    minute = Minute;
    second =  Second;

}
int Time::getHour() const {
    return hour;
}

int Time::getMinute() const {
    return minute;
}

int Time::getSecond() const {
    return second;
}

void Time::setHour(int aHour) {
    hour = aHour;
}

void Time::setMinute(int aMinute) {
    minute = aMinute;
}

void Time::setSecond(int aSecond) {
    second = aSecond;
}

void Time::PrintAMPM() const {
   int displayHour = hour % 12;  // Convert to 12-hour format
   std::string period;
    if (hour < 12) {
        period = "am"; 
    } else {
        period = "pm";
    }
    // Adjust display hour for midnight and noon
    if (displayHour == 0) {
        displayHour = 12;
    }

    std::cout << displayHour << ":";

    // Print leading zero for single-digit minutes
    if (minute < 10) {
        std::cout << "0";
    }

    std::cout << minute << ":";

    // Print leading zero for single-digit seconds
    if (second < 10) {
        std::cout << "0";
    }

    std::cout << second << " " << period << std::endl;
}

