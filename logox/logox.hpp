/*
 *    The main header file of LogOX.
 *       __  ______   ______   ______  __    __
 *      | | |  ____| |  __  | |  ____| \ \  / /
 *      | | | |___|| |____  | | |___||  \ \/ /
 *      |_| |______| |______| |______|  / /\ \
 *                                    /_/   \_\
 *
 *    By Elytraflyer(http://github.com/elytraflyer) 2020.12
 */

#ifdef __WIN32
#include "os/winos.hpp"
#endif
#ifdef __linux
#include "os/unix.hpp"
#endif

#ifndef LOGOX_HPP
#define LOGOX_HPP

#include "base/logox_msgbuf.hpp"
#include "base/logox_exception.hpp"
#include "base/logox_version.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <thread>

using namespace std;

// ************************************************************************************************
// ***********|                          main things                               |***************
// ************************************************************************************************

namespace Size{                         //designed for the sizerotating loggers
    constexpr int KBToByte(int kilobyte) noexcept{
        return kilobyte * 1048;
    }

    constexpr int MBToByte(int megabyte) noexcept{
        return megabyte * 1048 * 1048;
    }

    constexpr int GBToByte(int gigabyte) noexcept{
        return gigabyte * 1048 * 1048 * 1048;
    }
}   //namespace Size

namespace logox {

    // Output & File Stream
    ostream output(cout.rdbuf());
    ofstream outfile;

    // Rule Number
    #define NEWLINE_FLAG       0
    #define FILE_TRUNC_FLAG    1
    #define FILE_NTRUNC_FLAG   2
    #define TIME_FLAG          3
    #define TO_MSGBUF_FLAG     4

    // Logging level
    #define NORMAL_LEVEL       5
    #define TRACE_LEVEL        6
    #define DEBUG_LEVEL        7
    #define ALL_LEVEL          8

    class LOGOX {

    private:

        // flags and flag macros.
        bool log_flag[5] = {true, false, true, false, true};

        int log_level = NORMAL_LEVEL;

    public:

        //Default message buffer,Tracing message buffer,Debug message buffer
        msgbuf_t _MessageBuffer,_TraceBuffer,          _DebugBuffer;

        //Rules & Rules editor
        void ChLogRules(int RULES_NAME,bool value = true){ //change logger rules
            log_flag[RULES_NAME] = value;
        }

        // console loggers

        bool LogToConsole(string message, string placeholder = "[MESSAGE] ") {
            SetFontColor("white");
            output << placeholder << message;

            if (log_flag[NEWLINE_FLAG]) {
                output << '\n';
            }
            if (log_flag[TO_MSGBUF_FLAG]) {
                _MessageBuffer.InsertMsg(message);
            }
            return true;
        }

        bool LogToConsole_Cond(bool expr, string message,string placeholder = "[MESSAGE] ") {
            if (expr) {
                SetFontColor("white");
                output << placeholder << message;

                if (log_flag[NEWLINE_FLAG]) {
                    output << '\n';
                }
                if (log_flag[TO_MSGBUF_FLAG]) {
                    _MessageBuffer.InsertMsg(message);
                }
                return true;
            } else {
                return false;
            }
        }

        // warning loggers

        bool WarnToConsole(string message, string placeholder = "[WARNING] ") {
            SetFontColor("yellow");
            output << placeholder << message;

            if (log_flag[NEWLINE_FLAG]) {
                output << '\n';
            }
            if (log_flag[TO_MSGBUF_FLAG]) {
                _MessageBuffer.InsertMsg(message);
            }

            SetFontColor("white");
            return true;
        }

        bool WarnToConsole_Cond(bool expr, string message,string placeholder = "[WARNING] ") {
            if (expr) {
                SetFontColor("yellow");
                output << placeholder << message;

                if (log_flag[NEWLINE_FLAG]) {
                    output << '\n';
                }
                if (log_flag[TO_MSGBUF_FLAG]) {
                    _MessageBuffer.InsertMsg(message);
                }

                SetFontColor("white");
                return true;
            } else {
                return false;
            }
        }

        bool ErrorToConsole(string message, string placeholder = "[ERROR]   ") {
            SetFontColor("red");
            printf("%s",(placeholder + message).c_str());

            if (log_flag[NEWLINE_FLAG]) {
                printf("%c",'\n');
            }
            if (log_flag[TO_MSGBUF_FLAG]) {
                _MessageBuffer.InsertMsg(message);
            }

            SetFontColor("white");
            return true;
        }

