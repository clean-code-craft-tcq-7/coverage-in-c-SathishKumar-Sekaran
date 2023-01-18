void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);

typedef void (*alertFuncPtr)(BreachType);

extern alertFuncPtr alertType[2];
