/*
  Copyright (c) 2019 Andy England

  A BLE driver for Over the Air Updates

  Built on top of the BLE utilities by Neil Kolban
  https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleNotify.cpp
*/


#ifndef _BLE_H_
#define _BLE_H_

#include "Arduino.h"

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#include "esp_ota_ops.h"


class BLE; // forward declaration

class BLECustomServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      // deviceConnected = true;
      // // code here for when device connects
    };

    void onDisconnect(BLEServer* pServer) {
      // deviceConnected = false;
      // // code here for when device disconnects
    }
};

class otaCallback: public BLECharacteristicCallbacks {
  public:
    otaCallback(BLE* ble) {
      _p_ble = ble;
    }
    BLE* _p_ble;

    void onWrite(BLECharacteristic *pCharacteristic);
};

class BLE
{
  public:

    BLE(void);
    ~BLE(void);

    bool begin(const char* localName);
  
  private:
    String local_name;

    BLEServer *pServer = NULL;

    BLEService *pInfinitePyramidService = NULL;
    BLECharacteristic * pInfinitePyramidIdCharacteristic = NULL;

    BLEService *pService = NULL;
    BLECharacteristic * pVersionCharacteristic = NULL;
    BLECharacteristic * pOtaCharacteristic = NULL;
};

#endif