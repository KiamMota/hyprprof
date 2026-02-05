#include "timestamp.hpp"
#include <chrono>
#include <sstream>

void TimeStamp::start() {
    _start = clock::now();
    _running = true;
}

void TimeStamp::stop() {
    if (_running) {
        _end = clock::now();
        _running = false;
    }
}

const std::string& TimeStamp::to_string() const {
    auto end = _running ? clock::now() : _end;
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - _start);

    std::ostringstream oss;
    oss << diff.count() << " ms";
    _buffer = oss.str();

    return _buffer;
}
