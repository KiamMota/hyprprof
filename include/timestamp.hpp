#ifndef TIMESTAMP_HPP
#define TIMESTAMP_HPP

#include <string>
#include <chrono>
/**
 * @brief A simple timer utility for measuring elapsed time.
 * 
 * The TimeStamp class allows measuring the duration of operations in milliseconds.
 * It provides methods to start and stop the timer and to retrieve a human-readable
 * string representation of the elapsed time.
 */
class TimeStamp
{
    using clock = std::chrono::system_clock;

    clock::time_point _start;   /**< The starting point of the timer. */
    clock::time_point _end;     /**< The ending point of the timer. */
    mutable std::string _buffer; /**< Cached string representation of the elapsed time. */
    bool _running = false;       /**< Indicates whether the timer is currently running. */

public:
    /**
     * @brief Default constructor.
     * 
     * Initializes a new TimeStamp object. The timer is not running by default.
     */
    TimeStamp() = default;

    /**
     * @brief Starts the timer.
     * 
     * Records the current time as the start point.
     */
    void start();

    /**
     * @brief Stops the timer.
     * 
     * Records the current time as the end point and calculates the elapsed time.
     */
    void stop();

    /**
     * @brief Returns a string representation of the elapsed time.
     * 
     * If the timer has been stopped, it returns the duration between start and stop.
     * The format is human-readable (e.g., "23 ms").
     * 
     * @return const std::string& The elapsed time as a string.
     */
    const std::string& to_string() const;
};


#endif // TIMESTAMP_HPP
