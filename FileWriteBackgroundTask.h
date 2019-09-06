//
// Created by paulos on 9/5/19.
//

#ifndef ASYNCPROCCODECHALLENGE_FILEWRITEBACKGROUNDTASK_H
#define ASYNCPROCCODECHALLENGE_FILEWRITEBACKGROUNDTASK_H

#include <fstream>
#include "Stoppable.h"
#include "ThreadSafeBlockingQueue.h"

struct OpenFileException : std::exception{
    std::string filepath_;
    explicit OpenFileException(const std::string & filepath){
        filepath_ = filepath;
    }
    std::string what(){
        return "Coud not open File Exception";
    }
};

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

    void setLogFileName(const std::string fileName){fileName_ = fileName;}

    void setQueue(ThreadSafeBlockingQueue<std::future<std::string>> *pQueue){q_ = pQueue;};
};

#endif //ASYNCPROCCODECHALLENGE_FILEWRITEBACKGROUNDTASK_H
