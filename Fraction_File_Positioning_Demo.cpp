/*Задача 4: Создать и инициализировать массив из 4-х объектов типа Дробь (Fraction) и 
записать этот массив в файл в бинарном режиме.
Затем создать объект типа Дробь и считать из этого файла в этот объект данные 
предпоследнего объекта массива. Использовать позиционирование по файлу*/
#include <iostream>
#include <fstream>
using namespace std;

class Fraction {
    int numerator = 0;
    int denominator = 1;

public:
    void setNumerator(int num) {
        numerator = num;
    }

    void setDenominator(int denom) {
        if (denom == 0) denom = 1;
        denominator = denom;
    }

    Fraction() {}

    Fraction(int num, int denom) {
        setNumerator(num);
        setDenominator(denom);
    }

    void serialize(ofstream& outFile) const {
        outFile.write((char*)this, sizeof(Fraction));
    }

    void deserialize(ifstream& inFile) {
        inFile.read((char*)this, sizeof(Fraction));
    }

    void print() const {
        cout << numerator << " / " << denominator << "\n";
    }
};

int main() {
    setlocale(0, "");

    Fraction fractions[4] = {
        Fraction(1, 2),
        Fraction(3, 4),
        Fraction(5, 6),
        Fraction(7, 8)
    };

    ofstream outFile("fractions.dat", ios::binary);
    for (const Fraction& fraction : fractions) {
        fraction.serialize(outFile);
    }
    outFile.close();

    Fraction fractionToRead;

    ifstream inFile("fractions.dat", ios::binary);

    int shiftBytes = -2 * static_cast<int>(sizeof(Fraction));
    inFile.seekg(shiftBytes, ios::end); // сдвигаемся на два объекта типа Дробь назад от конца файла

    fractionToRead.deserialize(inFile);

    inFile.close();

    cout << "Данные предпоследнего объекта из файла: ";
    fractionToRead.print();

    return 0;
}
