# Clap-Sequence-Sensor
This is a clap sequence sensitive home automation prototype that switches a lamp on and off. The C++ code on an Arduino Nano triggers when two loud bursts are heard with a short delay between them. It also takes a running average of the ambient noise to dynamically adjust how loud a clap "should" be.

You can see the project in action [here](https://drive.google.com/file/d/1aQnVMMlvzVrTAkEzOU4e5Kmv4VtDMiW6/view?usp=sharing) and [here](https://drive.google.com/file/d/1mcpacmlS0m4yFFPM0VmUJa7d9wNWRGuU/view?usp=sharing)!

The project's priorities are:
* Control any mains voltage appliance only by clapping
* Only register two claps with a specified short delay and some tolerance
* Adjust for ambient noise to not give false positives
* Allow added manual control with a button

The project does not:
* Differentiate between claps and loud noises with the specific delay
* Have output states other than ON/OFF
* Be connected to any web services

This was built just as a proof of concept and is the first completely assembled prototype.
Further improvements may include:
* Adding Wi-Fi and Bluetooth capabilities for further non-contact control
* Multiple relays to control many different appliances with more coded signals

