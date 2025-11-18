#include <iostream>
#include <algorithm>
using namespace std;

class DynArr {
protected:
    int* elements;
    int count;

public:
    DynArr(int arrCount) {
        count = arrCount;
        elements = new int[count];
        for (int i = 0; i < count; i++) {
            elements[i] = 0;
        }
        cout << "Массив создан размером " << count << endl;
    }

    ~DynArr() {
        delete[] elements;
        cout << "Массив удален" << endl;
    }

    DynArr(const DynArr& source) {
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

    void setVal(int position, int number) {
        if (position < 0 || position >= count) {
            cout << "Ошибка: индекс " << position << " выходит за границы массива!" << endl;
            return;
        }
        if (number < -100 || number > 100) {
            cout << "Ошибка: значение " << number << " должно быть от -100 до 100!" << endl;
            return;
        }
        elements[position] = number;
        cout << "Элемент [" << position << "] = " << number << endl;
    }

    int getVal(int position) {
        if (position < 0 || position >= count) {
            cout << "Ошибка: индекс " << position << " выходит за границы массива!" << endl;
            return 0;
        }
        return elements[position];
    }

    void pushBack(int number) {
        if (number < -100 || number > 100) {
            cout << "Ошибка: значение " << number << " должно быть от -100 до 100!" << endl;
            return;
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

    void add(const DynArr& otherArr) {
        cout << "Сложение массивов..." << endl;
        for (int i = 0; i < count; i++) {
            int otherNumber = 0;
            if (i < otherArr.count) {
                otherNumber = otherArr.elements[i];
            }
            elements[i] += otherNumber;
        }
    }

    void subtract(const DynArr& otherArr) {
        cout << "Вычитание массивов..." << endl;

        for (int i = 0; i < count; i++) {
            int otherNum = 0;
            if (i < otherArr.count) {
                otherNum = otherArr.elements[i];
            }
            elements[i] -= otherNum;
        }
    }
    int getSize() {
        return count;
    }
};

class ExtendedDynArr : public DynArr {
public:
    ExtendedDynArr(int arrCount) : DynArr(arrCount) {}
    ExtendedDynArr(const DynArr& source) : DynArr(source) {}
    double getAverage() {
        int size = getSize();
        if (size == 0) {
            cout << "Ошибка: массив пуст!" << endl;
            return 0.0;
        }

        double sum = 0;
        for (int i = 0; i < size; i++) {
            sum += getVal(i);
        }
        return sum / size;
    }
    double getMedian() {
        int size = getSize();
        if (size == 0) {
            cout << "Ошибка: массив пуст!" << endl;
            return 0.0;
        }
        int* tempArr = new int[size];
        for (int i = 0; i < size; i++) {
            tempArr[i] = getVal(i);
        }
        sort(tempArr, tempArr + size);
        double median;
        if (size % 2 == 0) {
            median = (tempArr[size / 2 - 1] + tempArr[size / 2]) / 2.0;
        }
        else {
            median = tempArr[size / 2];
        }
        delete[] tempArr;
        return median;
    }

    int getMin() {
        int size = getSize();
        if (size == 0) {
            cout << "Ошибка: массив пуст!" << endl;
            return 0;
        }
        int minVal = getVal(0);
        for (int i = 1; i < size; i++) {
            int current = getVal(i);
            if (current < minVal) {
                minVal = current;
            }
        }
        return minVal;
    }

    int getMax() {
        int size = getSize();
        if (size == 0) {
            cout << "Ошибка: массив пуст!" << endl;
            return 0;
        }
        int maxVal = getVal(0);
        for (int i = 1; i < size; i++) {
            int current = getVal(i);
            if (current > maxVal) {
                maxVal = current;
            }
        }
        return maxVal;
    }
};