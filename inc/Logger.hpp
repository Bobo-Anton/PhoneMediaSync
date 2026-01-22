#pragma once

#include <cstdint>
#include <iomanip>
#include <iostream>

namespace Logger
{
enum class LogLevel : uint8_t
{
    kDebug,
    kWarn,
    kError
};

constexpr std::size_t WHITE_SPACE_BEFORE_LOG = 25;
constexpr std::size_t MIN_WHITE_SPACE_BEFORE_LOG = 4;

template <LogLevel level>
class LogStream
{
   public:
    constexpr LogStream()
    {
        if constexpr (level == LogLevel::kDebug)
        {
            std::cout << "[DEBUG]    ";
        }
        else if constexpr (level == LogLevel::kWarn)
        {
            std::cout << "[WARN ]    ";
        }
        else
        {
            std::cout << "[ERROR]    ";
        }
    }

    ~LogStream() { std::cout << std::endl; }

    constexpr LogStream& withLocation(const char (&file)[], int line)
    {
        const char* base = baseName(file);
        std::cout << base << ":" << line;

        std::size_t numWhitespaces = MIN_WHITE_SPACE_BEFORE_LOG;
        std::size_t baseLen = constexprStrlen(base);
        std::size_t lineLen = constexprIntLen(line);
        if (((baseLen + lineLen + 1) < WHITE_SPACE_BEFORE_LOG) && ((WHITE_SPACE_BEFORE_LOG - (baseLen + lineLen + 1)) > MIN_WHITE_SPACE_BEFORE_LOG))
        {
            numWhitespaces = WHITE_SPACE_BEFORE_LOG - (baseLen + lineLen + 1);
        }
        std::cout << std::setw(numWhitespaces) << "";
        return *this;
    }

    template <typename T>
    constexpr LogStream& operator<<(const T& value)
    {
        std::cout << value;
        return *this;
    }

   private:
    constexpr const char* baseName(const char* path)
    {
        const char* file = path;
        while (*path)
        {
            if (*path == '/')
                file = path + 1;
            ++path;
        }
        return file;
    }

    constexpr std::size_t constexprStrlen(const char* str)
    {
        std::size_t len = 0;
        while (str[len] != '\0')
        {
            ++len;
        }
        return len;
    }

    constexpr std::size_t constexprIntLen(int number)
    {
        std::size_t len = 0;
        while (number > 0)
        {
            len++;
            number /= 10;
        }
        return len;
    }
};
}  // namespace Logger

#define LOG_DEBUG() Logger::LogStream<Logger::LogLevel::kDebug>().withLocation(__FILE__, __LINE__)

#define LOG_WARN() Logger::LogStream<Logger::LogLevel::kWarn>().withLocation(__FILE__, __LINE__)

#define LOG_ERROR() Logger::LogStream<Logger::LogLevel::kError>().withLocation(__FILE__, __LINE__)
