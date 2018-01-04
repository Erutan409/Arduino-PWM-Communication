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

struct PWMC_TimeTracking {

	public:

		PWMC_TimeTracking(uint32_t *window) {
			this->_window = window;
			uint32_t micros = ::micros();
			(*this->commStart()) = micros;
			(*this->commLast()) = micros;
		};

		uint32_t *commStart(void) {
			return &this->_time[0];
		};

		uint32_t *commLast(void) {
			return &this->_time[1];
		};

		uint32_t *updateCommStart(void) {
			return this->_updateCommVal(this->commStart());
		};

		uint32_t *updateCommLast(void) {
			return this->_updateCommVal(this->commLast());
		};

		bool nextWindow(uint16_t bitsTransfered = 0) {
			uint32_t check = *this->_window * bitsTransfered;

			return Avail::micros(&check, this->commStart());
		};

	private:
		uint32_t _time[2] = {0};
		uint32_t *_window;

		uint32_t *_updateCommVal(uint32_t *val) {
			(*val) = micros();
			return val;
		};

};

struct PWMC_BitTracking {

	public:

		uint16_t *bitsReadInByte(void) {
			return &this->_bits[0];
		};

		uint16_t *totalBitsRead(void) {
			return &this->_bits[1];
		};

		uint16_t *updateBitsReadInByte(void) {
			return this->_updateBitsVal(this->bitsReadInByte());
		};

		uint16_t *updateTotalBitsRead(void) {
			return this->_updateBitsVal(this->totalBitsRead());
		};

		void resetBitsReadInByte(void) {
			(*this->bitsReadInByte()) = 0;
		};

		void resetTotalBitsRead(void) {
			(*this->totalBitsRead()) = 0;
		};

		void resetAll(void) {
			this->resetBitsReadInByte();
			this->resetTotalBitsRead();
		};

	private:
		uint16_t _bits[2] = { 0 };

		uint16_t *_updateBitsVal(uint16_t *val) {
			(*val)++;
			return val;
		};

};

class PWMC {

	public:

		PWMC(uint8_t sendPin, uint8_t receivePin) {
			this->_sendPin = sendPin;
			this->_receivePin = receivePin;
			this->_track = new PWMC_TimeTracking(&this->_window);
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
		PWMC_TimeTracking *_track;
		const uint32_t _window = 100; // microseconds
		uint8_t _byte = 0x0;
		uint8_t _bitsRead = 0x0;
		uint8_t _bitPos = 0x0;

		void _setMode(PWMC_Mode mode) {
			this->_mode = mode;
		};

		PWMC_Handshake &_doHandshake(void) {
			PWMC_Handshake &handshake = this->_handshake;
			PWMC_Mode &mode = this->_mode;
			BIT bit;
			uint8_t &bitsRead = this->_bitsRead;

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
			if ((*this->_track).nextWindow()) {
				bit = digitalRead(this->_receivePin);
				return true;
			}

			return false;
		};

		void _sendBit(BIT = HIGH_BIT) {
		
		};

};

#endif // !PWM_COMMUNICATION_H
