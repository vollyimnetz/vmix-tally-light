# Installation

## Prepare the Wemos D1 Mini
* Checkout/Download from git repository.
* copy `src/settings.example.h` and store as `src/settings.h`
* Use Platform.io to compile the project.
* Upload the webconfig to flash-memory (see below) to wemos d1 mini
* Upload the compiled project to wemos d1 mini

## Setup the Wifi-Connection
The board will create an public access point named `EspAutoWifi` for setup the correct WIFI-Settings. If the blue LED on the bottom of the board is blinking in short durations you need to setup new WIFI settings

* Connect to `EspAutoWifi`
* Navigate to `http://192.168.4.1/` in your Browser.
* Store the settings of your WIFI.

The system will reconnect to the specified WLAN. The board should now be connected. 

## Setup the VMix Settings
Visit your router settings to get the IP of the board in your local network. If the board is still connected to platformio you may also read the IP from the serial monitor (something like `STA IP Address: ...`).
* Navigate to the board in your Browser. You should see a page with the headline "TallyConfig".
* The board will restart every 


##

# Upload of Tally Light config-webpage to flash-memory

- Click the PIO icon at the left side bar. The project tasks should open.
- Expand the `d1_mini > Platform`
- Select `Build Filesystem Image`.
- Finally, click `Upload Filesystem Image`.

https://randomnerdtutorials.com/esp8266-nodemcu-vs-code-platformio-littlefs/