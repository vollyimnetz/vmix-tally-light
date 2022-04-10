# Installation

## Prepare the Wemos D1 Mini
* Checkout/Download from git repository.
* copy `src/settings.example.h` and store as `src/settings.h`. Make adjustments in the file to match your board configuration.
* copy `private_config.ini.example` and store as `private_config.ini`. Make adjustments in the file to match your build configuration.
* Use Platform.io to compile the project.
* Upload the webconfig to flash-memory (see below) to wemos d1 mini
* Upload the compiled project to wemos d1 mini

## Setup the Wifi-Connection
The board will create an public access point named `EspAutoWifi` for setup the correct WIFI-Settings. If the blue LED on the bottom of the board is blinking in short durations you need to setup new WIFI settings

* Connect to `EspAutoWifi`
* Navigate to `http://192.168.4.1/` in your Browser.
* Store the settings of your WIFI.

The system will reconnect to the specified WLAN. The board should now be connected. 

## Setup the VMix Settings on the board
Visit your router settings to get the IP of the board in your local network. If the board is still connected to platformio you may also read the IP from the serial monitor (something like `STA IP Address: ...`).
* Navigate to the IP-address of your board in the Browser. You should see a page with the headline "TallyConfig".
* Insert the ota-password in the field to be able to read/write the settings.


# Upload of Tally Light config-webpage to flash-memory

- Click the PIO icon at the left side bar. The project tasks should open.
- Expand the `d1_mini > Platform`
- Select `Build Filesystem Image`.
- Finally, click `Upload Filesystem Image`.

https://randomnerdtutorials.com/esp8266-nodemcu-vs-code-platformio-littlefs/


# vmix fake tally - php server
You can use http://vmix-fake-tally.totalmedial.de to test your board.

Use the following settings in on the config-page (see "Setup the VMix Settings on the board").
* Insert the Password defined in settings.h
* Settings
    * Mode: 1
    * VMix Host-Adresse: http://vmix-fake-tally.totalmedial.de
    * Key der Kamera/des Kanals: bf3928a3-cc06-4f79-b0b2-47639d9a405f
* click on "RESTART System"

ATTENTION: If you think about hosting the vmix-fake-tally yourself, do it on a proper server. The `php -S 0.0.0.0:80` command may serve the code BUT it will not send the proper end code after an http-response. So the board will not behave properly.