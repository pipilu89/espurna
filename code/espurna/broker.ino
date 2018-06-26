/*

BROKER MODULE

Copyright (C) 2017-2018 by Xose Pérez <xose dot perez at gmail dot com>

Module key prefix: bkr

*/

#if BROKER_SUPPORT

#include <vector>

std::vector<void (*)(const char *, unsigned char, const char *)> _broker_callbacks;

// -----------------------------------------------------------------------------

void brokerRegister(void (*callback)(const char *, unsigned char, const char *)) {
    _broker_callbacks.push_back(callback);
}

void brokerPublish(const char * topic, unsigned char id, const char * message) {
    //DEBUG_MSG_P(PSTR("[BROKER] Message %s[%u] => %s\n"), topic, id, message);
    for (unsigned char i=0; i<_broker_callbacks.size(); i++) {
        (_broker_callbacks[i])(topic, id, message);
    }
}

void brokerPublish(const char * topic, const char * message) {
    brokerPublish(topic, 0, message);
}

#endif // BROKER_SUPPORT
