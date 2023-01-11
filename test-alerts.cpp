#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "alertMsgConfig.h"
#include "typewise-alert.h"
#include "breachAnalysis.h"
#include "SendAlert.h"
#include <string.h>

extern char printBuffer[50];
extern const char* emailWarnMsg[2];

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
}

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(35, 20, 30) == TOO_HIGH);
}

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
}

TEST_CASE("Get the breach according to limits") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,-1) == TOO_LOW);
}

TEST_CASE("Get the breach according to limits") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,40) == TOO_HIGH);
}

TEST_CASE("Get the breach according to limits") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,27) == NORMAL);
}

TEST_CASE("Get the breach according to limits") {
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,-2) == TOO_LOW);
}

TEST_CASE("Get the breach according to limits") {
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,50) == TOO_HIGH);
}

TEST_CASE("Get the breach according to limits") {
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,37) == NORMAL);
}

TEST_CASE("Get the breach according to limits") {
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,-2) == TOO_LOW);
}

TEST_CASE("Get the breach according to limits") {
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,50) == TOO_HIGH);
}

TEST_CASE("Get the breach according to limits") {
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,37) == NORMAL);
}


TEST_CASE("Breach send to controller") {
  sendToController(TOO_LOW);
  REQUIRE((strcmp(printBuffer,"0xfeed : 0x01")) == 1);
}

TEST_CASE("Breach send to controller") {
  sendToController(TOO_HIGH);
  REQUIRE((strcmp(printBuffer,"0xfeed : 0x02")) == 1);
}

TEST_CASE("Breach send to controller") {
  sendToController(NORMAL);
  REQUIRE((strcmp(printBuffer,"0xfeed : 0x00")) == 1);
}

TEST_CASE("send to Email to recepiant") {
  sendToEmail(NORMAL);
  REQUIRE((strcmp(printBuffer,emailWarnMsg[0])) == 1);
}

TEST_CASE("send to Email to recepiant") {
  sendToEmail(TOO_LOW);
  REQUIRE((strcmp(printBuffer,emailWarnMsg[1])) == 1);
}

TEST_CASE("send to Email to recepiant") {
  sendToEmail(TOO_HIGH);
  REQUIRE((strcmp(printBuffer,emailWarnMsg[2])) == 1);
}

TEST_CASE("Check alert message send to Controller") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = PASSIVE_COOLING;
  checkAndAlert(TO_CONTROLLER,batteryChar,-2);
  REQUIRE((strcmp(printBuffer,"0xfeed : 0x01")) == 1);
}

TEST_CASE("Check alert message send to Controller") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = PASSIVE_COOLING;
  checkAndAlert(TO_CONTROLLER,batteryChar,20);
  REQUIRE((strcmp(printBuffer,"0xfeed : 0x00")) == 1);
}

TEST_CASE("Check alert message send to Controller") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = PASSIVE_COOLING;
  checkAndAlert(TO_CONTROLLER,batteryChar,43);
  REQUIRE((strcmp(printBuffer,"0xfeed : 0x02")) == 1);
}

TEST_CASE("Check alert message send to Controller") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = HI_ACTIVE_COOLING;
  checkAndAlert(TO_CONTROLLER,batteryChar,-2);
  REQUIRE((strcmp(printBuffer,"0xfeed : 0x01")) == 1);
}

TEST_CASE("Check alert message send to Controller") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = HI_ACTIVE_COOLING;
  checkAndAlert(TO_CONTROLLER,batteryChar,20);
  REQUIRE((strcmp(printBuffer,"0xfeed : 0x00")) == 1);
}

TEST_CASE("Check alert message send to Controller") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = HI_ACTIVE_COOLING;
  checkAndAlert(TO_CONTROLLER,batteryChar,50);
  REQUIRE((strcmp(printBuffer,"0xfeed : 0x02")) == 1);
}

TEST_CASE("Check alert message send to Controller") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  checkAndAlert(TO_CONTROLLER,batteryChar,-2);
  REQUIRE((strcmp(printBuffer,"0xfeed : 0x01")) == 1);
}

TEST_CASE("Check alert message send to Controller") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  checkAndAlert(TO_CONTROLLER,batteryChar,30);
  REQUIRE((strcmp(printBuffer,"0xfeed : 0x00")) == 1);
}

TEST_CASE("Check alert message send to Controller") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  checkAndAlert(TO_CONTROLLER,batteryChar,46);
  REQUIRE((strcmp(printBuffer,"0xfeed : 0x02")) == 1);
}

TEST_CASE("Check alert message send to Email") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = PASSIVE_COOLING;
  checkAndAlert(TO_EMAIL,batteryChar,-2);
  REQUIRE((strcmp(printBuffer,emailWarnMsg[1])) == 1);
}

TEST_CASE("Check alert message send to Email") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = PASSIVE_COOLING;
  checkAndAlert(TO_EMAIL,batteryChar,20);
  REQUIRE((strcmp(printBuffer,emailWarnMsg[0])) == 1);
}

TEST_CASE("Check alert message send to Email") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = PASSIVE_COOLING;
  checkAndAlert(TO_EMAIL,batteryChar,43);
  REQUIRE((strcmp(printBuffer,emailWarnMsg[2])) == 1);
}

TEST_CASE("Check alert message send to Email") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = HI_ACTIVE_COOLING;
  checkAndAlert(TO_EMAIL,batteryChar,-2);
  REQUIRE((strcmp(printBuffer,emailWarnMsg[1])) == 1);
}

TEST_CASE("Check alert message send to Email") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = HI_ACTIVE_COOLING;
  checkAndAlert(TO_EMAIL,batteryChar,20);
  REQUIRE((strcmp(printBuffer,emailWarnMsg[0])) == 1);
}

TEST_CASE("Check alert message send to Email") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = HI_ACTIVE_COOLING;
  checkAndAlert(TO_EMAIL,batteryChar,50);
  REQUIRE((strcmp(printBuffer,emailWarnMsg[2])) == 1);
}

TEST_CASE("Check alert message send to Email") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  checkAndAlert(TO_EMAIL,batteryChar,-2);
  REQUIRE((strcmp(printBuffer,emailWarnMsg[1])) == 1);
}

TEST_CASE("Check alert message send to Email") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  checkAndAlert(TO_EMAIL,batteryChar,30);
  REQUIRE((strcmp(printBuffer,emailWarnMsg[0])) == 1);
}

TEST_CASE("Check alert message send to Email") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  checkAndAlert(TO_EMAIL,batteryChar,46);
  REQUIRE((strcmp(printBuffer,emailWarnMsg[2])) == 1);
}