        bool ErrorToConsole_Cond(bool expr, string message,string placeholder = "[ERROR]   ") {
            if (expr) {
                SetFontColor("red");
                output << placeholder << message;

                if (log_flag[NEWLINE_FLAG]) {
                    output << '\n';
                }
                if (log_flag[TO_MSGBUF_FLAG]) {
                    _MessageBuffer.InsertMsg(message);
                }

                return true;
            } else {
                return false;
            }
        }

        // File Loggers

        bool LogToFile(string message, string ToFile,string placeholder = "[MESSAGE] ") {
            if(outfile){
                if (log_flag[FILE_NTRUNC_FLAG]) {
                    outfile.open(ToFile,ios::app);
                } else if (log_flag[FILE_TRUNC_FLAG]) {
                    outfile.open(ToFile,ios::trunc);
                } else {
                    LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("Logger file open mode not assigned.");
                    throw LXe;
                    return false;
                }

                outfile << placeholder << message;

                if (log_flag[NEWLINE_FLAG]) {
                    outfile << '\n';
                }
                if (log_flag[TO_MSGBUF_FLAG]) {
                    _MessageBuffer.InsertMsg(message);
                }

                outfile.close();
                return true;
            } else {
                LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File not opened.");
                throw LXe;
                return false;
            }
        }

        bool LogToFile_Cond(bool expr, string message, string ToFile,string placeholder = "[MESSAGE] ") {
            if (expr) {
                if(outfile){
                    if (log_flag[FILE_NTRUNC_FLAG]) {
                        outfile.open(ToFile,ios::app);
                    } else if (log_flag[FILE_TRUNC_FLAG]) {
                        outfile.open(ToFile,ios::trunc);
                    } else {
                        LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("Logger file open mode not assigned.");
                        throw LXe;
                        return false;
                    }

                    outfile << placeholder << message;

                    if (log_flag[NEWLINE_FLAG]) {
                        outfile << '\n';
                    }
                    if (log_flag[TO_MSGBUF_FLAG]) {
                        _MessageBuffer.InsertMsg(message);
                    }

                    outfile.close();
                    return true;
                } else {
                    LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File not opened.");
                    throw LXe;
                    return false;
                }
            } else {
                return false;
            }
        }

        bool WarnToFile(string message, string ToFile,string placeholder = "[WARNING] ") {
            if(outfile){
                if (log_flag[FILE_NTRUNC_FLAG]) {
                    outfile.open(ToFile,ios::app);
                } else if (log_flag[FILE_TRUNC_FLAG]) {
                    outfile.open(ToFile,ios::trunc);
                } else {
                    LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("Logger file open mode not assigned.");
                    throw LXe;
                    return false;
                }

                outfile << placeholder << message;

                if (log_flag[NEWLINE_FLAG]) {
                    outfile << '\n';
                }
                if (log_flag[TO_MSGBUF_FLAG]) {
                    _MessageBuffer.InsertMsg(message);
                }

                outfile.close();
                return true;
            } else {
                LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File not opened.");
                throw LXe;
                return false;
            }

            outfile.close();
            return true;
        }

        bool WarnToFile_Cond(bool expr, string message, string ToFile,string placeholder = "[WARNING] ") {
            if (expr) {
                if(outfile){
                    if (log_flag[FILE_NTRUNC_FLAG]) {
                        outfile.open(ToFile,ios::app);
                    } else if (log_flag[FILE_TRUNC_FLAG]) {
                        outfile.open(ToFile,ios::trunc);
                    } else {
                        LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("Logger file open mode not assigned.");
                        throw LXe;
                        return false;
                    }

                    outfile << placeholder << message;

                    if (log_flag[NEWLINE_FLAG]) {
                        outfile << '\n';
                    }
                    if (log_flag[TO_MSGBUF_FLAG]) {
                        _MessageBuffer.InsertMsg(message);
                    }

                    outfile.close();
                    return true;
                } else {
                    LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File not opened.");
                    throw LXe;
                    return false;
                }
            } else {
                return false;
            }
        }

