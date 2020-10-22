#include "additive_accumulator_1.h"

#include <stdexcept>

statement_1::statement_1() = default;

statement_1::statement_1(const std::string &x, const std::string &prev, const std::string &parent)
	: x(x), prev(prev), parent(parent)
{}

additive_accumulator_1::witness additive_accumulator_1::wit_create(const size_t &j, const size_t &i) {
	statement_1 p(x[i], r[i - 1], r[pred(i)]);
	if (i == j)
		return{ p };
	witness res = (pred(i) < j) ? wit_create(j, i - 1) : wit_create(j, pred(i));
	res.push_back(p);
	return res;
}

bool additive_accumulator_1::wit_verify(const std::string &z, const size_t &j, const size_t &i, witness &w) {
	statement_1 p = w.back();
	w.pop_back();
	if (sha256(p.x + p.prev + p.parent) != r[i])
		return false;
	if (i == j)
		return z == p.x;
	if (pred(i) < j)
		return wit_verify(z, j, i - 1, w);
	else
		return wit_verify(z, j, pred(i), w);
}

additive_accumulator_1::additive_accumulator_1() {
	size = 0;
	x = { "" };
	r = { "" };
	s = { "" };
}

void additive_accumulator_1::add(const std::string &z) {
	if (z.empty())
		throw std::invalid_argument("Adding empty string");
	size++;
	x.push_back(z);
	r.push_back(sha256(z + r.back() + r[pred(size)]));
	if (zeros(size) >= s.size())
		s.push_back("");
	s[zeros(size)] = sha256(z + s[zeros(size - 1)] + s[zeros(pred(size))]);
}

additive_accumulator_1::witness additive_accumulator_1::create_witness(const size_t &num, const size_t &i) {
	return wit_create(num, i);
}

additive_accumulator_1::witness additive_accumulator_1::create_witness(const size_t &num) {
	return wit_create(num, size);
}

bool additive_accumulator_1::verify_witness(const std::string &z, const size_t &num, const size_t &i, witness w) {
	return wit_verify(z, num, i, w);
}