#include <SoftwareSerial.h>
#include <DS3231.h>
#include <EmonLib.h>
#include <ArduinoJson.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

SoftwareSerial ESPserial(5, 6); // RX | TX
EnergyMonitor emon1;             // Create an instance
DS3231 rtc(A4, A5);
Time t;
const byte CountKWh = 2;

float data_counter_menit;
float data_counter_jam;
float data_counter_hari;
float data_counter_bulan;
float data_counter_tahun;
float pulse_counter;
float pulse_counter_permenit;
float KWh;
float KWh_menit;
float KWh_total_menit;
float S_total_menit;
float P_total_menit;
float irms_total_menit;
float vrms_total_menit;
float cospi_total_menit;
float KWh_total_jam;
float S_total_jam;
float P_total_jam;
float irms_total_jam;
float vrms_total_jam;
float cospi_total_jam;
float KWh_total_hari;
float S_total_hari;
float P_total_hari;
float irms_total_hari;
float vrms_total_hari;
float cospi_total_hari;
float KWh_total_bulan;
float S_total_bulan;
float P_total_bulan;
float irms_total_bulan;
float vrms_total_bulan;
float cospi_total_bulan;
float KWh_total_tahun;
float S_total_tahun;
float P_total_tahun;
float irms_total_tahun;
float vrms_total_tahun;
float cospi_total_tahun;
float menit;
float menitt;
float jam;
float jamm;
float hari;
float harii;
float bulan;
float bulann;
float tahun;
float tahunn;
float detik;
float Average_KWh_satu_menit;
float Average_S_satu_menit;
float Average_P_satu_menit;
float Average_irms_satu_menit;
float Average_vrms_satu_menit;
float Average_cospi_satu_menit;
float Average_KWh_satu_jam;
float Average_S_satu_jam;
float Average_P_satu_jam;
float Average_irms_satu_jam;
float Average_vrms_satu_jam;
float Average_cospi_satu_jam;
float Average_KWh_satu_hari;
float Average_S_satu_hari;
float Average_P_satu_hari;
float Average_irms_satu_hari;
float Average_vrms_satu_hari;
float Average_cospi_satu_hari;
float Average_KWh_satu_bulan;
float Average_S_satu_bulan;
float Average_P_satu_bulan;
float Average_irms_satu_bulan;
float Average_vrms_satu_bulan;
float Average_cospi_satu_bulan;
float Average_KWh_satu_tahun;
float Average_S_satu_tahun;
float Average_P_satu_tahun;
float Average_irms_satu_tahun;
float Average_vrms_satu_tahun;
float Average_cospi_satu_tahun;
String waktu;
String tanggal;
int layar = 1;

DynamicJsonDocument DataBase(256);
//DynamicJsonDocument DataBase_permenit(256);
////DynamicJsonDocument DataBase_perjam(256);
//DynamicJsonDocument DataBase_perhari(256);
//DynamicJsonDocument DataBase_perbulan(256);
//DynamicJsonDocument DataBase_pertahun(256);

void setup() {
  Serial.begin(9600);
  ESPserial.begin(9600);
  rtc.begin();

  // initialize the LCD
  lcd.begin();

  // Turn on the blacklight and print a message.
//  lcd.backlight();
//  lcd.print("Hello, world!");

  // The following lines can be uncommented to set the date and time
    rtc.setDate(31, 1, 2021);   //mensetting tanggal 07 april 2018
    rtc.setTime(22, 59, 00);     //menset jam 22:00:00
    rtc.setDOW(1);     //menset hari "Sabtu"

  t     = rtc.getTime();
  menit = float(t.min);
  jam   = float(t.hour);


  pinMode(CountKWh, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(CountKWh), countKWH, RISING);

  emon1.current(A0, 15);       // Current: input pin, calibration.
  emon1.voltage(A1, 635, 1.7);  // Voltage: input pin, calibration, phase_shift

}


