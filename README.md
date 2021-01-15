# LogOX

LogOX is a simple C++ logging library based on C++11.
To use it,please download the source code and copy the "logox" folder to your working directory.

### Examples:

Normal loggers(Colors supported):

```cpp
#include "logox/logox.hpp"
using namespace std;
using namespace logox;

int main(){
    LOGOX l;
    l.LogToConsole("This is a message.");
    l.WarnToConsole("This is a warning.");
    l.ErrorToConsole("This is an error.");
    l.LogToConsole_Cond(true,"Logging with bool expressions!");
    return 0;
}
```

Log To File:

```cpp
l.LogToFile("hello.txt","hello,world");
```

Message Buffer:

```cpp
LOGOX l;
msgbuf_t msgbuf;
msgbuf.InsertMsg("hello");
l.DumpBuffer(msgbuf);
```
