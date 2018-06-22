#include <SoftwareSerial.h>

SoftwareSerial BT1(10, 11); // RX | TX
const int led = 13;
 
int option;
 
void setup(){
  BT1.begin(9600);
  pinMode(led, OUTPUT); 
}
 
void loop(){
  //si existe información pendiente
  if (BT1.available()>0){
    //leeemos la opcion
    char option = BT1.read();
    //si la opcion esta entre '1' y '9'
    if (option >= '1' && option <= '9')
    {
      //restamos el valor '0' para obtener el numero enviado
      option -= '0';
      for(int i=0;i<option;i++){
         digitalWrite(led, HIGH);
         delay(100);
         digitalWrite(led, LOW);
         delay(200);
      }
    }
  }
}
