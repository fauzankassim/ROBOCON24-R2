#ifndef LOCALMEMORY_H
#define LOCALMEMORY_H

#include <Preferences.h>

Preferences preferences;

int point = 0;
int silo[5][3];

const char* SiloNamespace[5] = {"S1", "S2", "S3", "S4", "S5"};
const char* BallKeys[5][3] = {
  {"S1B1", "S1B2", "S1B3"},
  {"S2B1", "S2B2", "S2B3"},
  {"S3B1", "S3B2", "S3B3"},
  {"S4B1", "S4B2", "S4B3"},
  {"S5B1", "S5B2", "S5B3"}
};

class LocalMemory {
  public:
    void initialSetup() {
      read();
    }

    void read() {
      for (int PositionSilo = 0; PositionSilo < 5; PositionSilo++) {
        preferences.begin(SiloNamespace[PositionSilo], true);
        for (int PositionBall = 0; PositionBall < 3; PositionBall++) {
          silo[PositionSilo][PositionBall] = preferences.getInt(BallKeys[PositionSilo][PositionBall], 0);
        }
        preferences.end();
      }
    }
};

#endif
