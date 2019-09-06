//
// Created by paulos on 9/5/19.
//
#include "FileWriteBackgroundTask.h"

void FileWriteBackgroundTask::run()
{
    std::ofstream oFile;

    oFile.open(fileName_, std::ios::out);

    if(oFile.is_open()){
        // Check if thread is requested to stop ?
        while (!stopRequested()) {
            if(!q_->empty()) {
                std::string textConverted = q_->pop().get();
                oFile << textConverted<<std::endl;
//                std::cout<<textConverted << std::endl;
            }else{
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }
    }else{
        throw OpenFileException(fileName_);
    }

}
void FileWriteBackgroundTask::start(){
    thread_ = std::thread([this](){
        run();
    });
}

void FileWriteBackgroundTask::stop() {
    Stoppable::stop();
    thread_.join();
}

