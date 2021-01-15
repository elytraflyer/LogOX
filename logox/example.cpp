#include <iostream>
#include <string>
#include <chrono>
#include "logox.hpp"
using namespace std;
using namespace logox;

int main(){
    LOGOX logger;
    //simple log
    logger.LogToConsole("hello");
    logger.LogToConsole_Wait("hello",chrono::seconds(5));
    return 0;
}
