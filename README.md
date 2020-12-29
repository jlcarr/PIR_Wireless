# PIR_Wireless
An Arduino/AVR based PIR sensor which transmits its readings wirelessly.

## Components List
   - PIR sensor (Passive InfraRed sensor) (HC-SR505)
   - ATTiny85 (microcontroller)
   - 433Mhz transmitter (FS1000A)
   - 433Mhz receiver (MX-RM-5V)

## Methodology/Build
### Arduino as ISP for ATTiny85
One easy and accessible way to program ATTiny85 microcontrollers is to use an Ardunio as ISP (In-System Programmer)


## Experiments
The 433MHz transmitters and receivers are notoriously cheap and unreliable. ATTiny85 microcontrollers are also incompatible with many Arduino libraries. For these reasons I will document difficulties, experiments and possible solutions
### 433MHz Transmitters and Recivers
- **Issue**: Wireless range is low
   - **Details**: Many sources say out-of-the-box the range is less than 1 meter.
   - **Solution**: Solder on an antena to the sender and receiver.
- **Issue**: Data Corruption And Noise
   - **Experiment**: Basic receiver noise
      - **Method**: Attaching a receiver connected directly to a output LED.
      - **Result**: The LED was mostly off but flickered on frequently and would sometimes stay on.
   - **Experiment**: On/Off switch state transmition
      - **Method**: Connect data-pin of the transmitter to a potentiometer. Receiver connected directly to an LED.
      - **Result**: The LED would change correctly with the switch was turned. However when left in a given state would flicker and sometime even switch to wrong state. Especially from off to on.
   - **Experiment**: Continuous On/Off signal
      - **Method**: Connect data-pin of the transmitter to Ardunio with Blink sketch. Receiver connected directly to an LED.
      - **Result**: The LED consistently blinked with the same 1Hz frequency as the Ardunio. However it seemed out of phase by 0.5s.
      - **Note**: The consistency here is promising.

