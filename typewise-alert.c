#include <stdio.h>
#include "alertMsgConfig.h"
#include "typewise-alert.h"
#include "breachAnalysis.h"
#include "SendAlert.h"


void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  void (*alert_Funptr[2])(BreachType) = {sendToController, sendToEmail};
  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );
  (*alert_Funptr[alertTarget])(breachType);
}

