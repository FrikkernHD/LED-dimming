	
#include <LiquidCrystal.h>											// Inkluder LiquidCrystal-biblioteket for support for LCD

// Alle CONST-variabler endrer seg aldri i koden
const int lightsON = 8;												// LightsON er satt til pinne 8
const int lightsOFF = 7;											// LightsOFF er satt til pinne 7
const int led = 10;													// LED er satt til pinne 10 som støtter PWM
const int fadingDelay = 20;											// Bestemmer hvor lang tid det tar mellom hver for-loop i dimmeprosessen (målt i ms)
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2, v0 = 6;	// Alle pinnene på Arduino-en definert her er til bruk på LCD
const int contrast = 20;											// Bestemmer hvor høy kontrasten til LCD skal være
unsigned long turnOnDelay = 1500;									// Bestemmer hvor mange ms lightsON må holdes inne for at lysstyrken skal økes
unsigned long turnOffDelay = 1500;									// Bestemmer hvor mange ms lightsOFF må holdes inne for at lysstyrken skal minskes
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);							// Definerer at alle pinnene som sdkal brukes av LCD kan brukes av LiquidCrystal-biblioteket

// Variabler som kommer til å endre seg
unsigned long lightsONPushedMillis;									// Blir brukt til å telle hvor mange ms lightsON er aktivert
unsigned long lightsOFFPushedMillis;								// Blir brukt til å telle hvor mange ms lightsOFF er aktivert
double counter;
int lightsONState = 0;												// Blir brukt til å lese og lagre lightsON-state
int lightsOFFState = 0;												// Blir brukt til å lese og lagre lightsOFF-state
boolean ledState = false;											// Minne for om LED er på eller av

void setup() {
	pinMode(led, OUTPUT);											// LED er satt som OUTPUT
	pinMode(lightsON, INPUT_PULLUP);								// LightsON er satt som INPUT_PULLUP
	pinMode(lightsOFF, INPUT_PULLUP);								// LightsOFF er satt som INPUT_PULLUP
	digitalWrite(led, LOW);											// Tvinger LED av i starten
	digitalWrite(13, LOW);											// Slår av inkludert LED
	analogWrite(v0, contrast);										// Skriver CONTRAST til V0 på LCD. Tillater oss å ikke bruke en potensiometer

	lcd.clear();													// Tømmer LCD for å ikke ha noen rare glitcher
	lcd.begin(16, 2);												// Definerer hvor mange rader og kolonner LCD har
	lcd.setCursor(0, 0);
	lcd.print("LED is off!");										// Siden LED alltid er slått av i starten kan vi statisk skrive at LED er av
	lcd.setCursor(0, 1);
	lcd.print("FADE-value: 0");										// Skriver at FADE-verdien er 0. Den vil alltid være dette når den starter
}

