#include "raylib.h"
#ifndef Timer_Object
#define Timer_Object
class Time
{
    private:
    double Time;
    double End;
    public:
    void StartTimer(double sec){
        Time = GetTime();
        End = Time+sec;
    }
    
    float CurrentTime(){
        return End - Time;
    }
    
    void UpdateTimer(){
        Time += GetFrameTime();
    }
    
    bool IsTimerUp(){
        if (Time >= End) return true;
        else return false;
    }
};
#endif //Timer_Object