        bool ErrorToFile_Cond(bool expr, string message, string ToFile,string placeholder = "[ERROR]   ") {
            if (expr) {
                if(outfile){
                    if (log_flag[FILE_NTRUNC_FLAG]) {
                        outfile.open(ToFile,ios::app);
                    } else if (log_flag[FILE_TRUNC_FLAG]) {
                        outfile.open(ToFile,ios::trunc);
                    } else {
                        LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("Logger file open mode not assigned.");
                        throw LXe;
                        return false;
                    }

                    outfile << placeholder << message;

                    if (log_flag[NEWLINE_FLAG]) {
                        outfile << '\n';
                    }
                    if (log_flag[TO_MSGBUF_FLAG]) {
                        _MessageBuffer.InsertMsg(message);
                    }

                    outfile.close();
                    return true;
                } else {
                    LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File not opened.");
                    throw LXe;
                    return false;
                }
            } else {
                return false;
            }
        }

        bool LogToConsole_MT(int threads, string message,string placeholder = "[MESSAGE] ") {
            SetFontColor("white");
            thread thr[threads];
            for (int i = 0; i < threads; i++) {
                if(log_flag[NEWLINE_FLAG]){
                    thr[i] = thread([&](){
                        output << placeholder << message << '\n';
                    });
                } else {
                    thr[i] = thread([&](){
                        output << placeholder << message;
                    });
                }
            }
            for(int i = 0;i < threads;i++){
                thr[i].join();
            }

            if (log_flag[TO_MSGBUF_FLAG]) {
                _MessageBuffer.InsertMsg(message);
            }

            SetFontColor("white");
            return true;
        }

        bool LogToConsole_Daily(string message, string placeholder = "[MESSAGE] ") {
            SetFontColor("white");
            output << placeholder << message;
            if(log_flag[NEWLINE_FLAG]){
                output << '\n';
            }
            if (log_flag[TO_MSGBUF_FLAG]) {
                _MessageBuffer.InsertMsg(message);
            }

            while(true){
                this_thread::sleep_for(chrono::hours(24));
                output << placeholder << message;
                if(log_flag[NEWLINE_FLAG]){
                    output << '\n';
                }
            }

            SetFontColor("white");
            return true;
        }

        bool WarnToConsole_MT(int threads, string message,string placeholder = "[WARNING] ") {
            SetFontColor("yellow");
            thread thr[threads];
            for (int i = 0; i < threads; i++) {
                if(log_flag[NEWLINE_FLAG]){
                    thr[i] = thread([&](){
                        output << placeholder << message << '\n';
                    });
                } else {
                    thr[i] = thread([&](){
                        output << placeholder << message;
                    });
                }
            }
            for(int i = 0;i < threads;i++){
                thr[i].join();
            }

            if (log_flag[TO_MSGBUF_FLAG]) {
                _MessageBuffer.InsertMsg(message);
            }
            SetFontColor("white");
            return true;
        }

        bool WarnToConsole_Daily(string message, string placeholder = "[WARNING] ") {
            SetFontColor("yellow");
            output << placeholder << message;
            if(log_flag[NEWLINE_FLAG]){
                output << '\n';
            }
            if (log_flag[TO_MSGBUF_FLAG]) {
                _MessageBuffer.InsertMsg(message);
            }

            while(true){
                this_thread::sleep_for(chrono::hours(24));
                output << placeholder << message;
                if(log_flag[NEWLINE_FLAG]){
                    output << '\n';
                }
            }

            SetFontColor("white");
            return true;
        }

        bool ErrorToConsole_MT(int threads, string message,string placeholder = "[ERROR]   ") {
            SetFontColor("red");
            thread thr[threads];
            for (int i = 0; i < threads; i++) {
                if(log_flag[NEWLINE_FLAG]){
                    thr[i] = thread([&](){
                        output << placeholder << message << '\n';
                    });
                } else {
                    thr[i] = thread([&](){
                        output << placeholder << message;
                    });
                }
            }
            for(int i = 0;i < threads;i++){
                thr[i].join();
            }
            if (log_flag[TO_MSGBUF_FLAG]) {
                _MessageBuffer.InsertMsg(message);
            }

            SetFontColor("white");
            return true;
        }

