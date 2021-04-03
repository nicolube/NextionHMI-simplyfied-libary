#include <Arduino.h>
#include <SoftwareSerial.h>


class NextionObject {
    public:
        NextionObject(uint8_t pageId, uint8_t objectId);
        NextionObject(String pageName, String objectName);
        String getObejectPointer();
    protected:
        String objectPointer;
};

class NextionHMI {
    public:
        NextionHMI(HardwareSerial *serial);
        NextionHMI(SoftwareSerial *serial);
        void init();
        void tick();
        void setText(NextionObject *object, String text);
    protected:
        Stream *serial;
        void send(NextionObject *obj, String cmd);
        void terminate();
    private:
        uint8_t bufferSize = 0;
        uint8_t terminationCounter = 0;
        bool bt = false;
        uint8_t buffer[16];
        bool isHwSerial;
        void processCommand();
};