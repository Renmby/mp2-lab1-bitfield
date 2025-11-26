// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
using namespace std;
TBitField::TBitField(int len) {
	if (len < 0) {
		throw("incorrect length");
	}
	BitLen = len;
	MemLen = (BitLen + sizeof(uint)*8 - 1) / (sizeof(uint)*8);
	pMem = new uint[MemLen];
	for (int i = 0;i < MemLen;i++) {
		pMem[i] = 0;
	}
}
TBitField::TBitField(const TBitField& bf) { // конструктор копирования
	if (BitLen != bf.BitLen) {
		throw("mismatch");
	}
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new uint[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
}
TBitField::~TBitField() {
	delete[] pMem;
	pMem = nullptr;
}
int TBitField::GetMemIndex(const int n) const { // индекс Мем для бита 
	return (n / (sizeof(uint) * 8));
}
uint TBitField::GetMemMask(const int n) const { // битовая маска для бита n
	return 1 << (n % (sizeof(uint) * 8)); // << сдвиг влево
}
// доступ к битам битового поля
int TBitField::GetLength(void) const { // получить длину (к-во битов)
	//return MemLen / BitLen;
	return BitLen;
}
//void TBitField::SetBit(const int n) { // установить бит
//	if ((n<0)||(n>=BitLen)) {
//		throw("incorrect length");
//	}
//	int index = GetMemIndex(n);
//	uint mask = GetMemMask(n);
//	pMem[index] = pMem[index] | mask;
//}
void TBitField::SetBit(const int n) // установить бит
{
	if ((n<0)||(n>=BitLen)) {
		throw("incorrect length");
	}
	int index_n = GetMemIndex(n);
	uint maska = GetMemMask(n);
	pMem[index_n] |= maska;
}
void TBitField::ClearBit(const int n) { // очистить бит
	if ((n < 0) || (n >= BitLen)) {
		throw("incorrect length");
	}
	int index = GetMemIndex(n);
	uint mask = GetMemMask(n);
	pMem[index] = pMem[index] & ~mask; // ~ побитовое отрицание
}
int TBitField::GetBit(const int n) const { // получить значение бита
	if ((n < 0) || (n >= BitLen)) {
		throw("incorrect length");
	}
	int index = GetMemIndex(n);
	uint mask = GetMemMask(n);
	return (pMem[index] & mask) != 0;
}
// битовые операции
TBitField& TBitField::operator=(const TBitField& bf) { // присваивание
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	for (int i = 0;i < bf.MemLen;i++) {
		pMem[i] = bf.pMem[i];
	}
	return *this;
}
int TBitField::operator==(const TBitField& bf) const { // сравнение
	int a = 1;
	if (bf.BitLen != BitLen) {
		a = 0;
	}
	for (int i = 0;i < bf.MemLen;i++) {
		if (pMem[i] != bf.pMem[i]) {
			a = 0;
			break;
		}
	}
	return a;
}
int TBitField::operator!=(const TBitField& bf) const { // сравнение
	int a = 0;
	if (bf.BitLen != BitLen) {
		a = 1;
	}
	int k = 0;
	for (int i = 0;i < bf.MemLen;i++) {
		if (pMem[i] == bf.pMem[i]) {
			k++;
		}
	}
	if (k == MemLen) {
		a = 0;
	}
	else {
		a = 1;
	}
	k = 0;
	return a;
}
//TBitField TBitField::operator|(const TBitField& bf){ // операция "или"
//	if (BitLen != bf.BitLen) {
//		throw("mismatch");
//	}
//	if (BitLen == bf.BitLen) {
//		for (int i = 0;i < MemLen;i++) {
//			pMem[i] = pMem[i] | bf.pMem[i];
//		}
//	}
//	return *this;
//}
TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	int max_Len = max(BitLen, bf.BitLen);
	TBitField res(max_Len);

	for (int i = 0; i < MemLen; ++i) {
		res.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; ++i) {
		res.pMem[i] |= bf.pMem[i];
	}
	return res;
}
//TBitField TBitField::operator&(const TBitField& bf) {// операция "и"
//	int min_length = min(BitLen, bf.BitLen);
//	TBitField A(min_length);
//	for (int i = 0;i < min_length;i++) {
//		A.pMem[i] = pMem[i] & bf.pMem[i];
//	}
//	return A;
//}
TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	int max_Len = max(BitLen, bf.BitLen);
	int min_Size = min(MemLen, bf.MemLen);
	TBitField res(max_Len);

	for (int i = 0; i < min_Size; ++i) {
		res.pMem[i] = pMem[i] & bf.pMem[i];
	}

	return res;
}
//TBitField TBitField::operator~(void) {// отрицание
//	TBitField A(BitLen);
//	for (int i = 0;i < MemLen;i++) {
//		A.pMem[i] = ~pMem[i];
//	}
//	return A;
//}
TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(BitLen);

	for (int i = 0; i < MemLen; ++i) {
		res.pMem[i] = ~pMem[i];
	}

	int bitsInLast = BitLen % (sizeof(uint) * 8);
	if (bitsInLast != 0) {
		uint mask = (1 << bitsInLast) - 1;
		res.pMem[MemLen - 1] &= mask;
	}

	return res;
}
// ввод/вывод
istream& operator>>(istream& istr, TBitField& bf) { // ввод
	for (int i = 0;i < bf.MemLen;i++) {
		int value;
		istr >> value;
		if (value == 1) {
			bf.SetBit(i);
		}
		else {
			bf.ClearBit(i);
		}
	}
	return istr;
}
ostream& operator<<(ostream& ostr, const TBitField& bf) { // вывод
	for (int i = 0;i < bf.MemLen;i++) {
		ostr << bf.GetBit(i);
	}
	return ostr;
}