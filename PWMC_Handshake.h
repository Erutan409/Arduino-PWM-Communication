#ifndef PWMC_HANDSHAKE_H
#define PWMC_HANDSHAKE_H

namespace PWMC {

	typedef void (*HandshakeCallback)(void);
	
	class Handshake {

		public:
			Handshake() {};
			Handshake &negotiate(void) {};

			Handshake &loadNoneFunction(HandshakeCallback func) {
				this->_none = func;
				return *this;
			};

			Handshake &loadInProcessFunction(HandshakeCallback func) {
				this->_none = func;
				return *this;
			};

			Handshake &loadEstablishedFunction(HandshakeCallback func) {
				this->_none = func;
				return *this;
			};

		private:
			volatile HandshakeCallback _none, _inProcess, _established;

	};

}

#endif // !PWMC_HANDSHAKE_H
