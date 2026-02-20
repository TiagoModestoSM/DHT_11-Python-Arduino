/*
Autor: Tiago Modesto de Sousa Moura
Data:04/07/2024
Teste de Menu de Interface do LCD 
*/


// Incluir bibliotecas
#include <LiquidCrystal_I2C.h> // Inclui a biblioteca do LCD I2C
#include <Wire.h> // biblioteca de comunicacao I2C
#include <DHT.h> //Inclui a biblioteca do sensor DHT11



//Definir pinos
#define ButtonUp 4
#define ButtonDown 5
#define ButtonEnter 7
#define ButtonBack 6

#define Led1 9
#define Led2 10

#define Buzzer 11

#define DHTPIN 3 //Definir o pino de Sinal
#define DHTTYPE DHT11 // Definir o modelo do sensor


//Criação do objeto LCD 16x2, endereço 0x27
LiquidCrystal_I2C lcd(0x27,16,2);

//Criação do objeto DHT11
DHT dht(DHTPIN,DHTTYPE);

//Variaveis
bool up = 0, down = 0, enter = 0, back = 0;
bool StateUp = 1, StateDown = 1, EnableLCD = 0, StateEnterControl = 1, StateBackControl = 1;
bool StateLed1;
byte count = 1;
float t;
float f;
float h;
float hif;
float hic;
unsigned long previousMillis = 0; // Armazena o último tempo em que os dados foram enviados
const long interval = 2000; // Intervalo de 1 segundo


//Apresenta a tela 0
void screen0(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("=-=THERMOSTAT=-=");
  lcd.setCursor(0,1);
  lcd.print("=-=-=-=-=-=-=-=-");
}
//Apresenta a tela 1
void screen1(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("->Monitoramento");
  lcd.setCursor(0,1);
  lcd.print("  Control");
  lcd.write(byte(2));
  lcd.print("C");
}
//Apresenta a tela 2
void screen2(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  Monitoramento");
  lcd.setCursor(0,1);
  lcd.print("->Control");
  lcd.write(byte(2));
  lcd.print("C");
  
}
//Apresenta a tela 3
void screen3(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("->Control");
  lcd.write(byte(2));
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("  Modo");
  
}
//Apresenta a tela 4
void screen4(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  Control");
  lcd.write(byte(2));
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("->Modo");
  
}

//Simbolos especiais
byte grau[8] = {// Formato do Grau (°)
  B00000,
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
};

byte neve[8] = {// Formato do Floco de Neve
  B00000,
  B00000,
  B01010,
  B11011,
  B00100,
  B11011,
  B01010,
  B00000,
};

byte gota[8] ={ // Formato da Gota
  B00000,
  B00100,
  B00110,
  B01111,
  B11101,
  B11001,
  B01110,  
};



void setup() {

//Inicialização do LCD
lcd.init();
lcd.setBacklight(HIGH);
lcd.clear();

//Inicialização do DHT
  Serial.begin(9600); //Inicia o Serial
  Serial.println("Termostato");
  Serial.println("-----------------------------------------");
  dht.begin();

//Criação dos símbolos
lcd.createChar(2,grau);
lcd.createChar(1,gota);
lcd.createChar(0,neve);


//Pinos dos leds como saída
pinMode(Led1, OUTPUT);
pinMode(Led2, OUTPUT);


//Pinos dos botões como entrada
pinMode(ButtonUp, INPUT_PULLUP);
pinMode(ButtonDown, INPUT_PULLUP);
pinMode(ButtonEnter, INPUT_PULLUP);
pinMode(ButtonBack, INPUT_PULLUP);

//Pinos do Buzzer como saída
pinMode(Buzzer,OUTPUT);

//Tela Inicial
screen0 ();

}




void loop() {
    // Leitura do DHT e envio contínuo para o Serial
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);

    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Leitura do sensor DHT falhou");
      return;
    }

    float hif = dht.computeHeatIndex(f, h);
    float hic = dht.computeHeatIndex(t, h, false);
    
  Serial.println("------------------------------------------------------------------------------------------------------------");
  Serial.print("| Umidade:  ");
  Serial.print(h, 1); // Imprime com uma casa decimal
  Serial.print(" %\t|");
  Serial.print(" Temperatura:  ");
  Serial.print(t, 1); // Imprime com uma casa decimal
  Serial.print(" °C\t |");
  Serial.print(" Heat Index (F):  ");
  Serial.print(hif, 1); // Imprime com uma casa decimal
  Serial.print(" °F\t |");
  Serial.print(" Heat Index (C):  ");
  Serial.print(hic, 1); // Imprime com uma casa decimal
  Serial.println(" °C |");

  }
//Leitura dos botões
  up = digitalRead(ButtonUp);
  down = digitalRead(ButtonDown);
  enter = digitalRead(ButtonEnter);
  back = digitalRead(ButtonBack);

//Tela Inicial

//---------------------------------------------------------
if(down == 0 && StateDown == 1)// Verifica se o botão de mover para baixo está pressionado
{
    count++;
 if (count > 4){ //Verifica se o valor da contagem é maior que 4 (faz relação ao número de telas)
  count = 4;
}
StateDown = 0; //Atualiza o botão para 0
EnableLCD = 1; // Atribui 1 para permitir que a imagem da tela seja apresentada uma única vez
}

if (down == 1 && StateDown == 0)//Verifica se ButtonDown não está pressionado
{
  StateDown = 1;
}
//---------------------------------------------------------

if(up == 0 &&StateUp == 1)//Verifica se o Botão para cima está acionado
{
  count--; //decrementa o valor da contagem
  
    if(count <1) // se count for menor que 1, ele receberá valor 1
  { 
    count = 1;
  }
  StateUp = 0;
  EnableLCD = 1;
}
  
  if(up == 1 && StateUp == 0)
  {
    StateUp = 1;
}
//---------------------------------------------------------


//---------------------------------------------------------
if(EnableLCD == 1)
{
  if(count ==1)
{
    screen1();
    delay(250);
}
  if(count ==2)
{
    screen2();
    delay(250);
    
}
  if(count ==3)
{
    screen3();
    delay(250);
}
  if(count ==4)
{
    screen4();
    delay(250);
}
EnableLCD = 0;
  }
//-----------------------------------------------------------

 float h = dht.readHumidity();
 float t = dht.readTemperature();// Celsius é o padrão
 float f = dht.readTemperature(true);// lê em Fahrenheit

  if (isnan(h) || isnan(t) || isnan(f)){ // Para se alguma leitura falhar, ele fazer a leitura novamente
  Serial.println("Leitura do sensor DHT falhou");
  return; 
}

float hif = dht.computeHeatIndex(f, h); // temperatura em F
float hic = dht.computeHeatIndex(t, h, false);// temperatura em C

if(enter == 0 && StateEnterControl == 1) // Verifica se o botão Enter está pressionado
{
digitalWrite(Buzzer,HIGH);
delay(50);
digitalWrite(Buzzer,LOW);
  if(count == 1) // Verifica o valor da variável contagem
  {

 lcd.clear();
 lcd.setCursor(4,0);
 lcd.write(byte(0));
 lcd.print(t);
 lcd.write(byte(2));
 lcd.print("C  ");
 lcd.setCursor(4,1);
 lcd.write(byte(1));
 lcd.print(h);
 lcd.print("%");
 lcd.setCursor(0,0);

  delay(2000);
  screen1();
  }

  if(count == 2)
  {
 StateLed1= !StateLed1;
 digitalWrite(Led1,StateLed1);
  }

  
  if(count == 3)
  {
 StateLed1= !StateLed1;
 digitalWrite(Led1,StateLed1);
  }
}
}