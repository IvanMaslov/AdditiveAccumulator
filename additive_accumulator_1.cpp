#include "additive_accumulator_1.h"

#include "sha256.h"

statement::statement() = default;

statement::statement(const std::string &x, const std::string &prev, const std::string &parent)
	: x(x), prev(prev), parent(parent)
{}

size_t additive_accumulator::pred(const size_t &k) {
	return k & (k - 1);
}

size_t additive_accumulator::zeros(size_t k) {
	size_t res = 0;
	while (k > 0) {
		res++;
		k &= (k - 1);
	}
	return res;
}

witness additive_accumulator::wit_create(const size_t &j, const size_t &i) {
	statement p(x[i], r[i - 1], r[pred(i)]);
	if (i == j)
		return{ p };
	witness res = (pred(i) < j) ? wit_create(j, i - 1) : wit_create(j, pred(i));
	res.push_back(p);
	return res;
}

bool additive_accumulator::wit_verify(const std::string &z, const size_t &j, const size_t &i, witness &w) {
	statement p = w.back();
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

additive_accumulator::additive_accumulator() {
	size = 0;
	x = { "" };
	r = { "" };
	s = { "" };
}

void additive_accumulator::add(const std::string &z) {
	if (z.empty())
		throw std::invalid_argument("Adding empty string");
	size++;
	x.push_back(z);
	r.push_back(sha256(z + r.back() + r[pred(size)]));
	if (zeros(size) >= s.size())
		s.push_back("");
	s[zeros(size)] = sha256(z + s[zeros(size - 1)] + s[zeros(pred(size))]);
}

witness additive_accumulator::create_witness(const size_t &num, const size_t &i) {
	return wit_create(num, i);
}

witness additive_accumulator::create_witness(const size_t &num) {
	return wit_create(num, size);
}

bool additive_accumulator::verify_witness(const std::string &z, const size_t &num, const size_t &i, witness w) {
	return wit_verify(z, num, i, w);
}