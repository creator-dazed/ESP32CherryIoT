// ============================================
// ESP32 CherryIoT (Basic Kit + LightSensor)
// 光センサー(Lux)値を Wi-Fi 経由で Google Sheets へ
// ============================================

#include <WiFi.h>
#include <WiFiClientSecure.h>

// 接続先のSSIDとパスワード
const char* ssid = "xxxxx"; //無線ルーターのssidを入力
const char* password = "xxxxx"; //無線ルーターのパスワードを入力

// ---- Google Apps Script の URL ----
const char* gasHost = "script.google.com"; 
const String gasPath = "/macros/s/xxxxx/exec";

// ---- 光センサーのピン ----
const int litsnsrPin = 3; 

// ---- 時間管理 ----
unsigned long lastSheet = 0;
const unsigned long SHEET_INTERVAL = 10000;   // 10秒おきに送信

// ====== Wi-Fi 接続(未接続なら接続) ======
void ensureWiFi() {
  if (WiFi.status() == WL_CONNECTED) return;

  Serial.print("ssid:");
  Serial.print(ssid);
  Serial.println(" に接続します。");

  WiFi.begin(ssid, password);

  Serial.print("WiFiに接続中");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\n接続しました。");

  // IPアドレスの表示
  Serial.print("IP address:");
  Serial.println(WiFi.localIP());
}

// ====== 光センサー読み取り ======
float readLux() {
  float litsnsr_ad = analogRead(litsnsrPin); // アナログデータの読み取り
  float litsnsr_v = litsnsr_ad * 3.3 / 4096; // 電圧値の計算
  
  // ゼロ割りによるシステム停止を防止するガード
  if (litsnsr_v >= 3.3) litsnsr_v = 3.29;  
  
  float lux = 10000 * litsnsr_v / (3.3 - litsnsr_v) / 1000; // Lux値の計算
  return lux;
}

// ====== スプレッドシートへ送信 ======
void sendToSheet(float lux) {
  // Wi-Fi接続確認
  ensureWiFi();
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi未接続のため送信をスキップします");
    return;
  }

  WiFiClientSecure sslclient;
  sslclient.setInsecure(); // 証明書検証のスキップ

  Serial.println("サーバーに接続中...");
  if (!sslclient.connect(gasHost, 443)) {
    Serial.println("接続に失敗しました");
    return;
  }
  Serial.println("サーバーに接続しました");

  // シリアルモニターへのデータ出力
  Serial.print(lux);
  Serial.print(" Lux : ");
  if (lux > 40) {
    Serial.println("Bright");
  } else {
    Serial.println("Dark");
  }

  // URL組み立て
  String url = gasPath + "?1_cell=" + String(lux, 2);
  Serial.println("送信URL: https://" + String(gasHost) + url);

  // HTTP GET リクエスト送信
  sslclient.println("GET " + url + " HTTP/1.1");
  sslclient.println("Host: " + String(gasHost));
  sslclient.println("User-Agent: ESP32");
  sslclient.println("Connection: close");
  sslclient.println();

  delay(1000); // 送信待ち時間
  sslclient.stop();

  Serial.println("データ送信完了");
  Serial.println("");
}

void setup() {
  Serial.begin(115200);
  pinMode(litsnsrPin, INPUT);
  delay(1000);
  Serial.println("=== ESP32 Luxセンサー起動 ===");
  
  ensureWiFi();
}

void loop() {
  unsigned long currentMillis = millis();

  // 10秒に1回の周期で測定と送信を実行
  if (currentMillis - lastSheet >= SHEET_INTERVAL) {
    lastSheet = currentMillis;
    
    float currentLux = readLux();
    sendToSheet(currentLux);
  }
  
  delay(10);
}