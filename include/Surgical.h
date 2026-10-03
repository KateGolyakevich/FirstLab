#ifndef SURGICAL_H
#define SURGICAL_H

#include "Service.h"

class Surgical:public Service {
    private:
    std::string operation_type;
    public:
    Surgical();
    Surgical(std::string serve, int cost, int duration,
        std::string operation_type);
    ~Surgical() override;

    std::string get_operation_type() const;

    void set_operation_type(const std::string& operation_type);

    std::string get_serve_type() const override;

    friend std::ostream& operator<<(std::ostream& os, const Surgical& service);
};

#endif //SURGICAL_H
