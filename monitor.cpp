#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

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

int temperatureOK(float temperature) {
  if (temperature > 102 || temperature < 95) {
    cout << "Temperature is critical!\n";
    alertBreak();
    return 0;
  }
  return 1;
}

int pulseRateOK(float pulseRate) {
  if (pulseRate < 60 || pulseRate > 100) {
    cout << "Pulse Rate is out of range!\n";
    alertBreak();
    return 0;
  }
  return 1;
}

int spo2OK(float spo2) {
  if (spo2 < 90) {
    cout << "Oxygen Saturation out of range!\n";
    alertBreak();
    return 0;
  }
  return 1;
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
  return (temperatureOK(temperature) && pulseRateOK(pulseRate) && spo2OK(spo2));
}

