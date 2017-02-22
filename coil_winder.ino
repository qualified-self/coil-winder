#include <AccelStepper.h>
#include "linereader.h"

LineReader reader;
char *linein;

const int STEPS_PER_WINDING = 200;
const int MAX_SPEED = 2000;

// Define a stepper and the pins it will use
//AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper(AccelStepper::DRIVER, 4, 3);

void setup()
{
  Serial.begin(115200);
  
  stepper.setMaxSpeed(MAX_SPEED);
  stepper.setAcceleration(180);
}


void loop() {
  char *line;
  if ((line = reader.readln(Serial)) != NULL) {
    on_process_command( line );
  }

  stepper.run();
}


void stepper_drive(int windings) {
    Serial.print("Number of windings: ");
    Serial.print(windings);
    Serial.println();

    stepper.move(windings*STEPS_PER_WINDING);
}

void on_process_command(char *cmd) {

    int windings = 0;
    int rps = 0;
    
    if(sscanf(cmd, "%d", &windings) == 1) {
      stepper_drive( windings );
    }
}

