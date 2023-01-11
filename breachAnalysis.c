#include <stdio.h>
#include <alertMsgConfig.h>
#include <typewise-alert.h>
#include <breachAnalysis.h>

extern st_TempLimits tempLimitValues[3];

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  
  BreachType breachType = inferBreach(temperatureInC, tempLimitValues[coolingType].lowerLimit, 
                                              tempLimitValues[coolingType].upperLimit);
  return breachType;
}