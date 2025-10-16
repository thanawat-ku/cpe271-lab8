#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <HTTPClient.h>
#include <Arduino_JSON.h>

HTTPClient http;

void setup()
{
    WiFi.mode(WIFI_STA);
    Serial.begin(115200);
    WiFiManager wm;

    bool res;
    res = wm.autoConnect("AutoConnectAP", "password");
    if (!res)
    {
        Serial.println("Failed to connect");
        // ESP.restart();
    }
    else
    {
        // if you get here you have connected to the WiFi
        Serial.println("connected...yeey :)");
    }
    printMenu();
}
void printMenu()
{
    Serial.println("Method");
    Serial.println("1. GET");
    Serial.println("2. POST");
    Serial.println("3. PUT");
    Serial.println("4. DELETE");
    Serial.println("Select Method:");
}

String httpGetRequest()
{
    String payload = "{}";
    http.begin("http://your-server-ip/api/resource/123");
    int httpResponseCode = http.GET();
    payload = http.getString();
    // Free resources
    http.end();
    return payload;
}

String httpPostRequest(String postData)
{
    String payload = "{}";
        http.begin("http://your-server-ip/api/resource");
        http.addHeader("Content-Type", "application/json");
        int httpResponseCode = http.POST(postData);
        payload = http.getString();
    // Free resources
    http.end();
    return payload;
}

String httpPutRequest(String putData)
{
    String payload = "{}";
    http.begin("http://your-server-ip/api/resource/123"); // Specify resource URL
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.PUT(putData); // Send PUT request
    payload = http.getString();
    // Free resources
    http.end();
    return payload;
}

String httpDeleteRequest()
{
    String payload = "{}";
    http.begin("http://your-server-ip/api/resource/123"); // Specify resource URL
    int httpResponseCode = http.sendRequest("DELETE");    // Send DELETE request
    payload = http.getString();
    // Free resources
    http.end();
    return payload;
}

void loop()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        if (Serial.available())
        {
            char choice = Serial.read();
            switch (choice)
            {
            case '1':
                String returnString = httpGetRequest();
                Serial.print("Get Return:");
                Serial.println(returnString);
                break;
            case '2':
                String returnString = httpPostRequest("{\"id\"=\"123\",\"name\"=\"fookies\",\"email\"=\"fookies@hotmail.com\"}");
                Serial.print("Post Return:");
                Serial.println(returnString);
                break;
            case '3':
                String returnString = httpPutRequest("{\"name\"=\"thanawat\",\"email\"=\"thanawat@ku.th\"}");
                Serial.print("Put Return:");
                Serial.println(returnString);
                break;
            case '4':
                String returnString = httpDeleteRequest();
                Serial.print("Delete Return:");
                Serial.println(returnString);
                break;
            }
        }
    }
    else
    {
        Serial.println("Reconnecting to WiFi...");
        WiFi.disconnect();
        WiFi.reconnect();
    }
}
