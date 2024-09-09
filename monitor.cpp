#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds,
std::unordered_map, std::string;

unordered_map<string, unordered_map<string, string>> TranslationMap = {
    {"EN", {
        {"TEMP_CRITICAL", "Temperature is critical!"},
        {"TEMP_HYPER_WARNING", "Warning: Approaching hyperthermia"},
        {"TEMP_HYPO_WARNING", "Warning: Approaching hypothermia"},
        {"PULSE_CRITICAL", "Pulse Rate is out of range!"},
        {"PULSE_HIGH_WARNING", "Warning: Approaching high pulse rate"},
        {"PULSE_LOW_WARNING", "Warning: Approaching low pulse rate"},
        {"SPO2_CRITICAL", "Oxygen Saturation out of range!"},
        {"SPO2_LOW_WARNING", "Warning: Approaching low oxygen saturation"}
    }},
    {"DE", {
        {"TEMP_CRITICAL", "Temperatur ist kritisch!"},
        {"TEMP_HYPER_WARNING", "Warnung: Annäherung an Hyperthermie"},
        {"TEMP_HYPO_WARNING", "Warnung: Annäherung an Hypothermie"},
        {"PULSE_CRITICAL", "Pulsrate ist außerhalb des Bereichs!"},
        {"PULSE_HIGH_WARNING", "Warnung: Annäherung an hohe Pulsrate"},
        {"PULSE_LOW_WARNING", "Warnung: Annäherung an niedrige Pulsrate"},
        {"SPO2_CRITICAL", "Sauerstoffsättigung außerhalb des Bereichs!"},
        {"SPO2_LOW_WARNING", "Warnung: Annäherung an niedrige Sauerstoffsättigung"}
    }},
    {"ES", {
        {"TEMP_CRITICAL", "¡La temperatura es crítica!"},
        {"TEMP_HYPER_WARNING", "Advertencia: acercándose a la hipertermia"},
        {"TEMP_HYPO_WARNING", "Advertencia: acercándose a la hipotermia"},
        {"PULSE_CRITICAL", "¡La frecuencia del pulso está fuera de rango!"},
        {"PULSE_HIGH_WARNING", "Advertencia: acercándose a una alta frecuencia del pulso"},
        {"PULSE_LOW_WARNING", "Advertencia: acercándose a una baja frecuencia del pulso"},
        {"SPO2_CRITICAL", "¡La saturación de oxígeno está fuera de rango!"},
        {"SPO2_LOW_WARNING", "Advertencia: acercándose a una baja saturación de oxígeno"}
    }},
    {"FR", {
        {"TEMP_CRITICAL", "La température est critique!"},
        {"TEMP_HYPER_WARNING", "Attention : Approche de l'hyperthermie"},
        {"TEMP_HYPO_WARNING", "Attention : Approche de l'hypothermie"},
        {"PULSE_CRITICAL", "Le rythme cardiaque est hors de portée!"},
        {"PULSE_HIGH_WARNING", "Attention : Approche d'un rythme cardiaque élevé"},
        {"PULSE_LOW_WARNING", "Attention : Approche d'un rythme cardiaque faible"},
        {"SPO2_CRITICAL", "La saturation en oxygène est hors de portée!"},
        {"SPO2_LOW_WARNING", "Attention : Approche d'une faible saturation en oxygène"}
    }},
    {"IT", {
        {"TEMP_CRITICAL", "La temperatura è critica!"},
        {"TEMP_HYPER_WARNING", "Avvertimento: Vicino all'ipertermia"},
        {"TEMP_HYPO_WARNING", "Avvertimento: Vicino all'ipotermia"},
        {"PULSE_CRITICAL", "La frequenza del polso è fuori intervallo!"},
        {"PULSE_HIGH_WARNING", "Avvertimento: Vicino a una frequenza del polso alta"},
        {"PULSE_LOW_WARNING", "Avvertimento: Vicino a una frequenza del polso bassa"},
        {"SPO2_CRITICAL", "La saturazione di ossigeno è fuori intervallo!"},
        {"SPO2_LOW_WARNING", "Avvertimento: Vicino a una bassa saturazione di ossigeno"}
    }}
};

