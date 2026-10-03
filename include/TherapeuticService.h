#ifndef THERAPEUTIC_H
#define THERAPEUTIC_H

#include "Service.h"

class TherapeuticService : public Service {
    private:
    std::string tooth_number;
    bool is_repeated;
    public:
    TherapeuticService();
    TherapeuticService(std::string serve, int cost, int duration,
        std::string tooth_number, bool is_repeated);
    ~TherapeuticService() override;

    std::string get_tooth_number()const;
    bool get_is_repeated()const;

    void set_tooth_number(const std::string& tooth_number);
    void set_repeat(bool is_repeat);

    std::string get_serve_type()const override;
    bool is_repeated_service() const override;

    friend std::ostream& operator<<(std::ostream& os, const TherapeuticService& therapeutic);
};

#endif //THERAPEUTIC_H
