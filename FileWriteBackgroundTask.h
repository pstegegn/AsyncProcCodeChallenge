//
// Created by paulos on 9/5/19.
//

#ifndef ASYNCPROCCODECHALLENGE_FILEWRITEBACKGROUNDTASK_H
#define ASYNCPROCCODECHALLENGE_FILEWRITEBACKGROUNDTASK_H

#include <fstream>
#include "Stoppable.h"
#include "ThreadSafeBlockingQueue.h"

class FileWriteBackgroundTask: public Stoppable
{
    std::thread thread_;
    std::string fileName_;
    ThreadSafeBlockingQueue<std::future<std::string>> * q_;

public:
    // Function to be executed by thread function
    virtual void run();
    void start();
    void stop();
};

#endif //ASYNCPROCCODECHALLENGE_FILEWRITEBACKGROUNDTASK_H
