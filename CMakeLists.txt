cmake_minimum_required(VERSION 3.14)
project(AsyncProcCodeChallenge)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib/linux)

add_executable(AsyncProcCodeChallenge main.cpp ThreadPool.h FileWriteBackgroundTask.h Stoppable.h FileWriteBackgroundTask.cpp ThreadSafeBlockingQueue.h)
target_link_libraries(AsyncProcCodeChallenge PigLatinConverter pthread)