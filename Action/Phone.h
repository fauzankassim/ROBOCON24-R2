#ifndef PHONE_H
#define PHONE_H

#include <esp_now.h>
#include <WiFi.h>

typedef struct status {
  bool isMoving;
  bool isScoring;
} status;

status R2Status;

uint8_t receiverAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // MAC ADRESS RECEIVING ESP
esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {}
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) { memcpy(&R2Status, incomingData, sizeof(R2Status)); }

class Phone {
  public:
    void initialSetup() {
      WiFi.mode(WIFI_STA);
      esp_now_init();
      esp_now_register_send_cb(OnDataSent);
      memcpy(peerInfo.peer_addr, receiverAddress, 6);
      peerInfo.channel = 0;  
      peerInfo.encrypt = false;
      esp_now_add_peer(&peerInfo);
      esp_now_register_recv_cb(OnDataRecv);
    }

    void sendMessage() {
      esp_now_send(receiverAddress, (uint8_t *) &R2Status, sizeof(R2Status));
    }
    
};

#endif
