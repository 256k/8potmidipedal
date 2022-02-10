// Pro micro midi controller 8 x pots.
// By fayek Helmi( aka 256k )
// www.256klabs.com
//=====================================

#include <MIDIUSB.h>

#define NPOTS 8

// set hardware pin definitions
int POT[] = {A0, A1, A2, A3, A6, A7, A8, A9};

// set each POT's CC number
int POT_CC[] = {0,1,2,3,4,5,6,7};

// set each POT's MIDI channel
int MIDI_CH[] = {0,1,2,3,4,5,6,7};


// pot value reference store
int PotPrevValues[] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  Serial.begin(115200);
}

void loop() {
  for (int i = 0; i < NPOTS; i++) {
    int potVal = analogRead(POT[i]) / 8;
    if (potVal != PotPrevValues[i]) {
      PotPrevValues[i] = potVal;
      controlChange(MIDI_CH[i], POT_CC[i], potVal);
      MidiUSB.flush();
    }
  }
}

// stock function definitions:
void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}
