# LogOX

LogOX is a simple C++ logging library.

### Examples:

Normal loggers:

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
