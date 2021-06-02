#include "LongDecimal.h"

#define BYTE_LENGTH 8

using namespace std;

LongDecimal operator&(const LongDecimal& left, const LongDecimal& right)
{
    LongDecimal res;

    auto lit = left.m_bytes;
    auto lend = left.m_bytes + left.m_size;
    auto rit = right.m_bytes;
    auto rend = right.m_bytes + right.m_size;

    while (lit != lend && rit != rend) {
        res.push_byte(*lit & *rit);
        ++lit;
        ++rit;
    }

    return res;
}

LongDecimal operator|(const LongDecimal& left, const LongDecimal& right)
{
    LongDecimal res;

    auto lit = left.m_bytes;
    auto lend = left.m_bytes + left.m_size;
    auto rit = right.m_bytes;
    auto rend = right.m_bytes + right.m_size;

    while (lit != lend && rit != rend) {
        res.push_byte(*lit | *rit);
        ++lit;
        ++rit;
    }

    while (lit != lend) {
        res.push_byte(*lit);
        ++lit;
    }

    while (rit != rend) {
        res.push_byte(*rit);
        ++rit;
    }

    return res;
}

LongDecimal operator^(const LongDecimal& left, const LongDecimal& right)
{
    LongDecimal res;

    auto lit = left.m_bytes;
    auto lend = left.m_bytes + left.m_size;
    auto rit = right.m_bytes;
    auto rend = right.m_bytes + right.m_size;

    while (lit != lend && rit != rend) {
        res.push_byte(*lit ^ *rit);
        ++lit;
        ++rit;
    }

    while (lit != lend) {
        res.push_byte(*lit);
        ++lit;
    }

    while (rit != rend) {
        res.push_byte(*rit);
        ++rit;
    }

    return res;
}

LongDecimal operator<<(LongDecimal ld, unsigned shift)
{
    return (ld << shift);
}

LongDecimal operator>>(LongDecimal ld, unsigned shift)
{
    return (ld >>= shift);
}

LongDecimal operator+(const LongDecimal& left, const LongDecimal& right)
{
    // Для того чтобы сложить два числа нужно сложить их биты таким образом что если
    // единице соответствует другая единица то в этот разряд записывается ноль
    // а в следующий разряд помимо суммы двух бит добавляется 1
    // Таким образом чтобы получить все дополнительные биты мы считаем побитовую сумму &
    // и делаем побитовый сдвиг влево на 1
    // 
    // Пример:
    // .375 + .125
    // 0b011 + 0b001
    // (0b011 & 0b001) << 1 = 0b001 << 1 = 0b01
    // 0b011 ^ 0b001 = 0b01
    // Поскольку у нас есть биты которые переносятся в следующий разряд повторно выполняем сложение
    // 0b01 + 0b01 = .25 + .25
    // (0b01 & 0b01) << 1 = 0b01 << 1 = 0b1
    // 0b01 ^ 0b01 = 0b0
    // Поскольку у нас есть биты которые переносятся в следующий разряд повторно выполняем сложение
    // 0b1 + 0b0 = .5 + 0
    // (0b1 & 0b0) << 1 = 0b0 << 1 = 0b0
    // 0b1 ^ 0b0 = 0b1
    // Ответ 0b1 = .5

    LongDecimal bitwiseAnd = left & right;
    LongDecimal bitwiseXor = left ^ right;

    LongDecimal tmp;
    while (bitwiseAnd != 0) {
        bitwiseAnd <<= 1;
        tmp = bitwiseXor ^ bitwiseAnd;
        bitwiseAnd &= bitwiseXor;
        bitwiseXor = tmp;
    }

    return bitwiseXor;
}

LongDecimal operator-(const LongDecimal& left, const LongDecimal& right)
{
    if (right == 0) return left;
    LongDecimal negative = ~right + (LongDecimal(.5) >> (right.m_size * BYTE_LENGTH - 1));
    return left + negative;
}

LongDecimal operator*(const LongDecimal& left, const LongDecimal& right)
{
    LongDecimal a = left, b = right, result = 0;

    while (b != 0) {
        a >>= 1;

        if ((b & .5) != 0) {
            result = result + a;
        }

        b <<= 1;
    }

    return result;
}

std::ostream& operator<<(std::ostream& out, const LongDecimal& ld)
{
    return (out << ld.toDouble());
}

LongDecimal::LongDecimal()
{
    m_capacity = 1;
    m_size = 0;
    m_bytes = new byte_t[m_capacity];
}

LongDecimal::LongDecimal(double fraction, uint8_t bytesLimit) : LongDecimal()
{
    fraction -= (int)fraction;
    byte_t* currentByte = 0;
    uint8_t counter = 0;
    while (fraction) {
        if (!(counter % BYTE_LENGTH)) {
            if (bytesLimit <= m_size) break;
            push_byte(0);
            currentByte = m_bytes + m_size - 1;
            counter = 0;
        }
        else {
            *currentByte <<= 1;
        }

        fraction *= 2;

        if (fraction >= 1) {
            *currentByte |= 1;
            fraction--;
        }

        counter++;
    }

    if (currentByte) *currentByte <<= BYTE_LENGTH - counter;
}

LongDecimal::LongDecimal(byte_t* bytes, unsigned size) : LongDecimal()
{
    auto it = bytes;
    auto itend = bytes + size;

    while (it != itend) {
        push_byte(*it);
        ++it;
    }
}

LongDecimal::LongDecimal(std::vector<byte_t> bytes) : LongDecimal()
{
    for (const auto& byte : bytes) {
        push_byte(byte);
    }
}

