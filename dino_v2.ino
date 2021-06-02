#include <Servo.h>
#define PULS  2
#define LED_NOTTE  3
Servo myservo;  // comunica al sistema che è presente un servo e viene chiamato myservo (ogni comando che inizia con "myservo" si riferice infatti a questo motore)
int pos = 0;    // variabile che definisce la posizione 
int general_button;
int r =20 ;
int temp=0;
int temp1=0;
int temp2=0;
long day_night_sensor;  // variabile che definisce una variabile che cambia del corso del processo operativo (fotoresistore per rilevare la presenza di giorno o notte)
long status1;  // variabile che cambia del corso del procersso operativo (fotoresistore per rilevare la presenza ostacoli)


void setup() {   
  myservo.attach(9);  // definisce per la libreria, il pin di uscita dell' informazione per il servo "myservo"
  Serial.begin(9600); // inizializza il monitor seriale da 9600 baud
  pinMode (PULS, INPUT);
  pinMode (LED_NOTTE, OUTPUT);
  }

void loop() { // tutto quello che è scritto di seguito sarà eseguito all'infinito
 day_night_sensor = analogRead(A0);// legge il valore, da 0 a 1023, del sensore notte-giorno
 status1 = analogRead(A1); 
 general_button = digitalRead (PULS);
 Serial.println(day_night_sensor);
  if (temp > 20){
   r = 5;
  } 
 
if (general_button == LOW) {
  
 if (day_night_sensor > 250  ){
  analogWrite (LED_NOTTE, 0); 
  for (temp2=0; temp1<1; temp1+=1){
   delay( 5);
   salta();
  }
  giorno(); // richiama il void giorno
 }
 
 else{  
  analogWrite (LED_NOTTE,70);
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
    for (pos = 20; pos >= 10 ; pos -= 1) { // gira l'albero del servo, dalla posizione 25°, in giù di 1 grado alla volta, ripete questa azione finche non si trova a un grado maggiore di 15
    myservo.write(pos);              // comunica al servo di posizionarsi all'angolo di partenza 'pos', di cui abbiamo cambiato il valore nella riga precedente
    delay(r);                    // il servo ha tempo 3 millisecondi per uscire dal ciclo for (molto reattivo), e quindi per arrivare a destinazione
    }
    for  (pos = 10; pos <= 20 ; pos += 1) { // gira l'albero del servo, dalla posizione 15°, in su di 1 grado alla volta, ripete questa azione finche non si trova a un grado minore di 25
    myservo.write(pos);              // comunica al servo di posizionarsi all'angolo di partenza 'pos', di cui abbiamo cambiato il valore nella riga precedente
    delay(35);}                       // il servo ha tempo 15 millisecondi per uscire dal ciclo for (decisamente meno reattivo dell'andata), e quindi per arrivare a destinazione           
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
  if (status1 > day_night_sensor+50){
   salta();
  }
}
