#ifndef PWMC_HANDSHAKE_H
#define PWMC_HANDSHAKE_H

namespace PWMC {

	class Communication;

	using State = HandshakeState;

	class Handshake {

		public:
			Handshake(Communication *comm);
			Handshake &negotiate(void);


		private:
			Communication *_comm;
			State _state = State::NONE;
	};

}

#endif // !PWMC_HANDSHAKE_H