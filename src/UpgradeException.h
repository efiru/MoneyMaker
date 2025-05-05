#ifndef UPGRADE_EXCEPTIONS_H
#define UPGRADE_EXCEPTIONS_H

#include <stdexcept>
#include <string>

class UpgradeException : public std::exception {
protected:
    std::string msg;
public:
    explicit UpgradeException(std::string m) : msg(std::move(m)) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

class UpgradeAlreadyUsedException : public UpgradeException {
public:
    UpgradeAlreadyUsedException() : UpgradeException("Acest upgrade a fost deja folosit.") {}
};

class UpgradeRequirementException : public UpgradeException {
public:
    UpgradeRequirementException() : UpgradeException("Conditiile pentru activarea acestui upgrade nu sunt indeplinite.") {}
};

class UpgradeInsufficientClicksException : public UpgradeException {
public:
    UpgradeInsufficientClicksException() : UpgradeException("Nu ai suficiente clickuri pentru a activa acest upgrade.") {}
};

class UpgradeMinimumLevelException : public UpgradeException {
public:
    UpgradeMinimumLevelException() : UpgradeException("Trebuie sa ai cel putin nivel 5 pentru a folosi UltraUpgrade!") {}
};

#endif