#ifndef LOOP_MANAGER_H
#define LOOP_MANAGER_H

#include "../config.h"

class LoopManager {
private:
    const int API_UPDATE_INTERVAL;
    const int RESTART_THRESHOLD;
    int samplesTaken;
    int totalSamples;

public:
    LoopManager()
        : API_UPDATE_INTERVAL(::API_UPDATE_INTERVAL),
          RESTART_THRESHOLD(::RESTART_THRESHOLD),
          samplesTaken(0),
          totalSamples(0) {}

    void increment(){
        samplesTaken++;
        totalSamples++;
    }

    bool shouldUpdateAPI(){
        return samplesTaken >= API_UPDATE_INTERVAL;
    }

    bool shouldRestart(){
        return totalSamples >= RESTART_THRESHOLD;
    }

    int getTotalSamples() const{
        return totalSamples;
    }

    int getSamplesTaken() const{
        return samplesTaken;
    }

    void resetSamplesTaken(){
        samplesTaken = 0;
    }
};

#endif