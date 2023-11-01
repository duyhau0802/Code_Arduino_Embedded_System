// Cám biến nhiệt độ độ ẩm: chân vcc nối 5v arduino, GND nối GND, DAT nối chân số 2 của arduino
// 2 chân nút bấm như nhau, 1 chân nối GND, 1 chân nối với số 3 arduino
// LCd nối chân SDA với A4, SCL với A5 , vcc, gnd không biết nối thì nghỉ học

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2          // Chân kết nối cảm biến DHT11
#define DHTTYPE DHT11     // Loại cảm biến là DHT11
byte degree[8] = {
  0B01110,
  0B01010,
  0B01110,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
};

DHT dht(DHTPIN, DHTTYPE); // Khởi tạo cảm biến DHT11

LiquidCrystal_I2C lcd(0x27, 16, 2); // Khởi tạo màn hình LCD 16x2 I2C với địa chỉ 0x27

const int buttonPin = 3; // Khai báo chân kết nối của nút nhấn
int buttonState = 0;     // Biến lưu trạng thái của nút nhấn
boolean isCelsius = true;
unsigned long lastButtonPress = 0;
void setup() {
  lcd.createChar(1, degree);
  lcd.init();        // Khởi tạo màn hình LCD
  lcd.backlight();   // Bật đèn nền của màn hình LCD
  dht.begin();       // Khởi tạo cảm biến DHT11
  pinMode(buttonPin, INPUT_PULLUP); // Đặt chân nút nhấn là INPUT_PULLUP
}

void loop() {
  buttonState = digitalRead(buttonPin); // Đọc trạng thái của nút nhấn

  float temperature = dht.readTemperature(); // Đọc nhiệt độ từ cảm biến DHT11
  float fahrenheit = temperature * 1.8 + 32;
  unsigned long currentTime = millis();
 
    
  if (buttonState == LOW) {
    delay(50);
    if ( (currentTime - lastButtonPress) < 1500 && buttonState == LOW) {
      lcd.noDisplay();
      lcd.noBacklight();
    }      
    lastButtonPress = currentTime;        
      isCelsius = !isCelsius; // Toggle between Celsius and Fahrenheit
      delay(200);
    
  }
  
  if (isCelsius == true)
  { // Nếu nút nhấn được nhấn
    lcd.setCursor(0, 0); // Đặt con trỏ về vị trí đầu tiên trên màn hình LCD
    lcd.print("NhietDo: "); // Hiển thị chuỗi "Temp: " lên màn hình LCD
    lcd.print(temperature); // Hiển thị nhiệt độ lên màn hình LCD
    lcd.write(1);
    lcd.print("C");
      
    }
  
  else 
  { 
    lcd.setCursor(0, 0);
       // Chuyển đổi độ Celsius sang độ Fahrenheit
      
    lcd.print("NhietDo: ");
    lcd.print(fahrenheit); // Hiển thị nhiệt độ lên màn hình LCD
    lcd.write(1);
    lcd.print("F");
  }    
} 

