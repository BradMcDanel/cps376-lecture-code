// This example is a bit contrived, but show a simple example of a race
// condition

#include <iostream>
#include <thread>

void do_stuff(int &value) {
  // sleeping helps show the non-determinism
  // if you always see the same number printed, try making 10 larger or smaller
  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  // this value is the same memory address as in the main thread
  value += 5;
}

int main() {
  for (int i = 0; i < 100; ++i) {
    int value = 0;

    std::thread t(do_stuff, std::ref(value));

    // sleeping helps show the non-determinism
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    value += 10;

    t.join();
    std::cout << value << std::endl;
  }

  return 0;
}
