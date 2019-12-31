//
// Roli ipod dock
// Copyright Andrej Rolih, November 2019
// See license file for licensing information
// 
// This is a source for the roli ipod dock.
// Dock has 5 buttons (play/pouse, skip forward/back, volume plus/minus)
// It uses arduino aap for ipod control: https://github.com/finsprings/arduinaap
// It uses Bounce2 for button debouncing: https://github.com/thomasfredericks/Bounce2
//
// ---------------------------------------------------------------------------------------------------------
//

#include <SimpleRemote.h>
#include <Bounce2.h>

// Button debouncing
#define NUM_BUTTONS 5
const uint8_t BUTTON_PINS[NUM_BUTTONS] = {5, 6, 7, 8, 9};
Bounce * buttons = new Bounce[NUM_BUTTONS];

// Ipod interface
SimpleRemote simpleRemote;


void setup()
{
  // Prepare button bounce
  for (int i = 0; i < NUM_BUTTONS; i++) {
    buttons[i].attach(BUTTON_PINS[i] , INPUT_PULLUP  ); //setup the bounce instance for the current button
    buttons[i].interval(25); // interval in ms
  }

  // Prepare ipod remote
  Serial.begin(iPodSerial::IPOD_SERIAL_RATE);
}

void sendIpodProd() {
  // prod the iPod in case it went to sleep since we last talked to it
  // (after which older iPods will stop responding to us otherwise)
  
  simpleRemote.sendiPodOn();
  delay(50);
  simpleRemote.sendButtonReleased();
}

void loop()
{
  simpleRemote.loop();

  bool updates[] = {false, false, false, false, false};
  for (int i = 0; i < NUM_BUTTONS; i++)  {
    // Update the Bounce instance :
    updates[i] = buttons[i].update();
  }

  if (updates[0]) {
    // Play/pause button change
    
    if (buttons[0].read() == LOW) {
      sendIpodProd();
      simpleRemote.sendPlay();
    } else {
      simpleRemote.sendButtonReleased();
    }
  }

  if (updates[1]) {
    // Back button change
    
    if (buttons[1].read() == LOW) {
      sendIpodProd();
      simpleRemote.sendSkipBackward();
    } else {
      simpleRemote.sendButtonReleased();
    }
  }

  if (updates[2]) {
    // Forward button change
    
    if (buttons[2].read() == LOW) {
      sendIpodProd();
      simpleRemote.sendSkipForward();
    } else {
      simpleRemote.sendButtonReleased();
    }
  }

  if (updates[3]) {
    // Vol minus button change
    
    if (buttons[3].read() == LOW) {
      sendIpodProd();
      simpleRemote.sendVolMinus();
    } else {
      simpleRemote.sendButtonReleased();
    }
  }

  if (updates[4]) {
    // Vol plus button change
    
    if (buttons[4].read() == LOW) {
      sendIpodProd();
      simpleRemote.sendVolPlus();
    } else {
      simpleRemote.sendButtonReleased();
    }
  }
  
}

