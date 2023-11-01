// Duyệt 10led sử dụng uno mega

// int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; Trên này sử dụng Uno MEga 2600, có nhiều chân xung nên thích dùng nhiêu dùng
// arduino bình thường trên lớp chỉ có 6 chân xung, nên dùng 2 đèn điều khiển 1 chân
// Nên dùng 10 đèn cùng 1 loại led màu đỏ, vì điện trở nó phù hợp

int ledPins[] = {3, 5, 6, 9, 10}; // cứ 2 dend thì vào 1 chân, ở đây có 5 chân lần lượt 3, 5, 6, 9, 10

int potPin = A0; // Chân Analog Input của biến trở 
int potValue = 0; // Giá trị đọc được từ biến trở

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.begin(9600);  
}

void loop() {
  potValue = analogRead(potPin); // Đọc giá trị từ biến trở
  potValue = map(potValue, 0, 1023, 0, 255); // Chuyển đổi giá trị đọc được về mức độ sáng của LED
  Serial.print(potValue);
  for (int brightness = 0; brightness <= potValue; brightness++) {
    for (int i = 0; i < 5; i++) {
      analogWrite(ledPins[i], brightness); // Thiết lập độ sáng của LED
    }
    //delay(10); // Đợi 10ms để chuyển đến mức độ sáng tiếp theo
  }
}