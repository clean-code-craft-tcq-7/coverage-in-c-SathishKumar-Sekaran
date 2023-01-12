#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "alertMsgConfig.h"
#include "typewise-alert.h"
#include "breachAnalysis.h"
#include "SendAlert.h"
#include <string.h>

extern char printBuffer[50];
extern const char* emailWarnMsg[2];

TEST_CASE("infers the breach according to limit Is Low") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
}

TEST_CASE("infers the breach according to limit Is High") {
  REQUIRE(inferBreach(35, 20, 30) == TOO_HIGH);
}

TEST_CASE("infers the breach according to limit Is Normal") {
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
}

TEST_CASE("Get the breach according to limit Is Low with Passive cooling") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,-1) == TOO_LOW);
}

TEST_CASE("Get the breach according to limit Is High with Passive cooling") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,40) == TOO_HIGH);
}

TEST_CASE("Get the breach according to limit Is Normal with Passive cooling") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,27) == NORMAL);
}

TEST_CASE("Get the breach according to limit Is Low with Hi active cooling") {
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,-2) == TOO_LOW);
}

TEST_CASE("Get the breach according to limit Is High with Hi active cooling") {
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,50) == TOO_HIGH);
}

TEST_CASE("Get the breach according to limit Is Normal with Hi active cooling") {
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,37) == NORMAL);
}

TEST_CASE("Get the breach according to limit Is Low with Mid active cooling") {
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,-2) == TOO_LOW);
}

TEST_CASE("Get the breach according to limit Is High with Mid active cooling") {
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,50) == TOO_HIGH);
}

TEST_CASE("Get the breach according to limit Is Normal with Mid active cooling") {
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,37) == NORMAL);
}


TEST_CASE("Breach send to controller when limit is Low") {
  sendToController(TOO_LOW);
  REQUIRE((strcmp(printBuffer,"feed : 1")) == 0);
}

TEST_CASE("Breach send to controller when limit is High") {
  sendToController(TOO_HIGH);
  REQUIRE((strcmp(printBuffer,"feed : 2")) == 0);
}

TEST_CASE("Breach send to controller when limit is Normal") {
  sendToController(NORMAL);
  REQUIRE((strcmp(printBuffer,"feed : 0")) == 0);
}

TEST_CASE("send to Email to recepiant when limit is Normal") {
  sendToEmail(NORMAL);
  REQUIRE((strcmp(printBuffer,emailWarnMsg[0])) == 0);
}

TEST_CASE("send to Email to recepiant when limit is Low") {
  sendToEmail(TOO_LOW);
  REQUIRE((strcmp(printBuffer,emailWarnMsg[1])) == 0);
}

TEST_CASE("send to Email to recepiant when limit is High") {
  sendToEmail(TOO_HIGH);
  REQUIRE((strcmp(printBuffer,emailWarnMsg[2])) == 0);
}

TEST_CASE("Check alert message send to Controller for passive cooling type with Low limits") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = PASSIVE_COOLING;
  checkAndAlert(TO_CONTROLLER,batteryChar,-2);
  REQUIRE((strcmp(printBuffer,"feed : 1")) == 0);
}

TEST_CASE("Check alert message send to Controller for passive cooling type with Normal limits") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = PASSIVE_COOLING;
  checkAndAlert(TO_CONTROLLER,batteryChar,20);
  REQUIRE((strcmp(printBuffer,"feed : 0")) == 0);
}

TEST_CASE("Check alert message send to Controller for passive cooling type with High limits") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = PASSIVE_COOLING;
  checkAndAlert(TO_CONTROLLER,batteryChar,43);
  REQUIRE((strcmp(printBuffer,"feed : 2")) == 0);
}

TEST_CASE("Check alert message send to Controller for Hi active cooling type with Low limits") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = HI_ACTIVE_COOLING;
  checkAndAlert(TO_CONTROLLER,batteryChar,-2);
  REQUIRE((strcmp(printBuffer,"feed : 1")) == 0);
}

TEST_CASE("Check alert message send to Controller for Hi active cooling type with normal limits") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = HI_ACTIVE_COOLING;
  checkAndAlert(TO_CONTROLLER,batteryChar,20);
  REQUIRE((strcmp(printBuffer,"feed : 0")) == 0);
}

TEST_CASE("Check alert message send to Controller for Hi active cooling type with High limits") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = HI_ACTIVE_COOLING;
  checkAndAlert(TO_CONTROLLER,batteryChar,50);
  REQUIRE((strcmp(printBuffer,"feed : 2")) == 0);
}

TEST_CASE("Check alert message send to Controller for Mid active cooling type with Low limits") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  checkAndAlert(TO_CONTROLLER,batteryChar,-2);
  REQUIRE((strcmp(printBuffer,"feed : 1")) == 0);
}

TEST_CASE("Check alert message send to Controller for Mid active cooling type with Normal limits") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  checkAndAlert(TO_CONTROLLER,batteryChar,30);
  REQUIRE((strcmp(printBuffer,"feed : 0")) == 0);
}

TEST_CASE("Check alert message send to Controller for Mid active cooling type with High limits") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  checkAndAlert(TO_CONTROLLER,batteryChar,46);
  REQUIRE((strcmp(printBuffer,"feed : 2")) == 0);
}

TEST_CASE("Check alert message send to Email for passive cooling type with Low limits") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = PASSIVE_COOLING;
  checkAndAlert(TO_EMAIL,batteryChar,-2);
  REQUIRE((strcmp(printBuffer,emailWarnMsg[1])) == 0);
}

TEST_CASE("Check alert message send to Email for Passive cooling type with normal limits") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = PASSIVE_COOLING;
  checkAndAlert(TO_EMAIL,batteryChar,20);
  REQUIRE((strcmp(printBuffer,emailWarnMsg[1])) == 0);
}

TEST_CASE("Check alert message send to Email for Passive cooling type with High limits") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = PASSIVE_COOLING;
  checkAndAlert(TO_EMAIL,batteryChar,43);
  REQUIRE((strcmp(printBuffer,emailWarnMsg[2])) == 0);
}

TEST_CASE("Check alert message send to Email for Hi active cooling type with Low limits") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = HI_ACTIVE_COOLING;
  checkAndAlert(TO_EMAIL,batteryChar,-2);
  REQUIRE((strcmp(printBuffer,emailWarnMsg[1])) == 0);
}

TEST_CASE("Check alert message send to Email for Hi active cooling type with Normal limits") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = HI_ACTIVE_COOLING;
  checkAndAlert(TO_EMAIL,batteryChar,20);
  REQUIRE((strcmp(printBuffer,emailWarnMsg[1])) == 0);
}

TEST_CASE("Check alert message send to Email for Hi active cooling type with High limits") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = HI_ACTIVE_COOLING;
  checkAndAlert(TO_EMAIL,batteryChar,50);
  REQUIRE((strcmp(printBuffer,emailWarnMsg[2])) == 0);
}

TEST_CASE("Check alert message send to Email for Mid active cooling type with Low limits") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  checkAndAlert(TO_EMAIL,batteryChar,-2);
  REQUIRE((strcmp(printBuffer,emailWarnMsg[1])) == 0);
}

TEST_CASE("Check alert message send to Email for Mid active cooling type with Normal limits") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  checkAndAlert(TO_EMAIL,batteryChar,30);
  REQUIRE((strcmp(printBuffer,emailWarnMsg[1])) == 0);
}

TEST_CASE("Check alert message send to Email for Mid active cooling type with High limits") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  checkAndAlert(TO_EMAIL,batteryChar,46);
  REQUIRE((strcmp(printBuffer,emailWarnMsg[2])) == 0);
}