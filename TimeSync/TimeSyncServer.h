#ifndef TIME_SYNC_SERVER
#define TIME_SYNC_SERVER

#include "Timing.h"
#include "Operation.h"
#include "Connection.h"


class TimeSyncServer : public Operation{
    private:
        Timing * time;
        Connection * connection;
        bool logging;
    public:
        TimeSyncServer(Timing *, Connection *, bool logging = false);
        virtual void init();
        virtual void exec();
};
#endif