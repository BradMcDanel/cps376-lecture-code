#include <iostream>
#include <thread>
#include <vector>

void hello() {
  std::cout << "Hello from thread " << std::this_thread::get_id() << std::endl;
}

int main() {
  std::vector<std::thread> threads;
  for (int i = 0; i < 10; i++) {
    std::thread t(hello);
    threads.push_back(std::move(t));
  }

  for (auto &t : threads) {
    t.join();
  }

  return 0;
}
