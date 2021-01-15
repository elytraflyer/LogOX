#ifndef UNIX_HPP
#define UNIX_HPP

using namespace std;

#include <io.h>
#include <iostream>
#include <string>
#include <unistd.h>

bool FindFile(string ToFile){
    if((access(ToFile.c_str(),00)) != -1)
        return true;
    else
        return false;
}

bool SetFontColor(string color) noexcept{
    if(color == "white"){
        cout << "\033[37m";
    } else if(color == "red"){
        cout << "\033[31m";
    } else if(color == "green"){
        cout << "\033[32m";
    } else if(color == "blue"){
        cout << "\033[34m";
    } else if(color == "yellow"){
        cout << "\033[33m";
    } else if(color == "purple"){
        cout << "\033[35m";
    } else if(color == "Deep green"){
        cout << "\033[36m";
    } else if(color == "grey"){
        cout << "\033[37m\033[2m";
    } else if(color == "black"){
        cout << "\033[30m";
    }
    return true;
}

int FileSize(string filepath){
    ifstream infile(filepath,ios::binary);
    if(infile){
        infile.seekg(0,ios::end);
        int fsize = infile.tellg();
        return fsize;
    } else {
        return -1;
    }
}

#endif
