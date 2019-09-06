#include <iostream>
#include "PigLatinConverter.h"
#include "ThreadPool.h"
#include "ThreadSafeBlockingQueue.h"
#include <thread>

int main() {
    PigLatinConverter pigLatinConverter;
    std::vector<std::future<int> > results;


    //create thread pool manager
    ThreadPool threadPoolMgr(std::thread::hardware_concurrency() - 2);

    //thread safe queue for return of the
    ThreadSafeBlockingQueue<std::future<std::string>> threadSafeBlockingQueue;

    while (true) {
        std::string text;
        std::cout<<"Enter Text:";
        getline(std::cin,text);
        if(text == "q" || text == "quit"|| text=="exit") {
            break;
        }
        results.emplace_back(
                threadPoolMgr.enqueue([] {
                    std::cout << "hello from a thread" << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    return 1;
                })
        );
    }

    return 0;
}