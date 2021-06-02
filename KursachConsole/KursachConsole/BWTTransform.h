#pragma once

#include <string>

// –еализаци€ алгоритма bwt котора€ сортирует последовательность 
// таким образом чтобы образовать последовательности одинаковых символов
// ¬озвращает количество данных в байтах которые необходимы дл€ декодировани€
int bwt(std::string finname, std::string foutname, int shift = 0);
void bwtDecode(std::string finname, std::string foutname, int shift = 0);

// ÷иклична€ строка котора€ упростит хранение всех цикличных строк в пам€ти
class CyclicString {
public:
	CyclicString(const char* pch, size_t shift) : m_pch(pch), m_shift(shift) {}
	size_t getShift() const { return m_shift; }
	char getLastSymb() const { 
		if (m_shift) {
			return *(m_pch + m_shift - 1);
		}

		const char* curr = m_pch;
		while (*curr != 0) {
			++curr;
		}
		return *(curr - 1);
	}

	bool operator< (const CyclicString& other) const;

private:
	const char* m_pch;
	size_t m_shift;
};