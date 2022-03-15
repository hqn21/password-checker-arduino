#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h> // 引用Keypad程式庫
#include <string.h>

#define KEY_ROWS 4 // 按鍵模組的列數
#define KEY_COLS 4 // 按鍵模組的行數

// 依照行、列排列的按鍵字元（二維陣列）
char keymap[KEY_ROWS][KEY_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

byte colPins[KEY_COLS] = {9, 8, 7, 6};     // 按鍵模組，行1~4接腳。
byte rowPins[KEY_ROWS] = {13, 12, 11, 10}; // 按鍵模組，列1~4接腳。

/*
    初始化Keypad物件
    語法：Keypad(makeKeymap(按鍵字元的二維陣列), 模組列接腳, 模組行接腳, 模組列數, 模組行數)
*/
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, KEY_ROWS, KEY_COLS);

LiquidCrystal_I2C lcd(0x27, 16, 2); //設定LCD位置0x27,設定LCD大小為16*2

/*
    設置基本配置
*/
int passwordStatus = 0; // 設置密碼狀態 {0 => "尚未設置", 1 => "已設置"}
char password[4]; // 四位密碼
int delayTime = 1000; // 顯示提示字句後的延遲（毫秒）
char temp[4]; // 暫存
int nowTemp = 0; // 目前暫存位置
int guessStatus = 1;

void delayAndShowTemp() {
    delay(delayTime);
    lcd.clear();
    if(nowTemp > 0) {
        for(int i = 0; i < nowTemp; i++) {
            lcd.print(temp[i]);
        }
    }
}

void setup() {
    lcd.init(); // 初始化LCD
    lcd.backlight(); // 開啟背光
    lcd.print("START");
    delay(delayTime);
    lcd.clear(); // 清空螢幕
}

void loop() {
    char key = myKeypad.getKey(); // 透過Keypad物件的getKey()方法讀取按鍵的字元
    switch(key) {
        // 按鍵字元為空值
        case NO_KEY:
            break;
        // 確認鍵
        case 'A':
            lcd.clear();
            if(nowTemp != 4) {
                lcd.print("ERR_TP_NOT_EH_A");
                delayAndShowTemp();
                break;
            }
            // 猜密碼
            guessStatus = 1;
            if(passwordStatus) {
                for(int i = 0; i < 4; i++) {
                    if(password[i] != temp[i]) {
                        guessStatus = 0;
                        break;
                    }
                }
                nowTemp = 0;
                memset(temp, 0, sizeof(temp));
                if(guessStatus == 0) {
                  lcd.print("ERR_GU_PW_A");
                }
                else {
                  lcd.print("SUC_GU_PW_A");
                }
                delayAndShowTemp();
            }
            // 設置密碼
            else {
                for(int i = 0; i < 4; i++) {
                    password[i] = temp[i];
                }
                passwordStatus = 1;
                nowTemp = 0;
                memset(temp, 0, sizeof(temp));
                lcd.print("SUC_SET_PW_A");
                delayAndShowTemp();
            }
            break;
        // 查看目前密碼狀態
        case 'B':
            lcd.clear();
            if(!passwordStatus) {
                lcd.print("ERR_PW_NOT_SET_B");
                delayAndShowTemp();
                break;
            }
            lcd.print("SUC_PW_SET_B");
            delayAndShowTemp();
            break;
        // 顯示當前密碼
        case 'C':
            lcd.clear();
            if(!passwordStatus) {
                lcd.print("ERR_PW_NOT_SET_C");
                delayAndShowTemp();
                break;
            }
            for(int i = 0; i < 4; i++) {
                lcd.print(password[i]);
            }
            delayAndShowTemp();
            break;
        // 清空密碼
        case 'D':
            lcd.clear();
            if(!passwordStatus) {
              lcd.print("ERR_PW_NOT_SET_D");
              delayAndShowTemp();
              break;
            }
            passwordStatus = 0;
            memset(password, 0, sizeof(password));
            lcd.print("SUC_CLEAR_PW_D");
            delayAndShowTemp();
            break;
        // 按其他按鈕
        default:
            lcd.clear();
            if(nowTemp < 4) {
                temp[nowTemp] = key;
                nowTemp++;
            }
            else {
                temp[0] = temp[1];
                temp[1] = temp[2];
                temp[2] = temp[3];
                temp[3] = key;
            }
            if(nowTemp > 0) {
                for(int i = 0; i < nowTemp; i++) {
                    lcd.print(temp[i]);
                }
            }
            else {
                lcd.clear();
            }
            break;
    }
}
