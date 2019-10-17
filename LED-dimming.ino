// Alle CONST-variabler endrer seg aldri i koden
const int lightsON = 12;					// LightsON er satt til pinne 12
const int lightsOFF = 4;					// LightsOFF er satt til pinne 4
const int led = 10;							// LED er satt til pinne 10 som st�tter PWM
const int fadingDelay = 20;					// Bestemmer hvor lang tid det tar mellom hver for-loop i dimmeprosessen (m�lt i ms)

unsigned long lightsONPushedMillis;			// Blir brukt til � telle hvor mange ms lightsON er aktivert
unsigned long lightsOFFPushedMillis;		// Blir brukt til � telle hvor mange ms lightsOFF er aktivert
unsigned long turnOnDelay = 1000;			// Bestemmer hvor mange ms lightsON m� holdes inne for at lysstyrken skal �kes
unsigned long turnOffDelay = 1000;			// Bestemmer hvor mange ms lightsOFF m� holdes inne for at lysstyrken skal minskes

// Variabler som kommer til � endre seg
int lightsONState = 0;						// Blir brukt til � lese og lagre lightsON-state
int lightsOFFState = 0;						// Blir brukt til � lese og lagre lightsOFF-state
boolean ledState = false;					// Minne for om LED er p� eller av

void setup() {
	pinMode(led, OUTPUT);					// LED er satt som OUTPUT
	pinMode(lightsON, INPUT_PULLUP);		// LightsON er satt som INPUT_PULLUP
	pinMode(lightsOFF, INPUT_PULLUP);		// LightsOFF er satt som INPUT_PULLUP
	digitalWrite(led, LOW);					// Tvinger LED av i starten
}

void loop() {
	unsigned long currentMillis = millis();													// currentMillis blir brukt til � telle ms fra starten av denne loopen
	lightsONState = digitalRead(lightsON);													// Leser av lightsON-knapp og lagrer verdien i lightsONState
	lightsOFFState = digitalRead(lightsOFF);												// Leser av lightsOFF-knapp og lagrer verdien i lightsOFFState

	if (digitalRead(lightsON) == HIGH) {													// Hvis lightsON er aktivet
		lightsONPushedMillis = currentMillis;												// Tell hvor lenge lightsON er aktivert, og lagre verdien i lightsONPushedMillis
	}

	if (digitalRead(lightsOFF) == HIGH) {													// Hvis lightsOFF er aktivet
		lightsOFFPushedMillis = currentMillis;												// Tell hvor lenge lightsOFF er aktivert, og lagre verdien i lightsOFFPushedMillis
	}

	if (lightsONState == LOW) {																// Siden lightsON er av typen INPUT_PULLUP m� verdien v�re LOW for � fortsette
		if (ledState == false) {															// Fortsetter bare hvis fadingState er FALSE
			if ((unsigned long)(currentMillis - lightsONPushedMillis) >= turnOnDelay) {		// Fortsetter bare hvis lengden av loopen - lengden av lightsONPushedMillis (m�lt i ms) er mer enn turnOnDelay (1 sek)
				for (int fade = 0; fade <= 255; fade += 5) {								// Kj�rer for-loopen helt til fade-verdien er st�rre eller lik 255 (fullt p� analogt)
					analogWrite(led, fade);													// Skriver gjeldene fade-verdi til LED
					delay(fadingDelay);														// Venter en liten stund f�r for-loopen restarter for � gi en fade-lignende �kning av lysstyrke
				}
				ledState = !ledState;														// Gj�r om ledState-verdien til det omvendte av det den var
			}
		}
	}

	if (lightsOFFState == LOW) {															// Siden lightsOFF er av typen INPUT_PULLUP m� verdien v�re LOW for � fortsette
		if (ledState == true) {																// Fortsetter bare hvis fadingState er TRUE
			if ((unsigned long)(currentMillis - lightsOFFPushedMillis) >= turnOffDelay) {	// Fortsetter bare hvis lengden av loopen - lengden av lightsOFFPushedMillis (m�lt i ms) er mer enn turnOffDelay (1 sek)
				for (int fade = 255; fade >= 0; fade -= 5) {								// Kj�rer for-loopen helt til fade-verdien er mindre eller lik 0 (minst p� analogt)
					analogWrite(led, fade);													// Skriver gjeldene fade-verdi til LED
					delay(fadingDelay);														// Venter en liten stund f�r for-loopen restarter for � gi en fade-lignende dimming av lysstyrke
				}
				ledState = !ledState;														// Gj�r om ledState-verdien til det omvendte av det den var
			}
		}
	}
}