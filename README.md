# Audio-Frequency-Measurement-Test

A simple test sketch to see if a KY-037 Audio module can be used as a simple frequency meter.

The digital output from the audio module is connected to a pin on an Arduino Nano. An interrupt is used to update a counter. At a set time (250ms default) the number of pulses are counted, converted to Hz and displayed using the serial monitor.

A blog post with more information is available here https://garrysblog.com/2020/03/28/measuring-audio-frequency-with-an-arduino/
