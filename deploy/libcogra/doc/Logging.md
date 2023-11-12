# Logging

## Using the logging system

Everything to do with logging is in the namespace "cogra::io:log". To use the logging system include the header with `#include <cogra/io/Log.h>` and add a line like `cogra::io::LOG(cogra::io::log::info,"Your log entry here");` where you want to log something. Instead of `cogra::io::log::info` you can use a different channel to log to. For normal use of the logging systeme predefined logging channels are avaible. Those channels are:
- info: General info about the program
- warning: Something is not right like a file could not be found or loaded, but the program can still work
- error: Something went wrong and the program should not continue
- debug: Info for debugging purposes
- test: Channel for testing and grading purposes

Every channel outputs a message to the console, except test and debug. Debug trys to output, if used with windows, to the debug console of a running Visual Studio. Test addionally creates a file called "test.log" in the same diretory as the program and writes to that file if possible.

## Formating outputs

Most of the time there is the need to output variable info instead of static text, like a variable or adresses and the like. For this use case it is possible to use logging strings with tokens together with variables like `cogra::io::LOG(cogra::io::log::info,"First var: {0} Third var: {2} Second var: {1}",var1,var2,var3);`. The number in the "{}" is the index to the variable commandline after the string. "{0}" is the first, {2} the second and so on. The logging system automatically determines the type of the argument so there is no need to specify the type inside the String like with "printf()". There are advanced formatting options avalible, more info about them is listed under the URL http://fmtlib.net/latest/syntax.html . 

## Adding outputs to existing channels

It is possible to add more outputs to existing Channel during runtime. For example if you want to output debug infos not only to the console but also to a text file you can simply type `cogra::io::log::debug.add(cogra::io::log::LOG_FILE,"debug.log");` and every log entry after that line is writing its output to the console and a file called "debug.log". The second argument is the path to the desired logfile. Possible outputs are:
- LOG_CONSOLE : Log to the Console
- LOG_DEBUG : under windows with Visual Studio running, output is shown inside the Visual Studio Debug console. Under every other platform output is the same as LOG_CONSOLE
- LOG_FILE : The argument directly after LOG_FILE must be a string that names a filepath to the desired log file. If the file does not exist it the log system will try to create it.

## Custom log channels

If the predefined log channels are not enough it is possible to create a custom log channel. All that is needed to create a channel that logs to the console is a line like `cogra::io::log::LogChannel mylog("mylog",LOG_CONSOLE);` to create a custom channel with the name "mylog". Depending on where you create the channel you can simply use it just like the predefined channels only with the name of the new channel `cogra::io::LOG(cogra::io::log::mylog,"Your log entry here");` . As with the already defined channel it is possible to add additional outputs later or even at creation time. For example with `cogra::io::log::LogChannel mylog("mylog",cogra::io::log::LOG_CONSOLE,cogra::io::log::LOG_FILE,"mylog.log");` the created channel will output to console and to a file called "mylog.log"