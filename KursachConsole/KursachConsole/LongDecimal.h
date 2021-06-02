#pragma once

#include <vector>
#include <ostream>

class LongDecimal
{
public:
	using byte_t = unsigned char;

	LongDecimal();
	LongDecimal(double fraction, uint8_t bytesLimit = -1);
	LongDecimal(byte_t* bytes, unsigned size);
	LongDecimal(std::vector<byte_t> bytes);
	LongDecimal(const LongDecimal& other);
	LongDecimal(LongDecimal&& other) noexcept;
	~LongDecimal();

	std::vector<byte_t> getBytes() const { return std::vector<byte_t>(m_bytes, m_bytes + m_size); }
	double toDouble() const;
	unsigned size() const { return m_size; }

	LongDecimal& operator= (const LongDecimal& other);

	LongDecimal operator~ () const;

	LongDecimal& operator&= (const LongDecimal& other);
	friend LongDecimal operator& (const LongDecimal& left, const LongDecimal& right);
	LongDecimal& operator|= (const LongDecimal& other);
	friend LongDecimal operator| (const LongDecimal& left, const LongDecimal& right);
	LongDecimal& operator^= (const LongDecimal& other);
	friend LongDecimal operator^ (const LongDecimal& left, const LongDecimal& right);

	friend LongDecimal operator<< (LongDecimal ld, unsigned shift);
	LongDecimal& operator<<= (unsigned shift);
	friend LongDecimal operator>> (LongDecimal ld, unsigned shift);
	LongDecimal& operator>>= (unsigned shift);

	friend LongDecimal operator+ (const LongDecimal& left, const LongDecimal& right);
	LongDecimal& operator+= (const LongDecimal& other);
	friend LongDecimal operator- (const LongDecimal& left, const LongDecimal& right);
	LongDecimal& operator-= (const LongDecimal& other);
	friend LongDecimal operator* (const LongDecimal& left, const LongDecimal& right);
	LongDecimal& operator*= (const LongDecimal& other);

	bool operator<(const LongDecimal& other) const;
	bool operator==(const LongDecimal& other) const;
	bool operator>(const LongDecimal& other) const;
	bool operator<=(const LongDecimal& other) const;
	bool operator>=(const LongDecimal& other) const;
	bool operator!=(const LongDecimal& other) const;

	friend std::ostream& operator<< (std::ostream& out, const LongDecimal& ld);
private:
	void push_byte(byte_t byte);
	void resize();

	byte_t* m_bytes;
	unsigned m_size;
	unsigned m_capacity;
};

