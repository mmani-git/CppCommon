/*!
    \file latch.inl
    \brief Latch synchronization primitive inline implementation
    \author Ivan Shynkarenka
    \date 25.03.2016
    \copyright MIT License
*/

namespace CppCommon {

inline Latch::Latch(int counter) noexcept : _counter(counter), _generation(0)
{
    assert((counter > 0) && "Latch counter must be greater than zero!");
}

inline bool Latch::TryWaitFor(int64_t nanoseconds) noexcept
{
    return TryWaitFor(std::chrono::nanoseconds(nanoseconds));
}

template <class Rep, class Period>
inline bool Latch::TryWaitFor(const std::chrono::duration<Rep, Period>& duration) noexcept
{
    std::unique_lock<std::mutex> lock(_mutex);

    // Check the latch counter value
    if (_counter == 0)
        return true;

    // Remember the current latch generation
    int generation = _generation;

    // Wait for the next latch generation
    return _cond.wait_for(lock, duration, [=, this]() { return generation != _generation; });
}

template <class Clock, class Duration>
inline bool Latch::TryWaitUntil(const std::chrono::time_point<Clock, Duration>& timestamp) noexcept
{
    std::unique_lock<std::mutex> lock(_mutex);

    // Check the latch counter value
    if (_counter == 0)
        return true;

    // Remember the current latch generation
    int generation = _generation;

    // Wait for the next latch generation
    return _cond.wait_until(lock, timestamp, [=, this]() { return generation != _generation; });
}

} // namespace CppCommon