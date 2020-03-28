// ===========================================================================================
//                     AUDIO FREQUENCY TEST USING MICROPHONE MODULE
// ===========================================================================================

/*
 * A simple test sketch to see if a KY-037 Audio module can be used as a simple frequency meter.
 * The digital output from the audio module is connected to a pin on an Arduino Nano. An interrupt
 * is used to update a counter. At a set time the number of pulses are counted, converted to Hz
 * and displayed on the serial monitor
 * 
 * Useful online tone generator for testing http://onlinetonegenerator.com/
 */

// Connections:
//  Output DO from Audio module to Nano to 2
//  Audio module power to 0 and +5v

const byte INPUT_PIN = 2;                     // Input pin from the audio module (D2 on Nano)
int updateInterval = 250;                     // Number of milliseconds between each update of the display
int millisSinceUpdate = 0;                    // Time for the last update
unsigned long pulseCount = 0;                 // The number of pulses detected since last display update
unsigned long lastUpdateTime = 0;             // The time of the last display update
unsigned long freq = 0;                       // Frequency

// ===========================================================================================
//                                            SETUP
// ===========================================================================================

void setup() {

  // Open serial port and set data rate to 9600 bps
  Serial.begin(9600);                         

  // Setup pin for the audio module input
  pinMode(INPUT_PIN, INPUT);                  

  // Attach an interrupt when input falls
  attachInterrupt(digitalPinToInterrupt(INPUT_PIN), audio_ISR, FALLING);

  // Print something in the monitor to show it's ready to go
  Serial.println("Frequency test");

  // Set to now to start. Not really necessary
  lastUpdateTime = millis();                               
  
}

// ===========================================================================================
//                                          MAIN LOOP
// ===========================================================================================

void loop() {
  // Only update the display after a while and then calculate speed on number of counts since last update

  if (millis() - lastUpdateTime > updateInterval) {
    // It's time to calculate the frequency and update the display

    // Calculate the time that has past since last time
    millisSinceUpdate = millis() - lastUpdateTime;  

    // Calculate frequency
    freq = (pulseCount * 1000) / millisSinceUpdate;
    
    // Send the frequency to the serial monitor, but onliy if not zero
    if (freq != 0) {
      Serial.print(freq);
      Serial.println(" Hz");
    }

    // Reset variables
    pulseCount = 0;                 // Reset the pulse counter
    lastUpdateTime = millis();      // Set the last updated time to now
  }
}

// ===========================================================================================
//                                         INTERRUPT
// ===========================================================================================

void audio_ISR() {
  // Interrupt routine triggers when when input falls
  
  // Just add one to the number of pulses counted
  pulseCount++;
  
}
