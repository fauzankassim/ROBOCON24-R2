#ifndef MOTOR_H
#define MOTOR_H

#define speedKp 5
#define speedKi 5
#define positionKp 0.1
#define positionKi 0.1

template <typename T> int sgn(T val) {
  return (T(0) < val) - (val < T(0));
}

class Motor {
  public:
    Motor() {
      rotorAngle = 0;
      rotationSpeed = 0;
      torqueCurrent = 0;
      motorTemperature = 0;
      effort = 0;
      lastSpeedError = 0;
    }

    void speedControl() {
      int error = (speedSetPoint - rotationSpeed);
      effort += error * speedKp - lastSpeedError * speedKi;
      lastSpeedError = error;
      if (abs(effort) >= maxCurrent) {
          effort = sgn(effort) * maxCurrent;
      }
    }

    void positionControl() {
      int positionError = positionSetPoint - position;
      speedSetPoint = positionError * positionKp;
      if(abs(speedSetPoint) > 3000){
          speedSetPoint = sgn(speedSetPoint) * 3000;
      }
      speedControl();
    }

    void updatePosition() {
      int angleChange = rotorAngle - lastAngle;
      lastAngle = rotorAngle;
      if(abs(angleChange) > 4000){
          position -= sgn(angleChange) * 8190;
      }
      position += angleChange;
    }

    int positionSetPoint;
    int speedSetPoint;
    int16_t rotorAngle;
    int16_t rotationSpeed;
    int16_t torqueCurrent;
    int8_t motorTemperature;
    int position;
    int effort;
    int lastSpeedError;
    int lastAngle;
    
  private:
    int maxCurrent = 16384;
};

#endif