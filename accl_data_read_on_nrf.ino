
#include <ArduinoBLE.h>
#include <Arduino_LSM9DS1.h>
#include <Arduino_BMI270_BMM150.h>

// Define the BLE service and characteristics UUIDs
BLEService accel("1214");
BLEFloatCharacteristic xCh("1215", BLERead | BLENotify);
BLEFloatCharacteristic yCh("1216", BLERead | BLENotify);
BLEFloatCharacteristic zCh("1217", BLERead | BLENotify);


void setup() {

  Serial.begin(9600*4);
  // while (!Serial);

  if (!BLE.begin()) { // Initialize the BLE module
    Serial.println("Failed to initialize BLE");
    while (1);
  }

  
  // Add the characteristics to the service
  accel.addCharacteristic(xCh);
  accel.addCharacteristic(yCh);
  accel.addCharacteristic(zCh);


  // xCh.writeValue(0);
  // yCh.writeValue(0);
  // zCh.writeValue(0);

   // Set the local name and appearance of the BLE device
  BLE.addService(accel);
  BLE.setLocalName("Acclmeter");
  // BLE.setAppearance(0x01);
  BLE.setAdvertisedService(accel);
  BLE.advertise();

  // Initialize the accelerometer
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU");
    while (1);
  }
   
  Serial.println("Accelerometer BLE service initialized");
}



float x, y, z;

void loop() {

  // Read the accelerometer data
  BLE.poll();

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
    xCh.writeValue(x);
    Serial.print("x:");
    Serial.print(x);
    Serial.print("\t");

    yCh.writeValue(y);
    Serial.print("y:");
    Serial.print(y);
    Serial.print("\t");
    
    zCh.writeValue(z);
    Serial.print("z:");
    Serial.print(z);
    Serial.print("\n");
    
    delay(200);
  }
}
