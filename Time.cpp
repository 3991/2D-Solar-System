#include "Time.h"

Time::Time(){
    elapsed1 = 0;
    hour = 0, day = 1, month = 1, year = 1;
    change = false;
}

Time::~Time(){
}

int Time::update(int angle){

    if(elapsed1 == 7){
        change = true;
        hour++;
        if(hour == 24){
            hour = 0;
            day++;
        }
        if(day == 31){
            day = 1;
            month++;
        }
        if(month == 12){
            year++;
        }



        if(angle<360){
            //angle += 15;
        }else{
            //angle=0;
        }


        elapsed1 = 0;
        clock.restart();
    }
    elapsed1 = (int)clock.getElapsedTime().asSeconds();


    if(change){
        std::cout << "[D/M/Y]:" << day << "/" << month << "/" << year << std::endl;
        std::cout << "Hour:" << hour << ".00" << std::endl;
        change = false;
        return true;
    }

    return false;
}
