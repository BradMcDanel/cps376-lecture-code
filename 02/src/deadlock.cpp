#include <mutex>

int main() {
    std::mutex m;
    m.lock();
    m.lock(); // Deadlocked!

    return 0;
}