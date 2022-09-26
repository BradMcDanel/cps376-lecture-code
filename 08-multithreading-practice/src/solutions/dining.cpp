#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#define NUM_PHILOSOPHERS 5

void philosopher_action(int id, std::vector<std::mutex> &forks) {
  bool has_eaten = false;
  while (!has_eaten) {
    // Think
    std::cout << "Philosopher " << id << " is thinking" << std::endl
              << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Try to get left fork
    if (forks[id].try_lock()) {
      // Try to get right fork
      if (forks[(id + 1) % NUM_PHILOSOPHERS].try_lock()) {
        // Eat
        std::cout << "Philosopher " << id << " is eating" << std::endl
                  << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        has_eaten = true;

        // Put down right fork
        forks[(id + 1) % NUM_PHILOSOPHERS].unlock();
      }
      // Put down left fork
      forks[id].unlock();
    }
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
