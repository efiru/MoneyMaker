#ifndef JSON_EXCEPTION_H
#define JSON_EXCEPTION_H

#include <exception>
#include <string>

class JsonException : public std::exception {
protected:
    std::string msg;
public:
    explicit JsonException(std::string m) : msg(std::move(m)) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

class JsonParseException : public JsonException {
public:
    JsonParseException() : JsonException("Eroare la parsarea fișierului JSON.") {}
};

class JsonWriteException : public JsonException {
public:
    JsonWriteException() : JsonException("Eroare la scrierea în fișierul JSON.") {}
};

class JsonFileNotFoundException : public JsonException {
public:
    JsonFileNotFoundException() : JsonException("Fișierul JSON nu a fost găsit.") {}
};

#endif