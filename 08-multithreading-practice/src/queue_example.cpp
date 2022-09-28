#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#define NUM_CONSUMERS 8
#define NUM_PRODUCERS 4
#define ITEMS_PER_PRODUCER 100

void producer(std::queue<int> &q, int id, std::mutex &q_mutex) {
  for (int i = 0; i < ITEMS_PER_PRODUCER; i++) {
    q_mutex.lock();
    std::cout << "Producer " << id << " added value " << i * id << std::endl
              << std::flush;
    q.push(i * id);
    q_mutex.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
  }
}

void consumer(std::queue<int> &q, int id, std::mutex &q_mutex, int &sum) {
  while (!q.empty()) {
    q_mutex.lock();
    if (!q.empty()) {
      std::cout << "Consumer " << id << " got " << q.front() << std::endl
                << std::flush;
      sum += q.front();
      q.pop();
    }
    q_mutex.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  std::cout << id << " exited!" << std::endl;
}

int main() {
  std::queue<int> q;
  std::mutex q_mutex;
  std::vector<std::thread> threads;
  int sum = 0;

  for (int i = 0; i < NUM_PRODUCERS; i++) {
    std::thread t(producer, std::ref(q), i, std::ref(q_mutex));
    threads.push_back(std::move(t));
  }

  for (int i = 0; i < NUM_CONSUMERS; i++) {
    std::thread t(consumer, std::ref(q), i, std::ref(q_mutex), std::ref(sum));
    threads.push_back(std::move(t));
  }

  for (auto &t : threads) {
    t.join();
  }

  std::cout << "Total sum: " << sum << std::endl;

  return 0;
}
