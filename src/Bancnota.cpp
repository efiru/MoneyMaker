#include "Bancnota.h"
#include <algorithm>

std::map<bancnote, int> Valori{
    {UN_LEU, 1},
    {CINCI_LEI, 5},
    {ZECE_LEI, 10},
    {DOUAZECI_LEI, 20},
    {CINCIZECI_LEI, 50},
    {O_SUTA_LEI, 100},
    {DOUA_SUTE_LEI, 200},
    {CINCI_SUTE_LEI, 500}
};

std::vector<bancnote> ordineBancnote = {
    UN_LEU, CINCI_LEI, ZECE_LEI, DOUAZECI_LEI,
    CINCIZECI_LEI, O_SUTA_LEI, DOUA_SUTE_LEI, CINCI_SUTE_LEI
};

Bancnota::Bancnota() : tip(UN_LEU) {}

Bancnota::Bancnota(bancnote tip) : tip(tip) {}

int Bancnota::valoare1() const {
    return Valori.at(tip);
}

void Bancnota::set_valoare(bancnote tipNou) {
    tip = tipNou;
}

Bancnota::Bancnota(const Bancnota& other) : tip(other.tip) {}

Bancnota& Bancnota::operator=(const Bancnota& other) {
    if (this != &other) {
        tip = other.tip;
    }
    return *this;
}

Bancnota::~Bancnota() = default;

void Bancnota::upgrade(int nr_upgrades) {
    auto it = std::find(ordineBancnote.begin(), ordineBancnote.end(), tip);
    if (it != ordineBancnote.end()) {
        int index = std::distance(ordineBancnote.begin(), it);
        index = std::min(index + nr_upgrades, static_cast<int>(ordineBancnote.size() - 1));
        tip = ordineBancnote[index];
    }
}

void Bancnota::downgrade(int nr_downgrades) {
    auto it = std::find(ordineBancnote.begin(), ordineBancnote.end(), tip);
    if (it != ordineBancnote.end()) {
        int index = std::distance(ordineBancnote.begin(), it);
        index = std::max(index - nr_downgrades, 0);
        tip = ordineBancnote[index];
    }
}

std::ostream& operator<<(std::ostream& os, const Bancnota& b) {
    os << "Bancnota: " << Valori.at(b.tip) << " LEI";
    return os;
}

int Bancnota::operator+(const Bancnota& other) const {
    return this->valoare1() + other.valoare1();
}

int Bancnota::operator-(const Bancnota& other) const {
    return this->valoare1() - other.valoare1();
}

bool Bancnota::operator<(const Bancnota& other) const {
    return this->valoare1() < other.valoare1();
}

bool Bancnota::operator>(const Bancnota& other) const {
    return this->valoare1() > other.valoare1();
}

bool Bancnota::operator<=(const Bancnota& other) const {
    return this->valoare1() <= other.valoare1();
}

bool Bancnota::operator>=(const Bancnota& other) const {
    return this->valoare1() >= other.valoare1();
}

bool Bancnota::operator==(const Bancnota& other) const {
    return this->valoare1() == other.valoare1();
}

bool Bancnota::operator!=(const Bancnota& other) const {
    return this->valoare1() != other.valoare1();
}