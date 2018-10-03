// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len <= 0)
		throw "wrong bit length";

	BitLen = len;
	MemLen = (BitLen / (sizeof(TELEM) * 8)) + 1;
	pMem = new TELEM[MemLen];

	
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;

	pMem = new TELEM[MemLen];

	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0 || n >= BitLen)
		throw "Out of BitField range";
	return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << n;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	return pMem[GetMemIndex(n)];
}

// битовые операции	

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	
	MemLen = bf.MemLen;
	delete[] pMem;
	pMem = new TELEM[MemLen];
	BitLen = bf.BitLen;
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];

	return *this;

}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i])
			return 0;

	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int min;
	TBitField res(*this);
	min = bf.MemLen;
	if (bf.BitLen > BitLen)
	{
		res = bf;
		min = MemLen;
	}

	for (int i = 0; i < min; i++)
		res.pMem[i] = pMem[i] | bf.pMem[i];

	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int min;
	TBitField res(*this);
	min = bf.MemLen;
	if (bf.BitLen > BitLen)
	{
		res = bf;
		min = MemLen;
	}

	for (int i = 0; i < min; i++)
		res.pMem[i] = pMem[i] & bf.pMem[i];

	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(BitLen);
	for (int i = 0; i < BitLen; i++)
		if (GetBit(i) == 0)
			res.SetBit(i);

	return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	return ostr;
}
