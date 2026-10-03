#ifndef SURGICAL_H
#define SURGICAL_H

#include "Service.h"

class SurgicalService:public Service {
    private:
    std::string operation_type;
    public:
    SurgicalService();
    SurgicalService(std::string serve, int cost, int duration,
        std::string operation_type);
    ~SurgicalService() override;

    std::string get_operation_type() const;

    void set_operation_type(const std::string& operation_type);

    std::string get_serve_type() const override;

    friend std::ostream& operator<<(std::ostream& os, const SurgicalService& service);
};

#endif //SURGICAL_H
