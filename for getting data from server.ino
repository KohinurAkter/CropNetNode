

  HTTPClient http;

  Serial.print("[HTTP] begin...\n");

  http.begin("http://amlan.pythonanywhere.com/project47/default/send_sensor_data.json");// configure traged server and url

  Serial.print("[HTTP] POST...\n");// start connection and send HTTP header
  int httpCode = http.GET(); //For Receiving data from web
  String payload = http.getString(); //string type data is being receiving from web
// payload is a variable
  serial.println(payload);