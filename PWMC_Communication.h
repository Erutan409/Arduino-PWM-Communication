#ifndef PWM_COMMUNICATION_H
#define PWM_COMMUNICATION_H

namespace PWMC {

	class Communication {

		public:

			Communication(uint8_t sendPin, uint8_t receivePin) {
				this->_sendPin = sendPin;
				this->_receivePin = receivePin;
			};

			Mode *getMode(void) {
				return &this->_mode;
			};

			Communication &send(char byte) {
				this->_setMode(Mode::TALK);

				return *this;
			};

			void run(void) {
				Mode &mode = this->_mode;
			};

			bool ready(void) {
				return (*this->_getByte()).finished();
			};

			char read(void) {
				Byte &byte = *this->_getByte();

				if (byte.finished()) {
					uint8_t data = *byte.fetch();
					this->_goodbyeByte();
					return (char)data;
				}

				return char("");
			};

		private:
			uint8_t _sendPin, _receivePin;
			Mode _mode = Mode::LISTEN;
			TimeTracking _track = *new TimeTracking(100);

			Handshake _handshake = (*new Handshake()).loadNoneFunction(HandshakeCallback())
				.loadInProcessFunction(HandshakeCallback())
				.loadEstablishedFunction(HandshakeCallback());

			Byte *_byte;

			void _setMode(Mode mode) {
				this->_mode = mode;
			};

			Byte *_getByte(void) {
				if (this->_byte == nullptr) {
					this->_byte = new Byte();
				}

				return this->_byte;
			};

			void _goodbyeByte(void) {
				this->_byte = nullptr;
			};

			bool _readBit(BIT &bit) {
				if (this->_track.nextWindow()) {
					bit = (BIT)digitalRead(this->_receivePin);
					this->_track.bumpWindow();

					return true;
				}

				return false;
			};

			void _sendBit(BIT = BIT::HIGH_BIT) {

			};

	};

}

#endif // !PWM_COMMUNICATION_H
