#ifndef _TIMER_H_
#define _TIMER_H_

#include <chrono>
#include <iostream>

/*
 * Simple timer class using the C++11 chrono library and high resolution clock.
 * Usage:
 *  Timer t;
 *  t.start();
 *  // Do something
 *  t.stop();
 * std::cout << "Time elapsed: " << t.elapsed() << "s" << std::endl;
 */

// Type aliases to make accessing nested type easier
using chrono_t = std::chrono::high_resolution_clock;
template <typename T> std::chrono::microseconds micros(T duration) {
    return std::chrono::duration_cast<std::chrono::microseconds>(duration);
}

class Timer {
public:
  Timer() : m_start(), m_end() {}

  void start() { m_start = chrono_t::now(); }

  void stop() { m_end = chrono_t::now(); }

  double elapsed() const {
    return micros(m_end - m_start).count();
  }

private:
  std::chrono::high_resolution_clock::time_point m_start;
  std::chrono::high_resolution_clock::time_point m_end;
};

#endif // _TIMER_H_
