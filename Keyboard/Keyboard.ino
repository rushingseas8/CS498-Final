// Clears the send signal. If this isn't called, then the keyboard
// will continuously send the key.
void clear_print() {
  Keyboard.set_modifier(0);
  Keyboard.set_key1(0);
  Keyboard.send_now();
}

// Prints alt+tab (go to next window)
void print_alt_tab() {
  Keyboard.set_modifier(MODIFIERKEY_ALT);
  Keyboard.send_now();
  delay(500);
  
  Keyboard.set_key1(KEY_TAB);
  Keyboard.send_now();
  delay(500);
  
  clear_print();
}

// Prints alt+shift+tab (go back to previous window)
void print_alt_shift_tab() {
  // Alt
  Keyboard.set_modifier(MODIFIERKEY_ALT);
  Keyboard.send_now();
  delay(500);

  // Alt+shift
  Keyboard.set_modifier(MODIFIERKEY_SHIFT | MODIFIERKEY_ALT);
  Keyboard.send_now();
  delay(500);

  // Alt+shift+tab
  Keyboard.set_key1(KEY_TAB);
  Keyboard.send_now();
  delay(500);

  clear_print();
}

void print_ctrl_tab() {
  Keyboard.set_modifier(MODIFIERKEY_CTRL);
  Keyboard.send_now();
  delay(500);
  
  Keyboard.set_key1(KEY_TAB);
  Keyboard.send_now();
  delay(500);
  
  clear_print();
}

void print_ctrl_shift_tab() {
  Keyboard.set_modifier(MODIFIERKEY_SHIFT | MODIFIERKEY_CTRL);
  Keyboard.send_now();
  delay(500);
  
  Keyboard.set_key1(KEY_TAB);
  Keyboard.send_now();
  delay(500);
  
  clear_print();
}

void _pause() {
  Keyboard.press(KEY_MEDIA_PAUSE);
  Keyboard.release(KEY_MEDIA_PAUSE);
}

void _play() {
  Keyboard.press(KEY_MEDIA_PLAY);
  Keyboard.release(KEY_MEDIA_PLAY);
}

void volume_up() {
  Keyboard.press(KEY_MEDIA_VOLUME_INC);
  Keyboard.release(KEY_MEDIA_VOLUME_INC);
  delay(50);
}

void volume_down() {
  Keyboard.press(KEY_MEDIA_VOLUME_DEC);
  Keyboard.release(KEY_MEDIA_VOLUME_DEC);
  delay(50);
}

#define IR_PIN 15

void setup() {
  // put your setup code here, to run once:
  //Serial.println("Setup");
  Keyboard.println("Setup");

  delay(1000);

  // Setup IR pins. Unfortunately, the hardware is buggy, so
  // this part of the code could never be fully implemented.
  // Instead, this file is just a proof of concept for keyboard output.
  pinMode(IR_PIN, INPUT);
  digitalWrite(IR_PIN, LOW);
  
//  print_pause_play();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.print(".");
  
  delay(1000);
//  _pause();
//  _play();
//  print_ctrl_tab();
//  print_ctrl_shift_tab();
}
