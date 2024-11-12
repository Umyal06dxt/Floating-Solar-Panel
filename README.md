# Floating-Solar-Panel
This project aims to create a floating solar panel with light tracking capabilities, utilizing Arduino and servo motors to adjust the panel orientation for optimal light capture. The system is designed for ocean deployment, with built-in sensors to detect environmental changes and protect the setup from marine hazards.

## Project Overview
The floating solar panel system is designed to maximize energy generation by adjusting the solar panel orientation based on light intensity detected by sensors. This system includes:
- **Dual Servo Motors** for independent adjustments to optimize light capture on both the upper and lower panels.
- **Light Sensors** to detect light intensity at different angles and determine optimal panel positioning.
- **Environmental Protection** features to detect weather changes and adapt the system accordingly.

### Key Features
- **Light Tracking**: Automatically adjusts the solar panel's position based on detected light levels for efficient energy capture.
- **Marine Protection**: With sensors detecting environmental factors, the panel can react to severe conditions like high waves or storms.
- **Modular Design**: Designed for adaptability, allowing for future enhancements such as Fresnel lenses for concentrated light, marine life-safe garbage collection beneath the panel, and protection against saltwater and tides.

## Components
- **Arduino Uno**: Microcontroller to manage sensor inputs and servo outputs.
- **Servo Motors** (`upperServo` and `lowerServo`): Used to adjust the panel position based on light sensor readings.
- **Light Sensors** (`A0`, `A1`, `A2`, `A3`): Detect light intensity from different angles, feeding data to the Arduino to determine optimal panel orientation.
- **Additional Sensors**: This setup is adaptable to integrate sensors for natural calamity detection, such as ultrasonic sensors for waves and temperature/humidity sensors for weather changes.

## Code Structure
The main code controls the servos based on sensor readings:
1. **Sensor Reading**: Reads values from four analog light sensors.
2. **Comparison Logic**: Compares sensor readings to determine the brighter direction.
3. **Servo Control**: Adjusts the servos to point the panel towards the optimal light direction.

### Code Snippet
```cpp
#include <Servo.h>

// Servo and position setup
Servo upperServo;
Servo lowerServo;
int errorMargin = 5;
int upperServoPos = 90;
int lowerServoPos = 90;

void setup() {
  Serial.begin(9600);
  upperServo.attach(9);
  lowerServo.attach(11);
  upperServo.write(upperServoPos);
  lowerServo.write(lowerServoPos);
  delay(200);
}

void loop() {
  int sensorReading0 = analogRead(A0);
  int sensorReading1 = analogRead(A1);
  int sensorReading2 = analogRead(A2);
  int sensorReading3 = analogRead(A3);

  int diff1 = abs(sensorReading0 - sensorReading1);
  int diff2 = abs(sensorReading2 - sensorReading3);

  // Adjust upper servo
  if (diff1 > errorMargin) {
    if (sensorReading0 > sensorReading1 && upperServoPos > 0) {
      upperServoPos--;
      upperServo.write(upperServoPos);
    } else if (sensorReading0 < sensorReading1 && upperServoPos < 180) {
      upperServoPos++;
      upperServo.write(upperServoPos);
    }
  }

  // Adjust lower servo
  if (diff2 > errorMargin) {
    if (sensorReading2 > sensorReading3 && lowerServoPos < 180) {
      lowerServoPos++;
      lowerServo.write(lowerServoPos);
    } else if (sensorReading2 < sensorReading3 && lowerServoPos > 0) {
      lowerServoPos--;
      lowerServo.write(lowerServoPos);
    }
  }

  delay(200);
}
```

## Usage Instructions
1. **Setup**: Attach the servos to the Arduino pins (9 and 11). Connect light sensors to analog pins `A0` through `A3`.
2. **Power On**: Power the Arduino and upload the code.
3. **Monitor and Adjust**: Observe the serial output to monitor sensor readings and servo positions. Adjust error margin or servo limits as needed.

## Future Enhancements
- **Calamity Detection**: Incorporate sensors to detect environmental changes like tides or potential storms.
- **Garbage Collection**: Attach a system below the solar panel to separate marine life from waste.
- **Light Concentration**: Add Fresnel lenses or mirrors for enhanced solar intensity.
- **Protection Mechanisms**: Design saltwater and tidal protection for the long-term durability of the system.

## Troubleshooting
- **Servo Not Moving**: Ensure the servo positions stay within the 0-180 degree range.
- **Erratic Servo Movement**: Check the sensor values and make sure they are within a valid range. Adjust `errorMargin` if minor fluctuations cause constant adjustments.

## License
This project is open-source and can be modified or distributed as needed.
