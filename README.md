
# C++ JSON/Logs Boost Sample

This sample shows how to work with the libs of JSON and LOGS of BOOST. The sample covers the basic apects of Boost Log Lib and how to read a JSON file and, more important, how to compile and link the sample with these libs.

> **Important** Consider that the file boostlog.h contains all the macros to simplify the use of logs methdos on trivial mode:
 ```cpp
#define LT_TRACE    BOOST_LOG_TRIVIAL(trace)
#define LT_DEBUG    BOOST_LOG_TRIVIAL(debug)
#define LT_INFO     BOOST_LOG_TRIVIAL(info)
#define LT_WARN     BOOST_LOG_TRIVIAL(warning)
#define LT_ERROR    BOOST_LOG_TRIVIAL(error)
#define LT_FATAL    BOOST_LOG_TRIVIAL(fatal)
```

## Requierements

    1. C++17 Standar.
    2. Boost V1.77. All libraries are instaled into the `/user/local/lib` and headers in `/user/local/include`.
    3. Visual Studio Code 1.55 or above.
    4. For Linux: g++ (GCC) 11.1.0
    5. For OSX (11.5.2): Apple clang version 11.0.0 (clang-1100.0.33.17)

## Build

> Due to some problems at running time, in my case *"Segmentation Fault: 11"* at reading the files, its important to appoint that the library must be compiles with only Headers, avoiding linkig the *.so/.a* lib, on OSX environments. 

```cpp
json::value parseJson(std::istream &is, json::error_code &ec)
{
    ...

    json::value vval;

    try{
        vval = p.release();
    }
    catch(const std::exception &e)
    {
        LT_FATAL << "Error in parsing JSON file: " << e.what();
    }
    LT_TRACE << "Parsing JSON ended.";

    return vval;    // At this point the Parser's Destructor raises an exception.
}
```

1. **For JSON**, it needs to add at the beging of the *main.cpp** file the include `#include <boost/json/src.hpp>`, and remove from link step the library **boost_json**.
2.  **For Logs**, it needs to add the Macro `-DBOOST_LOG_DYN_LINK` on **link step**, to link the library as a dynamic liberary.
3.  Add the next libraries to link step: `-pthread -lboost_log -lboost_thread -lboost_log_setup -lstdc++`

## Make

To get help to use the Makefile:
```shell
$make help
.............................................
Build: make
Build with debug info: make DBGFLG=-g
Clean compiled files: make clean
```

To compile and build all the project:
```shell
$make
```

To compile and activate debug info:

```shell
$make DBGFLG=-g
```

To clean all the compiled files:

```shell
$make clean
```

## Testing

To run the sample change path to `{$workspace}/bin` and execute:

``` cmd
./sample <path to boost_jsonlogs proyect>/logs/sample_%N.log
```

## References

1. Getting starter [here](https://www.boost.org/doc/libs/1_77_0/more/getting_started/unix-variants.html).
2. JSON Lib with Header-Only [here](https://www.boost.org/doc/libs/1_75_0/libs/json/doc/html/json/overview.html#json.overview.requirements).
3. LOG Lib as Dynamic lib [here](https://www.boost.org/doc/libs/1_77_0/libs/log/doc/html/index.html).