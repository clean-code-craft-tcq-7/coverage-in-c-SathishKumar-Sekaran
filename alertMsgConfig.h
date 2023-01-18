typedef struct 
{
  int lowerLimit;
  int upperLimit;
}st_TempLimits;

typedef void (*alertFuncPtr)(BreachType);

extern alertFuncPtr alertType[2];
