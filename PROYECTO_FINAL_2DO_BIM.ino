/*
Centro Educativo Tecnico Laboral Kinal 
Taller de electronica y reparacion de computadoras
Integrantes  
* Diego Alejandro Culajay Gonzalez - 2019485 
* Henry Abraham Esquite Matheu - 2021206 
* Lenin giovanny toc muñoz - 2019363 
* Jared Hernan Ruiz Anleu - 2022011 
Codigo Tecnico EB5AM
Proyecto Silo de granos 
*/
#include <Wire.h>                 // Liberias para usar el protocolo I2C
#include <Servo.h>                // Libreria que permite utilizar el servo motor
#include <Keypad.h>               // Libreria que permite utilizar teclado matricial
#include <LiquidCrystal_I2C.h>    // Libreria que controla el LCD por medio de I2C

#define disparo   22              // Pin 22 a disparo 
#define receptor  23              // Pin 23 a receptor  
#define columnas 16               // No. de columnas del LCD
#define BUZZER 11                 // Pin 11 a Buzzer  
#define col 4                     // No. de columnas del teclado matricial
#define fil 4                     // No. de filas del teclado matricial
#define servo 12                   // Directivas de preprocesador
#define filas 2                   // No. de filas del LCD
#define direccion_lcd 0x27        // Ubicacion del LCD

char keys[fil][col] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}               // Matriz led con dispocision fisica de las teclas
};
byte pines_filas[fil] = {5,4,3,2};     // Arreglos de los pines a utilizar filas
byte pines_columnas[col] = {9,8,7,6};  // Arreglos de los pines a utilizar columnas

LiquidCrystal_I2C pantalla_grupo(direccion_lcd, fil, col);     // LCD con direccion 0x20 y tamanio 16x2
Keypad teclado_grupo = Keypad( makeKeymap(keys), pines_filas, pines_columnas,fil,col);  // Constructor para el uso del teclado matricial
Servo Servo_grupo;  //constructor del servo 

float d;                   // Declara una variable de tipo float llamada "d"
int capacidad;             // Declara una variable de tipo float llamada "capacidad"
float medicion();          // Declara una función llamada "medicion" que devuelve un valor de tipo float
int lectura_teclado();     // Declara una función llamada "lectura_teclado" que devuelve un valor de tipo int
long sensor, distancia;    // Declara dos variables, "sensor" y "distancia", de tipo long
void barra_led();          // Declara una función llamada "barra_led" que no devuelve ningún valor

void setup() {
  Serial.begin(9600);             // Inicia la comunicación serial
  Wire.begin();                   // Inicia la comunicación I2C
  pantalla_grupo.init();          // Inicializa la pantalla del grupo
  pantalla_grupo.backlight();     // Enciende el retroiluminación de la pantalla del grupo
  pinMode(disparo, OUTPUT);       // Configuracion del disparo como salida
  pinMode(receptor,INPUT);        // Configuracion del receptor como entrada
  Servo_grupo.attach(servo);      // Servo_grupo con el pin "servo" para controlar un servo motor
  Servo_grupo.write(0);           // Establece la pocision inicial del servo
  for(int i = 30; i <=39; i++){   // Configuracion de los pines del 30 al 39 como salidas 
  pinMode(i,OUTPUT);              // Configuracion del pin "i" como salida
  pinMode(11,OUTPUT);             // Configuracion del pin 11 como salida 
}
}
  
