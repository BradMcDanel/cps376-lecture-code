#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// Once you get it working, try changing the number of philosophers
#define NUM_PHILOSOPHERS 5

void philosopher_action(int id, std::vector<std::mutex> &forks) {
  bool has_eaten = false;
  while (!has_eaten) {
    // Acquire both forks and eat !
    // Hint: use forks[i].try_lock() to try to acquire a fork
    //       it will try to acquire the fork and return true if it was
    //       successful if it was not successful, it will return false use
    //       forks[i].unlock() to release a fork
  }
}

int main() {
  std::vector<std::thread> threads;
  std::vector<std::mutex> forks(NUM_PHILOSOPHERS);

  for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
    std::thread t(philosopher_action, i, std::ref(forks));
    threads.push_back(std::move(t));
  }

  for (auto &t : threads) {
    t.join();
  }

  return 0;
}
