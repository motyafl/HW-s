#include <iostream>

class Currency {
protected:
    double amount;

public:
    Currency(double am) : amount(am) {}
    virtual ~Currency() = default;

    virtual double toUSD() const = 0;
    virtual void print(std::ostream& os) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Currency& c);
};

std::ostream& operator<<(std::ostream& os, const Currency& c) {
    c.print(os);
    return os;
}

class Euro : public Currency {
public:
    Euro(double am) : Currency(am) {}

    double toUSD() const override {
        return amount * 1.08;
    }

    void print(std::ostream& os) const override {
        os << amount << " EUR";
    }

    operator double() const {
        return amount;
    }
};

class Pound : public Currency {
public:
    Pound(double am) : Currency(am) {}

    double toUSD() const override {
        return amount * 1.27;
    }

    void print(std::ostream& os) const override {
        os << amount << " GBP";
    }

    operator double() const {
        return amount;
    }
};

class Yen : public Currency {
public:
    Yen(double am) : Currency(am) {}

    double toUSD() const override {
        return amount * 0.0065;
    }

    void print(std::ostream& os) const override {
        os << amount << " JPY";
    }

    operator double() const {
        return amount;
    }
};

int main() {
    const int size = 3;
    Currency* wallet[size];

    wallet[0] = new Euro(100.0);
    wallet[1] = new Pound(50.0);
    wallet[2] = new Yen(10000.0);

    double totalUSD = 0.0;

    for (int i = 0; i < size; ++i) {
        std::cout << *wallet[i] << " = " << wallet[i]->toUSD() << " USD" << std::endl;
        totalUSD += wallet[i]->toUSD();
    }

    std::cout << "Общая сумма в долларах: " << totalUSD << " USD" << std::endl;

    for (int i = 0; i < size; ++i) {
        delete wallet[i];
    }

    return 0;
}

