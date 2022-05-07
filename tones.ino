/***************************
COPYRIGHT LESTER COVEY (me@lestercovey.ml),
2022

***************************/

void greetingTone() {
	tone(PIN_BUZZER_OUT, 420);
	delay(60);
	tone(PIN_BUZZER_OUT, 400);
	delay(60);
	tone(PIN_BUZZER_OUT, 620);
	delay(60);
	tone(PIN_BUZZER_OUT, 600);
	delay(60);
	tone(PIN_BUZZER_OUT, 520);
	delay(60);
	tone(PIN_BUZZER_OUT, 500);
	delay(60);
	noTone(PIN_BUZZER_OUT);
	delay(200);
	tone(PIN_BUZZER_OUT, 510);
	delay(100);
	noTone(PIN_BUZZER_OUT);
}

void alertTone(bool high) {
	tone(PIN_BUZZER_OUT, high ? ALERT_TONE_HIGH : ALERT_TONE_LOW);
}

void quickTone(int pitch) {
	tone(PIN_BUZZER_OUT, pitch);
	delay(50);
	noTone(PIN_BUZZER_OUT);
}

void quickDoubleTone(int firstPitch, int secondPitch) {
	tone(PIN_BUZZER_OUT, firstPitch);
	delay(100);
	tone(PIN_BUZZER_OUT, secondPitch);
	delay(100);
	noTone(PIN_BUZZER_OUT);
}

void longTone(int pitch) {
	tone(PIN_BUZZER_OUT, pitch);
	delay(1000);
	noTone(PIN_BUZZER_OUT);
}

void longTripleTone(int firstPitch, int secondPitch, int thirdPitch) {
	tone(PIN_BUZZER_OUT, firstPitch);
	delay(200);
	tone(PIN_BUZZER_OUT, secondPitch);
	delay(200);
	tone(PIN_BUZZER_OUT, thirdPitch);
	delay(200);
	noTone(PIN_BUZZER_OUT);
}

void batteryLevelTone(uint8_t batteryLevel) {
	for (int i = 0; i < batteryLevel; ++i) {
		quickTone(200);
		delay(500);
	}
}