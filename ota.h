#ifndef __LXLIB_OTA__
#define __LXLIB_OTA__

#include <stdlib.h>
#include "lxlib-config.h"

#define ON_UPLOAD_START() 0;
#define ON_UPLOAD_PROCESS(value) 0;
#define ON_UPLOAD_DONE() 0;
#define ON_UPLOAD_ERROR() 0;
#define ON_UPLOAD_DENIED() 0;

void initOTA();
void loopOTA();

#endif