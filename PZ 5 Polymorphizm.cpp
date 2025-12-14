#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

class DynamicArray {
protected:
    int* elements;
    int count;

    string generateFilename(const string& extension) const {
        auto now = chrono::system_clock::now();
        time_t time = chrono::system_clock::to_time_t(now);
        tm tm_time;
        localtime_s(&tm_time, &time);

        stringstream filename;
        filename << put_time(&tm_time, "%Y-%m-%d_%H-%M-%S") << extension;
        return filename.str();
    }

public:
    DynamicArray(int arrayCount) {
        count = arrayCount;
        elements = new int[count];
        for (int i = 0; i < count; i++) {
            elements[i] = 0;
        }
        cout << "Массив создан размером " << count << endl;
    }

    virtual ~DynamicArray() {
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

    virtual void printToFile() = 0;

    void print() const {
        cout << "Массив [";
        for (int i = 0; i < count; i++) {
            cout << elements[i];
            if (i < count - 1) cout << ", ";
        }
        cout << "]" << endl;
    }

    void setValue(int position, int number) {
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

    int getValue(int position) const {
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

    int getSize() const {
        return count;
    }
};

class ArrTxt : public DynamicArray {
public:
    ArrTxt(int arrayCount) : DynamicArray(arrayCount) {}

    void printToFile() override {
        string filename = generateFilename(".txt");
        ofstream file(filename);

        if (!file.is_open()) {
            cout << "Ошибка при создании файла: " << filename << endl;
            return;
        }

        file << "Массив размером " << count << " элементов:" << endl;
        file << "[";
        for (int i = 0; i < count; i++) {
            file << elements[i];
            if (i < count - 1) file << ", ";
        }
        file << "]" << endl;
        file << "Подробный список элементов:" << endl;
        for (int i = 0; i < count; i++) {
            file << "Элемент [" << i << "] = " << elements[i] << endl;
        }

        file.close();
        cout << "Массив сохранен в файл: " << filename << endl;
    }
};

class ArrCSV : public DynamicArray {
public:
    ArrCSV(int arrayCount) : DynamicArray(arrayCount) {}

    void printToFile() override {
        string filename = generateFilename(".csv");
        ofstream file(filename);

        if (!file.is_open()) {
            cout << "Ошибка при создании файла: " << filename << endl;
            return;
        }

        file << "Index,Value" << endl;

        for (int i = 0; i < count; i++) {
            file << i << "," << elements[i] << endl;
        }

        file << endl << "Summary" << endl;
        file << "Total elements," << count << endl;
        file << "Minimum value," << *min_element(elements, elements + count) << endl;
        file << "Maximum value," << *max_element(elements, elements + count) << endl;

        int sum = 0;
        for (int i = 0; i < count; i++) {
            sum += elements[i];
        }
        file << "Average value," << (count > 0 ? static_cast<double>(sum) / count : 0) << endl;

        file.close();
        cout << "Массив сохранен в CSV файл: " << filename << endl;
    }
};