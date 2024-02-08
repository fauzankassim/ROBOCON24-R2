#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <mcp_can.h>
#include "Motor.h"

Motor M1, M2, M3, M4;
MCP_CAN CAN0(5);

#define STANDARD_CAN_FRAME 0
struct can_frame {
    unsigned long   can_id;       // CAN_ID 
    byte            can_dlc;      // frame data length in byte 
    byte            data[8]={0};  // CAN_DATA 
}
can_output,         //CAN struct to store id,dlc and data for output from MCU to Speed controller
can_input,          //CAN struct to store id,dlc and data for input  from Speed controller to MCU
can_motor_msg[4];   //CAN struct to store id,dlc and data for M1 and M2

//char msgString[128]; For Debugging


class MotorController {
  public:
    void initialSetup() {
      CAN0.begin(MCP_ANY, CAN_1000KBPS,MCP_8MHZ);
      CAN0.setMode(MCP_NORMAL);   // Change to normal mode to allow messages to be transmitted
      can_output.can_id = 0x200;
      can_output.can_dlc = 8;
    }

    void read() {
      CAN0.readMsgBuf(&can_input.can_id, &can_input.can_dlc, can_input.data);
      switch(can_input.can_id){
        case 0x201:
        {
          can_motor_msg[0]=can_input;
          M1.rotorAngle = (int16_t) can_input.data[0] << 8 | can_input.data[1];
          M1.rotationSpeed = (int16_t) can_input.data[2] << 8 | can_input.data[3];
          M1.torqueCurrent = (int16_t) can_input.data[4] << 8 | can_input.data[5];
          M1.motorTemperature = can_input.data[6];
        }
        case 0x202:
        {
          can_motor_msg[1]=can_input;
          M2.rotorAngle = (int16_t) can_input.data[0] << 8 | can_input.data[1];
          M2.rotationSpeed = (int16_t) can_input.data[2] << 8 | can_input.data[3];
          M2.torqueCurrent = (int16_t) can_input.data[4] << 8 | can_input.data[5];
          M2.motorTemperature = can_input.data[6];
        }
        case 0x203:
        {
          can_motor_msg[2]=can_input;
          M3.rotorAngle = (int16_t) can_input.data[0] << 8 | can_input.data[1];
          M3.rotationSpeed = (int16_t) can_input.data[2] << 8 | can_input.data[3];
          M3.torqueCurrent = (int16_t) can_input.data[4] << 8 | can_input.data[5];
          M3.motorTemperature = can_input.data[6];
        }
        case 0x204:
        {
          can_motor_msg[3]=can_input;
          M4.rotorAngle = (int16_t) can_input.data[0] << 8 | can_input.data[1];
          M4.rotationSpeed = (int16_t) can_input.data[2] << 8 | can_input.data[3];
          M4.torqueCurrent = (int16_t) can_input.data[4] << 8 | can_input.data[5];
          M4.motorTemperature = can_input.data[6];
        }
      }

      //sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Speed(RPM): ", can_motor_msg[1].can_id, can_motor_msg[1].can_dlc);
      //Serial.print(msgString);
      //Serial.println(M2.rotationSpeed); 
    }

    void write() {
      can_output.data[0] = M1.effort >> 8;
      can_output.data[1] = M1.effort;
      can_output.data[2] = M2.effort >> 8;
      can_output.data[3] = M2.effort;
      can_output.data[4] = M3.effort >> 8;
      can_output.data[5] = M3.effort;
      can_output.data[6] = M4.effort >> 8;
      can_output.data[7] = M4.effort;
      CAN0.sendMsgBuf(can_output.can_id, STANDARD_CAN_FRAME, can_output.can_dlc, can_output.data);
    }

    void positionControl() {
      M1.positionControl();
      M2.positionControl();
      M3.positionControl();
      M4.positionControl();
    }

    void speedControl() {
      M1.speedControl();
      M2.speedControl();
      M3.speedControl();
      M4.speedControl();
    }

    void updatePosition() {
      M1.updatePosition();
      M2.updatePosition();
      M3.updatePosition();
      M4.updatePosition();
    }

};

#endif