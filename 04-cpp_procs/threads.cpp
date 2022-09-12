#include <iostream>
#include <thread>

void hello() {
  std::cout << "Hello from thread " << std::this_thread::get_id() << std::endl;
}

int main() {
  std::thread t(hello);
  t.join();
  return 0;
}
