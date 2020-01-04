#ifndef TIME_SYNC_CLIENT
#define TIME_SYNC_CLIENT

#include "ClientStageOne.h"
#include "ClientStageTwo.h"

class TimeSyncClient : public Operation
{
private:
    ClientStageOne * stageOne;
    ClientStageTwo * stageTwo;
    Timing * time;
    Connection * connection;
    bool logging;
    unsigned long start;
    unsigned long count;
    float syncTime;
    float lastSync;
public:
    TimeSyncClient(Timing *, Connection *, bool logging = false);
    ~TimeSyncClient();
    virtual void init();
    virtual void exec();
    bool done;
};

#endif