        bool ErrorToConsole_Daily(string message, string placeholder = "[ERROR]   ") {
            SetFontColor("red");
            output << placeholder + message;
            if(log_flag[NEWLINE_FLAG]){
                output << '\n';
            }
            if (log_flag[TO_MSGBUF_FLAG]) {
                _MessageBuffer.InsertMsg(message);
            }

            while(true){
                this_thread::sleep_for(chrono::hours(24));
                output << placeholder + message;
                if(log_flag[NEWLINE_FLAG]){
                    output << '\n';
                }
            }

            SetFontColor("white");
            return true;
        }

        bool LogToFile_Daily(string message, string ToFile,string placeholder = "[MESSAGE] ") {
            if (outfile) {
                if (log_flag[FILE_NTRUNC_FLAG]) {
                    outfile.open(ToFile, ios::app);
                } else if (log_flag[FILE_TRUNC_FLAG]) {
                    outfile.open(ToFile, ios::trunc);
                } else {
                    LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File open mode not assigned.");
                    throw LXe;
                    return false;
                }

                outfile << placeholder + message;

                if (log_flag[NEWLINE_FLAG]) {
                    outfile << '\n';
                }
                if (log_flag[TO_MSGBUF_FLAG]) {
                    _MessageBuffer.InsertMsg(message);
                }

                while(true){
                    this_thread::sleep_for(chrono::hours(24));
                    outfile << placeholder + message;
                    if(log_flag[NEWLINE_FLAG]){
                        outfile << '\n';
                    }
                }
            } else {
                LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File not opened.");
                throw LXe;
                return false;
            }
        }

        bool WarnToFile_Daily(string message, string ToFile,string placeholder = "[WARNING] ") {
            if (outfile) {
                if (log_flag[FILE_NTRUNC_FLAG]) {
                    outfile.open(ToFile, ios::app);
                } else if (log_flag[FILE_TRUNC_FLAG]) {
                    outfile.open(ToFile, ios::trunc);
                } else {
                    LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File open mode not assigned.");
                    throw LXe;
                    return false;
                }

                outfile << placeholder + message;

                if (log_flag[NEWLINE_FLAG]) {
                    outfile << '\n';
                }
                if (log_flag[TO_MSGBUF_FLAG]) {
                    _MessageBuffer.InsertMsg(message);
                }

                while(true){
                    this_thread::sleep_for(chrono::hours(24));
                    outfile << placeholder + message;
                    if(log_flag[NEWLINE_FLAG]){
                        outfile << '\n';
                    }
                }
            } else {
                LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File not opened.");
                throw LXe;
                return false;
            }
        }

        bool ErrorToFile_Daily(string message, string ToFile,string placeholder = "[ERROR]   ") {
            if (outfile) {
                if (log_flag[FILE_NTRUNC_FLAG]) {
                    outfile.open(ToFile, ios::app);
                } else if (log_flag[FILE_TRUNC_FLAG]) {
                    outfile.open(ToFile, ios::trunc);
                } else {
                    LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File open mode not assigned.");
                    throw LXe;
                    return false;
                }

                outfile << placeholder + message;

                if (log_flag[NEWLINE_FLAG]) {
                    outfile << '\n';
                }
                if (log_flag[TO_MSGBUF_FLAG]) {
                    _MessageBuffer.InsertMsg(message);
                }

                while(true){
                    this_thread::sleep_for(chrono::hours(24));
                    outfile << placeholder + message;
                    if(log_flag[NEWLINE_FLAG]){
                        outfile << '\n';
                    }
                }
            } else {
                LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File not opened.");
                throw LXe;
                return false;
            }
        }

        bool LogToFile_MT(int threads,string message, string ToFile,string placeholder = "[MESSAGE] ") {
            thread thr[threads];

            if (outfile) {
                if (log_flag[FILE_NTRUNC_FLAG]) {
                    outfile.open(ToFile, ios::app);
                } else if (log_flag[FILE_TRUNC_FLAG]) {
                    outfile.open(ToFile, ios::trunc);
                } else {
                    LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File open mode not assigned.");
                    throw LXe;
                    return false;
                }

                for(int i = 0;i < threads;i++){
                    if(log_flag[NEWLINE_FLAG]){
                        thr[i] = thread([&](){
                            outfile << placeholder + message + '\n';
                        });
                    } else {
                        thr[i] = thread([&](){
                            outfile << placeholder + message;
                        });
                    }
                }

                for(int i = 0;i < threads;i++){
                    thr[i].join();
                }

                if (log_flag[TO_MSGBUF_FLAG]) {
                    _MessageBuffer.InsertMsg(message);
                }
                outfile.close();
                return true;
            } else {
                LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File not opened.");
                throw LXe;
                return false;
            }
        }

