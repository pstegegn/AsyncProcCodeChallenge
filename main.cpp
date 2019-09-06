#include <iostream>
#include "PigLatinConverter.h"
#include "ThreadPool.h"
#include "ThreadSafeBlockingQueue.h"
#include "FileWriteBackgroundTask.h"
#include <thread>

int main() {
    PigLatinConverter pigLatinConverter;
    std::vector<std::future<int> > results;

    //create thread pool manager
    ThreadPool threadPoolMgr(std::thread::hardware_concurrency() - 2);

    //thread safe queue for return of the
    ThreadSafeBlockingQueue<std::future<std::string>> threadSafeBlockingQueue;

    FileWriteBackgroundTask fileWriteBackgroundTask;

    //set log file
    fileWriteBackgroundTask.setLogFileName("log.txt");

    fileWriteBackgroundTask.setQueue(&threadSafeBlockingQueue);

    try {
        fileWriteBackgroundTask.start();
    }catch (OpenFileException e){
        std::cerr<<"Background task error:"<< e.what()<<std::endl;
    }catch (std::exception & e){
        std::cerr<<"Background task error:"<< e.what()<<std::endl;
    }

    std::cout<<"To exit please enter (quit/exit/q)"<<std::endl;
    while (true) {
        std::string text;
        std::cout<<"Enter Text:";
        getline(std::cin,text);
        if(text == "q" || text == "quit"|| text=="exit") {
            pigLatinConverter.cancel();
            fileWriteBackgroundTask.stop();
            std::cout<<"Exiting..."<<std::endl;
            break;
        }

        threadSafeBlockingQueue.push(
                threadPoolMgr.enqueue([text,&pigLatinConverter] {
                    return pigLatinConverter.convert(text);
                    }));
    }

    std::cout<<"Done"<<std::endl;
    return 0;
}