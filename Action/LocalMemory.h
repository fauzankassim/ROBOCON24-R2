#ifndef LOCALMEMORY_H
#define LOCALMEMORY_H

#include <Preferences.h>
#include "Silozone.h"

Preferences preferences;
Silozone R2Silozone;

class LocalMemory {
  public:
    void initialSetup() {
      readSilo();
    }

    void refresh(){
      writeSilo();
      readSilo();
    }

  private:
    void readSilo() {
      for (int PositionSilo = 0; PositionSilo < 5; PositionSilo++) {
        preferences.begin(SiloNamespace[PositionSilo], true);
        for (int PositionBall = 0; PositionBall < 3; PositionBall++) {
          R2Silozone.silo[PositionSilo][PositionBall] = preferences.getInt(BallKeys[PositionSilo][PositionBall], 0);
        }
        preferences.end();
      }
    }

    void writeSilo() {
      for (int PositionSilo = 0; PositionSilo < 5; PositionSilo++) {
        preferences.begin(SiloNamespace[PositionSilo], true);
        for (int PositionBall = 0; PositionBall < 3; PositionBall++) {
          preferences.putInt(BallKeys[PositionSilo][PositionBall], R2Silozone.silo[PositionSilo][PositionBall]);
        }
        preferences.end();
      }
    }

};

#endif
