#define DELAY_MS 1

const int shcpPin = 12;
const int stcpPin = 10;
const int dataPin = 11;

const int col1Pin = 9; // Chân Arduino nối với cột 1 led ma trận
const int col2Pin = 8;
const int col3Pin = 7;
const int col4Pin = 6;
const int col5Pin = 5;
const int col6Pin = 4;
const int col7Pin = 3;
const int col8Pin = 2;


// Mã LED Ma trận
unsigned char matrixHex[][8] = {
  {0xFF,0x00,0x00,0xE7,0xE7,0x00,0x00,0xFF}, //H
  {0xFF,0x03,0x01,0xCC,0xCC,0x01,0x03,0xFF}, //A
  // {0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x3C}, //U
  {0xFF, 0x80, 0x00, 0x7F, 0x7F, 0x00, 0x80, 0xFF}, //U

  // {0x00, 0x00, 0x84, 0xFE, 0x80, 0x00, 0x00, 0x00}, //1
  // {0x00, 0x84, 0xC2, 0xA2, 0x92, 0x8C, 0x00, 0x00}, //2
  // {0x00, 0x42, 0x92, 0x9A, 0x92, 0x62, 0x00, 0x00}, //3
  // {0x00, 0x30, 0x2C, 0x20, 0xFE, 0x20, 0x00, 0x00}, //4
  // {0x00, 0x5E, 0x92, 0x92, 0x92, 0x62, 0x00, 0x00}, //5
  // {0x00, 0x7C, 0x92, 0x92, 0x92, 0x64, 0x00, 0x00}, //6
  // {0x00, 0x02, 0x02, 0xE2, 0x1A, 0x06, 0x00, 0x00}, //7
  // {0x00, 0x6C, 0x92, 0x92, 0x92, 0x6C, 0x00, 0x00}, //8
  // {0x00, 0x4C, 0x92, 0x92, 0x92, 0x7C, 0x00, 0x00}, //9
  
};

int num = 0;
unsigned long preMillis = 0;

void setup(){
  // Cau hinh cac chan noi voi Arduino la dau ra
  pinMode(shcpPin, OUTPUT);
  pinMode(stcpPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(col1Pin, OUTPUT);
  pinMode(col2Pin, OUTPUT);
  pinMode(col3Pin, OUTPUT);
  pinMode(col4Pin, OUTPUT);
  pinMode(col5Pin, OUTPUT);
  pinMode(col6Pin, OUTPUT);
  pinMode(col7Pin, OUTPUT);
  pinMode(col8Pin, OUTPUT);
}

void loop(){
  if (millis() - preMillis >= 2000){
    preMillis = millis();
  //   if (++num > 9) num = 0;
  
    if (++num > 2) num = 0;
  }  
  // num = 0;
  // Xuat ra ma cua cot 1
  HC595_shiftOut(matrixHex[num][0]);
  // bat hien thi cot 1
  MATRIX_setCol(1,0,0,0,0,0,0,0);
  // tre 1ms
  delay(DELAY_MS);
  // tat hien thi cot 1
  MATRIX_setCol(0,0,0,0,0,0,0,0);

  //Xuat ra ma cua cot 2
  HC595_shiftOut(matrixHex[num][1]);
  MATRIX_setCol(0,1,0,0,0,0,0,0);
  delay(DELAY_MS);
  MATRIX_setCol(0,0,0,0,0,0,0,0);

  // Xuat ra ma cua cot 3
  HC595_shiftOut(matrixHex[num][2]);
  // bat hien thi cot 3
  MATRIX_setCol(0,0,1,0,0,0,0,0);
  delay(DELAY_MS);
  MATRIX_setCol(0,0,0,0,0,0,0,0);

  // Xuat ra ma cua cot 4
  HC595_shiftOut(matrixHex[num][3]);
  MATRIX_setCol(0,0,0,1,0,0,0,0);
  delay(DELAY_MS);
  MATRIX_setCol(0,0,0,0,0,0,0,0);

  // Xuat ra ma cua cot 5
  HC595_shiftOut(matrixHex[num][4]);
  MATRIX_setCol(0,0,0,0,1,0,0,0);
  delay(DELAY_MS);
  MATRIX_setCol(0,0,0,0,0,0,0,0);

  // Xuat ra ma cua cot 6
  HC595_shiftOut(matrixHex[num][5]);
  MATRIX_setCol(0,0,0,0,0,1,0,0);
  delay(DELAY_MS);
  MATRIX_setCol(0,0,0,0,0,0,0,0);

  // Xuat ra ma cua cot 7
  HC595_shiftOut(matrixHex[num][6]);
  MATRIX_setCol(0,0,0,0,0,0,1,0);
  delay(DELAY_MS);
  MATRIX_setCol(0,0,0,0,0,0,0,0);

  // Xuat ra ma cua cot 8
  HC595_shiftOut(matrixHex[num][7]);
  MATRIX_setCol(0,0,0,0,0,0,0,1);
  delay(DELAY_MS);
  MATRIX_setCol(0,0,0,0,0,0,0,0);
}

void HC595_shiftOut(unsigned char b){
  // Đặt lại chân SHCP và STCP
  digitalWrite(shcpPin, LOW);
  digitalWrite(stcpPin, LOW);

  for (int i = 0; i<8; i++) {
  // Lấy từng bit MSB trước của byte cần xuất để kiểm tra
  // Nếu bit đó khác 0
    if(b & (0x80 >> i)) {
      // Keo chan DS len muc cao
      digitalWrite(dataPin, HIGH);
      // Nguoc lai
    } else {
      // Kéo chân DS xuống mức thấp
      digitalWrite(dataPin, LOW);
    }
    // Tạo xung L-to-H dịch dữ liệu
    digitalWrite(shcpPin, LOW);
    delayMicroseconds(1);
    digitalWrite(shcpPin, HIGH);
  }
  // Tạo xung L-to-H chốt dữ liệu
  
  digitalWrite(stcpPin, LOW);
  delayMicroseconds(1);
  digitalWrite(stcpPin, HIGH);
}
void MATRIX_setCol(int c1, int c2, int c3, int c4, int c5, int c6, int c7, int c8){
  digitalWrite(col1Pin, c1);
  digitalWrite(col2Pin, c2);
  digitalWrite(col3Pin, c3);
  digitalWrite(col4Pin, c4);
  digitalWrite(col5Pin, c5);
  digitalWrite(col6Pin, c6);
  digitalWrite(col7Pin, c7);
  digitalWrite(col8Pin, c8);
}
