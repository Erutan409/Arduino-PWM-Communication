#ifndef PWMC_ENUMS_H
#define PWMC_ENUMS_H

enum class BIT : uint8_t {
	HIGH_BIT = 0x01
	,LOW_BIT = 0x00
};

enum class PWMC_Mode : uint8_t {
	TALK = 0x01
	,LISTEN = 0x02
};

enum class PWMC_Handshake_State : uint8_t {
	NONE = 0x00
	,IN_PROCESS = 0x01
	,ESTABLISHED = 0x02
};

#endif // !PWMC_ENUMS_H