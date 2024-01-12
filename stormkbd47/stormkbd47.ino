#include <pins_arduino.h>
#include <Keyboard.h>

// Arduino pins associated with columns and rows for the
// keyboard matrix

const byte col1 = A4;
const byte col2 = 2;
const byte col3 = 3;
const byte col4 = 4;
const byte col5 = 5;
const byte col6 = 6;
const byte col7 = 7;
const byte col8 = 8;
const byte col9 = 9;
const byte col10 = 10;
const byte col11 = 11;
const byte col12 = 12;
const byte col13 = 13;

const byte row1 = A0;
const byte row2 = A1;
const byte row3 = A2;
const byte row4 = A3;

#define USE_KEYBOARD

void setup(void) {
#ifdef USE_KEYBOARD
  Keyboard.begin();
#else
  Serial.begin(9600);
#endif
  // basically we are setting rows to High-Z outputs which we will enable one by one in our keyboard scan routine
  
  digitalWrite(row1, LOW); // turn off pullup
  digitalWrite(row2, LOW); // turn off pullup
  digitalWrite(row3, LOW); // turn off pullup
  digitalWrite(row4, LOW); // turn off pullup

  pinMode(row1, INPUT); // High-Z
  pinMode(row2, INPUT); // High-Z 
  pinMode(row3, INPUT); // High-Z
  pinMode(row4, INPUT); // High-Z
  
  // Rows are inputs with pullups
  
  pinMode(row1, INPUT);
  pinMode(row2, INPUT);
  pinMode(row3, INPUT);
  pinMode(row4, INPUT);

  pinMode(col1, INPUT);
  pinMode(col2, INPUT);
  pinMode(col3, INPUT);
  pinMode(col4, INPUT);
  pinMode(col5, INPUT);
  pinMode(col6, INPUT);
  pinMode(col7, INPUT);
  pinMode(col8, INPUT);
  pinMode(col9, INPUT);
  pinMode(col10, INPUT);
  pinMode(col11, INPUT);
  pinMode(col12, INPUT);
  pinMode(col13, INPUT);

  digitalWrite(col1, HIGH); // set pullup
  digitalWrite(col2, HIGH); // set pullup
  digitalWrite(col3, HIGH); // set pullup
  digitalWrite(col4, HIGH); // set pullup
  digitalWrite(col5, HIGH); // set pullup
  digitalWrite(col6, HIGH); // set pullup
  digitalWrite(col7, HIGH); // set pullup
  digitalWrite(col8, HIGH); // set pullup
  digitalWrite(col9, HIGH); // set pullup
  digitalWrite(col10, HIGH); // set pullup
  digitalWrite(col11, HIGH); // set pullup
  digitalWrite(col12, HIGH); // set pullup
  digitalWrite(col13, HIGH); // set pullup
}

#define MOD_SHIFT 0x01
#define MOD_CTRL 0x02
#define MOD_FN 0x04
#define MOD_META 0x08
#define MOD_ALT 0x10
#define MOD_RALT 0x20
#define DEBOUNCE_DELAY 50

unsigned char prevkey = 0x00;
unsigned char prevmods = 0x00;
unsigned char dbkey = 0x00;
unsigned char dbmods = 0x00;

unsigned long last_dbtime = 0;

