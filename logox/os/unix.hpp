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
    FILE* file = fopen(filepath.c_str(), "r");
    int size;
    if (file){
        size = filelength(fileno(file));
        fclose(file);
    }
    return size;
}

void SetBGColor(string color){
    if(color == "white"){
        cout << "\033[47m";
    } else if(color == "red"){
        cout << "\033[41m";
    } else if(color == "yellow"){
        cout << "\033[33m\033[7m";
    } else if(color == "black"){
        cout << "\033[0m";
    }
}

#endif
