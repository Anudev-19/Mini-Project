# 🅿️ Wireless Charging Smart Parking Management System

> **Mini Project 2025 --- Electronics and Communication Engineering**\
> **College of Engineering Thalassery \| APJ Abdul Kalam Technological
> University**

## 📌 Overview

An Arduino-based **automated smart parking system** that manages vehicle
entry, monitors parking slot occupancy in real time, and activates
wireless charging automatically when an EV parks in a designated spot.
The system requires zero manual intervention --- from gate control to
charging activation.

## ✨ Features

-   🚗 **Automated Gate Control** --- servo-driven gate opens only when
    slots are available
-   📡 **Real-Time Slot Monitoring** --- ultrasonic sensors track each
    parking space
-   🔋 **Wireless Charging Activation** --- relay auto-triggers wireless
    coil when EV is detected
-   🖥️ **Live LCD Display** --- 16×2 I2C LCD shows available slot count
    in real time
-   🚫 **Full Lot Handling** --- displays `"No Spots Available"` and
    blocks gate when full
-   ⚡ **Energy Efficient** --- charging activates only when vehicle is
    present

## 🛠️ Hardware Components

  -----------------------------------------------------------------------
  Component               Model/Spec              Function
  ----------------------- ----------------------- -----------------------
  Microcontroller         Arduino UNO             Central controller
                          (ATmega328P)            

  Ultrasonic Sensors      HC-SR04 × 2             Detect vehicle in each
                                                  parking slot

  IR Sensor               Generic IR module       Detects vehicle
                                                  approaching entrance

  Servo Motor             SG90                    Drives entrance gate
                                                  open/close

  Relay Module            2-channel, 5V           Activates wireless
                                                  charging coil

  LCD Display             16×2 I2C (PCF8574)      Shows available parking
                                                  count

  Wireless Coil           Tx/Rx coil pair         Wireless power transfer
                                                  to parked EV

  Power Supply            9V battery              Powers Arduino and
                                                  peripherals
  -----------------------------------------------------------------------

## ⚙️ How It Works

``` text
Vehicle approaches entrance
        ↓
IR Sensor detects presence
        ↓
Arduino checks ultrasonic sensors → slots available?
        │
        ├── YES → Servo opens gate → Vehicle enters
        │          ↓
        │       Ultrasonic confirms parking → Relay ON → Wireless charging starts
        │          ↓
        │       LCD updates: "Slots: X available"
        │
        └── NO → Gate stays closed
                   ↓
                 LCD shows: "No Spots Available"

Vehicle exits:
Ultrasonic detects empty space → Relay OFF (charging stops) → LCD updates
```

## 🔌 Circuit Overview

-   **Arduino UNO** --- central controller (ATmega328P, 16MHz, 5V logic)
-   **Ultrasonic sensors** --- TRIG pin pulses out, ECHO pin measures
    return time → distance calculated
-   **IR sensor** --- digital output to Arduino interrupt pin; triggers
    entry check
-   **Servo** --- PWM signal from Arduino pin 9; 0° = closed gate, 90° =
    open gate
-   **Relay** --- Arduino digital pin → relay IN → switches wireless Tx
    coil circuit
-   **LCD (I2C)** --- SDA → A4, SCL → A5; only 2 wires needed due to I2C
    protocol

## 💻 Software

**Language:** C++ (Arduino IDE)

### Libraries Used

-   `Servo.h` --- servo motor control
-   `LiquidCrystal_I2C.h` --- I2C LCD communication
-   `NewPing.h` *(optional)* --- cleaner ultrasonic sensor reading

### Core Logic

``` cpp
if (IR_sensor detects vehicle) {
    slots = checkUltrasonicSensors();

    if (slots > 0) {
        openGate();              // servo to 90°
        delay(3000);
        closeGate();             // servo to 0°
        activateCharging();      // relay HIGH
        updateLCD(slots - 1);
    } else {
        LCD.print("No Spots Available");
    }
}
```

## 📁 Project Structure

``` text
parking-management/
├── src/
│   └── parking_system.ino       # Main Arduino sketch
├── docs/
│   └── report.docx              # Full project report
├── images/
│   ├── circuit_diagram.jpg
│   ├── block_diagram.jpg
│   ├── flowchart.jpg
│   └── prototype.jpg
├── components.md
└── README.md
```

## 📊 Key Specs

  Parameter                 Value
  ------------------------- -------------------------------------
  Microcontroller           ATmega328P @ 16MHz
  Parking slots monitored   2 (expandable)
  Ultrasonic range          2cm -- 400cm (HC-SR04)
  IR detection range        2cm -- 30cm
  Servo rotation            0° -- 90° for gate
  LCD                       16×2 characters, I2C
  Operating voltage         5V logic / 9V supply
  Wireless charging         Inductive (Qi-compatible coil pair)

## 🚀 Future Scope

-   Add IoT (ESP8266/ESP32) for remote monitoring via mobile app
-   RFID-based vehicle authentication before gate opens
-   Cloud dashboard for parking analytics
-   Multiple floor/zone support with centralised management
-   Payment gateway integration for paid parking
-   AI-based license plate recognition

## 👥 Team

  Name           Roll No
  -------------- ------------
  Abhishek K     TLY22EC007
  Anandhu VK     TLY22EC029
  Ajal Raj P P   TLY22EC020
  Anudev S S     TLY22EC031

**Guide:** Ms. Anagha A, Assistant Professor, Dept. of ECE, College of
Engineering Thalassery

## 📄 License

This project was developed for academic purposes under APJ Abdul Kalam
Technological University.
