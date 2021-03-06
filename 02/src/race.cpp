// This example is a bit contrived, but show a simple example of a race condition

#include <iostream>
#include <thread>

void do_stuff(int& value) {
  int tmp = value; // simulates a read to use value later

  // sleeping helps show the non-determinism
  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  // this value is the same memory address as in the main thread
  value = tmp + 5;
}

int main() {
  for (int i = 0; i < 20; ++i) {
    int value = 0;

    std::thread t(do_stuff, std::ref(value));

    int tmp = value;

    // sleeping helps show the non-determinism
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    value = tmp + 10;

    t.join();
    std::cout << value << std::endl;
  }

  return 0;
}
