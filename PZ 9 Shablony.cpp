#include <iostream>
#include <vector>
#include <stdexcept>
#include <typeinfo>
#include <type_traits>
#include <cmath>
#include <string>
#include <sstream>

template<typename Type>
class TemplateArray {
private:
    std::vector<Type> elements;
public:
    TemplateArray() = default;
    explicit TemplateArray(size_t size) : elements(size) {}
    TemplateArray(size_t size, const Type& value) : elements(size, value) {}
    TemplateArray(std::initializer_list<Type> initValues) : elements(initValues) {}
    Type& operator[](size_t index) {
        if (index >= elements.size()) {
            throw std::out_of_range("Индекс вне границ");
        }
        return elements[index];
    }
    const Type& operator[](size_t index) const {
        if (index >= elements.size()) {
            throw std::out_of_range("Индекс вне границ");
        }
        return elements[index];
    }
    size_t getSize() const {
        return elements.size();
    }
    template<typename OtherType = Type>
    typename std::enable_if<std::is_arithmetic<OtherType>::value>::type
        setElement(size_t index, OtherType value) {
        if (index >= elements.size()) {
            throw std::out_of_range("Индекс вне границ");
        }
        if constexpr (std::is_integral<OtherType>::value) {
            if (value < 0) {
                throw std::invalid_argument("Значение должно быть неотрицательным для целых чисел");
            }
            if (value > 10000) {
                throw std::invalid_argument("Значение превышает максимально допустимое (10000)");
            }
        }
        else if constexpr (std::is_floating_point<OtherType>::value) {
            if (value < 0.0 || value > 10000.0) {
                throw std::invalid_argument("Значение должно быть между 0.0 и 10000.0 для чисел с плавающей точкой");
            }
            if (std::isnan(value)) {
                throw std::invalid_argument("Значение должно быть числом");
            }
        }
        elements[index] = value;
    }
    template<typename OtherType = Type>
    typename std::enable_if<!std::is_arithmetic<OtherType>::value>::type
        setElement(size_t index, const OtherType& value) {
        if (index >= elements.size()) {
            throw std::out_of_range("Индекс вне границ");
        }
        elements[index] = value;
    }
    friend std::ostream& operator<<(std::ostream& outputStream, const TemplateArray<Type>& array) {
        outputStream << "[";
        for (size_t counter = 0; counter < array.elements.size(); ++counter) {
            outputStream << array.elements[counter];
            if (counter != array.elements.size() - 1) {
                outputStream << ", ";
            }
        }
        outputStream << "]";
        return outputStream;
    }
    template<typename OtherType = Type>
    static typename std::enable_if<std::is_arithmetic<OtherType>::value, double>::type
        calculateDistance(const TemplateArray<OtherType>& array1, const TemplateArray<OtherType>& array2) {
        if (array1.getSize() != array2.getSize()) {
            throw std::invalid_argument("Массивы должны быть одного размера");
        }
        double sum = 0.0;
        for (size_t counter = 0; counter < array1.getSize(); ++counter) {
            double difference = static_cast<double>(array1[counter]) - static_cast<double>(array2[counter]);
            sum += difference * difference;
        }
        return std::sqrt(sum);
    }
    template<typename OtherType = Type>
    static typename std::enable_if<!std::is_arithmetic<OtherType>::value, double>::type
        calculateDistance(const TemplateArray<OtherType>& array1, const TemplateArray<OtherType>& array2) {
        throw std::bad_typeid();
    }
};