void loop() {
  
  t     = rtc.getTime();
  menitt = float(t.min);
  jamm   = float(t.hour);
  harii  = float(t.date);
  bulann = float(t.mon);
  tahunn = float(t.year);
  emon1.calcVI(20, 2000);        // Calculate all. No.of half wavelengths (crossings), time-out
  float realPower       = emon1.realPower;        //extract Real Power into variable
  float apparentPower   = emon1.apparentPower;    //extract Apparent Power into variable
  float powerFactor     = emon1.powerFactor;      //extract Power Factor into Variable
  float Vrms            = emon1.Vrms;             //extract Vrms into Variable
  float Irms            = emon1.Irms;             //extract Irms into Variable
  DataBase["t"]  = harii;
  DataBase["b"]  = bulann;
  DataBase["th"]  = tahunn;
  DataBase["j"]  = jamm;
  DataBase["m"]  = menitt;
  DataBase["S"]      = apparentPower;
  DataBase["P"]      = realPower;
  DataBase["cospi"]  = powerFactor;
  DataBase["Vrms"]   = Vrms;
  DataBase["Irms"]   = Irms;
  DataBase["KWh"]    = KWh;

//  DataBase["S m"]         = 0;
//  DataBase["P m"]         = 0;
//  DataBase["cospi m"]     = 0;
//  DataBase["Vrms m"]      = 0;
//  DataBase["Irms m"]      = 0;
//  DataBase["PKWh m"]      = 0;
//
//  DataBase["S j"]         = 0;
//  DataBase["P j"]         = 0;
//  DataBase["cospi j"]     = 0;
//  DataBase["Vrms j"]      = 0;
//  DataBase["Irms j"]      = 0;
//  DataBase["PKWh j"]      = 0;
//
//  DataBase["S hi"]         = 0;
//  DataBase["P h"]         = 0;
//  DataBase["cospi h"]     = 0;
//  DataBase["Vrms h"]      = 0;
//  DataBase["Irms h"]      = 0;
//  DataBase["PKWh h"]      = 0;
//
  DataBase["S b"]         = 0;
  DataBase["P b"]         = 0;
  DataBase["cospi b"]     = 0;
  DataBase["Vrms b"]      = 0;
  DataBase["Irms b"]      = 0;
  DataBase["KWh b"]      = 0;
//
//  DataBase["S t"]         = 0;
//  DataBase["P t"]         = 0;
//  DataBase["cospi t"]     = 0;
//  DataBase["Vrms t"]      = 0;
//  DataBase["Irms t"]      = 0;
//  DataBase["PKWh t"]      = 0;

  KWh_total_menit          += KWh_menit;
  S_total_menit            += apparentPower;
  P_total_menit            += realPower;
  irms_total_menit         += Irms;
  vrms_total_menit         += Vrms;
  cospi_total_menit        += powerFactor;
  data_counter_menit++;

  if (t.min != menit) {
    Akumulasi_permenit();
    //    Serial.print("Average konsumsi KWh satu menit: ");
    //    Serial.println(Average_KWh_satu_menit);
    pulse_counter_permenit = 0;
    data_counter_menit  = 0;
    KWh_total_menit     = 0;
    S_total_menit       = 0;
    P_total_menit       = 0;
    irms_total_menit    = 0;
    vrms_total_menit    = 0;
    cospi_total_menit   = 0;
    KWh_menit           = 0;
    //    Serial.print("Akumulasi per-menit: ");
//    serializeJson(DataBase_permenit, ESPserial);
    //    Serial.println("");
    data_counter_jam++;

  }

  if (t.hour != jam) {
    Akumulasi_perjam();
    //    Serial.print("Average konsumsi KWh per-menit dalam satu jam: ");
    //    Serial.println(Average_KWh_satu_jam);
    data_counter_jam  = 0;
    KWh_total_jam     = 0;
    S_total_jam       = 0;
    P_total_jam       = 0;
    irms_total_jam    = 0;
    vrms_total_jam    = 0;
    cospi_total_jam   = 0;
    //    Serial.print("Akumulasi per-jam: ");
//    serializeJson(DataBase_perjam, ESPserial);
    //    Serial.println("");
    data_counter_hari++;

  }

  if (t.date != hari) {
    Akumulasi_perhari();
    //    Serial.print("Average konsumsi KWh per-jam dalam satu hari: ");
    //    Serial.println(Average_KWh_satu_hari);
    data_counter_hari = 0;
    KWh_total_hari    = 0;
    S_total_hari      = 0;
    P_total_hari      = 0;
    irms_total_hari   = 0;
    vrms_total_hari   = 0;
    cospi_total_hari  = 0;
    //    Serial.print("Akumulasi per-hari: ");
//    serializeJson(DataBase_perhari, ESPserial);
    //    Serial.println("");
    data_counter_bulan++;

  }

  if (t.mon != bulan) {
    Akumulasi_perbulan();
    //    Serial.print("Average konsumsi KWh per-hari dalam satu bulan: ");
    //    Serial.println(Average_KWh_satu_bulan);
    data_counter_bulan  = 0;
    KWh_total_bulan     = 0;
    S_total_bulan       = 0;
    P_total_bulan       = 0;
    irms_total_bulan    = 0;
    vrms_total_bulan    = 0;
    cospi_total_bulan   = 0;
    //    Serial.print("Akumulasi per-bulan: ");
//    serializeJson(DataBase_perbulan, ESPserial);
    //    Serial.println("");
    data_counter_tahun++;

  }
//
//  if (t.year != tahun && menit > 30) {
//    Akumulasi_pertahun();
//    //    Serial.print("Average konsumsi KWh per-bulan salam satu tahun: ");
//    //    Serial.println(Average_KWh_satu_tahun);
//    data_counter_tahun  = 0;
//    KWh_total_tahun     = 0;
//    S_total_tahun       = 0;
//    P_total_tahun       = 0;
//    irms_total_tahun    = 0;
//    vrms_total_tahun    = 0;
//    cospi_total_tahun   = 0;
//    //    Serial.print("Akumulasi per-tahun: ");
////    serializeJson(DataBase_pertahun, ESPserial);
//    //    Serial.println("");
//
//  }

//  DataBase["S"]      = apparentPower;
//  DataBase["P"]      = realPower;
//  DataBase["cospi"]  = powerFactor;
//  DataBase["Vrms"]   = Vrms;
//  DataBase["Irms"]   = Irms;
//  DataBase["KWh"]    = KWh;

  serializeJson(DataBase, ESPserial);
  serializeJson(DataBase, Serial);
  DataBase.clear();
  //  Serial.println(t.sec);
  Serial.println("");

  // kondisi satu
  if(layar == 1) {
    lcd.clear();
    lcd.setCursor(0,0);                      // untuk menampilkan karakter dari kolom 0 dan baris 1
    lcd.print("V:" + String(Vrms));       // untuk menampilkan tulisan di lcd
  
    lcd.setCursor(9,0); 
    lcd.print("I:" + String(Irms));       // untuk menampilkan tulisan di lcd

    lcd.setCursor(0,1); 
    lcd.print("S:" + String(apparentPower));       // untuk menampilkan tulisan di lcd
  
    lcd.setCursor(9,1); 
    lcd.print("P:" + String(realPower));       // untuk menampilkan tulisan di lcd
    
  }

  // kondisi dua
  if(layar == 2) {
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("S:" + String(apparentPower));       // untuk menampilkan tulisan di lcd
  
    lcd.setCursor(9,0); 
    lcd.print("P:" + String(realPower));       // untuk menampilkan tulisan di lcd

    lcd.setCursor(0,1); 
    lcd.print("PF:" + String(powerFactor));       // untuk menampilkan tulisan di lcd
  
    lcd.setCursor(9,1); 
    lcd.print("C:" + String(KWh));       // untuk menampilkan tulisan di lcd
    
  }

  // kondisi tiga
  if(layar == 3) {
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("PF:" + String(powerFactor));       // untuk menampilkan tulisan di lcd
  
    lcd.setCursor(9,0); 
    lcd.print("C:" + String(KWh));       // untuk menampilkan tulisan di lcd
    
    lcd.setCursor(0,1);                      // untuk menampilkan karakter dari kolom 0 dan baris 1
    lcd.print("V:" + String(Vrms));       // untuk menampilkan tulisan di lcd
  
    lcd.setCursor(9,1); 
    lcd.print("I:" + String(Irms));       // untuk menampilkan tulisan di lcd

    layar = 0;
    
  }

  layar++;

  delay(2500);
//  lcd.scrollDisplayLeft ();           // untuk menampilkan tulisan berjalan dari arah kanan
//  delay (1000);                                // delay saat tulisan berjalan
//  lcd.clear ();            

}

