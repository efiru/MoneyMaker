#ifndef BANCNOTA_HPP
#define BANCNOTA_HPP

#include <iostream>
#include <map>
#include <vector>

enum bancnote {
    UN_LEU,
    CINCI_LEI,
    ZECE_LEI,
    DOUAZECI_LEI,
    CINCIZECI_LEI,
    O_SUTA_LEI,
    DOUA_SUTE_LEI,
    CINCI_SUTE_LEI,
};

extern std::map<bancnote, int> Valori;
extern std::vector<bancnote> ordineBancnote;

class Bancnota {
private:
    bancnote tip;
public:
    Bancnota();
    explicit Bancnota(bancnote tip);
    Bancnota(const Bancnota& other);
    Bancnota& operator=(const Bancnota& other);
    ~Bancnota();

    int valoare1() const;
    void set_valoare(bancnote tipNou);

    void upgrade(int nr_upgrades);
    void downgrade(int nr_downgrades);

    friend std::ostream& operator<<(std::ostream& os, const Bancnota& b);
    int operator+(const Bancnota& other) const;
    int operator-(const Bancnota& other) const;
    bool operator<(const Bancnota& other) const;
    bool operator>(const Bancnota& other) const;
    bool operator<=(const Bancnota& other) const;
    bool operator>=(const Bancnota& other) const;
    bool operator==(const Bancnota& other) const;
    bool operator!=(const Bancnota& other) const;
};

#endif