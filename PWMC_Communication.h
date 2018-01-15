#ifndef PWM_COMMUNICATION_H
#define PWM_COMMUNICATION_H

namespace PWMC {

	class Communication {
		
		friend class Handshake;

		public:
			Communication(uint8_t sendPin, uint8_t receivePin);
			Mode *getMode(void);
			Communication &send(char byte);
			void run(void);
			bool ready(void);
			char read(void);

		private:
			uint8_t _sendPin, _receivePin;
			Mode _mode = Mode::LISTEN;
			TimeTracking _track = *(new TimeTracking(100));
			Handshake _handshake = *(new Handshake(this));
			Byte *_byte;

			void _setMode(Mode mode);
			Byte *_getByte(void);
			void _goodbyeByte(void);
			bool _readBit(BIT &bit);
			void _sendBit(BIT = BIT::HIGH_BIT);

	};

}

#endif // !PWM_COMMUNICATION_H
