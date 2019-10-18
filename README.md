# LED-dimming
Selve koden i .ino-filen. For at LCD skal fungere trengs også LiquidDisplay.h under "__vm". 

I dette prosjektet har vi to knapper og en LED.
Ved å holde inne en knapp i 1.5 sekunder vil LED slå seg sakte på.
Dette skjer fordi vi i begynnelsen av loopen starter en counter.
Når vi aktiverer knappen vil den nåværende counteren legges i en variabel, og endres ikke før neste loop igjen.
Vi tar counteren vi startet i begynnelsen minus den verdien som ble satt til knappen.
Når vi kommer til en differanse på 1500ms eller mer vil lyset begynne å slå seg på.
Når du holder den andre knappen inne i 1.5 sekunder vil LED slå seg av på samme måte som den slo seg på. 
Dette skjer fordi vi har en for-loop som øker en FADE-verdi som blir analogt sendt til LED.

Senere i prosjektet la jeg til support for en LCD-skjerm.
Denne er der bare for moro skyld og ikke nødvendig for å få koden til å fungere.
Dere som bare skal se på oppgaven trenger ikke denne. All kode som begynner på "lcd" kan ignoreres, 
og den øverste linjen som importerer LiquidCrystal-biblioteket kan fjernes.
Det denne gjør er å skrive ut som lyset er av eller på, og hva slags FADE-verdi den har.
Jeg har også fått til å printe en counter for hvor lenge knappene har blitt holdt inne.
Denne counteren fjernes automatisk hvis knappene ikke har blitt holdt lenge nok.
Det er bare litt tilleggsinformasjon som kan være morsomt å ha.
Det morsomme er at FADE-verdien oppdaterer seg på millisekundet.
Det vil si at under endringsprosessen av lyset vil verdien bli skrevet til skjermen hver gang loopen starter på nytt.
Jeg ser for meg at denne kan være hjelpsom hvis lyset er i et annet rom der du ikke kan se om lyset er på eller ikke, 
så du sjekker skjermen istedenfor.

Prosjektet er skrevet i Visual Studio 2019 med "Arduino IDE"-utvidelsen. Koden kan kopieres fra .ino-filen til Arduino CC for de som bruker det.
