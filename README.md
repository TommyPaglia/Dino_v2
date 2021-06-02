DINO
Tommaso Pagliarani & Francesco Casalboni

PROGETTO BASATO SULLA PIATTAFORMA ARDUINO




Scienze e Tecnologie Applicate - Prof. F.Filomena
A.S.2020-2021 - ITT PASCAL - CESENA


DESCRIZIONE
Il progetto consiste in un robot in grado di captare e evitare gli ostacoli in movimento su dino (gioco del dinosauro di google chrome). È inoltre in grado di distinguere il giorno dalla notte cambiando le sue impostazioni in base alla luminosità dello schermo.
COMPONENTI HARDWARE


Componenti hardware usati in questo progetto:
-Fotoresistore x3
-Arduino Uno
-Servo motore
-Resistore da 5.1 kΩ x3
-resistore da 330Ω
-Switch
-LED blu
-Cavi MM / MF
È presente un fotoresistore per la visione ostacoli e uno per distinguere il giorno dalla notte. Entrambi con resistenza di pull down.
Problematiche riscontrata con l’hardware:
I fotoresistori inizialmente non davano valori corretti perchè collegati male e avevamo difficoltà a collegare cose il pull down.



COMPONENTI SOFTWARE

Il software ha richiesto diverso tempo per le tarature di luminosità e reattività.
In più sono state necessarie migliorie e patch per punti ciechi incremento di velocità del dinosauro




Sketch:
#include <Servo.h>
#define PULS  2
#define LED_NOTTE  3
Servo myservo;  // comunica al sistema che è presente un servo e viene chiamato myservo (ogni comando che inizia con "myservo" si riferisce infatti a questo motore)
int pos = 0; // variabile che definisce la posizione
int general_button; // definisce il pin di input dello switch
int r =20 ; //variabile reattività che parte con valore 20
int temp=0; // variabile per il conteggio dei primi 20 salti
int temp1=0; // variabile per il salto fra notte e giorno
int temp2=0; // variabile per il salto fra giorno e notte
long day_night_sensor;  // variabile che definisce una variabile che cambia del corso del processo operativo (fotoresistore per rilevare la presenza di giorno o notte)
long status1;  // variabile che cambia del corso del processo operativo (fotoresistore per rilevare la presenza ostacoli)
 
 
void setup() {  
  myservo.attach(9);  // definisce per la libreria, il pin di uscita dell' informazione per il servo "myservo"
  Serial.begin(9600); // inizializza il monitor seriale da 9600 baud
  pinMode (PULS, INPUT);
  pinMode (LED_NOTTE, OUTPUT);
  }
 
void loop() { // tutto quello che è scritto di seguito sarà eseguito all'infinito
 day_night_sensor = analogRead(A0);// legge il valore, da 0 a 1023, del sensore notte-giorno
 status1 = analogRead(A1); // legge il valore, da 0 a 1023, del sensore notte-giorno
 general_button = digitalRead (PULS);
 Serial.println(day_night_sensor); // scrive nel monitor seriale il valore del resistore giorno-notte
  if (temp > 20){ // diminuisce il valore della variabile “r” dopo 20 salti
   r = 5;
  }
 
if (general_button == LOW) {
 
 if (day_night_sensor > 250  ){ // se la luminosità è alta va in modalità giorno altrimenti in quella notte
  analogWrite (LED_NOTTE, 0); // spegne l’eventuale LED acceso
  for (temp2=0; temp1<1; temp1+=1){ // fa un alto “casuale” nei cambi di luminosità che altrimenti sarebbero momenti ciechi
   delay( 5);
   salta(); // richiama il void salta
  }
  giorno(); // richiama il void giorno
 }
 
 else{  
  analogWrite (LED_NOTTE,70); // accende il LED ad una luminosità contenuta
  for (temp1=0; temp2<1; temp2+=1){
   delay(5);
   salta();
  }          
  notte(); // richiama il void notte
 }  
}
 
}
 
void giorno(void){
  if (status1 < day_night_sensor-60){
    for (pos = 20; pos >= 10 ; pos -= 1) { // gira l'albero del servo, dalla posizione 20°, in giù di 1 grado alla volta, ripete questa azione finché non si trova a un grado maggiore di 10
    myservo.write(pos);  // comunica al servo di posizionarsi all'angolo di partenza 'pos', di cui abbiamo cambiato il valore nella riga precedente
    delay(r); // diminuisce il tempo che a disposizione del servo per arrivare a destinazione (prima 20 poi 5 ms)
    }
    for  (pos = 10; pos <= 20 ; pos += 1) { //torna indietro
    myservo.write(pos); // comunica al servo di posizionarsi all'angolo di partenza 'pos', di cui abbiamo cambiato il valore nella riga precedente
    delay(35);} // il servo ha tempo 35 millisecondi per uscire dal ciclo, abbastanza da non ingolfarlo        
    temp+=1;
  }
}
 
void salta (void){
  for (pos = 20; pos >= 10 ; pos -= 1) {
   myservo.write(pos);              
   delay(5);                      
  }
  for (pos = 10 ; pos <= 20 ; pos += 1) {
   myservo.write(pos);              
   delay(35);  
  }
}
 
void notte(void){
  if (status1 > day_night_sensor+50){ // salta se nota un ostacolo (più chiaro dello sfondo)
   salta();
  }
}




CONCLUSIONI


L’obiettivo del progetto è stato raggiunto anche se quando il gioco diventa più difficile e veloce capita che non salti qualche cactus.
