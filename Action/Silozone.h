#ifndef SILOZONE_H
#define SILOZONE_H

const char* SiloNamespace[5] = {"S1", "S2", "S3", "S4", "S5"};
const char* BallKeys[5][3] = {
  {"S1B1", "S1B2", "S1B3"},
  {"S2B1", "S2B2", "S2B3"},
  {"S3B1", "S3B2", "S3B3"},
  {"S4B1", "S4B2", "S4B3"},
  {"S5B1", "S5B2", "S5B3"}
};

class Silozone {
  public:
    void initialSetup() {
      computePoint();
    }

    void computePoint() {
      point = 0;
      for (int PositionSilo = 0; PositionSilo < 5; PositionSilo++) {
        int sum = 0;
        for (int PositionBall = 0; PositionBall < 3; PositionBall++) {
          sum += silo[PositionSilo][PositionBall];
        }

        if (sum >= 2 && silo[PositionSilo][2] == 1) point++; 
      }
    }

    void insertBall(int PositionSilo, int PositionBall) {
      silo[PositionSilo][PositionBall] = 1;
    }

    void removeBall(int PositionSilo, int PositionBall) {
      silo[PositionSilo][PositionBall] = 0;
    }

    bool MuaVang() {
      return (point >= 3);
    }

    int point;
    int silo[5][3];
};

#endif