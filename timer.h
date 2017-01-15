#include <chrono>
using namespace std;
using namespace std::chrono;

class Timer
{
public:
    Timer() : m_begin(high_resolution_clock::now()) {}
    void reset() { m_begin = high_resolution_clock::now(); }

    int64_t elapsed_ms() const
    {
        return duration_cast<chrono::milliseconds>(high_resolution_clock::now() - m_begin).count();
    }
    //Œ¢√Î
    int64_t elapsed_us() const
    {
        return duration_cast<chrono::microseconds>(high_resolution_clock::now() - m_begin).count();
    }

    //ƒ…√Î
    int64_t elapsed_ns() const
    {
        return duration_cast<chrono::nanoseconds>(high_resolution_clock::now() - m_begin).count();
    }

    //√Î
    int64_t elapsed_s() const
    {
        return duration_cast<chrono::seconds>(high_resolution_clock::now() - m_begin).count();
    }

    //∑÷
    int64_t elapsed_minutes() const
    {
        return duration_cast<chrono::minutes>(high_resolution_clock::now() - m_begin).count();
    }

    // ±
    int64_t elapsed_hours() const
    {
        return duration_cast<chrono::hours>(high_resolution_clock::now() - m_begin).count();
    }

private:
    time_point<high_resolution_clock> m_begin;
};

