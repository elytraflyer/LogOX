#ifndef LOGOX_MSGBUF_HPP
#define LOGOX_MSGBUF_HPP

using namespace std;

#define INSERT_AT_BEGIN    1
#define INSERT_AT_END      2

#include "logox_exception.hpp"

#include <algorithm>
#include <string>
#include <vector>

namespace logox{
    class msgbuf_t{
    private:
        vector<string> _msgbuf;
        int MAXLEN = 0;    // when it's length is not set,MAXLEN = 0.
                            // when it's set,it means the message buffer has length.

    public:

        msgbuf_t() = default;
        msgbuf_t(int len){MAXLEN = len;}

        virtual ~msgbuf_t() = default;
        msgbuf_t& operator=(const msgbuf_t& other) = default;
        msgbuf_t(const msgbuf_t& other) = default;

        bool MsgExist(string msg){
            vector<string>::iterator it = find(_msgbuf.begin(), _msgbuf.end(), msg);
            if(it == _msgbuf.end()){
                return false;
            } else {
                return true;
            }
        }

        void DeleteMsg(int index){
            _msgbuf.erase(_msgbuf.begin() + (index - 1));
            _msgbuf.shrink_to_fit();
        }

        void DeleteMsg(string msg){
            vector<string>::iterator it = find(_msgbuf.begin(), _msgbuf.end(), msg);
            if(it == _msgbuf.end()){
                return;
            } else {
                _msgbuf.erase(it);
            }
        }

        int GetMsgBufMaxLimit(){
            return MAXLEN;
        }

        string GetMsg(int index){
            if(index - 1 < MAXLEN){
                return _msgbuf[index];
            } else {
                return NULL;
            }
        }

        int size(){
            return _msgbuf.size();
        }

        string operator [](int index){    //same as GetMsg
            if(MAXLEN == 0 || (MAXLEN > 0 && index < MAXLEN)){
                return _msgbuf[index];
            } else {
                return "";
            }
        }

        void EmptyBuf(){
            _msgbuf.empty();
        }

        bool InsertMsg(string msg,int mode = INSERT_AT_END){
            if(_msgbuf.size() > static_cast<long long unsigned int>(MAXLEN) && MAXLEN != 0){
                LOGOX_EXCEPTION LXe = LOGOX_EXCEPTION("Buffer can't insert any message now.");
                throw LXe;
                return false;
            } else {
                switch(mode){
                case INSERT_AT_BEGIN:
                    _msgbuf.insert(_msgbuf.begin(), msg);
                    break;
                case INSERT_AT_END:
                    _msgbuf.push_back(msg);
                    break;
                default:
                    return false;
                }
                return true;
            }
        }
    };

} //namespace logox

#endif
