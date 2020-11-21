void senddatatoIFTTT(String temp,String humi) {

// Use WiFiClient class to create TCP connections
WiFiClient client;
const int httpPort = 80;
if (!client.connect(host, httpPort)) {
Serial.println("connection failed");
return;
}

// We now create a URI for the request
String url = "/trigger/";
url += event;
url += "/with/key/";
url += privateKey;

value1 = temp;
value2 = humi;
value3 = "999";

genJSonObject();

Serial.print("Requesting URL: ");
Serial.println(url);
Serial.println(postData);

// This will send the request to the server
client.print(String("GET ") + url + " HTTP/1.1\r\n" +
"Host: " + host + "\r\n");

client.println("Content-Type: application/json");
client.print("Content-Length: ");
client.println(postData.length());
client.println();
client.println(postData);
client.println("Connection: close\r\n\r\n");


// Read all the lines of the reply from server and print them to Serial,
// the connection will close when the server has sent all the data.
while (client.connected())
{
if (client.available())
{
String line = client.readStringUntil('\r');
Serial.print(line);
} else {
// No data yet, wait a bit
delay(50);
};
}

// All done
Serial.println();
Serial.println("closing connection");

client.stop();
}
