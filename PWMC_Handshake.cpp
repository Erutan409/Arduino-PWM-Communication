#include <PWMC_Handshake.h>

namespace PWMC {

	Handshake::Handshake(Communication *comm) {
		this->_comm = comm;
	}

	Handshake &Handshake::negotiate(void) {
		Communication &comm = (*this->_comm);
		State &state = this->_state;
		Mode &mode = comm._mode;
		BIT bit;

		switch (state) {

		case State::NONE:
			if (mode == Mode::LISTEN && comm._readBit(bit) && bit == BIT::HIGH_BIT) {
				state = State::IN_PROCESS;
				++comm._byte;
			} else if (mode == Mode::TALK) {
				// do stuff
			}
			break;

		case State::IN_PROCESS:
			if (mode == Mode::LISTEN) {

			}
			break;

		case State::ESTABLISHED:
			// do nothing
			break;

		}

		return *this;
	}

}