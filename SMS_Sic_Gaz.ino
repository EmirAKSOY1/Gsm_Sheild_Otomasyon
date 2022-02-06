#include <KapadokyaGSM.h>
KapadokyaGSM Kapadokya;
String smsMetni, smsNumarasi;
#define gonderilecekTelNumarasi  "+905426307649" 
#define LM35_pin A0
int ates_sensoru = 6;
int deger = 0;
int gaz_mesaj=0;
int ates_mesaj=0;
void setup() {
  Kapadokya.basla();
  pinMode(ates_sensoru, INPUT);
  pinMode(red,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(green,OUTPUT);
  delay(2000);
  Serial.begin(9600);
  delay(2000);
  Kapadokya.tumSmsSil();
  delay(2000);
  Kapadokya.smsGonder(gonderilecekTelNumarasi, "Sistem acildi.");
 }

void loop() {
  smsMetni = Kapadokya.smsOku(1);
  if (smsMetni.indexOf("OK") != -1) {
    if (smsMetni.length() > 7) {
      smsNumarasi = Kapadokya.numaraliSmsOku(1);
      smsMetni.toUpperCase();

      if (smsMetni.indexOf("HAVA KAC DERECE?") != -1) {

        String Sicaklik = String(analogRead(LM35_pin) * 0.48828125);
        String Sicaklik2 = "Hava " + Sicaklik + " derece.";
        char SicaklikSMS2[] = "";
        Sicaklik2.toCharArray(SicaklikSMS2, 30);

        Kapadokya.smsGonder(gonderilecekTelNumarasi, SicaklikSMS2);
      }
	  Kapadokya.tumSmsSil();
    }
   }

      int sensorValue = analogRead(A1);
      

      if(sensorValue > 700)
      {
        
        gaz_mesaj++;
        
        if(gaz_mesaj == 1)
        {
          
         Kapadokya.smsGonder(gonderilecekTelNumarasi, "Duman Var");
        }
        }
      else
      {
      gaz_mesaj=0;
     
      }
  deger = digitalRead(ates_sensoru);
  if (deger == 1)
  {
    ates_mesaj++;
    if(ates_mesaj==1)
    {
      Kapadokya.smsGonder(gonderilecekTelNumarasi,"Yangin Var");
    }
   
  }
  else
  {
    ates_mesaj=0; 
  }


  delay(500);
}
