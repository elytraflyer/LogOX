#ifndef WINOS_HPP
#define WINOS_HPP

using namespace std;

#include <fstream>
#include <io.h>
#include <windows.h>
#include <string>

bool FindFile(string ToFile){
   WIN32_FIND_DATA FindFileData;
   HANDLE hFind;

   hFind = FindFirstFile(ToFile.c_str(),
                         &FindFileData
   );
   if (hFind == INVALID_HANDLE_VALUE){
     return false;
   }
   else{
     return true;
   }
}

bool SetFontColor(string color) noexcept{
    if(color == "white"){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED  |FOREGROUND_GREEN | FOREGROUND_BLUE);
    } else if(color == "red"){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
    } else if(color == "green"){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    } else if(color == "blue"){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    } else if(color == "yellow"){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |FOREGROUND_GREEN);
    } else if(color == "cyan"){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |FOREGROUND_BLUE);
    } else if(color == "grey"){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
    } else {
        return false;
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

#endif
