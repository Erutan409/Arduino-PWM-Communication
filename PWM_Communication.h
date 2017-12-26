#ifndef PWM_COMMUNICATION_H
#define PWM_COMMUNICATION_H

#include <PWM.h>

enum PWMC_Mode {
	TALK = 0x01
	,LISTEN = 0x02
};

class PWMC {

	public:

		PWMC(uint8_t sendPin, uint8_t receivePin) {
			this->_sendPin = new PWM(sendPin);
			this->_receivePin = new PWM(receivePin);
		};

		PWMC_Mode *getMode(void) {
			return &this->_mode;
		};

		PWMC &talk(char byte) {
			this->_setMode(TALK);

		};

		PWMC &listen(void) {
			this->_setMode(LISTEN);

		};

	private:
		PWM* _sendPin, _receivePin;
		PWMC_Mode _mode = LISTEN;

		void _setMode(PWMC_Mode mode) {
			this->_mode = mode;
		};

};

#endif // !PWM_COMMUNICATION_H
