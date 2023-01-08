#include "Wire.h"
#include "SparkFun_AS7265X.h"
#include <Adafruit_MLX90614.h>
#include <SPI.h>
#include <RTClib.h>
//#include <RH_RF95.h>
#include "Adafruit_TCS34725.h"
#include <Adafruit_BME280.h>
Adafruit_BME280 bmp;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
RTC_PCF8523 rtc;
#include <SD.h>
#define cardselect 13
File logfile;
#define TCAADDR 0x70
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}
/*void error (uint8_t errno) {
  while (1) {
    uint8_t i;
    for (i = 0; i < errno; i++) {
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
      delay(100);
    }
    for (i = errno; i < 10; i++) {
      delay(200);
      }
  }
}*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
AS7265X sensor;
int adr[8];
char dat0[] = "Triad, UP,SEN00,0000/00/00,00:00:00,0000000000,000000.00,000000.00,000000.00,000000.00,000000.00,000000.00,000000.00,000000.00,000000.00,000000.00,000000.00,000000.00,000000.00,000000.00,000000.00,000000.00,000000.00,000000.00\n";
char dat2[]= "BMP280, SEN00, BMP280 temp:00000000000, Pressure:00000000000, Elevation:0000000000, Humidity:00000000000 \n";
char dat3[] = "Thermal,SEN00, Ambient = 00.000000*C\tObject = 00.000000*C\n ";
char dat4[200] = "RGB, SEN00, R:00000000\tG:00000000\tB:00000000 \tC:00000000 \n";
char dat5[60] = "0000/00/00,00:00:00 \n";
int red,blue,green,col;
float hgInches = 30.00;
#define SEALEVELPRESSURE_HPA (hgInches/0.02952998751)
#define T xx//the I2C of triad sensor//
// standard Arduino setup()
////////////////////////////////////////////////////////////////////////////
void triad(int sel){
  tcaselect(sel);
  //digitalWrite(13, HIGH);

  sensor.takeMeasurements();
  
  String  a = String(sensor.getCalibratedA(), 2);
  String b = String(sensor.getCalibratedB(), 2);
  String c = String(sensor.getCalibratedC(), 2);
  String d = String(sensor.getCalibratedD(), 2);
  String e = String(sensor.getCalibratedE(), 2);
  String f = String(sensor.getCalibratedF(), 2);

  String g = String(sensor.getCalibratedG(), 2);
  String h = String(sensor.getCalibratedH(), 2);
  String i = String(sensor.getCalibratedR(), 2);
  String j = String(sensor.getCalibratedI(), 2);
  String k = String(sensor.getCalibratedS(), 2);
  String l = String(sensor.getCalibratedJ(), 2);

  String m = String(sensor.getCalibratedT(), 2);
  String n = String(sensor.getCalibratedU(), 2);
  String o = String(sensor.getCalibratedV(), 2);
  String p = String(sensor.getCalibratedW(), 2);
  String q = String(sensor.getCalibratedK(), 2);
  String r = String(sensor.getCalibratedL(), 2);
  
  char A[9]; char B[9]; char C[9]; char D[9]; char E[9]; char F[9];
  char G[9]; char H[9]; char I[9]; char J[9]; char K[9]; char L[9];
  char M[9]; char N[9]; char O[9]; char P[9]; char Q[9]; char R[9];
  
  a.toCharArray(A, 9); b.toCharArray(B, 9); c.toCharArray(C, 9); d.toCharArray(D, 9); e.toCharArray(E, 9); f.toCharArray(F, 9);
  g.toCharArray(G, 9); h.toCharArray(H, 9); i.toCharArray(I, 9); j.toCharArray(J, 9); k.toCharArray(K, 9); l.toCharArray(L, 9);
  m.toCharArray(M, 9); n.toCharArray(N, 9); o.toCharArray(O, 9); p.toCharArray(P, 9); q.toCharArray(Q, 9); r.toCharArray(R, 9);
  //IMPORTANT
  //edit this line every time you build a new sensor
  sprintf(dat0, "Triad, UP, SEN%u,%9s,%9s,%9s,%9s,%9s,%9s,%9s,%9s,%9s,%9s,%9s,%9s,%9s,%9s,%9s,%9s,%9s,%9s\n",/* now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second(), now.unixtime(),*/sel, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R);
  /*%04d/%02d/%02d,%02d:%02d:%02d,%010d,*/
  
  //Serial.println(sizeof(dat0));
  Serial.print(dat0);
  logfile.print(dat0);
}
void rgb(int sel){
  tcaselect(sel);
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);
  red=r;
  blue=b;
  green=g;
  col=c;
  sprintf(dat4,"RGB, SEN%u, R:%u\tG:%u\tB:%u\tC:%u\n",sel,red,green,blue,col);                  
  Serial.print(dat4);
  logfile.print(dat4);
}

