#include <vector>

#include "timer.h"

#define NUM_UNITS 1000000

struct Unit {
  int x;
  int extra1[16]; // Pretend this stuff is other unit data
  int y;
  int extra2[16]; // Pretend this stuff is other unit data
  int z;
};

int main() {
  // Array of Structures (AoS)
  std::vector<Unit> units(NUM_UNITS);
  for (int i = 0; i < NUM_UNITS; i++) {
    units[i].x = i;
    units[i].y = i;
    units[i].z = i;
  }

  Timer t;
  t.start();
  for (int i = 0; i < NUM_UNITS; i++) {
    units[i].x += 1;
    units[i].y += 1;
    units[i].z += 1;
  }
  t.stop();
  std::cout << "AoS Time: " << t.elapsed() << " us" << std::endl;

  // Structure of Arrays (SoA)
  // TODO: Instead of storing units as a vector of structs, store them as a
  // struct of vectors.  Then, iterate over the vectors and update the units.
  // You can use the same timer as above to measure the time it takes to update
  // the units.

  return 0;
}
