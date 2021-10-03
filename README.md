# EVERTY

We are creating plant life support system to improve crew's health and productivity during the Mars trip. Our system is
a transformable external module, during the flight it can be extended. During the returning from Mars crew will use
100% of the system power, but on the way to the Mars they will need only 30%. Our module allows to avoid taking
additional space, it will take only as much as required for the current period. This makes our system comfortable and
effective in use.

Watering plants as well as using a lot of substrate is known to be problematic in space conditions. We suggest to use
improved Hydroponic Drip System to deliver water specifically to each plant's root. This will be achieved by using Soft
Tube robots that will deliver solution of minerals directly to the root. Otherwise, there is a risk that plants will
not receive required water and substances.

Referring to the previous experience of NASA, to grow plants inside a starship we also need sensors. We will control
humidity, temperature, CO2, O2, pressure, ethylene. In addition to that, air circulation system will be used
https://ttu-ir.tdl.org/bitstream/handle/2346/67664/ICES_2016_320.pdf?sequence=1.

As a source of light we are using LED strips, that are built into the roof of the module. Plants need full spectre of
colours but the most effective is 450 nm and 640 nm waves, according to NASA
https://ttu-ir.tdl.org/bitstream/handle/2346/67664/ICES_2016_320.pdf?sequence=1.

Internal surfaces will be created using polymers, so it will be easy to clean them.

Water circulation will be closed. Extra humidity will be collected from air and used to water plants.

LED strips will raise temperature inside the module, so if necessary, cooling system will be activated.

Gases will also be controlled. This will solve problem that plants have different gas exchange rate during their life


# How to use

Space greenhouse project

The device is designed for growing plants in space. The
module can either be attached to the ISS or be used
separately on other planets or satellites, such as the Moon.
A special camera, with the help of a software and hardware
complex, maintains the microclimate and lighting at a
satisfactory level for plant growth.

How to run a project:
1. You need to install Arduino IDE and unpack
   the libraries into the "libraries" folder.
2. Open the file "EVERTY" in Arduino IDE.
3. Select a board in the board manager in the
   context menu at the top of the window
4. Press the "Load" button in the context
   menu at the top of the window.

Connect the sensors to the microcontroller pins:
DHT11/DHT22 - D2
FAN MOSFET  - D8
LED MOSFET  - D9
HUMIDIFIER  - D7
