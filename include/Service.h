#ifndef SERVICE_H
#define SERVICE_H

#include <iostream>
#include <string>
class Doctor;

class Service{
protected:
    std::string serve;
    int cost;
    int duration;
    Doctor* doctor;

public:
    Service();
    Service(std::string serve, int cost, int duration, Doctor* doctor = nullptr);
    virtual ~Service();

    std::string get_serve()const;
    virtual int get_cost()const;
    int get_duration()const;
    Doctor* get_doctor()const;

    void set_serve(const std::string& serve);
    void set_cost(int cost);
    void set_duration(int duration);

    virtual bool can_accept(Doctor* doctor) const = 0;
    bool set_doctor(Doctor* doctor);

    virtual std::string get_serve_type()const;
    virtual bool is_repeated_service() const;

    friend std::ostream& operator<<(std::ostream& os, const Service& service);
};

#endif