void loop() {
  void barra_led();                                // Llama a la función barra_led
   lectura_teclado();                              // Llama a la función lectura_teclado
   capacidad = 110 - medicion();                   // Calcula el valor de capacidad
   Serial.println(capacidad);                      // Imprime el valor de capacidad en el LCD
   if (capacidad <= 100){                          // Capasidad menor o igual a 100
   pantalla_grupo.setCursor(0,0);                  // Establece la posición del cursor en el LCD
   pantalla_grupo.print("Almacenado:");            // Imprime el texto Almacenado en el LCD
   pantalla_grupo.setCursor(11,0);                 // Establece la posición del cursor en la columna 11 y la fila 0 del LCD
   pantalla_grupo.print(capacidad);                // Imprime el valor de capacidad en el LCD
   pantalla_grupo.print("%  ");                    // Imprime el símbolo %
   pantalla_grupo.setCursor(0,1);                  // Establece la posición del cursor en la columna 0 y la fila 1 del LCD
   pantalla_grupo.print("Desea servir?   ");       // Imprime el texto Desea servir? en el LCD  
   }
   if(capacidad < 2){                           // Capacidad es menor a 2
    tone(BUZZER, 1000);                         // Genera un tono de 1000 Hz 
    digitalWrite(30, LOW);                      // Establece el pin 30 en estado bajo
    digitalWrite(31, LOW);                      // Establece el pin 31 en estado bajo
    digitalWrite(32, LOW);                      // Establece el pin 32 en estado bajo
    digitalWrite(33, LOW);                      // Establece el pin 33 en estado bajo   
    digitalWrite(34, LOW);                      // Establece el pin 34 en estado bajo
    digitalWrite(35, LOW);                      // Establece el pin 35 en estado bajo
    digitalWrite(36, LOW);                      // Establece el pin 36 en estado bajo
    digitalWrite(37, LOW);                      // Establece el pin 37 en estado bajo
    digitalWrite(38, LOW);                      // Establece el pin 38 en estado bajo
    digitalWrite(39, LOW);                      // Establece el pin 39 en estado bajo
    
    }
    else if(capacidad >= 3 && capacidad < 6){   // Condición capacidad es mayor o igual a 3 y menor que 6 
  digitalWrite(30, LOW);                        // Establece el pin 30 en estado bajo
    digitalWrite(31, LOW);                      // Establece el pin 31 en estado bajo
    digitalWrite(32, LOW);                      // Establece el pin 32 en estado bajo
    digitalWrite(33, LOW);                      // Establece el pin 33 en estado bajo
    digitalWrite(34, LOW);                      // Establece el pin 34 en estado bajo
    digitalWrite(35, LOW);                      // Establece el pin 35 en estado bajo  
    digitalWrite(36, LOW);                      // Establece el pin 36 en estado bajo
    digitalWrite(37, LOW);                      // Establece el pin 37 en estado bajo
    digitalWrite(38, LOW);                      // Establece el pin 38 en estado bajo
    digitalWrite(39, HIGH);                     // Establece el pin 39 en estado alto
    noTone(BUZZER);                             // Detiene la generación del tono  
    }
    else if(capacidad >= 10 && capacidad < 15){ // Condicion capacidad sea mayor o igual a 10 y menor que 15 
      digitalWrite(30, LOW);                    // Establece el pin 30 en estado bajo 
    digitalWrite(31, LOW);                      // Establece el pin 31 en estado bajo
    digitalWrite(32, LOW);                      // Establece el pin 32 en estado bajo
    digitalWrite(33, LOW);                      // Establece el pin 33 en estado bajo
    digitalWrite(34, LOW);                      // Establece el pin 34 en estado bajo
    digitalWrite(35, LOW);                      // Establece el pin 35 en estado bajo 
    digitalWrite(36, LOW);                      // Establece el pin 36 en estado bajo
    digitalWrite(37, LOW);                      // Establece el pin 37 en estado bajo
    digitalWrite(38, HIGH);                     // Establece el pin 38 en estado alto
    digitalWrite(39, HIGH);                     // Establece el pin 39 en estado alto
    noTone(BUZZER);                             // Detiene la generación del tono
    }
    else if(capacidad >= 20 && capacidad < 25){ // Condicion capacidad sea mayor o igual a 20 y menor que 25
    digitalWrite(30, LOW);                      // Establece el pin 30 en estado bajo  
    digitalWrite(31, LOW);                      // Establece el pin 31 en estado bajo 
    digitalWrite(32, LOW);                      // Establece el pin 32 en estado bajo 
    digitalWrite(33, LOW);                      // Establece el pin 33 en estado bajo 
    digitalWrite(34, LOW);                      // Establece el pin 34 en estado bajo 
    digitalWrite(35, LOW);                      // Establece el pin 35 en estado bajo  
    digitalWrite(36, LOW);                      // Establece el pin 36 en estado bajo 
    digitalWrite(37, HIGH);                     // Establece el pin 37 en estado alto 
    digitalWrite(38, HIGH);                     // Establece el pin 38 en estado alto 
    digitalWrite(39, HIGH);                     // Establece el pin 39 en estado alto
    noTone(BUZZER);                             // Detiene la generación del tono  
    }
    else if(capacidad >= 30 && capacidad < 35){ // Condicion capacidad sea mayor o igual a 30 y menor que 35 
    digitalWrite(30, LOW);                      // Establece el pin 30 en estado bajo 
    digitalWrite(31, LOW);                      // Establece el pin 31 en estado bajo 
    digitalWrite(32, LOW);                      // Establece el pin 32 en estado bajo 
    digitalWrite(33, LOW);                      // Establece el pin 33 en estado bajo 
    digitalWrite(34, LOW);                      // Establece el pin 34 en estado bajo 
    digitalWrite(35, LOW);                      // Establece el pin 35 en estado bajo 
    digitalWrite(36, HIGH);                     // Establece el pin 36 en estado alto 
    digitalWrite(37, HIGH);                     // Establece el pin 37 en estado alto 
    digitalWrite(38, HIGH);                     // Establece el pin 38 en estado alto 
    digitalWrite(39, HIGH);                     // Establece el pin 39 en estado alto
    noTone(BUZZER);                             // Detiene la generación del tono
    }
    else if(capacidad >= 40  && capacidad < 45){// Condicion capacidad sea mayor o igual a 40 y menor que 45   
      digitalWrite(30, LOW);                    // Establece el pin 30 en estado bajo  
    digitalWrite(31, LOW);                      // Establece el pin 31 en estado bajo 
    digitalWrite(32, LOW);                      // Establece el pin 32 en estado bajo 
    digitalWrite(33, LOW);                      // Establece el pin 33 en estado bajo 
    digitalWrite(34, LOW);                      // Establece el pin 34 en estado bajo 
    digitalWrite(35, HIGH);                     // Establece el pin 35 en estado alto
    digitalWrite(36, HIGH);                     // Establece el pin 36 en estado alto 
    digitalWrite(37, HIGH);                     // Establece el pin 37 en estado alto 
    digitalWrite(38, HIGH);                     // Establece el pin 38 en estado alto 
    digitalWrite(39, HIGH);                     // Establece el pin 39 en estado alto 
    noTone(BUZZER);                             // Detiene la generación del tono
    }
    else if(capacidad >= 50 && capacidad < 55){ // Condicion capacidad sea mayor o igual a 50 y menor que 55  
    digitalWrite(30, LOW);                      // Establece el pin 30 en estado bajo 
    digitalWrite(31, LOW);                      // Establece el pin 31 en estado bajo 
    digitalWrite(32, LOW);                      // Establece el pin 32 en estado bajo 
    digitalWrite(33, LOW);                      // Establece el pin 33 en estado bajo 
    digitalWrite(34, HIGH);                     // Establece el pin 34 en estado alto 
    digitalWrite(35, HIGH);                     // Establece el pin 35 en estado alto 
    digitalWrite(36, HIGH);                     // Establece el pin 36 en estado alto
    digitalWrite(37, HIGH);                     // Establece el pin 37 en estado alto 
    digitalWrite(38, HIGH);                     // Establece el pin 38 en estado alto 
    digitalWrite(39, HIGH);                     // Establece el pin 39 en estado alto 
    noTone(BUZZER);                             // Detiene la generación del tono
    }
    else if(capacidad >= 60 && capacidad < 65){ // Condicion capacidad sea mayor o igual a 60 y menor que 65  
    digitalWrite(30, LOW);                      // Establece el pin 30 en estado bajo 
    digitalWrite(31, LOW);                      // Establece el pin 31 en estado bajo 
    digitalWrite(32, LOW);                      // Establece el pin 32 en estado bajo 
    digitalWrite(33, HIGH);                     // Establece el pin 33 en estado alto 
    digitalWrite(34, HIGH);                     // Establece el pin 34 en estado alto  
    digitalWrite(35, HIGH);                     // Establece el pin 35 en estado alto 
    digitalWrite(36, HIGH);                     // Establece el pin 36 en estado alto 
    digitalWrite(37, HIGH);                     // Establece el pin 37 en estado alto 
    digitalWrite(38, HIGH);                     // Establece el pin 38 en estado alto 
    digitalWrite(39, HIGH);                     // Establece el pin 39 en estado alto 
    noTone(BUZZER);                             // Detiene la generación del tono

    }
    else if(capacidad >= 70 && capacidad < 75){ // Condicion capacidad sea mayor o igual a 70 y menor que 75   
    digitalWrite(30, LOW);                      // Establece el pin 30 en estado bajo  
    digitalWrite(31, LOW);                      // Establece el pin 31 en estado bajo 
    digitalWrite(32, HIGH);                     // Establece el pin 32 en estado alto 
    digitalWrite(33, HIGH);                     // Establece el pin 33 en estado alto 
    digitalWrite(34, HIGH);                     // Establece el pin 34 en estado alto 
    digitalWrite(35, HIGH);                     // Establece el pin 35 en estado alto 
    digitalWrite(36, HIGH);                     // Establece el pin 36 en estado alto 
    digitalWrite(37, HIGH);                     // Establece el pin 37 en estado alto   
    digitalWrite(38, HIGH);                     // Establece el pin 38 en estado alto 
    digitalWrite(39, HIGH);                     // Establece el pin 39 en estado alto   
    noTone(BUZZER);                             // Detiene la generación del tono

    }
    else if(capacidad >= 80 && capacidad < 85){ // Condicion capacidad sea mayor o igual a 80 y menor que 85   
    digitalWrite(30, LOW);                      // Establece el pin 30 en estado bajo 
    digitalWrite(31, HIGH);                     // Establece el pin 31 en estado alto 
    digitalWrite(32, HIGH);                     // Establece el pin 32 en estado alto 
    digitalWrite(33, HIGH);                     // Establece el pin 33 en estado alto 
    digitalWrite(34, HIGH);                     // Establece el pin 34 en estado alto 
    digitalWrite(35, HIGH);                     // Establece el pin 35 en estado alto 
    digitalWrite(36, HIGH);                     // Establece el pin 36 en estado alto 
    digitalWrite(37, HIGH);                     // Establece el pin 37 en estado alto 
    digitalWrite(38, HIGH);                     // Establece el pin 38 en estado alto 
    digitalWrite(39, HIGH);                     // Establece el pin 39 en estado alto 

    }
    else if(capacidad >= 90){                   // Condicion capacidad sea mayor o igual a 90
    digitalWrite(30, HIGH);                     // Establece el pin 30 en estado alto 
    digitalWrite(31, HIGH);                     // Establece el pin 31 en estado alto 
    digitalWrite(32, HIGH);                     // Establece el pin 32 en estado alto 
    digitalWrite(33, HIGH);                     // Establece el pin 33 en estado alto 
    digitalWrite(34, HIGH);                     // Establece el pin 34 en estado alto 
    digitalWrite(35, HIGH);                     // Establece el pin 35 en estado alto 
    digitalWrite(36, HIGH);                     // Establece el pin 36 en estado alto 
    digitalWrite(37, HIGH);                     // Establece el pin 37 en estado alto 
    digitalWrite(38, HIGH);                     // Establece el pin 38 en estado alto 
    digitalWrite(39, HIGH);                     // Establece el pin 38 en estado alto 
    noTone(BUZZER);                             // Detiene la generación del tono
    }
    
}

   float medicion(){                            // Funcion medicion  
   long t;                                      // Declara una variable t de tipo long
   digitalWrite(disparo, HIGH);                 // Establece el pin disparo en estado alto
   delayMicroseconds(10);                       // Espera durante 10 microsegundos.
   digitalWrite(disparo, LOW);                  // Establece el pin disparo en estado bajo 
   t = pulseIn(receptor, HIGH);                 // Mide el tiempo de pulso en el pin receptor 
   d= t / 59;                                   // Calcula el valor de d 
   int porcentaje = ((d)/20)*100;               // Calcula el valor de porcentaje                
  delay(100);                                   // Espera durante 100 milisegundos
  return porcentaje;                            // Devuelve el valor de porcentaje
   }
  int lectura_teclado(){                        // Lee la tecla presionada del teclado matricial
  char tecla = teclado_grupo.getKey();          // Lee la tecla presionada en el teclado y la asigna a la variable 
  if(tecla){                                    // Comienza una estructura condicional 
switch(tecla){                                  // que evaluará el valor de tecla
  
   case '1':                                    // Presionar tecla 1
   if(capacidad >= 5){                          // Se verifica si la capacidad es mayor o igual a 5
   pantalla_grupo.setCursor(0,1);               // Se configura el cursor en la posición (0, 1) del LCD
   pantalla_grupo.print("   1 onza      ");        // Se imprime "1 onza" en el LCD  
      Serial.println(capacidad);                // Escribe la cantidad que desea
      Servo_grupo.write(60);                    // Se mueve el servo a una posición de 90 grados
      delay(800);                              // espera de 2 segundos
      Servo_grupo.write(0);                     // Se regresa a la posicion inicial (0)
      delay(500);                               // Espera de 500 milisegundos
     
      break;                                    // Después de ejecutar las acciones 
   } else{    
    for(int i = 0; i < 3; i++){                  // Se verifica antes de cada iteración para determinar si el bucle debe continuar ejecutándose
      pantalla_grupo.setCursor(0,1);             // Se configura el cursor en la posición (0, 1) del LCD
      pantalla_grupo.print("escaso producto");   // Se imprime "producto" en el LCD
      delay(500);                                // Espera de 500 milisegundos                                             
    }
    break;                                       // Después de ejecutar las acciones 
  }

  case '2':                                      // Presionar tecla 2
   if(capacidad >= 10){                          // Se verifica si la capacidad es mayor o igua a 10
   pantalla_grupo.setCursor(0,1);                // Se configura el cursor en la posición (0, 1) del LCD
   pantalla_grupo.print("   8 onza      ");      // Se imprime "2 onzas" en el LCD
      Serial.println(capacidad);                 // Escribe la cantidad que desea
      Servo_grupo.write(60);                     // Se mueve el servo a una posición de 90 grados
      delay(3700);                              // Espera de 5 segundos
      Servo_grupo.write(0);                      // Se regresa a la posicion inicial (0)
      delay(500);                                // Espera de 500 milisegundos
      
      break;                                     // Después de ejecutar las acciones 
   } else{    
    for(int i = 0; i < 3; i++){                  // Se verifica antes de cada iteración para determinar si el bucle debe continuar ejecutándose
     pantalla_grupo.setCursor(0,1);              // Se configura el cursor en la posición (0, 1) del LCD
     pantalla_grupo.print("escaso producto");    // Se imprime "producto" en el LCD
     delay(500);                                 // Espera de 500 milisegundos                                             
    }  
    break;                                       // Después de ejecutar las acciones
  }

  case '3':                                      // Presionar tecla 3
   if(capacidad >= 20){                          // Se verifica si la capacidad es mayor o igua a 20 
   pantalla_grupo.setCursor(0,1);                // Se configura el cursor en la posición (0, 1) del LCD
   pantalla_grupo.print("   12 onzas     ");     // Se imprime "3 onzas" en el LCD
      Serial.println(capacidad);                 // Escribe la cantidad que desea
      Servo_grupo.write(60);                     // Se mueve el servo a una posición de 90 grados
      delay(7000);                              // Espera de 10 segundos   
      Servo_grupo.write(0);                      // Se regresa a la posicion inicial (0)
      delay(500);                                // Espera de 500 milisegundos  
      
      break;                                     // Después de ejecutar las acciones 
   } else{    
    for(int i = 0; i < 3; i++){                  // Se verifica antes de cada iteración para determinar si el bucle debe continuar ejecutándose
     pantalla_grupo.setCursor(0,1);              // Se configura el cursor en la posición (0, 1) del LCD
     pantalla_grupo.print("escaso producto");    // Se imprime "producto" en el LCD
     delay(500);                                 // Espera de 500 milisegundos                                             
    }
    break;                                       // Después de ejecutar las acciones  
  }

  case '4':                                      // Presionar tecla 4
   if(capacidad >= 30){                          // Se verifica si la capacidad es mayor o igua a 30 
   pantalla_grupo.setCursor(0,1);                // Se configura el cursor en la posición (0, 1) del LCD
   pantalla_grupo.print("   16 onzas     ");     // Se imprime "4 onzas" en el LCD
      Serial.println(capacidad);                 // Escribe la cantidad que desea
      Servo_grupo.write(60);                     // Se mueve el servo a una posición de 90 grados
      delay(10000);                              // Espera de 15 segundos  
      Servo_grupo.write(0);                      // Se regresa a la posicion inicial (0)
      delay(500);                                // Espera de 500 milisegundos 
      
      break;                                     // Después de ejecutar las acciones  
   } else{   
    for(int i = 0; i < 3; i++){                  // Se verifica antes de cada iteración para determinar si el bucle debe continuar ejecutándose
     pantalla_grupo.setCursor(0,1);              // Se configura el cursor en la posición (0, 1) del LCD
     pantalla_grupo.print("escaso producto");    // Se imprime "producto" en el LCD
     delay(500);                                 // Espera de 500 milisegundos                                             
    }
    break;                                       // Después de ejecutar las acciones  
  }
  case '5':                                      // Presionar tecla 5
   if(capacidad >= 40){                          // Se verifica si la capacidad es mayor o igua a 40 
   pantalla_grupo.setCursor(0,1);                // Se configura el cursor en la posición (0, 1) del LCD 
   pantalla_grupo.print("   24 onzas     ");     // Se imprime "5 onzas" en el LCD
      Serial.println(capacidad);                 // Escribe la cantidad que desea
      Servo_grupo.write(60);                     // Se mueve el servo a una posición de 90 grados
      delay(15000);                              // Espera de 20 segundos 
      Servo_grupo.write(0);                      // Se regresa a la posicion inicial (0)
      delay(500);                                // Espera de 500 milisegundos 
       
      break;                                     // Después de ejecutar las acciones 
   } else{   
    for(int i = 0; i < 3; i++){                  // Se verifica antes de cada iteración para determinar si el bucle debe continuar ejecutándose 
     pantalla_grupo.setCursor(0,1);              // Se configura el cursor en la posición (0, 1) del LCD
     pantalla_grupo.print("escaso producto");    // Se imprime "producto" en el LCD
     delay(500);                                 // Espera de 500 milisegundos                                             
    } 
    break;                                       // Después de ejecutar las acciones
  }

  case '6':                                      // Presionar tecla 6
   if(capacidad >= 50){                          // Se verifica si la capacidad es mayor o igua a 50 
   pantalla_grupo.setCursor(0,1);                // Se configura el cursor en la posición (0, 1) del LCD 
   pantalla_grupo.print("   32 onzas     ");     // Se imprime "6 onzas" en el LCD
      Serial.println(capacidad);                 // Escribe la cantidad que desea
      Servo_grupo.write(60);                     // Se mueve el servo a una posición de 90 grados
      delay(25000);                              // Espera de 30 segundos 
      Servo_grupo.write(0);                      // Se regresa a la posicion inicial (0)
      delay(500);                                // Espera de 500 milisegundos
     
      break;                                     // Después de ejecutar las acciones 
   } else{   
    for(int i = 0; i < 3; i++){                  // Se verifica antes de cada iteración para determinar si el bucle debe continuar ejecutándose 
     pantalla_grupo.setCursor(0,1);              // Se configura el cursor en la posición (0, 1) del LCD
     pantalla_grupo.print("escaso producto");    // Se imprime "producto" en el LCD
     delay(500);                                 // Espera de 500 milisegundos                                             
    }
    break;                                       // Después de ejecutar las acciones 
  }
  case '7':                                      // Presionar tecla 7
   pantalla_grupo.setCursor(0,1);                // Se configura el cursor en la posición (0, 1) del LCD 
   pantalla_grupo.print("     sirvete   ");      // Se imprime "sirvete :)" en el LCD 
   delay(900);                                   // Espera de 900 milisegundos
    break;                                       // Después de ejecutar las acciones
    case '8':                                    // boton invalido
   pantalla_grupo.setCursor(0,1);                // Se configura el cursor en la posición (0, 1) del LCD 
   pantalla_grupo.print("     sirvete   ");       // Se imprime "sirvete :)" en el LCD 
   delay(900);                                   // Espera de 900 milisegundos
    break;                                       // Después de ejecutar las acciones
    case '9':                                    // Presionar tecla 9
   pantalla_grupo.setCursor(0,1);                // Se configura el cursor en la posición (0, 1) del LCD 
   pantalla_grupo.print("     sirvete   ");       // Se imprime "sirvete :)" en el LCD
   delay(900);                                   // Espera de 900 milisegundos
    break;                                       // Después de ejecutar las acciones
    case '0':                                    // Presionar tecla 0  
   pantalla_grupo.setCursor(0,1);                // Se configura el cursor en la posición (0, 1) del LCD 
   pantalla_grupo.print("     sirvete   ");       // Se imprime "sirvete :)" en el LCD
   delay(900);                                   // Espera de 900 milisegundos
    break;                                       // Después de ejecutar las acciones
    case 'A':                                    // Presionar tecla A
   pantalla_grupo.setCursor(0,1);                // Se configura el cursor en la posición (0, 1) del LCD 
   pantalla_grupo.print("     sirvete   ");       // Se imprime "sirvete :)" en el LCD
   delay(900);                                   // Espera de 900 milisegundos
    break;                                       // Después de ejecutar las acciones
    case 'B':                                    // Presionar tecla B
   pantalla_grupo.setCursor(0,1);                // Se configura el cursor en la posición (0, 1) del LCD 
   pantalla_grupo.print("     sirvete   ");       // Se imprime "sirvete :)" en el LCD
   delay(900);                                   // Espera de 900 milisegundos
    break;                                       // Después de ejecutar las acciones
    case 'C':                                    // Presionar tecla C 
   pantalla_grupo.setCursor(0,1);                // Se configura el cursor en la posición (0, 1) del LCD 
   pantalla_grupo.print("     sirvete   ");       // Se imprime "sirvete :)" en el LCD
   delay(900);                                   // Espera de 900 milisegundos
    break;                                       // Después de ejecutar las acciones
    case 'D':                                    // Presionar tecla D
   pantalla_grupo.setCursor(0,1);                // Se configura el cursor en la posición (0, 1) del LCD 
   pantalla_grupo.print("     sirvete   ");       // Se imprime "sirvete :)" en el LCD 
   delay(900);                                   // Espera de 900 milisegundos
    break;                                       // Después de ejecutar las acciones
    case '*':                                    // Presionar tecla *
   pantalla_grupo.setCursor(0,1);                // Se configura el cursor en la posición (0, 1) del LCD 
   pantalla_grupo.print("     sirvete   ");       // Se imprime "sirvete :)" en el LCD  
   delay(900);                                   // Espera de 900 milisegundos
    break;                                       // Después de ejecutar las acciones
    case '#':                                    // Presionar tecla #
   pantalla_grupo.setCursor(0,1);                // Se configura el cursor en la posición (0, 1) del LCD 
   pantalla_grupo.print("     sirvete   ");       // Se imprime "sirvete :)" en el LCD
   delay(900);                                   // Espera de 900 milisegundos
    break;                                       // Después de ejecutar las acciones
  }
} 
  }
