#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <string>
#include <chrono>

using namespace std;

/*

*/

class Timer
{
private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point endTime;

public:
    Timer(/* args */);
    ~Timer();
    void saveStart();
    void saveEnd();
    double getElapsedSeconds();
    double getElapsedSecondsNow();
    static void printTime(double);
};

Timer::Timer(/* args */)
{
}

Timer::~Timer()
{
}

void Timer::saveStart()
{
    startTime = std::chrono::high_resolution_clock::now();
}

void Timer::saveEnd()
{
    endTime = std::chrono::high_resolution_clock::now();
}

double Timer::getElapsedSeconds()
{
    std::chrono::duration<double> duration = endTime - startTime;
    return duration.count();
}

double Timer::getElapsedSecondsNow()
{
    saveEnd();
    std::chrono::duration<double> duration = endTime - startTime;
    return duration.count();
}

void Timer::printTime(double seconds)
{
    std::cout << endl
              << "---------------------------------------------------------------------------" << std::endl;
    std::cout << "\t[La funcion se demoro " << seconds << " segundos en ejecutarse.]" << std::endl;
    std::cout << "---------------------------------------------------------------------------" << std::endl
              << std::endl;
}

#endif