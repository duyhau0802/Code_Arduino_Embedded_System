// Cắm 3 con led 3 màu theo thứ tự các chân dương vào 3,5,6 . nhớ luôn có biến trở
int a[]={3,5,6};
String s;
int i;  

void setup()
{
  
 
  Serial.begin(9600);
}

int number(){
  i++;
  int t = 0;
  while(isdigit(s[i])){
    t = t*10 + s[i]-'0';
    i++;
  }
  if(t>255) t=255;
  return t;
}
int time(){
    i++;
  int t = 0;
  while(isdigit(s[i])){
    t = t*10 + s[i]-'0';
    i++;
  }  return t;
}

void loop()
{ 
  
  while(Serial.available()){
    s = Serial.readString();
    i = 0;
    for(i = 0;i<s.length();i++){
      if(s[i]=='R') analogWrite(3,number());
        if(s[i]=='G') analogWrite(5,number());
        if(s[i]=='B') analogWrite(6,number());
        if(s[i]=='D') {
          delay(time());
          analogWrite(3,0);
          analogWrite(5,0);
          analogWrite(6,0);
           }
         
    }
   

  }
}