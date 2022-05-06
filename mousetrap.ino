void setup() {
	// put your setup code here, to run once:
	pinMode(5,OUTPUT);
	pinMode(2,OUTPUT);
	digitalWrite(2, LOW);
	tone(5, 200);

	pinMode(11, OUTPUT);
	pinMode(12, INPUT);
	pinMode(13, OUTPUT);
	digitalWrite(11, LOW);
	digitalWrite(13, HIGH);

	Serial.begin(9600);
}

void loop() {
	// put your main code here, to run repeatedly:
	Serial.println(digitalRead(12));
	delay(1000);
}
