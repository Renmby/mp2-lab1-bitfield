// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле
#include "tbitfield.h"
using namespace std;
TBitField::TBitField(int len){
	BitLen = len;
	MemLen = ((len + sizeof(uint)) * 8 - 1) / (sizeof(uint) * 8);
	pMem = new uint[MemLen];
	for (int i = 0;i < MemLen;i++) {
		pMem[i] = 0;
	}
}
TBitField::TBitField(const TBitField& bf){ // конструктор копирования
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	for (int i = 0;i < bf.MemLen;i++) {
		pMem[i]= bf.pMem[i];
	}
}
TBitField::~TBitField(){
	//delete[] pMem;
}
int TBitField::GetMemIndex(const int n) const{ // индекс Мем для бита 
	return (n / (sizeof(uint) * 8));
}
uint TBitField::GetMemMask(const int n) const{ // битовая маска для бита n
	return 1 << (n % (sizeof(uint) * 8)); // << сдвиг влево
}
// доступ к битам битового поля
int TBitField::GetLength(void) const{ // получить длину (к-во битов)
	//return MemLen / BitLen;
	return BitLen;
}
void TBitField::SetBit(const int n){ // установить бит
	int index = GetMemIndex(n);
	uint mask = GetMemMask(n);
	pMem[index] =pMem[index]| mask;
}
void TBitField::ClearBit(const int n){ // очистить бит
	int index = GetMemIndex(n);
	uint mask = GetMemMask(n);
	pMem[index] = pMem[index] & ~mask; // ~ побитовое отрицание
}
int TBitField::GetBit(const int n) const { // получить значение бита
	int index = GetMemIndex(n);
	uint mask = GetMemMask(n);
	return (pMem[index] & mask) != 0;
}
// битовые операции
TBitField& TBitField::operator=(const TBitField& bf){ // присваивание
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	for (int i = 0;i < bf.MemLen;i++) {
		pMem[i] = bf.pMem[i];
	}
	return *this;
}
int TBitField::operator==(const TBitField& bf) const{ // сравнение
	bool a = 1;
	for (int i = 0;i < bf.MemLen;i++) {
		if (pMem[i] != bf.pMem[i]) {
			return 0;
			break;
		}
	}
	return a;
}
int TBitField::operator!=(const TBitField& bf) const{ // сравнение
	bool a = 0;
	for (int i = 0;i < bf.MemLen;i++) {
		if (pMem[i] == bf.pMem[i]) {
			return 1;
			break;
		}
	}
	return a;
}
TBitField TBitField::operator|(const TBitField& bf){ // операция "или"
	if (bf.BitLen == BitLen) {
		for (int i = 0;i < bf.BitLen;i++) {
			pMem[i] = pMem[i]|bf.pMem[i];
		}
	}
	return *this;
}
TBitField TBitField::operator&(const TBitField& bf) {// операция "и"
	if (bf.BitLen == BitLen) {
		for (int i = 0;i < bf.BitLen;i++) {
			pMem[i] = pMem[i]&bf.pMem[i];
		}
	}
	return *this;
}
TBitField TBitField::operator~(void){// отрицание
	TBitField A(BitLen);
	for (int i = 0;i < MemLen;i++) {
		A.pMem[i] = ~pMem[i];
	}
	return A;
}
// ввод/вывод
istream& operator>>(istream& istr, TBitField& bf){ // ввод
	for (int i = 0;i < bf.MemLen;i++) {
		int value;
		istr >> value;
		if (value == 1) {
			bf.SetBit(i);
		}
		else{
			bf.ClearBit(i);
		}
	}
	return istr;
}
ostream& operator<<(ostream& ostr, const TBitField& bf){ // вывод
	for (int i = 0;i < bf.MemLen;i++) {
		ostr << bf.GetBit(i);
	}
	return ostr;
}