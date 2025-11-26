// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp) {
    MaxPower = mp;
}
// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField) {
    MaxPower = s.MaxPower;
    BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf) {
}
TSet::operator TBitField() {
    return BitField;
}

int TSet::GetMaxPower(void) const { // получить макс. к-во эл-тов
    return MaxPower;
}

int TSet::IsMember(const int Elem) const { // элемент множества?
    if ((Elem < 0) || (Elem >= MaxPower)) {
        throw("error");
    }
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) { // включение элемента множества
    if ((Elem < 0) || (Elem >= MaxPower)) {
        throw("error");
    }
    /*TBitField A(MaxPower);
    A.SetBit(Elem);
    BitField = BitField | A;*/
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) { // исключение элемента множества
    if ((Elem < 0) || (Elem >= MaxPower)) {
        throw("error");
    }
    BitField.ClearBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) { // присваивание
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet& s)const { // сравнение
    if (MaxPower == s.MaxPower) {
        if (BitField == s.BitField) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}
int TSet::operator!=(const TSet& s) const { // сравнение
    if (MaxPower == s.MaxPower) {
        if (BitField == s.BitField) {
            return 0;
        }
        else {
            return 1;
        }
    }
    else {
        return 1;
    }
}
TSet TSet::operator+(const TSet& s) { // объединение
    TSet A(max(MaxPower,s.MaxPower));
    A.BitField = BitField | s.BitField;
    return A;
}
TSet TSet::operator+(const int Elem) { // объединение с элементом
    if ((Elem < 0) || (Elem >= MaxPower)) {
        throw("error");
    }
    TSet result(MaxPower);
    result.InsElem(Elem);
    return result;
}
TSet TSet::operator-(const int Elem) { // разность с элементом
    if ((Elem < 0) || (Elem >= MaxPower)) {
        throw("error");
    }
    BitField.ClearBit(Elem);
    return *this;
}
TSet TSet::operator*(const TSet& s) { // пересечение
    TSet A(max(MaxPower,s.MaxPower));
    A.BitField = BitField & s.BitField;
    return A;
}

TSet TSet::operator~(void) { // дополнение
    TSet A(MaxPower);
    A.BitField = ~BitField;
    return A;
}
// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) { // ввод
    int value;
    while (istr >> value) {
        if (value < s.MaxPower) {
            s.InsElem(value);
        }
        else {
            break;
        }
    }
    return istr;
}
ostream& operator<<(ostream& ostr, const TSet& s) { // вывод
    for (int i = 0;i < s.MaxPower;i++) {
        if (s.IsMember(i)) {
            ostr << i << " ";
        }
    }
    return ostr;
}