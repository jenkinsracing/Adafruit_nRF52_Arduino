/*********************************************************************
 This is an example for our nRF52 based Bluefruit LE modules

 Pick one up today in the adafruit shop!

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/

#include <bluefruit.h>

void setup() 
{
  Serial.begin(115200);

  Serial.println("Bluefruit52 Central Scan Example");

  // up to 1 peripheral conn and 1 central conn
  Bluefruit.begin(true, true);
  Bluefruit.setName("Bluefruit52");

  // Increase BLink rate to different from PrPh advertising mode 
  Bluefruit.setConnLedInterval(250);

  // Callbacks for Central
  Bluefruit.central.setConnectCallback(connect_callback);
  Bluefruit.central.setDisconnectCallback(disconnect_callback);

  // Start Central Scan
  Bluefruit.central.setScanCallback(scan_callback);
  Bluefruit.central.startScanning();
}

void scan_callback(ble_gap_evt_adv_report_t* report)
{
  // Check if advertising contain BleUart service
  if ( Bluefruit.central.checkUuidInScan(report, BLEUART_UUID_SERVICE) )
  {
    Serial.println("BLE UART service detected");
    Serial.println("Attempt to connect ... ");

    // Connect to device with bleuart service in advertising
    // Use Min & Max Connection Interval default value
    Bluefruit.central.connect(report);
  }
}

void connect_callback(void)
{
  Serial.println("Connected");
}

void disconnect_callback(uint8_t reason)
{
  (void) reason;
  
  Serial.println("Disconnected");
  Serial.println("Bluefruit will auto start scanning (default)");
}

void loop() 
{
  // Toggle both LEDs every 1 second
  digitalToggle(LED_BUILTIN);

  delay(1000);
}
