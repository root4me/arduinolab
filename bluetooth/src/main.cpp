#include "Arduino.h"

//#define DEBUG
#ifdef DEBUG
 #define PRINTLN(x)  Serial.println (x)
#else
 #define PRINTLN(x)
#endif


char command[10]; // command retrived from bluetooth serial. Commad starts and ends with #
int index = 0;
char input; // character read from bluetooth serial
bool commandStart=false;

void handleStart();
void handleStop();

void setup() {
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, LOW);

        Serial.begin(115200); // Default connection rate for my BT module
}

void loop() {

        if (Serial.available() > 0) {
                input = Serial.read();

                Serial.println(input);
                if (input == '#') // command starts ad
                {
                        if (!(commandStart))
                        {
                                commandStart = true;
                        }
                        else
                        {
                                commandStart= false;
                        }
                        command[index] = input;
                        index++;

                        if (!(commandStart))
                        {
                                // Compare the string. do somethign and them empty out the string
                                if (strcmp(command, "#start#") == 0)
                                {
                                        PRINTLN("match found");
                                        PRINTLN(command);
                                        handleStart();
                                }
                                else if (strcmp(command, "#stop#") == 0)
                                {
                                        handleStop();

                                }
                                else
                                {
                                        PRINTLN(command);
                                        Serial.println("Unknown command");
                                }

                                // Once command is handled clear out char array and be prepated to accept next command
                                //command[0] = 0;
                                memset( command, 0, sizeof(command));
                                index=0;
                                PRINTLN("Cleared");
                                PRINTLN(command);
                        }
                }
                else
                {
                        if (commandStart) // keep adding character to array till second # is encountered
                        {
                                command[index] =input;
                                index++;
                        }
                }
        }
        else
        {
                //Serial.println(sizeof(inData));
                //memset(inData, 0, sizeof(inData));
                //index = 0;
        }

}

void handleStart()
{
        Serial.println("Handling Start command");
}

void handleStop()
{
        Serial.println("Handling Stop command");
}
