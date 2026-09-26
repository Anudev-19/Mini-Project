#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// =====================================================
//              SMART PARKING SYSTEM
// =====================================================
// Hardware:
// Arduino Uno
// 1 x IR Sensor - Entrance
// 2 x Ultrasonic Sensors - Parking Spaces
// 1 x Servo Motor - Entrance Gate
// 1 x 16x2 I2C LCD
//
// Parking capacity: 2 vehicles
// =====================================================


// ---------------- LCD ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);


// ---------------- Servo ----------------
Servo gateServo;


// ---------------- Pin Definitions ----------------

// IR sensor at entrance
const int irSensorPin = 2;

// Ultrasonic sensor - Parking Space 1
const int trigPin1 = 3;
const int echoPin1 = 4;

// Ultrasonic sensor - Parking Space 2
const int trigPin2 = 5;
const int echoPin2 = 6;

// Servo motor for entrance gate
const int servoPin = 13;


// ---------------- Parking Settings ----------------

const int totalSpots = 2;

// Distance below which a parking space
// is considered occupied
const int distanceThreshold = 15;   // cm


// ---------------- Servo Positions ----------------

// Change these two values if your physical
// gate is mounted in the opposite direction.
const int gateOpenPosition = 0;
const int gateClosedPosition = 90;


// ---------------- IR Sensor ----------------

// Change HIGH to LOW if your IR sensor
// outputs LOW when a vehicle is detected.
const int IR_DETECTED = HIGH;


// ---------------- Variables ----------------

int availableSpots = totalSpots;


// =====================================================
//                         SETUP
// =====================================================

void setup()
{
  Serial.begin(9600);

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  // IR sensor
  pinMode(irSensorPin, INPUT);

  // Ultrasonic sensor 1
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  // Ultrasonic sensor 2
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // Servo
  gateServo.attach(servoPin);

  // Start with gate closed
  closeGate();

  // Display initial parking status
  updateParkingStatus();

  delay(1000);
}


// =====================================================
//                       MAIN LOOP
// =====================================================

void loop()
{
  // Check parking spaces
  bool spot1Occupied = isSpotOccupied(trigPin1, echoPin1);
  bool spot2Occupied = isSpotOccupied(trigPin2, echoPin2);


  // Calculate available parking spaces
  availableSpots = totalSpots;

  if (spot1Occupied)
  {
    availableSpots--;
  }

  if (spot2Occupied)
  {
    availableSpots--;
  }


  // Update LCD
  updateParkingStatus();


  // ---------------------------------------------------
  // CHECK FOR VEHICLE AT ENTRANCE
  // ---------------------------------------------------

  if (digitalRead(irSensorPin) == IR_DETECTED)
  {
    Serial.println("Vehicle detected at entrance.");


    // -------------------------------------------------
    // PARKING SPACE AVAILABLE
    // -------------------------------------------------

    if (availableSpots > 0)
    {
      Serial.println("Parking space available.");
      Serial.println("Opening gate.");

      openGate();


      // Wait for the vehicle to pass
      // through the
