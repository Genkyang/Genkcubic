#include "network.h"

char weather_info[12] = "";
int codeday = 0,temper = 99;
const char* host = "api.seniverse.com";
const char* host2 = "api.seniverse.com";

void Network::init(String ssid, String password)
{
  Serial.println("scan start");
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
  {
    Serial.println("no networks found");
  }
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");
  Serial.print("Connecting: ");
  Serial.print(ssid.c_str());
  Serial.print(" @");
  Serial.println(password.c_str());

  WiFi.begin(ssid.c_str(), password.c_str());
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

 int Network::getWeather(void)
{
  
 Serial.print("connecting to XinZhi");
  Serial.println(host);
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return 0;
  }
  // We now create a URI for the request
  String url = "/v3/weather/now.json?key=StWBQx3j5-mjmGrPU&location=WWSKUMUVE3TR&language=en&unit=c";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(100);
  // Read all the lines of the reply from server and print them to Serial
  String weather_data;
  while (client.available()) {
    String line = client.readStringUntil('\r');
    weather_data += line;
  }
 
  client.stop();
  Serial.println();
  Serial.println("closing connection");
 
  // Process weather_json
  Serial.println();
  //Serial.println("weather_data: ");
  // Serial.println(weather_data);
 
  // Convert to JSON
  String json_weather_data;
  int jsonIndex;
 
  for (int i = 0; i < weather_data.length(); i++) {
    if (weather_data[i] == '{') {
      jsonIndex = i;
      break;
    }
  }
 
  // Get JSON data
  json_weather_data = weather_data.substring(jsonIndex);
  Serial.println();
  Serial.println("json_weather_data: ");
  Serial.println(json_weather_data);
 
 
  //利用arduinoJson库解析心知返回的json天气数据
  //可以利用 https://arduinojson.org/v5/assistant/ Arduinojson助手生成相关json解析代码  很方便！！！
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6) + 250;
DynamicJsonBuffer jsonBuffer(capacity);

const char* json = "{\"results\":[{\"location\":{\"id\":\"WWSKUMUVE3TR\",\"name\":\"Dongying\",\"country\":\"CN\",\"path\":\"Dongying,Dongying,Shandong,China\",\"timezone\":\"Asia/Shanghai\",\"timezone_offset\":\"+08:00\"},\"now\":{\"text\":\"Sunny\",\"code\":\"0\",\"temperature\":\"21\"},\"last_update\":\"2021-02-20T12:00:00+08:00\"}]}";

JsonObject& root = jsonBuffer.parseObject(json_weather_data);

JsonObject& results_0 = root["results"][0];

JsonObject& results_0_location = results_0["location"];
const char* results_0_location_id = results_0_location["id"]; // "WWSKUMUVE3TR"
const char* results_0_location_name = results_0_location["name"]; // "Dongying"
const char* results_0_location_country = results_0_location["country"]; // "CN"
const char* results_0_location_path = results_0_location["path"]; // "Dongying,Dongying,Shandong,China"
const char* results_0_location_timezone = results_0_location["timezone"]; // "Asia/Shanghai"
const char* results_0_location_timezone_offset = results_0_location["timezone_offset"]; // "+08:00"

JsonObject& results_0_now = results_0["now"];
const char* results_0_now_text = results_0_now["text"]; // "Sunny"
const char* results_0_now_code = results_0_now["code"]; // "0"
const char* results_0_now_temperature = results_0_now["temperature"]; // "21"

const char* results_0_last_update = results_0["last_update"]; // "2021-02-20T12:00:00+08:00"
  // Test if parsing succeeds.
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return 0;
  }

 


  Serial.print("Dongying Temperature:");
  Serial.println(results_0_now_temperature);
  codeday = atoi(results_0_now_code);
  temper = atoi(results_0_now_temperature);
  Serial.print(temper);
//  
//if(results_0_daily_0_text_day[0] == 'S')
//  Serial.println("1");
//else
//  Serial.println("0");
//  return 0;


}



int Network::getTime(void)
{
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host2, httpPort)) {
    Serial.println("connection failed");
    return 0;
  }
  // We now create a URI for the request
  String url2 = "/v3/weather/now.json?key=StWBQx3j5-mjmGrPU&location=WWSKUMUVE3TR&language=en&unit=c";
  Serial.print("Requesting URL: ");
  Serial.println(url2);
  // This will send the request to the server
  client.print(String("GET ") + url2 + " HTTP/1.1\r\n" +
               "Host: " + host2 + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(100);
  // Read all the lines of the reply from server and print them to Serial
  String Time_data;
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Time_data += line;
  }
 
  client.stop();
  Serial.println();
  Serial.println("closing connection");
 
  // Process weather_json
  Serial.println();
  //Serial.println("weather_data: ");
  // Serial.println(weather_data);
 
  // Convert to JSON
  String json_time_data;
  int jsonIndex;
 
  for (int i = 0; i < Time_data.length(); i++) {
    if (Time_data[i] == '{') {
      jsonIndex = i;
      break;
    }
  }
 
  // Get JSON data
  json_time_data = Time_data.substring(jsonIndex);
  Serial.println();
  Serial.println("json_time_data: ");
  Serial.println(json_time_data);
 
 
  //利用arduinoJson库解析心知返回的json天气数据
  //可以利用 https://arduinojson.org/v5/assistant/ Arduinojson助手生成相关json解析代码  很方便！！！
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6) + 250;
DynamicJsonBuffer jsonBuffer(capacity);

const size_t capacity2 = JSON_OBJECT_SIZE(2) + 60;
DynamicJsonBuffer jsonBuffer2(capacity2);

const char* json = "{\"sysTime2\":\"2021-02-20 20:47:14\",\"sysTime1\":\"20210220204714\"}";

JsonObject& root = jsonBuffer2.parseObject(json_time_data);

const char* sysTime2 = root["sysTime2"]; // "2021-02-20 20:47:14"
const char* sysTime1 = root["sysTime1"]; // "20210220204714" 
// Test if parsing succeeds.
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return 0;
  }

 


  Serial.print("Time:　");
  Serial.println(sysTime1);
//  
//if(results_0_daily_0_text_day[0] == 'S')
//  Serial.println("1");
//else
//  Serial.println("0");
//  return 0;


}