        bool WarnToFile_MT(int threads,string message, string ToFile,string placeholder = "[WARNING] ") {
            thread thr[threads];

            if (outfile) {
                if (log_flag[FILE_NTRUNC_FLAG]) {
                    outfile.open(ToFile, ios::app);
                } else if (log_flag[FILE_TRUNC_FLAG]) {
                    outfile.open(ToFile, ios::trunc);
                } else {
                    LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File open mode not assigned.");
                    throw LXe;
                    return false;
                }

                for(int i = 0;i < threads;i++){
                    if(log_flag[NEWLINE_FLAG]){
                        thr[i] = thread([&](){
                            outfile << placeholder + message + '\n';
                        });
                    } else {
                        thr[i] = thread([&](){
                            outfile << placeholder + message;
                        });
                    }
                }

                for(int i = 0;i < threads;i++){
                    thr[i].join();
                }

                if (log_flag[TO_MSGBUF_FLAG]) {
                    _MessageBuffer.InsertMsg(message);
                }
                outfile.close();
                return true;
            } else {
                LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File not opened.");
                throw LXe;
                return false;
            }
        }

        bool ErrorToFile_MT(int threads,string message, string ToFile,string placeholder = "[ERROR]   ") {
            thread thr[threads];

            if (outfile) {
                if (log_flag[FILE_NTRUNC_FLAG]) {
                    outfile.open(ToFile, ios::app);
                } else if (log_flag[FILE_TRUNC_FLAG]) {
                    outfile.open(ToFile, ios::trunc);
                } else {
                    LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File open mode not assigned.");
                    throw LXe;
                    return false;
                }

                for(int i = 0;i < threads;i++){
                    if(log_flag[NEWLINE_FLAG]){
                        thr[i] = thread([&](){
                            outfile << placeholder + message + '\n';
                        });
                    } else {
                        thr[i] = thread([&](){
                            outfile << placeholder + message;
                        });
                    }
                }

                for(int i = 0;i < threads;i++){
                    thr[i].join();
                }

                if (log_flag[TO_MSGBUF_FLAG]) {
                    _MessageBuffer.InsertMsg(message);
                }
                outfile.close();
                return true;
            } else {
                LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File not opened.");
                throw LXe;
                return false;
            }
        }

        bool LogToFile_SR(int bytes,string message,string ToFile,string placeholder = "[MESSAGE] "){ //SR: Size Rotating
            if(FileSize(ToFile) > bytes && outfile){
                outfile.open(ToFile, ios::trunc);

                outfile << placeholder + message;
                if(log_flag[NEWLINE_FLAG]){
                    outfile << '\n';
                }
                if(log_flag[TO_MSGBUF_FLAG]){
                    _MessageBuffer.InsertMsg(message);
                }
                outfile.close();
                return true;
            } else {
                LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File not opened OR There's problem on the file size.");
                throw LXe;
                return false;
            }

            if (FileSize(ToFile) <= bytes && outfile) {
                if (log_flag[FILE_NTRUNC_FLAG]) {
                    outfile.open(ToFile, ios::app);
                } else if (log_flag[FILE_TRUNC_FLAG]) {
                    outfile.open(ToFile, ios::trunc);
                } else {
                    outfile.open(ToFile);
                }

                outfile << placeholder + message;
                if(log_flag[NEWLINE_FLAG]){
                    outfile << '\n';
                }
                if(log_flag[TO_MSGBUF_FLAG]){
                    _MessageBuffer.InsertMsg(message);
                }

                outfile.close();
                return true;
            } else {
                LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File not opened.");
                throw LXe;
                return false;
            }
        }

