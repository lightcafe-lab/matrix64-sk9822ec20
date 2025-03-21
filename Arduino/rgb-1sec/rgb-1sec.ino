#include <Adafruit_DotStar.h>
#include <SPI.h>

#define NUM_LEDS 64*5   // 8x8 マトリクス
#define DATA_PIN D10
#define CLOCK_PIN D8

// DotStar オブジェクトを作成
Adafruit_DotStar strip(NUM_LEDS, DATA_PIN, CLOCK_PIN, DOTSTAR_BGR);

// 明るさの設定（0.0 ～ 1.0 の範囲）
float brightness = 1;  // 最大輝度（0～255）

// RGBカラーリスト（7色）
const uint8_t colors[][3] = {
    {1, 0, 0},  // 赤
    {1, 1, 0},  // 黄
    {0, 1, 0},  // 緑
    {0, 1, 1},  // シアン
    {0, 0, 1},  // 青
    {1, 0, 1},  // マゼンタ
    {1, 1, 1}   // 白
};

void setup() {
    strip.begin();
    strip.show();  // すべての LED をオフ
}

void loop() {
    for (int c = 0; c < 7; c++) {  // 配列内の全色を順番に表示
        for (int i = 0; i < NUM_LEDS; i++) {
            strip.setPixelColor(i, strip.Color(colors[c][0] * brightness, 
                                               colors[c][1] * brightness, 
                                               colors[c][2] * brightness));
        }
        strip.show();
        delay(1000);
    }
}
