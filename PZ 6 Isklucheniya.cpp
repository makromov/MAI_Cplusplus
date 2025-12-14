#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class DynamicArray {
private:
    int* elements;
    int count;

public:
    DynamicArray(int arrayCount) {
        count = arrayCount;
        elements = new int[count];
        for (int i = 0; i < count; i++) {
            elements[i] = 0;
        }
        cout << "Массив создан размером " << count << endl;
    }
    ~DynamicArray() {
        delete[] elements;
        cout << "Массив удален" << endl;
    }
    DynamicArray(const DynamicArray& source) {
        count = source.count;
        elements = new int[count];
        for (int i = 0; i < count; i++) {
            elements[i] = source.elements[i];
        }
        cout << "Массив скопирован" << endl;
    }
    void print() {
        cout << "Массив [";
        for (int i = 0; i < count; i++) {
            cout << elements[i];
            if (i < count - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    void setValue(int position, int number) {
        if (position < 0 || position >= count) {
            throw out_of_range("Индекс " + to_string(position) + " выходит за границы массива размером " + to_string(count));
        }

        if (number < -100 || number > 100) {
            throw invalid_argument("Значение " + to_string(number) + " должно быть в диапазоне от -100 до 100");
        }

        elements[position] = number;
        cout << "Элемент [" << position << "] = " << number << endl;
    }
    int getValue(int position) {
        if (position < 0 || position >= count) {
            throw out_of_range("Индекс " + to_string(position) + " выходит за границы массива размером " + to_string(count));
        }
        return elements[position];
    }
    void pushBack(int number) {
        if (number < -100 || number > 100) {
            throw invalid_argument("Значение " + to_string(number) + " должно быть в диапазоне от -100 до 100");
        }
        int* newElements = new int[count + 1];
        for (int i = 0; i < count; i++) {
            newElements[i] = elements[i];
        }
        newElements[count] = number;
        delete[] elements;
        elements = newElements;
        count++;
        cout << "Добавлен элемент: " << number << ". Новый размер: " << count << endl;
    }
    void add(const DynamicArray& otherArray) {
        cout << "Сложение массивов..." << endl;
        for (int i = 0; i < count; i++) {
            int otherNumber = 0;
            if (i < otherArray.count) {
                otherNumber = otherArray.elements[i];
            }
            elements[i] += otherNumber;
        }
    }
    void subtract(const DynamicArray& otherArray) {
        cout << "Вычитание массивов..." << endl;
        for (int i = 0; i < count; i++) {
            int otherNumber = 0;
            if (i < otherArray.count) {
                otherNumber = otherArray.elements[i];
            }
            elements[i] -= otherNumber;
        }
    }
    int getSize() {
        return count;
    }
};