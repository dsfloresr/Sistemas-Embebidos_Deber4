/*
*     ///////////////// MASTER /////////////
* CAP III: MODULOS DE CX
* COD 12: Envio y recepcion de mensajes por cx 12c
* Obj: Conocer el protocolo i2c
* Funciones:  
*           Wire.begin() //Iniciar el hardware
*           Wire.beginTransmission(adrress)  // comenzar la transmision
*           Wire.ednTransmission() //finaliza la transmision
*           Wire.requestFrom(address,nBytes) // Solicitar envio de datos desde esclavo
*           
*/

 #include<LiquidCrystal.h>
 #include <Wire.h>
 LiquidCrystal lcd(13,12,11,10,9,8); //RS,E,D4,D5,D6,D7 
int cont =0; // variable de conteo
String dato;
int nDato;
int tam;
char cadena[20];
void setup() {
  lcd.begin(16,2);      //Inicializa el objeto lcd
  Wire.begin();  // cx i2c
  Serial.begin(9600); // cx Serial
}

void loop() {
    if(Serial.available()>0){
        dato=Serial.readString();     //Obtención dato mediante terminal
        tam=dato.length()+1;        //Obtención del tamaño del vector
        char vector[tam];           //Creación del vector
        dato.toCharArray(vector,tam);   //Almacena los datos en el vector
        Wire.beginTransmission(4);  //Enviar informacion al eswclavo con id 4
    Wire.write(vector);       //Envio de dato
    Wire.endTransmission();   //Fin de cx
   delay(3000);
   Wire.requestFrom(4,20);   //solicitud de mensaje
   while(Wire.available()>0)   {
    Serial.println("Recibido");
    char dato = Wire.read(); // Recibe la palabra del i2c tx
    if (dato != '\0')   {
        cadena[nDato] = dato;//guarda el caracter recibido en una poscicion del vector
        nDato++;//incrementamos el contador
    }
    else
        break;//al finalizar la transmicion rompemos el while
  }
    lcd.setCursor(0,0);            //Ubicación en pantalla LCD
    for(int k;k<19;k++){
     lcd.print(String(cadena[k]));      //Muestra de mensaje recibido
    }
   }
} 