void thermal(int sel){
  tcaselect(sel);
  //digitalWrite(13, HIGH);
  double A3=(mlx.readAmbientTempC());
  double B3= mlx.readObjectTempC();
  //char A[5];char B[5];
  sprintf(dat3,"Thermal,SEN%u, Ambient = %8f*C\tObject = %8f*C\n",sel,A3,B3);
  Serial.print(dat3);
  logfile.print(dat3);
}

void env(int sel){
   tcaselect(sel);
    float BMPt = (bmp.readTemperature());                               // read the temperature
    float BMPp = (bmp.readPressure() / 100.0F);                         // read the pressure
    float BMPa = (bmp.readAltitude(SEALEVELPRESSURE_HPA));  
    float BMPh = (bmp.readHumidity());
    sprintf(dat2,"BME280, SEN%u, BMP280 temp:%f, Pressure:%f, Elevation:%f, Humidity:%f \n",sel,BMPt,BMPp,BMPa,BMPh);
    Serial.print(dat2);
    logfile.print(dat2);
}












void setup()
{
Wire.begin();
Serial.begin(9600);
 /* while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }*/ // decomment if using serial
//pinMode(13, OUTPUT);
if (!SD.begin(cardselect)) {
   Serial.println("No SD Card");
   while(1);
  }
  Serial.println("SD OK");
if (!rtc.begin()) {
    Serial.println("No RTC");
  }
rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  rtc.start();
char filename[15];
strcpy(filename, "/ABC.TXT");
/*for (uint8_t i = 0; i < 100; i++) {
    filename[7] = '0' + i/10;
    filename[8] = '0' + i%10;
    // create if does not exist, do not open existing, write, sync after write
    if (! SD.exists(filename)) {
      break;
    }
  }*/
logfile = SD.open(filename, FILE_WRITE);


if (!logfile) {
  Serial.print("Couldn't create ");
  Serial.println(filename);
  //error(4);
}



Serial.print("Writing to ");
Serial.println(filename);

    for (int j=0;j<7;j++){
      adr[j]=0;
    }
    //while (!Serial); //decomment this line if using serial
    delay(1000);
    Serial.println("\nTCAScanner ready!");
    
    for (uint8_t t=0; t<8; t++) {
      tcaselect(t);
      Serial.print("TCA Port #"); Serial.println(t);

      for (uint8_t addr = 0; addr<=127; addr++) {
        if (addr == TCAADDR || addr == 104 ) continue;

        Wire.beginTransmission(addr);
        if (!Wire.endTransmission()) {
          Serial.print("Found I2C 0x");  Serial.println(addr,HEX);
          if (addr!=104){
          adr[t]=addr;}   
          bool status;
          delay(100);
          Serial.begin(9600);      
          if (mlx.begin()) {
          Serial.println("Found MLX990614 sensor");
          Serial.print("Emissivity = "); Serial.println(mlx.readEmissivity());
        };
         if (sensor.begin()==true) {
          Serial.println("Found AS7265X sensor");
          //sensor.disableIndicator();
        }
        if (tcs.begin()) {
          Serial.println("Found RGB sensor");
         } 
         if (bmp.begin(0x76)){
          Serial.println("Found BME sensor");
         }
      }
    }}
    for (int j=0;j<8;j++){
      Serial.print(adr[j]);
      Serial.print(",");
    }
    //pinMode(13,OUTPUT);
    //digitalWrite(13, LOW);
    Serial.print("/n");
    Serial.println("_____________________________ Code Begins _____________________________");}
   

  
  /*sensor.takeMeasurements(); //This is a hard wait while all 18 channels are measured

  Serial.print(sensor.getCalibratedA()); //410nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedB()); //435nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedC()); //460nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedD()); //485nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedE()); //510nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedF()); //535nm
  Serial.print(",");

  Serial.print(sensor.getCalibratedG()); //560nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedH()); //585nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedR()); //610nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedI()); //645nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedS()); //680nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedJ()); //705nm
  Serial.print(",");

  Serial.print(sensor.getCalibratedT()); //730nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedU()); //760nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedV()); //810nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedW()); //860nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedK()); //900nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedL()); //940nm
  Serial.print(",");

  Serial.println();*/
void loop() 
{
  DateTime x = rtc.now();
  sprintf(dat5,"%04d/%02d/%02d,%02d:%02d:%02d \n",x.year(),x.month(),x.day(),x.hour(),x.minute(),x.second());
  Serial.print(dat5);
  logfile.print(dat5);
  ///////////////////////////////////////////////////
  for (int i=0;i<8;i++){
    if (adr[i]==0){
      continue;
    }
    else if (adr[i]==90){
     thermal(i); 
    }
    else if (adr[i]==41){
      rgb(i);
    }
    else if (adr[i]==73){
      triad(i);
    }
    else if (adr[i]==118){
      env(i);
    }
    
  }  
  logfile.flush();
  delay(60000);
}
////////////////////////////////////////////////////////////////////////////
