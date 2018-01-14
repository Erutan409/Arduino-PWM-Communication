#ifndef PWMC_HANDSHAKE_H
#define PWMC_HANDSHAKE_H

// forward declare
class PWMC_Communication;

using Handshake = PWMC_Handshake_State;
using Mode = PWMC_Mode;
using Byte = PWMC_Byte;
using Communication = PWMC_Communication;

class PWMC_Handshake {

	public:
		PWMC_Handshake(PWMC_Communication *pwmc) {
			this->_pwmc = pwmc;
		};

		PWMC_Handshake_State *state(void) {
			return &this->_state;
		};

		PWMC_Handshake &doHandshake() {
			Communication comm = *this->_pwmc;
			Handshake &handshake = this->_state;
			Mode &mode = comm->_mode;
			BIT bit;

			switch (handshake) {
			
				case Handshake::NONE:
					if (mode == Mode::LISTEN && comm->_readBit(bit) && bit == BIT::HIGH_BIT) {
						handshake = Handshake::IN_PROCESS;
						// ++byte;
					} else if (mode == Mode::TALK) {
						// do stuff
					}
					break;

				case Handshake::IN_PROCESS:
					if (mode == Mode::LISTEN && ) {
					
					}
					break;

			}

			return *this;
		};


	private:
		Communication *_pwmc;
		Handshake _state;

};

#endif // !PWMC_HANDSHAKE_H