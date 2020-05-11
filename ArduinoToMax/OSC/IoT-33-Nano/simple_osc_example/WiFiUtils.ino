//Setting up a WiFi connection - COMPLETE
void connectToWifi(const char ssidName[], const char pass[])
{
  Serial.println("Starting...");
  Serial.println("Connecting to WiFi.");

  int status;
  int attempts = 0;
  while ( status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssidName, pass);     // Connect to WPA/WPA2 network:
    delay(5000);
  }

  if (status == WL_CONNECTED)
  {
    Serial.println("OK!");
  }
  else if (status == WL_IDLE_STATUS)
  {
    Serial.println("Idle");
  }
  else
  {
    Serial.println("WiFi Connection Failed!");
  }

}
//------------------------------------------------------------
void printMac()
{
  WiFi.macAddress(mac);
  for (int i = 5; i >= 0; i--)
  {
    if (mac[i] < 16)
      Serial.print(0);

    Serial.print(mac[i], HEX);
    Serial.print((i == 0) ? "" : ":");
  }
}
//------------------------------------------------------------
void haltFirmware()
{
  Serial.println("\n\nSTOPPING THE PROGRAM!");
  while (true) {}
}
