//
// Created by paulos on 9/5/19.
//
#include "FileWriteBackgroundTask.h"
void FileWriteBackgroundTask::run()
{
    std::ofstream oFile;

    oFile.open(fileName_, std::ios::out);
    std::cout << "FileWriteBackgroundTask Start" << std::endl;

    if(oFile.is_open()){
        // Check if thread is requested to stop ?
        while (!stopRequested()) {
            if(!q_->empty()) {
                oFile << "result"<<std::endl;
                std::cout << "FileWriteBackgroundTask writing to file :"<<fileName_ << std::endl;
            }else{
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }
        std::cout << "FileWriteBackgroundTask End" << std::endl;
    }

}
void FileWriteBackgroundTask::start(){
    thread_ = std::thread([this](){
        run();
    });
}

void FileWriteBackgroundTask::stop() {
//    Stoppable::stop();
}
