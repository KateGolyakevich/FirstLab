#ifndef THERAPEUTIC_H
#define THERAPEUTIC_H

#include "Service.h"

class Therapeutic : public Service {
    private:
    int tooth_number;
    bool is_repeated;
    public:
    Therapeutic();
    Therapeutic(std::string serve, int cost, int duration,
        int tooth_number, bool is_repeated);
    ~Therapeutic() override;

    int get_toth_number()const;
    bool is_repeat()const;

    void set_toth_number(int tooth_number);
    void set_repeat(bool is_repeat);

    std::string get_serve_type()const override;
    int get_total_cost()const override;

    friend std::ostream& operator<<(std::ostream& os, const Therapeutic& therapeutic);
};

#endif //THERAPEUTIC_H