void countKWH() {
  pulse_counter++;
  pulse_counter_permenit++;
  KWh = pulse_counter * 0.0005;
  KWh_menit = pulse_counter_permenit * 0.0005;

}


void Akumulasi_permenit() {

  Average_KWh_satu_menit                          = KWh_total_menit / data_counter_menit;
  Average_S_satu_menit                            = S_total_menit / data_counter_menit;
  Average_P_satu_menit                            = P_total_menit / data_counter_menit;
  Average_irms_satu_menit                         = irms_total_menit / data_counter_menit;
  Average_vrms_satu_menit                         = vrms_total_menit / data_counter_menit;
  Average_cospi_satu_menit                        = cospi_total_menit / data_counter_menit;
  menit                                           = float(t.min);
  //  DataBase["Waktu"]                               = rtc.getTimeStr();
  //  DataBase["Tanggal"]                             = rtc.getDateStr();
//  DataBase["S m"]         = Average_S_satu_menit;
//  DataBase["P m"]         = Average_P_satu_menit;
//  DataBase["cospi m"]     = Average_cospi_satu_menit;
//  DataBase["Vrms m"]      = Average_vrms_satu_menit;
//  DataBase["Irms m"]      = Average_irms_satu_menit;
//  DataBase["PKWh m"]      = (String(Average_KWh_satu_menit) + "KWh");

  KWh_total_jam                                  += KWh_total_menit;
  S_total_jam                                    += Average_S_satu_menit;
  P_total_jam                                    += Average_P_satu_menit;
  irms_total_jam                                 += Average_irms_satu_menit;
  vrms_total_jam                                 += Average_vrms_satu_menit;
  cospi_total_jam                                += Average_cospi_satu_menit;
  data_counter_jam++;
}

