import processing.serial.*;

Serial arduino;  // Arduinoとのシリアル通信用オブジェクト
int ballCount = 0;  // 玉のカウンタ

Button resetButton;  // リセットボタン

void setup() {
  size(200, 150);
  arduino = new Serial(this, Serial.list()[0], 9600);  // Arduinoとのシリアル通信
  
  // リセットボタンの作成
  resetButton = new Button(width / 2 - 50, height / 2 + 25, 100, 50, "Reset");
  resetButton.setOnClick(() -> {
    ballCount = 0;
    arduino.write('R');  // Arduinoにリセット信号を送信
  });
}

void draw() {
  background(220);
  
  // 玉のカウント表示
  textAlign(CENTER, CENTER);
  textSize(32);
  text("Count: " + ballCount, width / 2, height / 2 - 25);
  
  // リセットボタンの表示
  resetButton.display();
}

void serialEvent(Serial port) {
  String data = port.readStringUntil('\n');  // シリアル通信からのデータを読み取る
  
  if (data != null) {
    data = trim(data);  // 改行を取り除く
    
    if (data.equals("Ball detected!")) {
      ballCount++;  // 玉を検出した場合、カウンタをインクリメント
    }
  }
}

// ボタン
class Button {
  float x, y, width, height;
  String label;
  Runnable onClick;

  Button(float x, float y, float width, float height, String label) {
    this.x = x;
    this.y = y;
    this.width = width;
    this.height = height;
    this.label = label;
  }

  void setOnClick(Runnable onClick) {
    this.onClick = onClick;
  }

  void display() {
    fill(255);
    stroke(0);
    rect(x, y, width, height);
    textAlign(CENTER, CENTER);
    textSize(16);
    fill(0);
    text(label, x + width / 2, y + height / 2);
  }

  boolean isClicked() {
    if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height) {
      return true;
    }
    return false;
  }
  
  void update() {
    if (isClicked() && onClick != null) {
      onClick.run();
    }
  }
}

void mousePressed() {
  resetButton.update();
}
