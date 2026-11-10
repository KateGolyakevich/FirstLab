#ifndef CLINICEXCEPTION_H
#define CLINICEXCEPTION_H

#include <exception>
#include <string>

class ClinicException : public std::exception {
protected:
    std::string message;

public:
    explicit ClinicException(const std::string& msg);
    virtual ~ClinicException() noexcept = default;
    const char* what() const noexcept override;
};

#endif //CLINICEXCEPTION_H
