#include <Adafruit_DotStar.h>
#include <SPI.h>

#define NUM_LEDS_PER_FACE 64  // 1面あたりのLED数 (8x8)
#define NUM_FACES 5           // 5面
#define NUM_LEDS (NUM_LEDS_PER_FACE * NUM_FACES)  // 総LED数

#define DATA_PIN D10
#define CLOCK_PIN D8

Adafruit_DotStar strip(NUM_LEDS, DATA_PIN, CLOCK_PIN, DOTSTAR_BGR);

// 各面の回転角度（0, 90, 180, 270）
int orientation[NUM_FACES] = {180, 180, 180, 180, 0};

// 折り返し配置を考慮したLEDインデックスの計算
int mapLED(int x, int y, int face) {
    int mappedX = x;
    int mappedY = y;

    // 各面の回転処理
    switch (orientation[face]) {
        case 90:
            mappedX = y;
            mappedY = 7 - x;
            break;
        case 180:
            mappedX = 7 - x;
            mappedY = 7 - y;
            break;
        case 270:
            mappedX = 7 - y;
            mappedY = x;
            break;
    }

    // 折り返し配置（ジグザグマトリクス処理）
    int index;
    if (mappedY % 2 == 0) {
        index = mappedY * 8 + mappedX;
    } else {
        index = mappedY * 8 + (7 - mappedX);
    }

    return face * NUM_LEDS_PER_FACE + index;  // 面ごとのオフセット
}

void setup() {
    Serial.begin(115200);
    strip.begin();
    strip.show();  // すべての LED をオフ
}

void loop() {
    // "A" の 8x8 マトリクスデータ（1: 点灯, 0: 消灯）
    const uint8_t letterA[8][8] = {
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    // 各面に "A" を順番に表示
    for (int face = 0; face < NUM_FACES; face++) {
        strip.clear();

        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                int ledIndex = mapLED(x, y, face);
                if (letterA[y][x] == 1) {
                    strip.setPixelColor(ledIndex, strip.Color(1, 0, 0)); // 白色で表示
                }
            }
        }
        
        strip.show();
        delay(1000);  // 1秒ごとに次の面に移動

    }
}
