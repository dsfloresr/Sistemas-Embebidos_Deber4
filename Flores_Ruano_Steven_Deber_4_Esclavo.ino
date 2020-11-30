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
#include <Wire.h>
int nDato;
int tam;
String dato;
char cadena[20];
String salida;
void setup() {
  Serial.begin(9600);
  Wire.begin(4);
  Wire.onReceive(datoRecibido); //Evento de recepcion de mensajes
}

void loop() {
  delay(100) ;
}


void datoRecibido()
{
  nDato=0;//ponemos a 0 la variable de conteo
  while(Wire.available()>0)   {
    char dato = Wire.read(); // Recibe la palabra del i2c tx
    if (dato != '\0')   {
        cadena[nDato] = dato;//guarda el caracter recibido en una poscicion del vector
        nDato++;//incrementamos el contador
    }
    else
        break;//al finalizar la transmicion rompemos el while
  }
  for(byte i=0;i<=19;i++){//imprimimos lo que hay en el vector
    Serial.print(cadena[i]);
  }
      for(int i=0;i<=19;i++){
        switch(cadena[i]){
        case 'a':
        salida=salida+" @";  //codificación
        break;
        case 'e':
        salida=salida+" #";  //codificación
        break;
        case 'i':
        salida=salida+" !";  //codificación
        break;
        case 'o':
        salida=salida+" *";  //codificación
        break;
        case 'u':
        salida=salida+" $"; //codificación
        break;
        default: 
        salida=salida+" "+cadena[i];
        }
    }
    Serial.println(" ");
    Serial.println(String(salida));
    dato=salida;
    tam=dato.length()+1;        //Obtención del tamaño del vector
    char vector[tam];           //Creación del vector
    dato.toCharArray(vector,tam);   //Almacena los datos en el vector
    Wire.write(vector);
    Serial.println("Enviado");
  
}
