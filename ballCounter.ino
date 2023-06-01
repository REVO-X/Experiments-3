// 定数の定義
const int sensorPin = 0;    //センサの出力ピン
const int ballThreshold = 600;  // 玉を検出するしきい値

// 変数の定義
int ballCount = 0;  // 玉のカウンタ

void setup() {
  Serial.begin(9600);  // シリアル通信の開始
  pinMode(sensorPin, INPUT);  // センサのピンを入力モードに設定
}

void loop() {
  int sensorValue = analogRead(sensorPin);  // センサからの読み取り
  if (sensorValue > ballThreshold) {  // 玉を検出した場合
    ballCount++;  // カウンタをインクリメント
    Serial.println("Ball detected!");
    Serial.print("Count: ");
    Serial.println(ballCount);
    delay(500);  // カウント間の遅延
  }
}
