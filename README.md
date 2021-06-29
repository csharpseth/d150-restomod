
# Dodge D150 Resto Mod
This is the repo for all of the digital resources used in the resto-mod of my 1984 Dodge D150.


## Light Controller ::
This is the Arduino Nano that controls all of the external lights on the truck.

### Light Controller Resources

 - [Arduino Nano](https://www.amazon.com/REXQualis-Board-ATmega328P-Compatible-Arduino/dp/B07WK4VG58/ref=sr_1_3?dchild=1&keywords=arduino+nano&qid=1624931847&sr=8-3)
 - [Momentary Hinge Switches](https://www.amazon.com/gp/product/B00MFRMFS6/ref=ppx_yo_dt_b_asin_title_o03_s01?ie=UTF8&psc=1)
 - [Momentary Push Buttons](https://www.amazon.com/gp/product/B07F9JBR7N/ref=ppx_yo_dt_b_asin_title_o01_s01?ie=UTF8&psc=1)
 - [4 Channel Relay](https://www.amazon.com/gp/product/B08GC83G1G/ref=ppx_yo_dt_b_asin_title_o03_s00?ie=UTF8&psc=1)
 - [2 Channel Relays](https://www.amazon.com/gp/product/B072BY3KJF/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1)
 - [DC to DC Buck Converter](https://www.amazon.com/gp/product/B06XZ1DKF2/ref=ppx_yo_dt_b_asin_title_o05_s00?ie=UTF8&psc=1)

### Light Controller Setup
- First Upload the supplied 'd150_lightcontroller' code to your Arduino Nano

- Next, using your Buck Converter set to 5V DC, wire `OUT(-)` to `GND` then wire `OUT(+)` to `VIN` on the Arduino.

- Then wire the Arduino Inputs as follows:
  - D2 = Left Signal Switch
  - D3  = Right Signal Switch
  - D4  = Brake Switch
  - D5  = Headlight Switch
  - D6  = Kill Lights Switch

- Now wire the Arduino Outputs as follows:
  - D7  = Left Front Signal Lights Relay
  - D8  = Right Front Signal Lights Relay
  - D9  = Left Rear Signal Lights Relay
  - D10 = Right Rear Signal Lights Relay
  - D11 = Low Beam Lights Relay
  - D12 = High Beam Lights Relay

- Finally Supply power to the relays and connect the out put wires to the appropriate relay to the apropriate lights.