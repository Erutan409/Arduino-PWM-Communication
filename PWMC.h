#ifndef PWMC_H
#define PWMC_H

enum BIT {
	HIGH_BIT = 0x01
	, LOW_BIT = 0x00
};

enum PWMC_Mode {
	TALK = 0x01
	, LISTEN = 0x02
};

enum PWMC_Handshake {
	NONE = 0x00
	, IN_PROCESS = 0x01
	, ESTABLISHED = 0x02
};

#include <PWMC_Byte.h>
#include <PWMC_TimeTracking.h>
#include <PWM_Communication.h>

using PWMC = PWMC_Communication;

#endif // !PWMC_H