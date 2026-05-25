#include <iostream>
#include <stdexcept>
#include <string>

namespace CustomPointer {

    class NullPointerException : public std::runtime_error {
    public:
        NullPointerException() : std::runtime_error("Ошибка: Попытка доступа по нулевому указателю") {}
    };

    template <typename T>
    class SmartPointer {
    private:
        T* ptr;
        static int referenceCount;

    public:
        explicit SmartPointer(T* p = nullptr) : ptr(p) {
            if (ptr) ++referenceCount;
        }

        SmartPointer(const SmartPointer& other) : ptr(other.ptr) {
            if (ptr) ++referenceCount;
        }

        ~SmartPointer() {
            if (ptr) {
                --referenceCount;
                if (referenceCount == 0) {
                    delete ptr;
                    ptr = nullptr;
                }
            }
        }

        SmartPointer& operator=(const SmartPointer& other) {
            if (this != &other) {
                if (ptr) {
                    --referenceCount;
                    if (referenceCount == 0) delete ptr;
                }
                ptr = other.ptr;
                if (ptr) ++referenceCount;
            }
            return *this;
        }

        T& operator*() const {
            if (!ptr) throw NullPointerException();
            return *ptr;
        }

        T* operator->() const {
            if (!ptr) throw NullPointerException();
            return ptr;
        }

        static int getRefCount() { return referenceCount; }
    };

    template <typename T>
    int SmartPointer<T>::referenceCount = 0;

    // Специализация для массива объектов
    template <typename T>
    class SmartPointer<T[]> {
    private:
        T* ptr;
        static int referenceCount;

    public:
        explicit SmartPointer(T* p = nullptr) : ptr(p) {
            if (ptr) ++referenceCount;
        }

        SmartPointer(const SmartPointer& other) : ptr(other.ptr) {
            if (ptr) ++referenceCount;
        }

        ~SmartPointer() {
            if (ptr) {
                --referenceCount;
                if (referenceCount == 0) {
                    delete[] ptr;
                    ptr = nullptr;
                }
            }
        }

        SmartPointer& operator=(const SmartPointer& other) {
            if (this != &other) {
                if (ptr) {
                    --referenceCount;
                    if (referenceCount == 0) delete[] ptr;
                }
                ptr = other.ptr;
                if (ptr) ++referenceCount;
            }
            return *this;
        }

        T& operator[](int index) const {
            if (!ptr) throw NullPointerException();
            return ptr[index];
        }

        static int getRefCount() { return referenceCount; }
    };

    template <typename T>
    int SmartPointer<T[]>::referenceCount = 0;
}

class Action {
public:
    void run() const {
        std::cout << "Вызов метода класса через SmartPointer выполнен" << std::endl;
    }
};

int main() {
    try {
        CustomPointer::SmartPointer<Action> emptyPtr(nullptr);
        
        try {
            std::cout << "Попытка вызова метода через неинициализированный указатель..." << std::endl;
            void (Action::*methodPtr)() const = &Action::run;
            ((*emptyPtr).*methodPtr)();
        } catch (const CustomPointer::NullPointerException& e) {
            std::cout << "Внутренний catch: " << e.what() << std::endl;
            throw;
        }
    } catch (const std::exception& e) {
        std::cout << "Внешний catch: Ошибка обработана на верхнем уровне" << std::endl;
    }

    CustomPointer::SmartPointer<Action> validPtr(new Action());
    void (Action::*methodPtr)() const = &Action::run;
    ((*validPtr).*methodPtr)();

    return 0;
}

