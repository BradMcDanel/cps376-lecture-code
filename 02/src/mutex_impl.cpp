#include <chrono>
#include <thread>

class Mutex {
private:
  bool locked;
  bool test_and_set() {
    bool tmp = locked;
    // acquire lock if it is unlocked
    if (!locked) {
      locked = true;
    }
    return tmp;
  }

public:
  Mutex() : locked(false){};

  /* In practice, this would be assembly code or using
   * something like:
   * https://en.cppreference.com/w/cpp/atomic/atomic_flag
   */
  void lock() {
    /* This type of construction is called a 'spinlock'
     * This code still could trigger a race condition!
     * In practice, it needs to be implemented using atomic
     * assembly instructions that test if its unlocked and
     * acquire the lock in the same cycle!
     */
    while (test_and_set() == 1) {
    }
  };

  void unlock() { locked = false; };
};

int main() {
  Mutex m;
  m.lock();
  m.unlock();
}
