#include "input.h"

#include <genesis.h>

void input_init() {
	joystate = 0;
	oldstate = 0;
	controllerType = JOY_getPortType(JOY_1);
}
