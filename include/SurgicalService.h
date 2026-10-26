#ifndef SURGICAL_SERVICE_H
#define SURGICAL_SERVICE_H

#include "Service.h"
#include "Surgeon.h"

class SurgicalService : public Service {
private:
    std::string operation_type;

public:
    SurgicalService();
    SurgicalService(std::string serve, int cost, int duration,
                    std::string operation_type, Doctor* doctor = nullptr);
    ~SurgicalService() override;

    std::string get_operation_type() const;
    void set_operation_type(const std::string& operation_type);

    std::string get_serve_type() const override;
    bool can_accept(Doctor* doctor) const override;
    void execute_service() const override;
    void print_info(std::ostream& os) const override;
};

#endif // SURGICAL_SERVICE_H