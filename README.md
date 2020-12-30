# PIR_Wireless
An Arduino/AVR based PIR sensor which transmits its readings wirelessly.

## Components List
   - 1x PIR sensor (Passive InfraRed sensor) (part #: HC-SR505)
   - 1x AVR microcontroller (part #: ATTiny85)
   - 1x 433Mhz transmitter (part #: FS1000A)
   - 1x 433Mhz receiver (part #: MX-RM-5V)

## Methodology/Build
### Arduino as ISP for ATTiny85
One easy and accessible way to program ATTiny85 microcontrollers is to use an Ardunio as ISP (In-System Programmer).  
Instructions on how to set up an Arduino as ISP for an ATTiny85 are available from the following links:
- http://highlowtech.org/?p=1706
- http://highlowtech.org/?p=1695


## Experiments
The 433MHz transmitters and receivers are notoriously cheap and unreliable. ATTiny85 microcontrollers are also incompatible with many Arduino libraries. For these reasons I will document difficulties, experiments and possible solutions
### 433MHz Transmitters and Receivers
- **Issue**: Data Corruption And Noise
   - **Details**: Due to the cheapness of these modules there tends to be quite a bit on noise in the communication. Even with no signal the the receiver will flicker and turn on.
   - **Solution**: Keep the data transmitted simple and small. Based on the "Experiment #3" transmitting a persistent pattern than can then be modulated could help.
   - **Experiment #1**: Basic receiver noise
      - **Method**: Attaching a receiver connected directly to a output LED.
      - **Result**: The LED was mostly off but flickered on frequently and would sometimes stay on.
   - **Experiment #2**: On/Off switch state transmition
      - **Method**: Connect data-pin of the transmitter to a potentiometer. Receiver connected directly to an LED.
      - **Result**: The LED would change correctly with the switch was turned. However when left in a given state would flicker and sometime even switch to wrong state. Especially from off to on.
   - **Experiment #3**: Continuous On/Off signal
      - **Method**: Connect data-pin of the transmitter to Ardunio with Blink sketch. Receiver connected directly to an LED.
      - **Result**: The LED consistently blinked with the same 1Hz frequency as the Ardunio. However it seemed out of phase by 0.5s.
      - **Note**: The consistency here is promising.
   - **Research**: Causes of noise in cheap 433MHz receivers
      - **Finding**: It seems that the receiver will lower its on-state threshold until consistent data is received. This can lead to the threshold being brought down to catch background noise.
      - **Source**: https://electronics.stackexchange.com/questions/310926/noise-presence-at-a-433mhz-receiver
   - **Experiment #5**: Sending Data Via Frequency Change
      - **Method**: Program the ATTiny85 to blink at 10Hz if reading is HIGH, 5Hz if reading is low. Connect ATTiny85 blink pin to an LED and transmitter. Connect receiver to Ardunio. Have Arduino Serial.out "ON" if it receives a blink signal that is on for 0.05s, "OFF" for 0.1s, and "UNKNOWN" otherwise. Also print the blink length.
      - **Result**: The signal seems to be caught very reliably. There wasn't a single "UNKNOWN", and switching was right on target.
      - **Other Finding**: The 'delayMicroseconds' function does not seem to work on ATTiny85. Using it seems to make the chip behave strangely.
      - **Note**: This is the best reliability yet. There is probably method to make the period reading more robust.
   - **Experiment #7**: Decoupling Transmitter and receiver circuits
      - **Method**: Decoupled set-up from "Experiment #6". Used an opto-coupler (LTV4N35) to test de-coupled data transmission. Then switched to 433MHz set.
      - **Result**: Opto-coupler worked as expected. Switching to the 433MHz receiver with an idicator LED seemed to work.
      - **Note**: This is experiment was was originally performed because of the failure of "Experiment #6", and then re-doing "Experiment #5" with the actual 433MHz transmitter removed resulted in teh receiver still receiving the correct signal! This implies electrical noise, rather than transmission was responsible for the receiver's data output. 
      - **Note**: See "Experiment #8" for range test.
      - **Source**: https://www.instructables.com/4N35/
- **Issue**: Wireless Range Is Low
   - **Details**: Many sources say out-of-the-box the range is less than 1 meter.
- **Issue**: Wireless Range Is Low
   - **Details**: Many sources say out-of-the-box the range is less than 1 meter.
   - **Solution**: Solder on an antena to the sender and receiver.
   - **Experiment #4**: Basic Range
      - **Method**: Use the set-up of the "Experiment #3". But put the receiver on a different breadboard, powed using 3 1.5V AA batteries. Walk away with receiver checking fidelity of data transfer.
      - **Result**: Fidelity seems to drop past 1 meter. Past 3 meters and around corner seems to only receive noise.
   - **Experiment #6**: 10Hz Signal Range
      - **Method**: Use the set-up of the "Experiment #5". But put the transmitter on a different breadboard, powed using 3 1.5V AA batteries. Walk away with receiver checking fidelity of data transfer.
      - **Result**: Receiver does not seem to pick up its signal at all. Attaching the transmitter's breadboard to the Ardunio's 5V and GND lines (instead of the AA batteries) makes it able to transmit again. Transmitter LED was noticeably dimmer. Voltmeter said batteries were supplying 4.74V while the Arduino was supplying 5.02V.
   - **Experiment #8**: Decoupled Range Test
      - **Method**: Same as the wireless "Experiment #7".
      - **Result**: Range seems to be about 30cm. This implies the longer results of "Experiment #4" are probably just noise (the exact 5V transmitter vs 4.75V transmitter is unlikely to make up much of the difference). 

## Resources
### Circuit Design
- https://en.wikipedia.org/wiki/Comparison_of_EDA_software
### ATTiny85
- http://highlowtech.org/?p=1706
- http://highlowtech.org/?p=1695
### 433MHz Radio Communication
- https://lastminuteengineers.com/433mhz-rf-wireless-arduino-tutorial/
### ATTiny85 AND 433MHz RF Modules
- https://www.electronoobs.com/eng_arduino_tut45.php
- https://aherrero.github.io/arduino/rf/2019/11/17/Radio-attiny.html
