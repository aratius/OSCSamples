#include <ArduinoOSC.h>

//WiFiルータ Settings
const char* ssid = "synologyMain";  // ネットワーク名
const char* pwd = "osaka30art";  // パスワード
const IPAddress gateway(192, 168, 77, 1);  // ゲートウェイ = ネットワークのベース
const IPAddress subnet(255, 255, 255, 0);  // サブネット = だいたいこの値

IPAddress ip(192, 168, 77, 16);  // 自分のIPを決定する（pingコマンドなどで事前にIPが空いているか確認するのが望ましい） 

const char* host = "192.168.77.12";  // クライアント（送信先）IP
const int portOutgoing = 12001;  // クライアント（送信先）ポート

const int portIncomming = 12000;  // サーバ（受信）ポート

bool isConnecting = false;

void setup () {
  Serial.begin(115200);

  // 初期設定 まえの接続が残ってたりするといけないので一回消す
  WiFi.disconnect(true, true);
  delay(1000);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, pwd);
  WiFi.config(ip, gateway, subnet);

  int cnt = 0;
  bool isConnected = true;
  delay(1000);
  
  Serial.print("INFO : Wi-Fi Start Connect.");

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
    //受信のリスナー設定
    OscWiFi.subscribe(portIncomming, "/app/status", onOscReceivedStatus);
  } else {
    Serial.println("INFO : Wi-Fi Connect Failed.");
  }
  
  //コネクト処理終了フラグ
  isConnecting = false;
}

void onOscReceivedStatus(OscMessage& m) {
  int statusVal = m.arg<int>(0);  // 一つ目の引数（int）を取得
  Serial.print("onOscReceivedStatus : ");
  Serial.println(statusVal);
  // 何らかの処理
}

void loop () {
  OscWiFi.update();
  
  // 例）
  // 送信実装（実際には送ってません）
  if(false) {  // ボタンが押されたら...とか
    sendOsc("/button/status", 1);
  }
}

void sendOsc(char* address, int val){
  OscWiFi.send(host, port, address, val);
}
