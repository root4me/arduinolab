
#include <Arduino.h>
#include <HTTPresponse.h>
#include <ArduinoJson.h>

StaticJsonBuffer<200> jsonBuffer;

String HTTPresponse::alive()
{

        String retval;

        JsonObject& root = jsonBuffer.createObject();
        root["status"] = "alive";

        root.prettyPrintTo(Serial);
        root.printTo(retval);

        return retval;

}
