//Kapadokya GSM Shield : http://bit.ly/GSMshield
//İnceleme ve proje videosu: https://youtu.be/zijlJ2-lzhg

#include <KapadokyaGSM.h>
KapadokyaGSM Kapadokya;
String smsMetni, smsNumarasi;
#define gonderilecekTelNumarasi  "+905426307649" // Numarayı değiştirmeyi unutmayın :) 
#define LM35_pin A0
const int AOUTpin=A3;  // Analog çıkış pini
const int DOUTpin=7;  //  Dijital çıkış pini
int ates_sensoru = 6;
int deger;
int esik;  // Eşik değeri
int ppm;  // Ölçülen CO ppm değeri
int gaz_mesaj=0;
int ates_mesaj=0;
void setup() {
  Kapadokya.basla();
  pinMode(DOUTpin, INPUT);
  pinMode(ates_sensoru, INPUT);
  delay(2000);
  Serial.begin(9600);
  delay(2000);
  Kapadokya.tumSmsSil();
  delay(2000);
  Serial.println("Sistem Calisiyor");
  Kapadokya.smsGonder(gonderilecekTelNumarasi, "Sistem acildi.");
}

void loop() {
  
  smsMetni = Kapadokya.smsOku(1);
  if (smsMetni.indexOf("OK") != -1) {
    if (smsMetni.length() > 7) {
      smsNumarasi = Kapadokya.numaraliSmsOku(1);
      Serial.println(smsNumarasi);
      smsMetni.toUpperCase();

      if (smsMetni.indexOf("HAVA KAC DERECE?") != -1) {
        Serial.println("Hava SMSi Geldi");
        String Sicaklik = String(analogRead(LM35_pin) * 0.48828125);
        String Sicaklik2 = "Hava " + Sicaklik + " derece.";
        char SicaklikSMS2[] = "";
        Sicaklik2.toCharArray(SicaklikSMS2, 30);
        Serial.println(SicaklikSMS2);
        Kapadokya.smsGonder(gonderilecekTelNumarasi, SicaklikSMS2);
      }
      else {
        Serial.println("Tanimsiz SMS............");
      }
      Kapadokya.tumSmsSil();
    }
  ppm= analogRead(AOUTpin);  // ppm değerini Analog pinden oku
  esik= digitalRead(DOUTpin);  // eşik değerinin aşılıp aşılmadığını oku
  Serial.print(" CO miktarı: ");  
  Serial.print(ppm);  //CO miktarını yaz
  Serial.print("ppm.");
  // Eşik değerinin aşılıp aşılmadığını kontrol et ve seri porta yaz
  if (esik == 1)
  {
    Serial.println("Eşik değerinin altında");
    gaz_mesaj=0;
  }
  else
  {
    gaz_mesaj++;
    if(gaz_mesaj==1)
    {
      Kapadokya.smsGonder(gonderilecekTelNumarasi,"Gaz Var");
    }
    Serial.println("Eşik değerinin üzerinde");
  }
  delay(500);  // Yarım saniye bekle
  }
  deger = digitalRead(ates_sensoru);
  if (deger == 1)
  {
    ates_mesaj++;
    if(ates_mesaj==1)
    {
      Kapadokya.smsGonder(gonderilecekTelNumarasi,"Yangın Var");
    }
   
  }
  else
  {
    ates_mesaj=0;
    
  }
  delay(500);
}