void alertBreak() {
    int repeatCount = 6;
    int timeInSeconds = 1;
    for (int i = 0; i < repeatCount; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(timeInSeconds));
        cout << "\r *" << flush;
        sleep_for(seconds(timeInSeconds));
    }
}

string chooseLanguage() {
    // list of available languages
	// EN - English
	// DE - Dutch
	// ES - Spanish
	// FR - French
	// IT - Italian
    string currentLanguage = "EN";
    return currentLanguage;
}

void displayMessage(string message) {
    string language = "EN";
    language = chooseLanguage();
    cout << TranslationMap[language][message] << "\n";
    alertBreak();
}

bool checkLimitNotInRange(float actualValue, float upperLimit, float lowerLimit) {
    if (actualValue < lowerLimit || actualValue > upperLimit)
        return true;
    return false;
}

string checkLimitApproching(float actualValue, float upperLimit, float lowerLimit) {
    float warningTolerance = 1.5 / 100;
    float upperWarningLimit = upperLimit - (upperLimit * warningTolerance);
    float lowerWarningLimit = lowerLimit + (lowerLimit * warningTolerance);
    if (actualValue > upperWarningLimit)
        return "UPPERWARNING";
    else if (actualValue < lowerWarningLimit)
        return "LOWERWARNING";
    else
        return "NORMAL";
}

void temperatureInWarningLimits(string message) {
    string temperatureInUpperWarning = "UPPERWARNING";
    string temperatureInLowerWarning = "LOWERWARNING";
    if (message == temperatureInUpperWarning)
        displayMessage("TEMP_HYPER_WARNING");
    else
        displayMessage("TEMP_HYPO_WARNING");
}

int temperatureOK(float temperature) {
    float upperLimit = 102;
    float lowerLimit = 95;
    if (checkLimitNotInRange(temperature , upperLimit, lowerLimit)) {
        displayMessage("TEMP_CRITICAL");
        return 0;
    }else {
        string valueWithinRange = "NORMAL";
        string message = checkLimitApproching(temperature, upperLimit, lowerLimit);
        if (message != valueWithinRange)
            temperatureInWarningLimits(message);
        return 1;
    }
}

void pulseRateInWarningLimits(string message) {
    string pulseRateInUpperWarning = "UPPERWARNING";
    string pulseRateInLowerWarning = "LOWERWARNING";
    if (message == pulseRateInUpperWarning)
        displayMessage("PULSE_HIGH_WARNING");
    else
        displayMessage("PULSE_LOW_WARNING");
}

int pulseRateOK(float pulseRate) {
    float upperLimit = 100;
    float lowerLimit = 60;
  if (checkLimitNotInRange(pulseRate, upperLimit, lowerLimit)) {
      displayMessage("PULSE_CRITICAL");
    return 0;
  }else {
      string valueWithinRange = "NORMAL";
      string message = checkLimitApproching(pulseRate, upperLimit, lowerLimit);
      if (message != valueWithinRange)
          pulseRateInWarningLimits(message);   
  }
  return 1;
}

void spo2InWarningLimits(string message) {
    string pulseRateInUpperWarning = "UPPERWARNING";
    string pulseRateInLowerWarning = "LOWERWARNING";
    if (message == pulseRateInLowerWarning)
        displayMessage("SPO2_LOW_WARNING");
}

int spo2OK(float spo2) {
    float upperLimit = 100;
    float lowerLimit = 90;
    if (checkLimitNotInRange(spo2, upperLimit, lowerLimit)) {
        displayMessage("SPO2_CRITICAL");
        return 0;
    }
    else {
        string valueWithinRange = "NORMAL";
        string message = checkLimitApproching(spo2, upperLimit, lowerLimit);
        if (message != valueWithinRange)
            spo2InWarningLimits(message);
    }
    return 1;
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
  return (temperatureOK(temperature) && pulseRateOK(pulseRate) && spo2OK(spo2));
}
