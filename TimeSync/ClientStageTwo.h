#ifndef CLIENT_STAGE_TWO
#define CLIENT_STAGE_TWO

#include "Timing.h"
#include "Operation.h"
#include "Connection.h"

class ClientStageTwo : public Operation
{
private:
    bool logging;
    Timing * time;
    Connection * connection;
    int count;
    void log(unsigned long, unsigned long);
public:
    ClientStageTwo(Timing *, Connection *,  bool logging = false);
    bool sync();
    virtual void init();
    virtual void exec();
    bool done;
};

#endif