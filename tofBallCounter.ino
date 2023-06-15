#include <Wire.h>

#define ADDRESS 0x52

uint16_t distance;
uint16_t distance_tmp;
uint8_t data_cnt;

const int ballThreshold = 50;  // 玉を検出するしきい値
int ballCount = 0;             // 玉のカウンタ

void setup()
{
  Serial.begin(9600);
  Serial.println("MTOF171000C0_I2C");
  Wire.begin();
  delay(1000);
}

void loop()
{
  delay(100);

  uint16_t distance = readDistance(0xD3);

  if (distance < ballThreshold)
  {
    ballCount++;
    Serial.println("Ball detected!");
    Serial.print("Count: ");
    Serial.println(ballCount);
    delay(1000);  // 玉の検出後の待機時間
  }
}

uint16_t readDistance(byte reg)
{
  Wire.beginTransmission(ADDRESS);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(ADDRESS, 2);
  data_cnt = 0;
  distance = 0;
  distance_tmp = 0;
  while(Wire.available())
  {
    distance_tmp = Wire.read();
    distance = (distance << (data_cnt*8)) | distance_tmp;
    data_cnt++;
  }
  return distance;
}
