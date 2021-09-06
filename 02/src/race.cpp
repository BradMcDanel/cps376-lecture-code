#include <iostream>
#include <thread>

void do_stuff(int& value) {
  // sleeping helps show the non-determinism
  std::this_thread::sleep_for(std::chrono::milliseconds(1));

  // this value is the same memory address as in the main thread
  value = 5;
}

int main() {
  for (int i = 0; i < 20; ++i) {
    int value = 0;

    std::thread t(do_stuff, std::ref(value));

    // sleeping helps show the non-determinism
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    value = 10;

    t.join();
    std::cout << value << std::endl;
  }

  return 0;
}