void Akumulasi_perjam() {
  Average_KWh_satu_jam                        = KWh_total_jam / data_counter_jam;
  Average_S_satu_jam                          = S_total_jam / data_counter_jam;
  Average_P_satu_jam                          = P_total_jam / data_counter_jam;
  Average_irms_satu_jam                       = irms_total_jam / data_counter_jam;
  Average_vrms_satu_jam                       = vrms_total_jam / data_counter_jam;
  Average_cospi_satu_jam                      = cospi_total_jam / data_counter_jam;
  jam                                         = float(t.hour);;
  //  DataBase["Waktu"]                           = rtc.getTimeStr();
  //  DataBase["Tanggal"]                         = rtc.getDateStr();
//  DataBase["S j"]       = Average_S_satu_jam;
//  DataBase["P j"]       = Average_P_satu_jam;
//  DataBase["cospi j"]   = Average_cospi_satu_jam;
//  DataBase["Vrms j"]    = Average_vrms_satu_jam;
//  DataBase["Irms j"]    = Average_irms_satu_jam;
//  DataBase["KWh j"]     = (String(Average_KWh_satu_jam) + "KWh permenit dalam satu jam");

  KWh_total_hari                             += KWh_total_jam;
  S_total_hari                               += Average_S_satu_jam;
  P_total_hari                               += Average_P_satu_jam;
  irms_total_hari                            += Average_irms_satu_jam;
  vrms_total_hari                            += Average_vrms_satu_jam;
  cospi_total_hari                           += Average_cospi_satu_jam;
  data_counter_hari++;

}

