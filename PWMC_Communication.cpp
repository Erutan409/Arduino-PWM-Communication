#include <PWMC_Communication.h>

namespace PWMC {

	Communication::Communication(uint8_t sendPin, uint8_t receivePin) {
		this->_sendPin = sendPin;
		this->_receivePin = receivePin;
	}

	Mode *Communication::getMode(void) {
		return &this->_mode;
	}

	Communication &Communication::send(char byte) {
		this->_setMode(Mode::TALK);

		return *this;
	}

	void Communication::run(void) {
		Mode &mode = this->_mode;
	}

	bool Communication::ready(void) {
		return (*this->_getByte()).finished();
	}

	char Communication::read(void) {
		Byte &byte = *this->_getByte();

		if (byte.finished()) {
			uint8_t data = *byte.fetch();
			this->_goodbyeByte();

			return (char)data;
		}

		return char("");
	}

	void Communication::_setMode(Mode mode) {
		this->_mode = mode;
	}

	Byte *Communication::_getByte(void) {
		if (this->_byte == nullptr) {
			this->_byte = new Byte();
		}

		return this->_byte;
	}

	void Communication::_goodbyeByte(void) {
		this->_byte = nullptr;
	}

	bool Communication::_readBit(BIT &bit) {
		if (this->_track.nextWindow()) {
			bit = (BIT)digitalRead(this->_receivePin);
			this->_track.bumpWindow();

			return true;
		}

		return false;
	}

	void Communication::_sendBit(BIT &bit = BIT::HIGH_PIT) {
		// do nothing
	}

}