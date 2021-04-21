const char* host = "8266.monitoring-esp.ml";
const char* key = "712";
void sendtoweb(double Current, double Wh){
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) { //works!
      Serial.println("connection failed");
      return;
    }
    String url = "/add.php";
    url += "?I=";
    url += Current;
    url += "&Wh=";
    url += Wh;
    url += "&key=";
    url += key;
    Serial.print("Requesting URL: ");
    Serial.println(url);
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");

    Serial.println();
    Serial.println("closing connection");
}
