#ifndef THERAPEUTIC_SERVICE_H
#define THERAPEUTIC_SERVICE_H

#include "Service.h"
#include "Therapist.h"

class TherapeuticService : public Service {
private:
    std::string tooth_number;
    bool is_repeated;

public:
    TherapeuticService();
    TherapeuticService(std::string serve, int cost, int duration,
                       std::string tooth_number, bool is_repeated, Doctor* doctor = nullptr);
    ~TherapeuticService() override;

    std::string get_tooth_number() const;
    bool get_is_repeated() const;
    void set_tooth_number(const std::string& tooth_number);
    void set_repeat(bool is_repeat);

    std::string get_serve_type() const override;
    bool can_accept(Doctor* doctor) const override;
    bool is_repeated_service() const override;
    void execute_service() const override;
    void print_info(std::ostream& os) const override;
};

#endif // THERAPEUTIC_SERVICE_H