const int inputPins[] = {2, 3, 4, 5, 6};
const int outputPins[] = {7, 8, 9, 10, 11, 12, LED_BUILTIN};

///In MS
const int turnSignalDelay = 500;

unsigned long lastTurnSignalTime = 0;
unsigned long currentTurnSignalTime = 0;
int nextLeftState = LOW;
int nextRightState = LOW;

int headlightState = 0;
bool canIncrementHeadlight = true;

bool killCanToggle = false;
bool killLights = false;

int inputStates[] = {LOW, LOW, LOW, LOW, LOW};
int outputStates[] = {LOW, LOW, LOW, LOW, HIGH, HIGH, LOW};

bool defaultStatesWritten = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  
  for(int i = 0; i < 5; i++)
  {
    pinMode(inputPins[i], INPUT_PULLUP);
  }

  for(int i = 0; i < 6; i++)
  {
    pinMode(outputPins[i], OUTPUT);
  }
  
}

void loop() {

  //If inputs haven't changed no need to run the rest of the function
  if(ReadInputs() == false)
  {
    if(defaultStatesWritten == false)
    {
      defaultStatesWritten = true;
      SetDefaultStates();
      WriteOutputs();
    }
    return;
  }

  //If an input value has changed proceed to process that change
  SetDefaultStates();
  currentTurnSignalTime = millis();
  
  /*
    =-=-=-=-=-=-=
    INPUT STATES
    =-=-=-=-=-=-=
    inputStates[0] = Left Switch
    inputStates[1] = Right Switch
    inputStates[2] = Brake Switch
    inputStates[3] = Headlight Switch
    inputStates[4] = Kill Switch

    =-=-=-=-=-=-=
    OUTPUTS
    =-=-=-=-=-=-=
    outputPins[0] = Front Left Signal Lights
    outputPins[1] = Rear Left Signal Lights
    outputPins[2] = Front Right Signal Lights
    outputPins[3] = Rear Right Signal Lights
    outputPins[4] = Headlights LOWBEAMS
    outputPins[5] = Headlights HIGHBEAMS
    outputPins[6] = Onboard LED
  */
  /*
  if(inputStates[2] == HIGH)
  {
    outputStates[1] = HIGH;
    outputStates[3] = HIGH;
    outputStates[6] = HIGH;
  }
  */


  /*   --- BRAKE LIGHTS ---   */
  if(inputPins[2] == HIGH)
  {
    outputStates[1] = HIGH;
    outputStates[3] = HIGH;
  }
  
  /*   --- LEFT SIGNAL ---   */
  if(inputStates[0] == HIGH)
  {
    
    if(currentTurnSignalTime - lastTurnSignalTime >= turnSignalDelay)
    {
      nextLeftState = !nextLeftState;
      lastTurnSignalTime = currentTurnSignalTime;
    }

    outputStates[0] = nextLeftState;
    outputStates[2] = nextLeftState;
    outputStates[6] = nextLeftState;
  }else{ nextLeftState = LOW; }

  /*   --- RIGHT SIGNAL ---   */
  if(inputStates[1] == HIGH)
  {
    if(currentTurnSignalTime - lastTurnSignalTime >= turnSignalDelay)
    {
      nextRightState = !nextRightState;
      lastTurnSignalTime = currentTurnSignalTime;
    }

    outputStates[1] = nextRightState;
    outputStates[3] = nextRightState;
    outputStates[6] = nextRightState;
  }else{ nextRightState = LOW; }

  /*   --- HEADLIGHTS ---   */
  if(headlightState == 0)
  {
    outputStates[4] = HIGH;
    outputStates[5] = HIGH;
  }
  else if(headlightState == 1)
  {
    outputStates[4] = LOW;
    outputStates[5] = HIGH;
  }
  else if(headlightState == 2)
  {
    outputStates[4] = HIGH;
    outputStates[5] = LOW;
  }
  
  /*   --- KILLSWITCH ---   */
  if(killLights == true)
  {
    SetDefaultStates();
  }
  
  WriteOutputs();
}

void SetDefaultStates()
{
  for(int i = 0; i < 7; i++)
  {
    if(i == 4 || i == 5)
    {
      outputStates[i] = HIGH;
    }else{
      outputStates[i] = LOW;
    }
  }
}

bool ReadInputs()
{
  for(int i = 0; i < 5; i++)
  {
    //Current State
    int state = !digitalRead(inputPins[i]);

    if(i == 3) { HandleHeadlightInput(state); }
    if(i == 4) { HandleKillswitchInput(state); }

    inputStates[i] = state;
  }

  defaultStatesWritten = false;
  return true;
}

void WriteOutputs()
{
  for(int i = 0; i < 7; i++)
  {
    digitalWrite(outputPins[i], outputStates[i]);
  }
}

void HandleHeadlightInput(int state)
{
  if(state == HIGH)
  {
    if(canIncrementHeadlight == true)
    {
      canIncrementHeadlight = false;
      headlightState++;
      if(headlightState > 2)
      {
        headlightState = 0;
      }
    }
  }else
  {
    canIncrementHeadlight = true;
  }
}

void HandleKillswitchInput(int state)
{
  if(state == HIGH)
  {
    if(killCanToggle == true)
    {
      killCanToggle = false;
      killLights = !killLights;
    }
  }else
  {
    killCanToggle = true;
  }
}