        bool WarnToFile_SR(int bytes,string message,string ToFile,string placeholder = "[WARNING] "){ //SR: Size Rotating
            if(FileSize(ToFile) > bytes && outfile){
                outfile.open(ToFile, ios::trunc);

                outfile << placeholder + message;
                if(log_flag[NEWLINE_FLAG]){
                    outfile << '\n';
                }
                if(log_flag[TO_MSGBUF_FLAG]){
                    _MessageBuffer.InsertMsg(message);
                }
                outfile.close();
                return true;
            } else {
                LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File not opened OR There's problem on the file size.");
                throw LXe;
                return false;
            }

            if (FileSize(ToFile) <= bytes && outfile) {
                if (log_flag[FILE_NTRUNC_FLAG]) {
                    outfile.open(ToFile, ios::app);
                } else if (log_flag[FILE_TRUNC_FLAG]) {
                    outfile.open(ToFile, ios::trunc);
                } else {
                    outfile.open(ToFile);
                }

                outfile << placeholder + message;
                if(log_flag[NEWLINE_FLAG]){
                    outfile << '\n';
                }
                if(log_flag[TO_MSGBUF_FLAG]){
                    _MessageBuffer.InsertMsg(message);
                }

                outfile.close();
                return true;
            } else {
                LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File not opened.");
                throw LXe;
                return false;
            }
        }

        bool ErrorToFile_SR(int bytes,string message,string ToFile,string placeholder = "[ERROR]   "){ //SR: Size Rotating
            if(FileSize(ToFile) > bytes && outfile){
                outfile.open(ToFile, ios::trunc);

                outfile << placeholder + message;
                if(log_flag[NEWLINE_FLAG]){
                    outfile << '\n';
                }
                if(log_flag[TO_MSGBUF_FLAG]){
                    _MessageBuffer.InsertMsg(message);
                }
                outfile.close();
                return true;
            } else {
                LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File not opened OR There's problem on the file size.");
                throw LXe;
                return false;
            }

            if (FileSize(ToFile) <= bytes && outfile) {
                if (log_flag[FILE_NTRUNC_FLAG]) {
                    outfile.open(ToFile, ios::app);
                } else if (log_flag[FILE_TRUNC_FLAG]) {
                    outfile.open(ToFile, ios::trunc);
                } else {
                    outfile.open(ToFile);
                }

                outfile << placeholder + message;
                if(log_flag[NEWLINE_FLAG]){
                    outfile << '\n';
                }
                if(log_flag[TO_MSGBUF_FLAG]){
                    _MessageBuffer.InsertMsg(message);
                }

                outfile.close();
                return true;
            } else {
                LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File not opened.");
                throw LXe;
                return false;
            }
        }

        bool LogToConsole_Wait(string message,chrono::duration<long long int> du = chrono::seconds(1),string placeholder = "[MESSAGE] "){
            this_thread::sleep_for(du);

            output << placeholder << message;

            if(log_flag[NEWLINE_FLAG]){
                output << '\n';
            }
            if(log_flag[TO_MSGBUF_FLAG]){
                _MessageBuffer.InsertMsg(message);
            }
            return true;
        }

        bool WarnToConsole_Wait(string message,chrono::duration<long long int> du = chrono::seconds(1),string placeholder = "[WARNING] "){
            this_thread::sleep_for(du);

            SetFontColor("yellow");
            output << placeholder << message;

            if(log_flag[NEWLINE_FLAG]){
                output << '\n';
            }
            if(log_flag[TO_MSGBUF_FLAG]){
                _MessageBuffer.InsertMsg(message);
            }
            return true;
        }

        bool ErrorToConsole_Wait(string message,chrono::duration<long long int> du = chrono::seconds(1),string placeholder = "[ERROR]   "){
            this_thread::sleep_for(du);

            output << placeholder << message;

            if(log_flag[NEWLINE_FLAG]){
                output << '\n';
            }
            if(log_flag[TO_MSGBUF_FLAG]){
                _MessageBuffer.InsertMsg(message);
            }
            return true;
        }

        bool LogToFile_Wait(string message, string ToFile,chrono::duration<long long int> du = chrono::seconds(1),string placeholder = "[MESSAGE] ") {
            if (outfile) {
                if (log_flag[FILE_NTRUNC_FLAG]) {
                    outfile.open(ToFile, ios::app);
                } else if (log_flag[FILE_TRUNC_FLAG]) {
                    outfile.open(ToFile, ios::trunc);
                } else {
                    outfile.open(ToFile);
                }

                this_thread::sleep_for(du);
                outfile << placeholder << message;

                if (log_flag[NEWLINE_FLAG]) {
                    outfile << '\n';
                }
                if (log_flag[TO_MSGBUF_FLAG]) {
                    _MessageBuffer.InsertMsg(message);
                }

                outfile.close();
                return true;
            } else {
                LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File not opened.");
                throw LXe;
                return false;
            }
        }

