#include <NextionHMI.h>

NextionObject::NextionObject(uint8_t pageId, uint8_t objectId) {
    this->objectPointer = "p["+String(pageId)+"].b["+String(objectId)+"].";
}

NextionObject::NextionObject(String pageName, String objectName) {
    this->objectPointer = pageName+"."+objectName+".";
}

String NextionObject::getObejectPointer() {
    return this->objectPointer;
}

NextionHMI::NextionHMI(HardwareSerial *serial) {
    this->isHwSerial = true;
    this->serial = serial;
}

NextionHMI::NextionHMI(SoftwareSerial *serial) {
    this->isHwSerial = false;
    this->serial = serial;
}

void NextionHMI::init() {
    if (this->isHwSerial) {
        ((HardwareSerial *)serial)->begin(512000);
    } else {
        ((SoftwareSerial *)serial)->begin(9600);
    }
    this->terminate();
}

void NextionHMI::tick() {
    while (serial->available()) {
        uint8_t data = serial->read();
        if (data == 0xFF) {
            if (++terminationCounter >= 3) {
                processCommand();
                terminationCounter = 0;
                bufferSize = 0;
                bt = false;
            }
            bt = true;
        } else if (bt == true) {
            bt = false;
            terminationCounter--;
        }

        buffer[bufferSize++] = data;
    }
}

void NextionHMI::send(NextionObject *object, String cmd) {
    this->serial->print(object->getObejectPointer() + cmd);
    this->terminate();
}

void NextionHMI::terminate() {
    this->serial->write(0xFF);
    this->serial->write(0xFF);
    this->serial->write(0xFF);
}

void NextionHMI::setText(NextionObject *object, String text) {
    this->send(object, "txt=\""+text+'\"');
}

void NextionHMI::processCommand() {
    if (bufferSize < 3) return;
    switch (buffer[0])
    {
    case 0x00: //Nextion Startup
        break;
    case 0x24: //Serial Overflow
        break;
    case 0x65: //Touch Event
        break;
    case 0x66: //Current Page number
        break;
    case 0x67: //Touch Coordinate (akawe)
        break;
    case 0x68: //Tuch Coordinate (sleep)
        break;
    case 0x70: //String data
        break;
    case 0x71: //Numeric data
        break;
    case 0x86: //Auto Entered Sleep mode
        break;
    case 0x87: //Auto Wake from Sleep mode
        break;
    case 0x88: //Finshed powered up
        break;
    default:
        break;
    }
}