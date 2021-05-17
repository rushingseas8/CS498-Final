// Constants for pins
#define IR_PIN 15
#define LED_OUT 11

// Used for counting pulse numbers.
long countLow = 0;
long countHi = 0;
long epochs = 0;

void setup() {
  // put your setup code here, to run once:
  // Set baud rate + initialize pins
  Serial.begin(9600);
  Serial.println("Setup called");
  pinMode(IR_PIN, INPUT);
  digitalWrite(IR_PIN, LOW); // Pulldown the resistor to help with noise issues
  pinMode(LED_OUT, OUTPUT);
}

/**
 * This code reads in IR signal and reports any interesting pulses.
 * 
 * When this was run on the Nano Every, this gave me results that were closest to
 * correct from the IR remote.
 */
void readPulses() {
//  int initialValue = HIGH;
  long pulseLength = 0;
  cli(); // Turn off BG interrupts to improve timing
  // Wait up to 1 second before timing out. Repeat until we find something.
  while ((pulseLength = pulseIn(IR_PIN, HIGH, 1000000)) == 0) {
    Serial.print(".");
  }
  sei(); // Back on

  // Okay, didn't time out- that's interesting

  // We do not expect pulse lengths different from 0.6ms, 1.2ms, or 2.4ms.
  if (pulseLength > 3000) {
    //Serial.println("Pulse filtered (too long).");
    return;
  }

  Serial.println();
  Serial.print("ON pulse of ");
  Serial.print(pulseLength);
  Serial.print(" us.");

  // Read the LOW signal, too (gaps are important to validate IR signal)
  while ((pulseLength = pulseIn(IR_PIN, LOW, 65000)) == 0) {
    Serial.print(".");
  }
  
  Serial.println();
  Serial.print("OFF pulse of ");
  Serial.print(pulseLength);
  Serial.print(" us.");
}

/**
 * Debugging code. This was used to detect that the IR output signal was actually
 * oscillating. So quickly in fact, it looked like it was just on!
 */
void countPulses() {

  // Read input pin
  int val = digitalRead(IR_PIN);

  // Keep track of how long the pin was thsi fixed value
  unsigned long start = micros();
  while (digitalRead(IR_PIN) == val) {
    // Busy waiting
  }
  unsigned long endTime = micros();
  unsigned long delta = endTime - start;
  if (delta < 50000) {
    Serial.print("Time stuck on ");
    Serial.print(val);
    Serial.print(" is: ");
    Serial.println(delta);
  }

  // Count how long the value stayed
  if (val == HIGH) {
    countHi++;
  } else if (val == LOW) {
    countLow++;
  } else {
    Serial.println("Got weird value!");
  }
  
  // LED debug!
  digitalWrite(LED_BUILTIN, val);

  //  Serial.print(val);
  // Used to only print out chunks of 1,000 values at once
  // (instead of flooding the serial port)
  if ((countHi + countLow) % 1000 == 0) {
    char buffer[64 + 0];
    sprintf(buffer, "Epoch [%d] Counthi: %d low: %d", epochs, countHi, countLow);
    Serial.println(buffer);
    countHi = 0;
    countLow = 0;
    epochs++;
  }
}

/**
 * Debugging code. Turns the LED on when the IR pin gets a signal.
 */
void debugLED() {
  // Read IR pin. Since we expect it to be HIGH, invert the signal when
  // matching it to the LED.
  int val = digitalRead(IR_PIN);
  digitalWrite(LED_BUILTIN, !val);
}

void loop() {
  // put your main code here, to run repeatedly:
  debugLED();
}