        bool WarnToFile_Wait(string message, string ToFile,chrono::duration<long long int> du = chrono::seconds(1),string placeholder = "[WARNING] ") {
            if (outfile) {
                if (log_flag[FILE_NTRUNC_FLAG]) {
                    outfile.open(ToFile, ios::app);
                } else if (log_flag[FILE_TRUNC_FLAG]) {
                    outfile.open(ToFile, ios::trunc);
                } else {
                    outfile.open(ToFile);
                }

                this_thread::sleep_for(du);
                outfile << placeholder << message;

                if (log_flag[NEWLINE_FLAG]) {
                    outfile << '\n';
                }
                if (log_flag[TO_MSGBUF_FLAG]) {
                    _MessageBuffer.InsertMsg(message);
                }

                outfile.close();
                return true;
            } else {
                LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File not opened.");
                throw LXe;
                return false;
            }
        }

        bool ErrorToFile_Wait(string message, string ToFile,chrono::duration<long long int> du = chrono::seconds(1),string placeholder = "[ERROR]   ") {
            if (outfile) {
                if (log_flag[FILE_NTRUNC_FLAG]) {
                    outfile.open(ToFile, ios::app);
                } else if (log_flag[FILE_TRUNC_FLAG]) {
                    outfile.open(ToFile, ios::trunc);
                } else {
                    outfile.open(ToFile);
                }

                this_thread::sleep_for(du);
                outfile << placeholder << message;

                if (log_flag[NEWLINE_FLAG]) {
                    outfile << '\n';
                }
                if (log_flag[TO_MSGBUF_FLAG]) {
                    _MessageBuffer.InsertMsg(message);
                }

                outfile.close();
                return true;
            } else {
                LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("File not opened.");
                throw LXe;
                return false;
            }
        }

        void DumpBuffer(msgbuf_t& __msgbuf){
            for(int i = 0;i < __msgbuf.size();i++){
                output << __msgbuf[i];
                if(log_flag[NEWLINE_FLAG]){
                    output << '\n';
                } else {
                    output << ' ';
                }
            }
        }

        bool GetLogRule(int RULE_NUMBER) noexcept{
            return log_flag[RULE_NUMBER];
        }

        bool Log_Trace(string message,string placeholder = "[MESSAGE]"){
            _TraceBuffer.InsertMsg(message);
            if(log_level == TRACE_LEVEL || log_level == ALL_LEVEL){
                SetBGColor("white");
                SetFontColor("grey");
                output << placeholder << message;
                if(log_flag[NEWLINE_FLAG]){
                    output << '\n';
                }
                SetBGColor("black");
                SetFontColor("white");
            }
            return true;
        }

        bool Warn_Trace(string message,string placeholder = "[WARNING]"){
            _TraceBuffer.InsertMsg(message);
            if(log_level == TRACE_LEVEL || log_level == ALL_LEVEL){
                SetBGColor("yellow");
                SetFontColor("white");
                output << placeholder << message;
                if(log_flag[NEWLINE_FLAG]){
                    output << '\n';
                }
                SetBGColor("black");
            }
            return true;
        }

        bool Error_Trace(string message,string placeholder = "[ERROR]   "){
            _TraceBuffer.InsertMsg(message);
            if(log_level == TRACE_LEVEL || log_level == ALL_LEVEL){
                SetBGColor("red");
                SetFontColor("white");
                output << placeholder << message;
                if(log_flag[NEWLINE_FLAG]){
                    output << '\n';
                }
                SetBGColor("black");
            }
            return true;
        }

        bool DEBUG_LOG(string message,string placeholder = "[DEBUG]   "){
            _DebugBuffer.InsertMsg(message);
            if(log_level == DEBUG_LEVEL || log_level == ALL_LEVEL){
                SetBGColor("red");
                SetFontColor("white");
                output << placeholder << message;
                if(log_flag[NEWLINE_FLAG]){
                    output << '\n';
                }
                SetBGColor("black");
            }
            return true;
        }
    // end of class
    };

}   //namespace LOGOX


// ************************************************************************************************
// ***********|                      end main things                             |*****************
// ************************************************************************************************


#endif
