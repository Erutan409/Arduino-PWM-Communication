#ifndef PWMC_TIMETRACKING_H
#define PWMC_TIMETRACKING_H

#include <Avail.h>

class PWMC_TimeTracking {

	public:

		PWMC_TimeTracking(const uint32_t window) {
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
			uint32_t check = this->_window * bitsTransfered;

			return Avail::micros(&check, this->commStart());
		};

		uint32_t *bumpWindow(void) {
			uint32_t *start = this->commStart();

			(*this->commLast()) = (*start += this->_window);

			return start;
		};

		PWMC_TimeTracking &operator++ () {
			this->bumpWindow();

			return *this;
		};

	private:
		uint32_t _time[2] = { 0 };
		uint32_t _window;

		uint32_t *_updateCommVal(uint32_t *val) {
			(*val) = micros();
			return val;
		};

};

#endif // !PWMC_TIMETRACKING_H