// Shows how the race condition in race.cpp can be fixed via a mutex.
// In this case, the execution is essentially 100% serial across the
// two threads.

#include <iostream>
#include <mutex>
#include <thread>

void do_stuff(int &value, std::mutex &m) {
  m.lock(); // blocks until the lock is granted

  // sleeping helps show the non-determinism
  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  // this value is the same memory address as in the main thread
  value += 5;

  m.unlock(); // don't forget to unlock (or you will deadlock)!
}

int main() {
  for (int i = 0; i < 20; ++i) {
    int value = 0;
    std::mutex m;

    std::thread t(do_stuff, std::ref(value), std::ref(m));

    m.lock(); // blocks until the lock is granted

    // sleeping helps show the non-determinism
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    value += 10;

    m.unlock();

    t.join();
    std::cout << value << std::endl;
  }

  return 0;
}