void loop() {
	unsigned long currentMillis = millis();													// currentMillis blir brukt til å telle ms fra starten av denne loopen
	lightsONState = digitalRead(lightsON);													// Leser av lightsON-knapp og lagrer verdien i lightsONState
	lightsOFFState = digitalRead(lightsOFF);												// Leser av lightsOFF-knapp og lagrer verdien i lightsOFFState

	if (digitalRead(lightsON) == HIGH) {													// Hvis lightsON er aktivet
		lightsONPushedMillis = currentMillis;												// Tell hvor lenge lightsON er aktivert, og lagre verdien i lightsONPushedMillis
	}

	if (digitalRead(lightsOFF) == HIGH) {													// Hvis lightsOFF er aktivet
		lightsOFFPushedMillis = currentMillis;												// Tell hvor lenge lightsOFF er aktivert, og lagre verdien i lightsOFFPushedMillis
	}

	if (lightsONState == LOW) {																// Siden lightsON er av typen INPUT_PULLUP må verdien være LOW for å fortsette
		if (ledState == false) {															// Fortsetter bare hvis fadingState er FALSE
			counter = (currentMillis - lightsONPushedMillis);								// Lagrer antall ms lightsON er aktivert i COUNTER
			counter = counter / 1000;														// Endrer COUNTER fra ms til sekunder
			counter = round(counter * 10.0) / 10.0;											// Runder av COUNTER til bare en desimal
			lcd.clear();
			lcd.setCursor(0, 0);
			lcd.print("Counting...");
			lcd.setCursor(0, 1);
			lcd.print("Seconds: ");
			lcd.setCursor(9, 1);
			lcd.print(counter, 1);															// Skriver antall sekunder lightsON er aktivert til LCD
			delay(100);																		// Smoother ut printout til LCD

			if (digitalRead(lightsON) == HIGH) {											// Hvis lightsON slippes under tellingen vil telleren bli borte og gammel tekst vil komme tilbake
				lcd.clear();
				lcd.setCursor(0, 0);
				lcd.print("LED is off!");
				lcd.setCursor(0, 1);
				lcd.print("FADE-value: 0");
			}

			if ((unsigned long)(currentMillis - lightsONPushedMillis) >= turnOnDelay) {		// Fortsetter bare hvis lengden av loopen - lengden av lightsONPushedMillis (målt i ms) er mer enn turnOnDelay (1 sek)
				for (int fade = 0; fade <= 255; fade += 5) {								// Kjører for-loopen helt til fade-verdien er større eller lik 255 (fullt på analogt)
					lcd.clear();
					lcd.setCursor(0, 0);
					lcd.print("Turning on LED!");											// Denne kjører bare når lightsON er aktivert, og sier at LED skrur seg på					
					lcd.setCursor(0, 1);
					lcd.print("FADE-value: ");
					lcd.setCursor(12, 1);
					lcd.print(fade);														// Printer FADE-verdi til LCD
					analogWrite(led, fade);													// Skriver gjeldene fade-verdi til LED
					delay(fadingDelay);														// Venter en liten stund før for-loopen restarter for å gi en fade-lignende økning av lysstyrke
				}
				ledState = !ledState;														// Gjør om ledState-verdien til det omvendte av det den var
				counter = 0;																// Resetter COUNTER til null
				lcd.clear();																// Tømmer LCD for å ikke ha noen rare glitcher
				lcd.setCursor(0, 0);
				lcd.print("LED is on!");													// Skriver at LED er på. Beskjeden vil holde seg på skjermen til LED slår seg av igjen
				lcd.setCursor(0, 1);
				lcd.print("FADE-value: 255");												// Skriver at FADE-verdien er 255. Den vil alltid være dette etter denne loopen er kjørt
			}
		}
	}

	if (lightsOFFState == LOW) {															// Siden lightsOFF er av typen INPUT_PULLUP må verdien være LOW for å fortsette
		if (ledState == true) {																// Fortsetter bare hvis fadingState er TRUE
			counter = (currentMillis - lightsOFFPushedMillis);								// Lagrer antall ms lightsON er aktivert i COUNTER
			counter = counter / 1000;														// Endrer COUNTER fra ms til sekunder
			counter = round(counter * 10.0) / 10.0;											// Runder av COUNTER til bare en desimal
			lcd.clear();
			lcd.setCursor(0, 0);
			lcd.print("Counting...");
			lcd.setCursor(0, 1);
			lcd.print("Seconds: ");
			lcd.setCursor(9, 1);
			lcd.print(counter, 1);															// Skriver antall sekunder lightsON er aktivert til LCD
			delay(100);																		// Smoother ut printout til LCD

			if (digitalRead(lightsOFF) == HIGH) {											// Hvis lightsOFF slippes under tellingen vil telleren bli borte og gammel tekst vil komme tilbake
				lcd.clear();
				lcd.setCursor(0, 0);
				lcd.print("LED is on!");
				lcd.setCursor(0, 1);
				lcd.print("FADE-value: 255");
			}

			if ((unsigned long)(currentMillis - lightsOFFPushedMillis) >= turnOffDelay) {	// Fortsetter bare hvis lengden av loopen - lengden av lightsOFFPushedMillis (målt i ms) er mer enn turnOffDelay (1 sek)
				for (int fade = 255; fade >= 0; fade -= 5) {								// Kjører for-loopen helt til fade-verdien er mindre eller lik 0 (minst på analogt)
					lcd.clear();
					lcd.setCursor(0, 0);
					lcd.print("Turning off LED!");											// Denne kjører bare når lightsOFF er aktivert, og sier at LED skrur seg av
					lcd.setCursor(0, 1);
					lcd.print("FADE-value: ");	
					lcd.setCursor(12, 1);
					lcd.print(fade);														// Printer FADE-verdi til LCD
					analogWrite(led, fade);													// Skriver gjeldene fade-verdi til LED
					delay(fadingDelay);														// Venter en liten stund før for-loopen restarter for å gi en fade-lignende dimming av lysstyrke
				}
				ledState = !ledState;														// Gjør om ledState-verdien til det omvendte av det den var
				counter = 0;																// Resetter COUNTER til null
				lcd.clear();																// Tømmer LCD for å ikke ha noen rare glitcher
				lcd.setCursor(0, 0);
				lcd.print("LED is off!");													// Skriver at LED er av. Beskjeden vil holde seg på skjermen til LED slår seg på igjen
				lcd.setCursor(0, 1);
				lcd.print("FADE-value: 0");													// Skriver at FADE-verdien er 0. Den vil alltid være dette etter denne loopen er kjørt
			}
		}
	}
}