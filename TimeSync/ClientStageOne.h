#ifndef CLIENT_STAGE_ONE
#define CLIENT_STAGE_ONE

#include "Timing.h"
#include "Operation.h"
#include "Connection.h"


class ClientStageOne : public Operation
{
private:
    Connection * connection;
    bool logging;
    bool syncStarted;
    void log(unsigned long now);
public:
    ClientStageOne(Timing *, Connection *, bool logging = false);
    virtual void init();
    virtual void exec();
    int count;
    bool done;
    Timing * time;
};

#endif