void Akumulasi_perhari() {
  Average_KWh_satu_hari                        = KWh_total_hari / data_counter_hari;
  Average_S_satu_hari                          = S_total_hari / data_counter_hari;
  Average_P_satu_hari                          = P_total_hari / data_counter_hari;
  Average_irms_satu_hari                       = irms_total_hari / data_counter_hari;
  Average_vrms_satu_hari                       = vrms_total_hari / data_counter_hari;
  Average_cospi_satu_hari                      = cospi_total_hari / data_counter_hari;
  hari                                         = float(t.date);
  //  DataBase["Tanggal"]                          = rtc.getDateStr();
//  DataBase_perhari["S h"]       = Average_S_satu_hari;
//  DataBase_perhari["P h"]       = Average_P_satu_hari;
//  DataBase_perhari["cospi h"]   = Average_cospi_satu_hari;
//  DataBase_perhari["Vrms h"]    = Average_vrms_satu_hari;
//  DataBase_perhari["Irms h"]    = Average_irms_satu_hari;
//  DataBase_perhari["KWh h"]     = Average_KWh_satu_hari;

  KWh_total_bulan                             += KWh_total_hari;
  S_total_bulan                               += Average_S_satu_hari;
  P_total_bulan                               += Average_P_satu_hari;
  irms_total_bulan                            += Average_irms_satu_hari;
  vrms_total_bulan                            += Average_vrms_satu_hari;
  cospi_total_bulan                           += Average_cospi_satu_hari;
  data_counter_bulan++;

}

void Akumulasi_perbulan() {
  Average_KWh_satu_bulan                        = KWh_total_bulan / data_counter_bulan;
  Average_S_satu_bulan                          = S_total_bulan / data_counter_bulan;
  Average_P_satu_bulan                          = P_total_bulan / data_counter_bulan;
  Average_irms_satu_bulan                       = irms_total_bulan / data_counter_bulan;
  Average_vrms_satu_bulan                       = vrms_total_bulan / data_counter_bulan;
  Average_cospi_satu_bulan                      = cospi_total_bulan / data_counter_bulan;
  bulan                                         = float(t.mon);
  //  DataBase_perbulan["Bulan"]                    = t.mon;
  //  DataBase_perbulan["Tahun"]                    = t.year;
  DataBase["S b"]       = Average_S_satu_bulan;
  DataBase["P b"]       = Average_P_satu_bulan;
  DataBase["cospi b"]   = Average_cospi_satu_bulan;
  DataBase["Vrms b"]    = Average_vrms_satu_bulan;
  DataBase["Irms b"]    = Average_irms_satu_bulan;
  DataBase["KWh b"]     = Average_KWh_satu_bulan;

  KWh_total_tahun                              += KWh_total_bulan;
  S_total_tahun                                += Average_S_satu_bulan;
  P_total_tahun                                += Average_P_satu_bulan;
  irms_total_tahun                             += Average_irms_satu_bulan;
  vrms_total_tahun                             += Average_vrms_satu_bulan;
  cospi_total_tahun                            += Average_cospi_satu_bulan;
  data_counter_tahun++;

}

//void Akumulasi_pertahun() {
//  Average_KWh_satu_tahun                        = KWh_total_tahun / data_counter_tahun;
//  Average_S_satu_tahun                          = S_total_tahun / data_counter_tahun;
//  Average_P_satu_tahun                          = P_total_tahun / data_counter_tahun;
//  Average_irms_satu_tahun                       = irms_total_tahun / data_counter_tahun;
//  Average_vrms_satu_tahun                       = vrms_total_tahun / data_counter_tahun;
//  Average_cospi_satu_tahun                      = cospi_total_tahun / data_counter_tahun;
//  tahun                                         = float(t.year);
//  //  DataBase_pertahun["Tahun"]                    = t.year;
//  DataBase_pertahun["S t"]       = Average_S_satu_tahun;
//  DataBase_pertahun["P t"]       = Average_P_satu_tahun;
//  DataBase_pertahun["cospi t"]   = Average_cospi_satu_tahun;
//  DataBase_pertahun["Vrms t"]    = Average_vrms_satu_tahun;
//  DataBase_pertahun["Irms t"]    = Average_irms_satu_tahun;
//  DataBase_pertahun["KWh t"]     = Average_KWh_satu_tahun;
//
//}
