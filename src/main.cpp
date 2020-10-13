/* 

ESP32_Bluetooth_Low_Energy_BLE_Arduino
Implement ESP32 Bluetooth Low Energy / BLE server for Espressif Systems ESP32 boards 
by Arduino framework 

Developed by: Walid Amriou
Last update: October 2020

*/

#include <Arduino.h>

// You will found more about this library here: https://github.com/nkolban/ESP32_BLE_Arduino
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// Define UUID's for the Service and Characteristic 
// You can use: https://www.uuidgenerator.net
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

void setup() {
  Serial.begin(115200);
  
  // Create a BLE device called “walidamriou_esp32_device_BLE”
  BLEDevice::init("walidamriou_esp32_device_BLE");

  // Set the BLE device as a server
  BLEServer *pServer = BLEDevice::createServer();

  // Create a service for the BLE server with the UUID defined earlier
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Set the characteristic for that service. use the UUID defined earlier, 
  // and pass arguments to the characteristic’s properties. 
  // In this case, it’s: READ and WRITE
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
    );
  
  // Set the characteristic value
  pCharacteristic->setValue("This is Walid Amriou BLE device based ESP32 board");
  
  // Start the service
  pService->start();
  
  // Start the advertising, so other BLE devices can scan and find this BLE device
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void loop() {
  delay(2000);
}