LongDecimal::LongDecimal(const LongDecimal& other)
{
    m_capacity = other.m_capacity;
    m_bytes = new byte_t[m_capacity];
    m_size = 0;

    auto it = other.m_bytes;
    auto itend = other.m_bytes + other.m_size;

    while (it != itend) {
        push_byte(*it);
        ++it;
    }
}

LongDecimal::LongDecimal(LongDecimal&& other) noexcept
{
    m_bytes = other.m_bytes;
    m_size = other.m_size;
    m_capacity = other.m_capacity;

    other.m_bytes = 0;
}

LongDecimal::~LongDecimal()
{
    delete[] m_bytes;
}

double LongDecimal::toDouble() const
{
    double bitValue = .5;
    double res = 0;

    for (unsigned i = 0; i < m_size; i++) {
        if (!bitValue) break;

        for (byte_t bit = 1 << 7; bit; bit >>= 1) {
            res += m_bytes[i] & bit ? bitValue : 0;
            bitValue /= 2;
        }
    }

    return res;
}

LongDecimal& LongDecimal::operator=(const LongDecimal& other)
{
    delete[] m_bytes;
    m_size = 0;
    m_capacity = other.m_capacity;
    m_bytes = new byte_t[m_capacity];

    for (unsigned i = 0; i < other.m_size; i++) {
        push_byte(other.m_bytes[i]);
    }

    return *this;
}

LongDecimal LongDecimal::operator~() const
{
    LongDecimal res;
    for (unsigned i = 0; i < m_size; i++) {
        res.push_byte(~m_bytes[i]);
    }
    return res;
}

LongDecimal& LongDecimal::operator&=(const LongDecimal& other)
{
    *this = *this & other;

    return *this;
}

LongDecimal& LongDecimal::operator|=(const LongDecimal& other)
{
    *this = *this | other;

    return *this;
}

LongDecimal& LongDecimal::operator^=(const LongDecimal& other)
{
    *this = *this ^ other;

    return *this;
}

LongDecimal& LongDecimal::operator<<=(unsigned shift)
{
    if (shift != 1) {
        for (unsigned i = 0; i < shift; i++) {
            *this <<= 1;
        }

        return *this;
    }

    bool lastCarry = 0;
    bool carry = 0;

    for (auto it = m_bytes + m_size - 1, itend = m_bytes - 1; it != itend; --it) {
        carry = *it & (1 << 7);

        *it <<= 1;

        *it |= lastCarry;
        lastCarry = carry;
    }

    return *this;
}

LongDecimal& LongDecimal::operator>>=(unsigned shift)
{
    if (shift != 1) {
        for (unsigned i = 0; i < shift; i++) {
            *this >>= 1;
        }

        return *this;
    }

    bool lastCarry = 0;
    bool carry = 0;

    for (auto it = m_bytes, itend = m_bytes + m_size; it != itend; ++it) {
        carry = *it & 1;

        *it >>= 1;

        *it |= lastCarry << 7;
        lastCarry = carry;
    }

    if (lastCarry) push_byte(1 << 7);

    return *this;
}

LongDecimal& LongDecimal::operator+=(const LongDecimal& other)
{
    *this = *this + other;
    return *this;
}

LongDecimal& LongDecimal::operator-=(const LongDecimal& other)
{
    *this = *this - other;

    return *this;
}

LongDecimal& LongDecimal::operator*=(const LongDecimal& other)
{
    *this = *this * other;
    return *this;
}

bool LongDecimal::operator<(const LongDecimal& other) const
{
    auto it = m_bytes;
    auto itend = m_bytes + m_size;
    auto oit = other.m_bytes;
    auto oitend = other.m_bytes + other.m_size;

    while (it != itend && oit != oitend && *it == *oit) {
        ++it;
        ++oit;
    }

    // Если мы вышли из цикла то есть три варианта:
    // 
    // 1. Мы дошли до конца второго числа
    // Нам не нужно проверять первое так как второе уже точно не больше
    //
    // 2. Мы дошли до конца первого числа 
    // Тогда все байты первого равны соответствующим байтам второго
    // и нам нужно лишь проверить что второе число имеет дальше ненулевые байты
    //
    // 3. Какие-то байты оказались не равны
    // Просто возвращаем результат их сравнения
    
    if (oit == oitend) return false;

    if (it == itend) {
        while (oit != oitend) {
            if (*oit) return true;
            ++oit;
        }
        return false;
    }

    return *it < *oit;
}

bool LongDecimal::operator==(const LongDecimal& other) const
{
    auto it = m_bytes;
    auto itend = m_bytes + m_size;
    auto oit = other.m_bytes;
    auto oitend = other.m_bytes + other.m_size;

    while (it != itend && oit != oitend) {
        if (*it != *oit) return false;
        ++it;
        ++oit;
    }

    if (it != itend) {
        while (it != itend) {
            if (*it) return false;
            ++it;
        }
    }

    if (oit != oitend) {
        while (oit != oitend) {
            if (*oit) return false;
            ++oit;
        }
    }

    return true;
}

bool LongDecimal::operator>(const LongDecimal& other) const
{
    return other < *this;
}

bool LongDecimal::operator<=(const LongDecimal& other) const
{
    return !(*this > other);
}

bool LongDecimal::operator>=(const LongDecimal& other) const
{
    return !(*this < other);
}

bool LongDecimal::operator!=(const LongDecimal& other) const
{
    return !(*this == other);
}

void LongDecimal::push_byte(byte_t byte)
{
    if (m_size >= m_capacity) resize();
    m_bytes[m_size++] = byte;
}

void LongDecimal::resize()
{
    byte_t* oldBytes = m_bytes;

    m_capacity <<= 1;
    m_bytes = new byte_t[m_capacity];

    for (unsigned i = 0; i < m_size; i++) {
        m_bytes[i] = oldBytes[i];
    }

    delete[] oldBytes;
}
