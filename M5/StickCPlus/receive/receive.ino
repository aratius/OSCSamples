// OSC部はArduinoOSCなのでESPと同じです
#include <M5StickCPlus.h>
#include <ArduinoOSC.h>

//WiFiルータ Settings
const char* ssid = "HUMAX-BD2EB";  // ネットワーク名
const char* pwd = "MjdjMmNxMEgaX";  // パスワード
const IPAddress ip(192, 168, 0, 102);  // 自分のIPを決定する（pingコマンドなどで事前にIPが空いているか確認するのが望ましい） 
const IPAddress gateway(192, 168, 0, 1);  // ゲートウェイ = ネットワークのベース
const IPAddress subnet(255, 255, 255, 0);  // サブネット = だいたいこの値
const int portIncomming = 12000;  // サーバ（受信）ポート
bool isConnecting = false;

float x = 0;
float y = 0;
bool isPressed = false;

void setup() {
  Serial.begin(115200);
  M5.begin(); //Init M5Core.  初始化 M5Core

    // 初期設定 まえの接続が残ってたりするといけないので一回消す
  WiFi.disconnect(true, true);
  delay(1000);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, pwd);
  WiFi.config(ip, gateway, subnet);

  int cnt = 0;
  bool isConnected = true;
  delay(1000);
  
  Serial.print("INFO : Trying to connect Wi-Fi");

  // WiFiがつながるまでwhileを回す
  while (WiFi.status() != WL_CONNECTED) { 
    Serial.print(".");
    delay(500);
    if (cnt == 5) {
      isConnected = false;
      break;
    }
    cnt += 1;
  }
  Serial.println("");

  if (isConnected) {
    Serial.println("INFO : Wi-Fi Connected.");
    setUpOsc();
  } else {
    Serial.println("INFO : Wi-Fi Connect Failed.");
  }
  
  //コネクト処理終了フラグ
  isConnecting = false;
}

void loop(){
  OscWiFi.update();
  
  if(isPressed)
    M5.Lcd.fillCircle(x, y, 20, RED); //Draw a red circle of radius 50 at (x,y)
  else
    M5.Lcd.fillCircle(x, y, 20, WHITE); //Draw a red circle of radius 50 at (x,y)

  M5.update();
}

void setUpOsc() {
  // 受信のリスナー設定
  OscWiFi.subscribe(portIncomming, "/position/x", onOscReceivedPosX);
  OscWiFi.subscribe(portIncomming, "/position/y", onOscReceivedPosY);
  OscWiFi.subscribe(portIncomming, "/mouse/isPressed", onOscReceivedIsPressed);
}

void onOscReceivedPosX(OscMessage& m) {
  float _x = m.arg<float>(0) * (float)M5.Lcd.width();
  if(_x != x) {
    M5.Lcd.fillScreen(BLACK);
    x = _x;
  }
}

void onOscReceivedPosY(OscMessage& m) {
  float _y = m.arg<float>(0) * (float)M5.Lcd.height();
  if(_y != y) {
    M5.Lcd.fillScreen(BLACK);
    y = _y;    
  }
}

void onOscReceivedIsPressed(OscMessage& m) {
  M5.Lcd.fillScreen(BLACK);
  isPressed = m.arg<int>(0) == 1;
}
