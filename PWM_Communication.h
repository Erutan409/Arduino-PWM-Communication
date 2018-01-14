#ifndef PWM_COMMUNICATION_H
#define PWM_COMMUNICATION_H

class PWMC_Communication {

	public:

		PWMC_Communication(uint8_t sendPin, uint8_t receivePin) {
			this->_sendPin = sendPin;
			this->_receivePin = receivePin;
		};

		PWMC_Mode *getMode(void) {
			return &this->_mode;
		};

		PWMC_Communication &send(char byte) {
			this->_setMode(PWMC_Mode::TALK);

			return *this;
		};

		void run(void) {
			PWMC_Mode &mode = this->_mode;
		};

		bool ready(void) {
			return (*this->_getByte()).finished();
		};

		char read(void) {
			PWMC_Byte &byte = *this->_getByte();

			if (byte.finished()) {
				uint8_t data = *byte.fetch();
				this->_goodbyeByte();
				return (char)data;
			}

			return char("");
		};

	private:
		friend class PWMC_Handshake;

		uint8_t _sendPin, _receivePin;
		PWMC_Mode _mode = PWMC_Mode::LISTEN;
		PWMC_TimeTracking _track = *(new PWMC_TimeTracking(100));
		PWMC_Handshake _handshake = *(new PWMC_Handshake(this));
		PWMC_Byte *_byte;

		void _setMode(PWMC_Mode mode) {
			this->_mode = mode;
		};

		PWMC_Byte *_getByte(void) {
			if (this->_byte == nullptr) {
				this->_byte = new PWMC_Byte();
			}

			return this->_byte;
		};

		void _goodbyeByte(void) {
			this->_byte = nullptr;
		};

		bool _readBit(BIT &bit) {
			if ((*this->_track).nextWindow()) {
				bit = (BIT)digitalRead(this->_receivePin);
				(*this->_track).bumpWindow();

				return true;
			}

			return false;
		};

		void _sendBit(BIT = BIT::HIGH_BIT) {
		
		};

		PWMC_Handshake &_doHandshake(void) {
			PWMC_Handshake &handshake = this->_handshake;
			PWMC_Mode &mode = this->_mode;
			BIT bit;
			PWMC_Byte &byte = (*this->_getByte());

			switch (handshake) {

			case NONE:
				if (mode == LISTEN && this->_readBit(bit) && bit == HIGH_BIT) {
					handshake = IN_PROCESS;
					++byte;
				}
				else if (mode == TALK) {
					// do stuff
				}
				break;

			case IN_PROCESS:
				if (mode == LISTEN && this->_readBit(bit)) {
					if (bit == HIGH_BIT && (++byte).finished()) {
						handshake = ESTABLISHED;
					}
					else if (bit == LOW_BIT) { // handshake failed
						handshake = NONE;
						this->_goodbyeByte();
					}
				}
				else if (mode == TALK) {
					// do stuff
				}
				break;

			case ESTABLISHED:
				// do nothing
				break;

			}

			return handshake;
		};

};

#endif // !PWM_COMMUNICATION_H
