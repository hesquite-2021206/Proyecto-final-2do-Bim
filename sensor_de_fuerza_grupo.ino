// Incluir las bibliotecas necesarias
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Definir los pines del sensor de fuerza y la dirección de la pantalla LCD I2C
#define FSR_PIN  A0
const int LCD_ADDRESS = 0x27;

// Definir las constantes de calibración
int CALIBRATION_FACTOR = 14.5; // Factor de calibración para convertir a onzas
int MIN_FORCE = 00.0; // Fuerza mínima en el sensor
int MAX_FORCE = 200.0; // Fuerza máxima en el sensor

// Crear un objeto de la clase LiquidCrystal_I2C
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

void setup() {
  Serial.begin(9600);
 // Inicializar la comunicación I2C y el LCD
 Wire.begin();
 lcd.init();
 lcd.backlight();

 // Mostrar un mensaje de bienvenida
 lcd.setCursor(0, 0);
 lcd.print("Sensor de Fuerza");
 lcd.setCursor(0, 1);
 lcd.print("Presione...");

 delay(1000);
}

void loop() {

 // Leer el valor del sensor de fuerza
 int fsrValue = analogRead(FSR_PIN);
 Serial.println(fsrValue);

 // Convertir el valor del sensor a onzas
 float force = map(fsrValue, 0, 1023, MIN_FORCE, MAX_FORCE);
 float ounces = force / CALIBRATION_FACTOR;

 // Mostrar el valor en el LCD
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("gramos: ");
 lcd.print(force);
 lcd.print(" g");
 lcd.setCursor(0, 1);
 lcd.print("onzas: ");
 lcd.print(ounces, 2);
 lcd.print(" oz");

 delay(1000);
}
