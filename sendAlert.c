#include <stdio.h>
#include <string.h>
#include <typewise-alert.h>
#include <SendAlert.h>
#include <print.h>

char printBuffer[50];
extern const char* emailWarnMsg[2];

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  sprintf(printBuffer,"%x : %x", header, breachType);
  printMsg(printBuffer);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  char printMailId[50];
  sprintf(printMailId,"To: %s", recepient);
  printMsg(printMailId);
  if(breachType != NORMAL)
  {
    sprintf(printBuffer,"%s", emailWarnMsg[breachType]);
    printMsg(printBuffer);
  }
}