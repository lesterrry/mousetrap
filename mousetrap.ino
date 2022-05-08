/***************************
COPYRIGHT LESTER COVEY (me@lestercovey.ml),
2022

***************************/

#include <Battery_Shield.h>

// #define MOTION_DEBUG
// #define ITERATE_TONES

#define PIN_BUZZER_OUT A1
#define PIN_MOTION_OUT 13
#define PIN_MOTION_IN 12
#define PIN_MOTION_GND 11
#define ALERT_TONE_HIGH 1650
#define ALERT_TONE_LOW 650

enum State {
	Locked,
	Cooldown,
	ArmingLazy,
	ArmingNervous,
	Armed,
	Alert
};

Battery_Shield battery;
uint32_t timer;
uint32_t lastMotionTimer;
State currentState;
bool currentAlertToneIsHigh;

void setup() {
	pinMode(PIN_MOTION_GND, OUTPUT);
	pinMode(PIN_MOTION_IN, INPUT);
	pinMode(PIN_MOTION_OUT, OUTPUT);
	digitalWrite(PIN_MOTION_GND, LOW);
	digitalWrite(PIN_MOTION_OUT, HIGH);

	greetingTone();
	delay(2000);

	battery.begin(0.0128f);

	if (battery.getState() != CHARGING_IDLE) {
		longTripleTone(450, 500, 550);
	} else {
		int batteryLevel = battery.getLevel() / 10;
		if (batteryLevel == 0) {
			longTripleTone(550, 500, 450);
		} else {
			batteryLevelTone(batteryLevel);
		}
	}

	delay(2000);

	#ifdef MOTION_DEBUG
		Serial.begin(9600);
	#endif
	#ifdef ITERATE_TONES
		int i = 50;
		while(true) {
			Serial.println(i);
			tone(A1, i);
			delay(1000);
			i += 50;
		}
	#endif
	#ifdef MOTION_DEBUG
		while (true) {
			Serial.println(digitalRead(PIN_MOTION_IN));
			delay(500);
		}
	#endif

	timer = millis();
	lastMotionTimer = millis();
	currentState = Locked;
	currentAlertToneIsHigh = false;
}

void loop() {
	if (currentState != Armed) {
		if (currentState == ArmingNervous && millis() - timer >= 100) {  // Every 1/10th of a second (nervous)
			quickTone(700);
			if (millis() - lastMotionTimer >= 3000) {
				longTone(700);
				currentState = Armed;
			}
			timer = millis();
		} else if (millis() - timer >= 1000) {  // Every second (lazy)
			switch (currentState) {
				case Locked:
					if (millis() - lastMotionTimer >= 30000) {
						longTone(300);
						delay(500);
						if (battery.getState() == CHARGING_IDLE) {
							battery.off();
							delay(1000);
						} else {
							while(true) {
								batteryLevelTone(battery.getLevel() / 10);
								delay(60000);
							}
						}
					}
					quickTone(300);
					break;
				case Cooldown:
					if (millis() - lastMotionTimer >= 10000) {
						currentState = ArmingLazy;
						lastMotionTimer = millis();
					}
					quickDoubleTone(500, 400);
					break;
				case ArmingLazy:
					if (millis() - lastMotionTimer >= 5000) {
						currentState = ArmingNervous;
						lastMotionTimer = millis();
					}
					quickTone(700);
					break;
				case Alert:
					alertTone(currentAlertToneIsHigh);
					currentAlertToneIsHigh = !currentAlertToneIsHigh;
					break;
			}
			timer = millis();
		}
	}
	if (digitalRead(PIN_MOTION_IN) == 1) {
		if (currentState == Armed) {
			delay(2000);  // Preventing false alarm
			if (digitalRead(PIN_MOTION_IN) == 1) {
				currentState = Alert;
			}
		} else if (currentState != Alert) {
			currentState = Cooldown;
		}
		lastMotionTimer = millis();
	}
	delay(1000);
}
