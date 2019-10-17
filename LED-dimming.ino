// Alle CONST-variabler endrer seg aldri i koden
const int lightsON = 12;					// LightsON er satt til pinne 12
const int lightsOFF = 4;					// LightsOFF er satt til pinne 4
const int led = 10;							// LED er satt til pinne 10 som støtter PWM
const int fadingDelay = 20;					// Bestemmer hvor lang tid det tar mellom hver for-loop i dimmeprosessen (målt i ms)

unsigned long lightsONPushedMillis;			// Blir brukt til å telle hvor mange ms lightsON er aktivert
unsigned long lightsOFFPushedMillis;		// Blir brukt til å telle hvor mange ms lightsOFF er aktivert
unsigned long turnOnDelay = 1000;			// Bestemmer hvor mange ms lightsON må holdes inne for at lysstyrken skal økes
unsigned long turnOffDelay = 1000;			// Bestemmer hvor mange ms lightsOFF må holdes inne for at lysstyrken skal minskes

// Variabler som kommer til å endre seg
int lightsONState = 0;						// Blir brukt til å lese og lagre lightsON-state
int lightsOFFState = 0;						// Blir brukt til å lese og lagre lightsOFF-state
boolean ledState = false;					// Minne for om LED er på eller av

void setup() {
	pinMode(led, OUTPUT);					// LED er satt som OUTPUT
	pinMode(lightsON, INPUT_PULLUP);		// LightsON er satt som INPUT_PULLUP
	pinMode(lightsOFF, INPUT_PULLUP);		// LightsOFF er satt som INPUT_PULLUP
	digitalWrite(led, LOW);					// Tvinger LED av i starten
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
			if ((unsigned long)(currentMillis - lightsONPushedMillis) >= turnOnDelay) {		// Fortsetter bare hvis lengden av loopen - lengden av lightsONPushedMillis (målt i ms) er mer enn turnOnDelay (1 sek)
				for (int fade = 0; fade <= 255; fade += 5) {								// Kjører for-loopen helt til fade-verdien er større eller lik 255 (fullt på analogt)
					analogWrite(led, fade);													// Skriver gjeldene fade-verdi til LED
					delay(fadingDelay);														// Venter en liten stund før for-loopen restarter for å gi en fade-lignende økning av lysstyrke
				}
				ledState = !ledState;														// Gjør om ledState-verdien til det omvendte av det den var
			}
		}
	}

	if (lightsOFFState == LOW) {															// Siden lightsOFF er av typen INPUT_PULLUP må verdien være LOW for å fortsette
		if (ledState == true) {																// Fortsetter bare hvis fadingState er TRUE
			if ((unsigned long)(currentMillis - lightsOFFPushedMillis) >= turnOffDelay) {	// Fortsetter bare hvis lengden av loopen - lengden av lightsOFFPushedMillis (målt i ms) er mer enn turnOffDelay (1 sek)
				for (int fade = 255; fade >= 0; fade -= 5) {								// Kjører for-loopen helt til fade-verdien er mindre eller lik 0 (minst på analogt)
					analogWrite(led, fade);													// Skriver gjeldene fade-verdi til LED
					delay(fadingDelay);														// Venter en liten stund før for-loopen restarter for å gi en fade-lignende dimming av lysstyrke
				}
				ledState = !ledState;														// Gjør om ledState-verdien til det omvendte av det den var
			}
		}
	}
}