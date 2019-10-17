# LED-dimming
Selve koden som er viktig ligger i .ino-filen.

I dette prosjektet har vi to knapper og en LED.
Ved å holde inne en knapp i 1.5 sekunder vil LED slå seg sakte på. 
Når du holder den andre knappen inne i 1.5 sekunder vil LED slå seg av på samme måte som den slo seg på. 
Dette skjer fordi vi har en for-loop som øker en FADE-verdi som blir analogt sendt til LED.

Senere i prosjektet la jeg til support for en LCD-skjerm.
Denne er der bare for moro skyld og ikke nødvendig for å få koden til å fungere.
Dere som bare skal se på oppgaven trenger ikke denne. All kode som begynner på "lcd" kan ignoreres, 
og den øverste linjen som importerer LiquidCrystal-biblioteket kan fjernes.
Det denne gjør er å skrive ut som lyset er av eller på, og hva slags FADE-verdi den har. Ikke noe mer.
Det morsomme er at FADE-verdien oppdaterer seg på millisekundet.
Det vil si at under endringsprosessen av lyset til verdien skriver til skjermen for hver cycle den kjører gjennom.
Jeg ser for meg at denne kan være hjelpsom hvis lyset er i et annet rom der du ikke kan se om lyset er på eller ikke, så du sjekker skjermen istedenfor.

Prosjektet er skrevet i Visual Studio 2019 med "Arduino IDE"-utvidelsen. 
