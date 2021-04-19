//Global Latency Timers
#ifndef LATENCYTIMERS_H
#define LATENCYTIMERS_H

extern float fullDuration;
extern float tweetDuration;
extern float USDuration;
extern float imageReadDuration;
extern float photoDuration; 
extern float udpDuration;

extern FILE* fullDurLog; 
extern FILE* tweetDurLog; 
extern FILE* photoDurLog; 
extern FILE* usDurLog;
extern FILE* imReadDurLog;
extern FILE* udpLog;

#endif