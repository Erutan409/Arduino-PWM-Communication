#ifndef PWMC_BYTE_H
#define PWMC_BYTE_H

namespace PWMC {

	class Byte {

		public:

			Byte(void);

			Byte(char byte) {
				(*this->fetch()) = byte;
			};

			Byte &writeBit(BIT bit) {
				if (!this->finished()) {
					bitWrite(this->_byte, this->_currentBit++, (bool)bit);
				}

				return *this;
			};

			BIT readBit() {
				BIT bit = (BIT)bitRead(this->_byte, this->_currentBit++);

				return bit;
			};

			bool finished(void) {
				return _currentBit == 8;
			};

			uint8_t *fetch(void) {
				return &this->_byte;
			};

			Byte &operator++ () {
				this->writeBit(BIT::HIGH_BIT);

				return *this;
			};

		private:
			uint8_t _byte, _currentBit = 0;

	};

}

#endif // !PWMC_BYTE_H