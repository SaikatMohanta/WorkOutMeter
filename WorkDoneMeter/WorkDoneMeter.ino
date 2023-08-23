#include <MPU6050SI.h>
#include <VectorAlgebra.h>

#define UPPER_THRESHOLD 0.65
#define ERROR 0.71

MPU6050SI mpu;
VectorAlgebra vectorAlgebra;

float accelX, accelY, accel;
float prevAccelX, prevAccelY;
float timeElapsed = 0.0;
float displacement = 0.0;
float workDone = 0.0;
float mass = 1.0;  // Mass of the object (in kg)

void setup() {
  Serial.begin(9600);

  if (!mpu.begin()) {
    Serial.println("Failed to initialize MPU6050");
    while (1)
      ;
  }
}

void loop() {

  mpu.update();
  accelX = mpu.getAccelerationX();
  //accelX = accelX - 0.5;
  accelY = mpu.getAccelerationY();
  //accelY = accelY - 0.5;
 
  accel = vectorAlgebra.magnitude(accelX, accelY, 0.0);
  accel = abs(accel - ERROR);
  Serial.print("Magnitude of acceleration: ");
  Serial.print(accel);
  Serial.print(" m/s^2\t");
  
  timeElapsed += 20;  // Assuming a constant time interval of 10 milli seconds
  if (abs(accel) >= UPPER_THRESHOLD) {

    displacement = 0.5 * accel * (timeElapsed / 1000) * (timeElapsed / 1000);

    // Calculate work done per unit mass
    workDone = displacement * (mass * accel);

  } else {
    timeElapsed = 0.0;
    accel = 0.0;
    displacement = 0.0;
    workDone = 0.0;
  }
  
  // Print results
  Serial.print("Time Elapsed: ");
  Serial.print(timeElapsed/1000, 3);
  Serial.print(" s\t");

  Serial.print("Displacement: ");
  Serial.print(displacement,4);
  Serial.print(" m \t");

  Serial.print("Work Done per Unit Mass: ");
  Serial.print(abs(workDone));
  Serial.println(" J/kg");
  // Adjust the delay as needed to control the sampling rate
  delay(20);
}
/*
  Serial.print("Acceleration X: ");
  Serial.print(accX, 3);
  Serial.print(" m/s², Y: ");
  Serial.print(accY, 3);
  Serial.print(" m/s²");
  Serial.print(" m/s², Z: ");
  Serial.print(accZ, 3);
  Serial.println(" m/s²");
  Serial.println("");

  delay(100);*/
//}
