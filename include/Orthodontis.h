#ifndef ORTHODONTIS_H
#define ORTHODONTIS_H

#include "Doctor.h"

class Orthodontist : public Doctor {
    private:
    int braces_patients;

    public:
    Orthodontist();
    Orthodontist(std::string name, int experience, int braces_patients);
    ~Orthodontist() override;

    int get_braces_patients() const;
    void set_braces_patients(int braces_patients);

    std::string get_specialization() const override;
    void print() const override;

    friend std::ostream& operator<<(std::ostream& os, const Orthodontist& ororthodontist);
};

#endif //ORTHODONTIS_H
