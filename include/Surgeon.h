#ifndef SURGEON_H
#define SURGEON_H
#include "Doctor.h"

class Surgeon : public Doctor {
private:
    int operations_count;  // проведено операций

public:
    Surgeon();
    Surgeon(std::string name, int experience, int operations_count);
    ~Surgeon() override;

    int get_operations_count() const;
    void set_operations_count(int o);

    std::string get_specialization() const override;
    void print() const override;

    friend std::ostream& operator<<(std::ostream& os, const Surgeon& surgeon);
};
#endif //SURGEON_H
