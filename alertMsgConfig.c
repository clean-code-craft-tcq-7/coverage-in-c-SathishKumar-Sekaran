#include <stdio.h>
#include "alertMsgConfig.h"

st_TempLimits tempLimitValues[3] = {
        {
          .lowerLimit = 0,
          .upperLimit = 35,
        },
        {
          .lowerLimit = 0,
          .upperLimit = 45,
        },
        {
          .lowerLimit = 0,
          .upperLimit = 40,
        },
};

const char* emailWarnMsg[3] = {
        "Hi, the temerature is Normal",
        "Hi, the temperature is too low",
        "Hi, the temperature is too high",
};
