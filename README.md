PAD- Projekt
Gruppe 4

Ausgewählter Themenkreis: Themenkreis 1 – Auswertung von Sensor-Rohdaten
Projektvertreter: Clemens Holzer
Projektmitglieder: Andreas Haindl, Lukas Krenn


Erste Schritte:
Unsere ersten Schritte werden das implementieren und einrichten von Github sein. Danach werden wir uns um das Auslesen und Auswerten der Sensordaten kümmern. Wenn wir dies geschafft haben erstellen wir einen Suchalgorithmus um schnellstmöglich die notwendigen Daten aus dem Dokument zu suchen. Zwischendurch werden wir immer die Funktionalität des Programmes überprüfen.

Entwicklungsstufen:
-	Auswerten und Suchen von Sensordaten
-	Dynamische Speicherung der gesuchten Daten 
-	Ausgabe der Daten 
-	Implementierung der Funktionen in eine Library
-	Gestalten der Benutzeroberfläche
-	Korrektur der Letzen Fehler

Milestones:
-	21.5.2020 – Implementierung von Github
-	24.5.2020 – Auslesen & Suchen nach Zeitstempeln nach eingegeben Datum
-	30.5.2020 – Implementierung der 3 Funktionen der einzelnen Sensoren
-	03.6.2020 – Benutzeroberfläche Erstellen 
-	06.6.2020 – Testapplikation & Libraries erstellen 
-	08.6.2020 – Fehlerbehebungen und Korrekturen
-	08.6.2020 – Abgabe

Umsetzung:
Die Umsetzungorganisation erfolgt über Github.
Die Sensorauswertungen werden innerhalb der Gruppe aufgeteilt.
Zur Gruppeninternen Kommunikation werden Programme wie Whatsapp, Discord und MS-Teams verwendet. 
Kann ein Programmteil nicht alleine bewältigt werden, werden diese gemeinsam programmiert.
Die Daten werden als Struct dynamisch gespeichert.
Alle Auswertungen werden als Funktionen in Librarys implementiert, das Hauptprogramm besteht nur noch aus der Benutzeroberfläche und den Funktionsaufrufen.
Das Programm soll so effizient wie möglich programmiert werden. 





Programmfunktionen:

-	Menü zur Auswahl der auszugebenen Daten bei gewählter Zeit und Datums Angabe

Verfügbare Ausgaben:

-	XYZ- Koordinaten 
-	Temperatur 
-	Druck
-	Luftfeuchtigkeit
-	Uhrzeit

Verwendete Sensoren: 

-	HTS221 (Luftfeuchtigkeit und Temperatur)
-	LPS25HB (Druck)
-	LSM9DS1 (XYZ-Koordinaten)

Fehlermanagement:
-	Sensorausschläge sollen ignoriert werden
-	Datum und Uhrzeiteingabe muss vollständig sein und vorhanden sein


Allgemeine Funktionserklärung:

Das fertige Programm soll dem Benutzer die Möglichkeit geben, die Temperatur, den Druck, die Luftfeuchtigkeit oder den Standort zu einem Gewünschten Zeitpunkt/Zeitraum auszugeben. Dabei sollen die Fehler in der Sensordatei ignoriert werden, indem man diese mit den vorherigen und vorangehenden Sensorwerten vergleicht. Der Benutzer soll alles über ein Menü steuern können. 
Die Daten werden dabei nicht im gesamten gespeichert, sondern es werden nur die benötigten von dem Zeitpunkt/Zeitraum betroffenen Daten dynamisch abgespeichert. 


Use case:

Für die erfolgreiche Ausführung des Programmes und dessen Features wird eine Datei vorausgesetzt welche Sensordaten enthält vorausgesetzt. Diese Datei soll Sensordaten zur Temperatur, Luftfeuchtigkeit, Luftdruck zur XYZ Koordinate des Rasberry-Pi enthalten mit entsprechenden Zeitstemplel wann diese Daten aufgezeichnet wurden. Natürlich können nur Daten aufgerufen werden welche auch verfügbar sind, was bedeutet dass der Benutzer sich im klaren ist das er keinen Daten aus der Zukunft aufrufen kann. Das Programm kann dazu genutzt werden um in der Agrarwirtschaft die Umweltfaktoren für das ideale Pflanzenwachstum zu überwachen.

