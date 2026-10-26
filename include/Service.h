#ifndef SERVICE_H
#define SERVICE_H

#include <iostream>
#include <string>
#include "Doctor.h"

class Service {
protected:
    std::string serve;
    int cost;
    int duration;
    Doctor* doctor;

public:
    Service();
    Service(std::string serve, int cost, int duration, Doctor* doctor = nullptr);
    virtual ~Service();

    std::string get_serve() const;
    int get_duration() const;
    Doctor* get_doctor() const;

    void set_serve(const std::string& serve);
    void set_cost(int cost);
    void set_duration(int duration);
    bool set_doctor(Doctor* doctor);

    // Чисто виртуальные методы
    virtual std::string get_serve_type() const = 0;
    virtual bool can_accept(Doctor* doctor) const = 0;
    virtual void execute_service() const = 0;

    // Виртуальные методы с базовой реализацией
    virtual int get_cost() const;
    virtual bool is_repeated_service() const;
    virtual void print_info(std::ostream& os) const;

    friend std::ostream& operator<<(std::ostream& os, const Service& service);
};

#endif // SERVICE_H