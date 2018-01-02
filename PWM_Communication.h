#ifndef PWM_COMMUNICATION_H
#define PWM_COMMUNICATION_H

#include <Avail.h>
#include <PWM.h>

enum PWMC_Mode {
	TALK = 0x01
	,LISTEN = 0x02
};

enum PWMC_Handshake {
	NONE = 0x00
	,IN_PROCESS = 0x01
	,ESTABLISHED = 0x02
};

enum BIT {
	HIGH_BIT = 0x01
	,LOW_BIT = 0x00
};

class PWMC {

	public:

		PWMC(uint8_t sendPin, uint8_t receivePin) {
			this->_sendPin = sendPin;
			this->_receivePin = receivePin;

			this->_updateLastAction();
		};

		PWMC_Mode *getMode(void) {
			return &this->_mode;
		};

		PWMC &send(char byte) {
			this->_setMode(TALK);

			return *this;
		};

		void run(void) {
			PWMC_Mode &mode = this->_mode;

			if (mode == LISTEN && this->_doHandshake() == ESTABLISHED) {
				// do work
			} else if (mode == TALK && this->_doHandshake() == ESTABLISHED) {
			
			}
		};

	private:
		uint8_t _sendPin, _receivePin;
		PWMC_Mode _mode = LISTEN;
		PWMC_Handshake _handshake = NONE;
		uint32_t _lastAction;
		const uint32_t _window = 100; // microseconds
		uint8_t _byte = 0x0;
		uint8_t _bitPos = 0;

		void _setMode(PWMC_Mode mode) {
			this->_mode = mode;
		};

		void _updateLastAction(void) {
			this->_lastAction = micros();
		};

		PWMC_Handshake &_doHandshake(void) {
			PWMC_Handshake &handshake = this->_handshake;
			PWMC_Mode &mode = this->_mode;
			BIT bit;

			static uint8_t bitsRead = 0;

			switch (handshake) {

				case NONE:
					if (mode == LISTEN && this->_readBit(bit) && bit == HIGH_BIT) {
						handshake = IN_PROCESS;
						bitsRead = 1;
					} else if (mode == TALK) {
						// do stuff
					}
					break;

				case IN_PROCESS:
					if (mode == LISTEN && this->_readBit(bit)) {
						if (bit == HIGH_BIT) {
							if (++bitsRead == 8) { // done
								handshake = ESTABLISHED;
							}
						} else { // handshake failed
							handshake = NONE;
						}
					} else if (mode == TALK) {
						// do stuff
					}
					break;

				case ESTABLISHED:
					// do nothing
					break;

			}

			return handshake;
		};

		bool _readBit(BIT &bit) {
			if (Avail::micros(&this->_window, &this->_lastAction)) {
				bit = digitalRead(this->_receivePin);
				this->_updateLastAction();
				return true;
			}

			return false;
		};

		void _sendBit(BIT = HIGH_BIT) {
		
		};

};

#endif // !PWM_COMMUNICATION_H
