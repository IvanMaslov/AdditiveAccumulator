#include "test_util.h"

namespace TestUtil {
	extern std::random_device rnd_dev = std::random_device();
	extern std::mt19937 rnd(rnd_dev());


	statement_1 break_statement_1(statement_1 w) {
		bool had = false;
		std::string x_orig, prev_orig, parent_orig;
		x_orig = w.x;
		prev_orig = w.prev;
		parent_orig = w.parent;
		if (rnd() % 100 < 4) {
			w.x.push_back(0);
			had |= true;
		}
		if (rnd() % 100 < 4) {
			w.x[0] = 0;
			had |= true;
		}
		if (rnd() % 100 < 4) {
			w.x.pop_back();
			had |= true;
		}
		
		if (rnd() % 100 < 4) {
			w.prev = w.x;
			had |= true;
		}
		if (rnd() % 100 < 4) {
			w.prev.push_back(0);
			had |= true;
		}
		if (rnd() % 100 < 4 && !w.prev.empty()) {
			w.prev[0] = 0;
			had |= true;
		}
		if (rnd() % 100 < 4 && !w.prev.empty()) {
			w.prev.pop_back();
			had |= true;
		}

		if (rnd() % 100 < 4) {
			w.parent = w.prev;
			had |= true;
		}
		if (rnd() % 100 < 4) {
			w.parent.push_back(0);
			had |= true;
		}
		if (rnd() % 100 < 4 && !w.parent.empty()) {
			w.parent[0] = 0;
			had |= true;
		}
		if (rnd() % 100 < 4 && !w.parent.empty()) {
			w.parent.pop_back();
			had |= true;
		}

		had = parent_orig != w.parent || prev_orig != w.prev || x_orig != w.x;
		if (!had) return break_statement_1(w);
		return w;
	}
	
	statement_2 break_statement_2(statement_2 w) {
		std::string x_orig, rh_orig;
		x_orig = w.x;
		rh_orig = w.rh;
		bool had = false;
		if (rnd() % 100 < 4) {
			w.x.push_back(0);
			had |= true;
		}
		if (rnd() % 100 < 4) {
			w.x[0] = 0;
			had |= true;
		}
		if (rnd() % 100 < 4) {
			w.x.pop_back();
			had |= true;
		}

		if (rnd() % 100 < 4) {
			w.rh = w.x;
			had |= true;
		}
		if (rnd() % 100 < 4 && !w.rh.empty()) {
			w.rh[0] = 0;
			had |= true;
		}

		had = rh_orig != w.rh || x_orig != w.x;
		if (!had) return break_statement_2(w);
		return w;
	}

	additive_accumulator_1::witness break_witness_1(additive_accumulator_1::witness arg) {
		bool had = false;
		for(auto& i : arg) {
			if (rnd() % 100 < 30) {
				i = break_statement_1(i);
				had = true;
			}
		}

		if (!had) return break_witness_1(arg);
		return arg;
	}

	additive_accumulator_2::witness break_witness_2(additive_accumulator_2::witness arg) {
		bool had = false;
		for(auto& i : arg) {
			if (rnd() % 100 < 30) {
				i = break_statement_2(i);
				had = true;
			}
		}

		if (!had) return break_witness_2(arg);
		return arg;
	}
}
