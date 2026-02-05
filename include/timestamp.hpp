#ifndef TIMESTAMP_HPP
#define TIMESTAMP_HPP

#include <string>
#include <chrono>
class TimeStamp {
    using clock = std::chrono::system_clock;
    std::chrono::system_clock::time_point now;

    clock::time_point _start;
    clock::time_point _end;
    mutable std::string _buffer;
    bool _running = false;

  public:
    TimeStamp() = default;
    void start();
    void stop();
    const std::string& to_string() const;
};

#endif // TIMESTAMP_HPP