void loop(void) {
  unsigned char key = 0x00;
  unsigned char mods = 0x00;

  pinMode(row1, OUTPUT); 
  digitalWrite(row1, LOW);
  
  if (digitalRead(col1)==0) { key = KEY_ESC; }   // Esc ` ~
  if (digitalRead(col2)==0) { key = 'q'; }   // Q ! 1
  if (digitalRead(col3)==0) { key = 'w'; }   // W @ 2
  if (digitalRead(col4)==0) { key = 'e'; }   // E # 3
  if (digitalRead(col5)==0) { key = 'r'; }   // R $ 4
  if (digitalRead(col6)==0) { key = 't'; }   // T % 5
  if (digitalRead(col7)==0) { key = 'y'; }   // Y ^ 6
  if (digitalRead(col8)==0) { key = 'u'; }   // U & 7
  if (digitalRead(col9)==0) { key = 'i'; }   // I * 8
  if (digitalRead(col10)==0) { key = 'o'; }  // O ( 9
  if (digitalRead(col11)==0) { key = 'p'; }  // P ) 0
  if (digitalRead(col12)==0) { key = '['; }  // { [ } ]
  if (digitalRead(col13)==0) { key = KEY_BACKSPACE; }  // Backspace Del

  pinMode(row1, INPUT); 
  pinMode(row2, OUTPUT); 
  digitalWrite(row2, LOW);

  if (digitalRead(col1)==0) { key = KEY_TAB; }  // Tab
  if (digitalRead(col2)==0) { key = 'a'; }  // A F1
  if (digitalRead(col3)==0) { key = 's'; }  // S F2
  if (digitalRead(col4)==0) { key = 'd'; }  // D F3
  if (digitalRead(col5)==0) { key = 'f'; }  // F F4
  if (digitalRead(col6)==0) { key = 'g'; }  // G F5
  if (digitalRead(col7)==0) { key = 'h'; }  // H F6
  if (digitalRead(col8)==0) { key = 'j'; }  // J F7
  if (digitalRead(col9)==0) { key = 'k'; }  // K F8
  if (digitalRead(col10)==0) { key = 'l'; } // L F9
  if (digitalRead(col11)==0) { key = ';'; } // ; : " '
  if (digitalRead(col12)==0) {  } // (not used)
  if (digitalRead(col13)==0) { key = KEY_RETURN; } // Enter

  pinMode(row2, INPUT); 
  pinMode(row3, OUTPUT); 
  digitalWrite(row3, LOW);

  if (digitalRead(col1)==0) { mods |= MOD_SHIFT; } // Shift
  if (digitalRead(col2)==0) {  } // (not used)
  if (digitalRead(col3)==0) { key = 'z'; } // Z Ins
  if (digitalRead(col4)==0) { key = 'x'; } // X Del
  if (digitalRead(col5)==0) { key = 'c'; } // C Break
  if (digitalRead(col6)==0) { key = 'v'; } // V Pause
  if (digitalRead(col7)==0) { key = 'b'; } // B PrtSc
  if (digitalRead(col8)==0) { key = 'n'; } // N SysRq
  if (digitalRead(col9)==0) { key = 'm'; } // M F10
  if (digitalRead(col10)==0) { key = ','; } // < , F11
  if (digitalRead(col11)==0) { key = '.'; } // > . 
  if (digitalRead(col12)==0) { key = KEY_UP_ARROW; } // UpArrow PgUp
  if (digitalRead(col13)==0) { key = '/'; } // ? /
 
  pinMode(row3, INPUT); 
  pinMode(row4, OUTPUT); 
  digitalWrite(row4, LOW);

  if (digitalRead(col1)==0) { mods |= MOD_CTRL; } // Ctrl
  if (digitalRead(col2)==0) { mods |= MOD_FN; } // Fn
  if (digitalRead(col3)==0) { mods |= MOD_META; } // Meta
  if (digitalRead(col4)==0) { mods |= MOD_ALT; } // Left Alt
  if (digitalRead(col5)==0) {  } // (not used)
  if (digitalRead(col6)==0) { key = ' '; } // Space
  if (digitalRead(col7)==0) {  } // (not used)
  if (digitalRead(col8)==0) { mods |= MOD_RALT; } // Right Alt
  if (digitalRead(col9)==0) { key = KEY_MENU; } // Menu?
  if (digitalRead(col10)==0) { key = '\\'; } // | backslash
  if (digitalRead(col11)==0) { key = KEY_LEFT_ARROW; } // Left Arrow Home
  if (digitalRead(col12)==0) { key = KEY_DOWN_ARROW; } // Down Arrow PgDn
  if (digitalRead(col13)==0) { key = KEY_RIGHT_ARROW; } // Right Arrow End
  pinMode(row4, INPUT); 

  // Debounce
  if (!(dbkey == key && dbmods == mods))
    last_dbtime = millis();
  
  if ((millis() - last_dbtime) < DEBOUNCE_DELAY) {
    dbkey = key;
    dbmods = mods;
    return;
  }

  // Handle the Fn key
  if (mods & MOD_FN) {
    switch (key) {
      case KEY_ESC:
        key = '`';
        break;
      case 'q':
        key = '1';
        break;
      case 'w':
        key = '2';
        break;
      case 'e':
        key = '3';
        break;
      case 'r':
        key = '4';
        break;
      case 't':
        key = '5';
        break;
      case 'y':
        key = '6';
        break;
      case 'u':
        key = '7';
        break;
      case 'i':
        key = '8';
        break;
      case 'o':
        key = '9';
        break;
      case 'p':
        key = '0';
        break;
      case '[':
        key = ']';
        break;
      case KEY_BACKSPACE:
        key = KEY_DELETE;
        break;
      case 'a':
        key = KEY_F1;
        break;
      case 's':
        key = KEY_F2;
        break;
      case 'd':
        key = KEY_F3;
        break;
      case 'f':
        key = KEY_F4;
        break;
     case 'g':
        key = KEY_F5;
        break;
     case 'h':
        key = KEY_F6;
        break;
     case 'j':
        key = KEY_F7;
        break;
     case 'k':
        key = KEY_F8;
        break;
     case 'l':
        key = KEY_F9;
        break;
     case ';':
        key = '\'';
        break;
     case 'z':
        key = KEY_INSERT;
        break;
      case 'x':
        key = KEY_DELETE;
        break;
      case 'c':
        key = KEY_PAUSE;
        break;
      case 'v':
        key = KEY_PAUSE;
        break;
      case 'b':
        key = KEY_PRINT_SCREEN;
        break;
      case 'n':
        key = KEY_PRINT_SCREEN;
        break;
      case 'm':
        key = KEY_F10;
        break;
      case ',':
        key = KEY_F11;
        break;
      case '.':
        key = KEY_F12;
        break;
     case KEY_UP_ARROW:
        key = KEY_PAGE_UP;
        break;
     case '/':
        key = '=';
        break;
     case '\\':
        key = '-';
        break;
     case KEY_LEFT_ARROW:
        key = KEY_HOME;
        break;
     case KEY_DOWN_ARROW:
        key = KEY_PAGE_DOWN;
        break;
     case KEY_RIGHT_ARROW:
        key = KEY_END;
        break;
    }
  }

  // Handle the shift key
  if (mods & MOD_SHIFT) {
    switch (key) {
      case '`':
        key = '~';
        break;
      case 'q':
        key = 'Q';
        break;
      case 'w':
        key = 'W';
        break;
      case 'e':
        key = 'E';
        break;
      case 'r':
        key = 'R';
        break;
      case 't':
        key = 'T';
        break;
      case 'y':
        key = 'Y';
        break;
      case 'u':
        key = 'U';
        break;
      case 'i':
        key = 'I';
        break;
      case 'o':
        key = 'O';
        break;
      case 'p':
        key = 'P';
        break;
      case '[':
        key = '{';
        break;
      case ']':
        key = '}';
        break;
      case '1':
        key = '!';
        break;
      case '2':
        key = '@';
        break;
      case '3':
        key = '#';
        break;
      case '4':
        key = '$';
        break;
      case '5':
        key = '%';
        break;
      case '6':
        key = '^';
        break;
      case '7':
        key = '&';
        break;
      case '8':
        key = '*';
        break;
      case '9':
        key = '(';
        break;
      case '0':
        key = ')';
        break;
      case 'a':
        key = 'A';
        break;
      case 's':
        key = 'S';
        break;
      case 'd':
        key = 'D';
        break;
      case 'f':
        key = 'F';
        break;
      case 'g':
        key = 'G';
        break;
      case 'h':
        key = 'H';
        break;
      case 'j':
        key = 'J';
        break;
      case 'k':
        key = 'K';
        break;
      case 'l':
        key = 'L';
        break;
      case ';':
        key = ':';
        break;
      case '\'':
        key = '\"';
        break;
      case 'z':
        key = 'Z';
        break;
      case 'x':
        key = 'X';
        break;
      case 'c':
        key = 'C';
        break;
      case 'v':
        key = 'V';
        break;
      case 'b':
        key = 'B';
        break;
      case 'n':
        key = 'N';
        break;
      case 'm':
        key = 'M';
        break;
      case ',':
        key = '<';
        break;
      case '.':
        key = '>';
        break;
      case '/':
        key = '?';
        break;
      case '=':
        key = '+';
        break;
      case '\\':
        key = '|';
        break;
      case '-':
        key = '_';
        break;

    }
  }
#ifdef USE_KEYBOARD
  if (prevkey != key || prevmods != mods) {
    Keyboard.releaseAll();
    if (mods & MOD_SHIFT && key == 0x00)
      Keyboard.press(KEY_LEFT_SHIFT);
    if (mods & MOD_CTRL)
      Keyboard.press(KEY_LEFT_CTRL);
    if (mods & MOD_ALT)
      Keyboard.press(KEY_LEFT_ALT);
    if (mods & MOD_RALT)
      Keyboard.press(KEY_RIGHT_ALT);
    if (mods & MOD_META)
      Keyboard.press(KEY_LEFT_GUI);
    if (key != 0x00)
      Keyboard.press(key);
    prevkey = key;
    prevmods = mods;
  }
#else
  if (prevkey != key || prevmods != mods) {
    // keyboard state change
    Serial.print("Release: ");
    Serial.print(prevkey, HEX);
    Serial.print(" Mods: ");
    Serial.println(prevmods, HEX);
    Serial.print("Press: ");
    Serial.print(key, HEX);
    Serial.print(" Mods: ");
    Serial.println(mods, HEX);
    prevkey = key;
    prevmods = mods;
  }
#endif

#if 0
  // Raw scan code tester
  unsigned int keys[48];
  unsigned int *keyptr = keys;

  pinMode(row1, OUTPUT); 
  digitalWrite(row1, LOW);
  
  if (digitalRead(col1)==0) { *keyptr++ = 0x11; }   // Esc ` ~
  if (digitalRead(col2)==0) { *keyptr++ = 0x12; }   // Q ! 1
  if (digitalRead(col3)==0) { *keyptr++ = 0x13; }   // W @ 2
  if (digitalRead(col4)==0) { *keyptr++ = 0x14; }   // E # 3
  if (digitalRead(col5)==0) { *keyptr++ = 0x15; }   // R $ 4
  if (digitalRead(col6)==0) { *keyptr++ = 0x16; }   // T % 5
  if (digitalRead(col7)==0) { *keyptr++ = 0x17; }   // Y ^ 6
  if (digitalRead(col8)==0) { *keyptr++ = 0x18; }   // U & 7
  if (digitalRead(col9)==0) { *keyptr++ = 0x19; }   // I * 8
  if (digitalRead(col10)==0) { *keyptr++ = 0x1a; }  // O ( 9
  if (digitalRead(col11)==0) { *keyptr++ = 0x1b; }  // P ) 0
  if (digitalRead(col12)==0) { *keyptr++ = 0x1c; }  // { [ __ -
  if (digitalRead(col13)==0) { *keyptr++ = 0x1d; }  // }] + =

  pinMode(row1, INPUT); 
  pinMode(row2, OUTPUT); 
  digitalWrite(row2, LOW);

  if (digitalRead(col1)==0) { *keyptr++ = 0x21; }  // Tab
  if (digitalRead(col2)==0) { *keyptr++ = 0x22; }  // A F1
  if (digitalRead(col3)==0) { *keyptr++ = 0x23; }  // S F2
  if (digitalRead(col4)==0) { *keyptr++ = 0x24; }  // D F3
  if (digitalRead(col5)==0) { *keyptr++ = 0x25; }  // F F4
  if (digitalRead(col6)==0) { *keyptr++ = 0x26; }  // G F5
  if (digitalRead(col7)==0) { *keyptr++ = 0x27; }  // H F6
  if (digitalRead(col8)==0) { *keyptr++ = 0x28; }  // J F7
  if (digitalRead(col9)==0) { *keyptr++ = 0x29; }  // K F8
  if (digitalRead(col10)==0) { *keyptr++ = 0x2a; } // L F9
  if (digitalRead(col11)==0) { *keyptr++ = 0x2b; } // ; : " '
  if (digitalRead(col12)==0) { *keyptr++ = 0x2c; } // (not used)
  if (digitalRead(col13)==0) { *keyptr++ = 0x2d; } // Enter

  pinMode(row2, INPUT); 
  pinMode(row3, OUTPUT); 
  digitalWrite(row3, LOW);

  if (digitalRead(col1)==0) { *keyptr++ = 0x31; } // Shift
  if (digitalRead(col2)==0) { *keyptr++ = 0x32; } // (not used)
  if (digitalRead(col3)==0) { *keyptr++ = 0x33; } // Z Ins
  if (digitalRead(col4)==0) { *keyptr++ = 0x34; } // X Del
  if (digitalRead(col5)==0) { *keyptr++ = 0x35; } // C Break
  if (digitalRead(col6)==0) { *keyptr++ = 0x36; } // V Pause
  if (digitalRead(col7)==0) { *keyptr++ = 0x37; } // B PrtSc
  if (digitalRead(col8)==0) { *keyptr++ = 0x38; } // N SysRq
  if (digitalRead(col9)==0) { *keyptr++ = 0x39; } // M F10
  if (digitalRead(col10)==0) { *keyptr++ = 0x3a; } // < , F11
  if (digitalRead(col11)==0) { *keyptr++ = 0x3b; } // > . 
  if (digitalRead(col12)==0) { *keyptr++ = 0x3c; } // UpArrow PgUp
  if (digitalRead(col13)==0) { *keyptr++ = 0x3d; } // ? /
 
  pinMode(row3, INPUT); 
  pinMode(row4, OUTPUT); 
  digitalWrite(row4, LOW);

  if (digitalRead(col1)==0) { *keyptr++ = 0x41; } // Ctrl
  if (digitalRead(col2)==0) { *keyptr++ = 0x42; } // Fn
  if (digitalRead(col3)==0) { *keyptr++ = 0x43; } // Meta
  if (digitalRead(col4)==0) { *keyptr++ = 0x44; } // Left Alt
  if (digitalRead(col5)==0) { *keyptr++ = 0x45; } // (not used)
  if (digitalRead(col6)==0) { *keyptr++ = 0x46; } // Space
  if (digitalRead(col7)==0) { *keyptr++ = 0x47; } // (not used)
  if (digitalRead(col8)==0) { *keyptr++ = 0x48; } // Right Alt
  if (digitalRead(col9)==0) { *keyptr++ = 0x49; } // Menu?
  if (digitalRead(col10)==0) { *keyptr++ = 0x4a; } // | backslash
  if (digitalRead(col11)==0) { *keyptr++ = 0x4b; } // Left Arrow Home
  if (digitalRead(col12)==0) { *keyptr++ = 0x4c; } // Down Arrow PgDn
  if (digitalRead(col13)==0) { *keyptr++ = 0x4d; } // Right Arrow End
  pinMode(row4, INPUT); 

  if (keyptr > keys) {
    Serial.print("Scancodes: ");
    for (unsigned int *sc = keys; sc < keyptr; sc++) {
      Serial.print(*sc, HEX);
      Serial.print(" ");
    }
    Serial.println("");
  }
#endif

} 