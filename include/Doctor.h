#ifndef DOCTOR_H
#define DOCTOR_H

#include <iostream>
#include <string>

class Doctor {
    protected:
        std::string name;
        int experience;
    public:
        Doctor();
        Doctor(std::string name, int experience);
        virtual ~Doctor();

        std::string get_name()const;
        int get_experience()const;

        void set_name(const std::string& name);
        void set_experience(int experience);

        virtual std::string get_doctor_type()const = 0;
        virtual double get_coefficient()const = 0;
        virtual void perform_procedure() const = 0;

        virtual void print_info(std::ostream& os) const;
        friend std::ostream& operator<<(std::ostream& os, const Doctor& doctor);
};

#endif //DOCTOR_H
