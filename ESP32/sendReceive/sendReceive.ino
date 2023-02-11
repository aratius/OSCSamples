// https://github.com/hideakitai/ArduinoOSC
#include <ArduinoOSC.h>

//WiFiルータ Settings
const char* ssid = "synologyMain";  // ネットワーク名
const char* pwd = "osaka30art";  // パスワード
const IPAddress ip(192, 168, 77, 16);  // 自分のIPを決定する（pingコマンドなどで事前にIPが空いているか確認するのが望ましい） 
const IPAddress gateway(192, 168, 77, 1);  // ゲートウェイ = ネットワークのベース
const IPAddress subnet(255, 255, 255, 0);  // サブネット = だいたいこの値

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

void setUpOsc() {
  // 受信のリスナー設定
  OscWiFi.subscribe(portIncomming, "/app/status", onOscReceivedStatus);
  OscWiFi.subscribe(portIncomming, "/*", onOscReceivedAny);  // ワイルドカード
}

void onOscReceivedStatus(OscMessage& m) {
  Serial.println(m.remoteIP()/* 送信元IP */);
  Serial.println(m.remotePort()/* 受信ポート */);
  Serial.println(m.size()/*引数の数*/);
  Serial.println(m.address()/*OSCアドレス*/);
  Serial.print(m.arg<int>(0)/*1番目の引数(int)をパース*/);
  // Serial.print(m.arg<float>(1)/*2番目の引数(float)をパース*/);
  // Serial.print(m.arg<String>(2)/*3番目の引数(String)をパース*/);
  
  int someValue = m.arg<int>(0);
  // 何らかの処理
}

void onOscReceivedAny(OscMessage& m) {
  Serial.println(m.remoteIP()/* 送信元IP */);
  Serial.println(m.remotePort()/* 受信ポート */);
  Serial.println(m.size()/*引数の数*/);
  Serial.println(m.address()/*OSCアドレス*/);
  Serial.print(m.arg<int>(0)/*1番目の引数(int)をパース*/);
  // Serial.print(m.arg<float>(1)/*2番目の引数(float)をパース*/);
  // Serial.print(m.arg<String>(2)/*3番目の引数(String)をパース*/);

  String& address = m.address();

  if(address == "/someValue") {
    int someValue = m.arg<float>(0);
    // 何らかの処理
  } else if (address == "/otherValue") {
    int otherValue = m.arg<String>(0);
    // 何らかの処理
  }

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
