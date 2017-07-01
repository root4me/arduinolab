
#include "Arduino.h"
#include "HTTPresponse.h"
#include "ArduinoJson.h"

StaticJsonBuffer<200> jsonBuffer;

String HTTPresponse::alive()
{

        String retval;
        digitalWrite(LED_BUILTIN, LOW);

        JsonObject& root = jsonBuffer.createObject();
        root["status"] = "alive";

        root.prettyPrintTo(Serial);
        root.printTo(retval);

        return retval;

}
