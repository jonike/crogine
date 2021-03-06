/*-----------------------------------------------------------------------

Matt Marchant 2017
http://trederia.blogspot.com

crogine - Zlib license.

This software is provided 'as-is', without any express or
implied warranty.In no event will the authors be held
liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions :

1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but
is not required.

2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any
source distribution.

-----------------------------------------------------------------------*/

//flexible logging class

#ifndef CRO_LOGGER_HPP_
#define CRO_LOGGER_HPP_

#include <crogine/Config.hpp>
#include <crogine/core/Console.hpp>
#include <crogine/util/String.hpp>

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <list>
#include <ctime>

#ifdef _MSC_VER
#define NOMINMAX
#include <Windows.h>
#endif //_MSC_VER

#ifdef __ANDROID__
#include <android/log.h>
#endif //__ANDROID__

namespace cro
{
    /*!
    \brief Class to allowing messages to be logged to a combination
    of one or more destinations such as the console, log file or
    output window in Visual Studio
    */
    class CRO_EXPORT_API Logger final
    {
    public:
        enum class Output
        {
            Console,
            File,
            All
        };

        enum class Type
        {
            Info,
            Warning,
            Error
        };
        /*!
        \brief Logs a message to a given destination.
        \param message Message to log
        \param type Whether this message gets tagged as information, a warning or an error
        \param output Destination for the message. Can be the console via cout, a log file on disk, or both
        */
        static void log(const std::string& message, Type type = Type::Info, Output output = Output::Console)
        {
            std::string outstring;
            switch (type)
            {
            case Type::Info:
            default:
                outstring = "INFO: " + message;
                break;
            case Type::Error:
                outstring = "ERROR: " + message;
                break;
            case Type::Warning:
                outstring = "WARNING: " + message;
                break;
            }
#ifndef __ANDROID__
            if (output == Output::Console || output == Output::All)
            {
                (type == Type::Error) ?
                    std::cerr << outstring << std::endl
                    :
                    std::cout << outstring << std::endl;

                Console::print(outstring);
                
                const std::size_t maxBuffer = 30;
                buffer().push_back(outstring);
                if (buffer().size() > maxBuffer)buffer().pop_front(); //no majick here pl0x
                updateOutString(maxBuffer);

#ifdef _MSC_VER
                outstring += "\n";
                OutputDebugString(outstring.c_str());
#endif //_MSC_VER
            }
            if (output == Output::File || output == Output::All)
            {
                //output to a log file
                std::ofstream file("output.log", std::ios::app);
                if (file.good())
                {

                    std::time_t time = std::time(nullptr);
                    auto tm = *std::localtime(&time);

                    file.imbue(std::locale());
                    file << std::put_time(&tm, "%d/%m/%y-%H:%M:%S: ");

                    file << outstring << std::endl;
                    file.close();
                }
                else
                {
                    log(message, type, Output::Console);
                    log("Above message was intended for log file. Opening file probably failed.", Type::Warning, Output::Console);
                }
            }
#else
			//use logcat
			__android_log_print(ANDROID_LOG_VERBOSE, "CroApp", message.c_str(), 1);
#endif //__ANDROID__
        }

        static const std::string& bufferString(){ return stringOutput(); }

    private:
        static std::list<std::string>& buffer(){ static std::list<std::string> buffer; return buffer; }
        static std::string& stringOutput() { static std::string output; return output; }
        static void updateOutString(std::size_t maxBuffer)
        {
            static size_t count = 0;
            stringOutput().append(buffer().back());
            stringOutput().append("\n");
            count++;

            if (count > maxBuffer)
            {
                stringOutput() = stringOutput().substr(stringOutput().find_first_of('\n') + 1, stringOutput().size());
                count--;
            }
        }
    };
}
#ifndef _DEBUG_
#define LOG(message, type)
#else
#define LOG(message, type) {\
std::string fileName(__FILE__); \
fileName = cro::Util::String::getFileName(fileName); \
std::stringstream ss; \
ss << message << " (" << fileName << ", " << __LINE__ << ")"; \
cro::Logger::log(ss.str(), type);}
#endif //_DEBUG_
//fileName = xy::FileSystem::getFileName(fileName); 
#endif //CRO_LOGGER_HPP_