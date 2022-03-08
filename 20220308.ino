#include <LiquidCrystal_I2C.h> 
#include <Wire.h> 
#include <Keypad.h>    // 引用Keypad程式庫

#define KEY_ROWS 4 // 按鍵模組的列數
#define KEY_COLS 4 // 按鍵模組的行數

// 依照行、列排列的按鍵字元（二維陣列）
char keymap[KEY_ROWS][KEY_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte colPins[KEY_COLS] = {9, 8, 7, 6};     // 按鍵模組，行1~4接腳。
byte rowPins[KEY_ROWS] = {13, 12, 11, 10}; // 按鍵模組，列1~4接腳。

// 初始化Keypad物件
// 語法：Keypad(makeKeymap(按鍵字元的二維陣列), 模組列接腳, 模組行接腳, 模組列數, 模組行數)
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, KEY_ROWS, KEY_COLS);

LiquidCrystal_I2C lcd(0x27,16,2);  //設定LCD位置0x27,設定LCD大小為16*2

int set = 0;
char password[4];
int now = 0;
int nowGuess;
char guess[4];

void setup() {
  lcd.init(); //初始化LCD 
  lcd.backlight(); //開啟背光
  lcd.clear();

  
}

void loop() {
  char key = myKeypad.getKey(); // 透過Keypad物件的getKey()方法讀取按鍵的字元
    if(key != NO_KEY) {
      switch(key) {
        case 'A':
          lcd.clear();
          if(set == 0) {
            if(now != 4) {
              lcd.print("NO FINISH");
              delay(1000);
              lcd.clear();
              for(int i = 0; i < now; i++) {
                lcd.print(password[i]);
              }
            }
            else {
              set = 1;
              lcd.print("OK SET");
            }
          }
          else {
            lcd.print("ALREADY SET");
            delay(1000);
            for(int i = 0; i < nowGuess; i++) {
              lcd.print(guess[i]);
            }
          }
          break;

        case 'B':
          lcd.clear();
          if(set != 1) {
            lcd.print("NO SET");
          }
          else {
            for(int i = 0; i < 4; i++) {
              lcd.print(password[i]);
            }
          }
          break;

        case 'C':
          lcd.clear();
          if(set == 0) {
            lcd.print("NO SET");
            delay(1000);
            for(int i = 0; i < now; i++) {
              lcd.print(password[i]);
            }
          }
          else {
            if(nowGuess != 4) {
              lcd.print("NO FINISH GUESS");
              delay(1000);
              lcd.clear();
              for(int i = 0; i < nowGuess; i++) {
                lcd.print(guess[i]);
              }
            }
            else {
              if(guess[0] == password[0] && guess[1] == password[1] && guess[2] == password[2] && guess[3] == password[3]) {
                lcd.print("GOOD");
              }
              else {
                lcd.print("FAIL");
              }
            }
          }
          break;

        case 'D':
          lcd.clear();
          if(set == 0) {
            lcd.print("NO SET");
            delay(1000);
            for(int i = 0; i < now; i++) {
              lcd.print(password[i]);
            }
          }
          break;

        default:
          if(set == 0 && now < 4) {
            password[now] = key;
            now++;
            lcd.clear();
            for(int i = 0; i < now; i++) {
              lcd.print(password[i]);
            }
          }
          else {
            if(set == 0) {
              password[0] = password[1];
              password[1] = password[2];
              password[2] = password[3];
              password[3] = key;
              lcd.clear();
              for(int i = 0; i < 4; i++) {
                lcd.print(password[i]);
              }
            }
            else {
              if(nowGuess != 4) {
                guess[0] = guess[1];
                guess[1] = guess[2];
                guess[2] = guess[3];
                guess[3] = key;
              }
              else {
                guess[nowGuess];
                nowGuess++;
              }
            }
          }
          break;
      }
  }
}
