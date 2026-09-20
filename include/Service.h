#ifndef SERVICE_H
#define SERVICE_H

#include <iostream>
#include <string>

class Service{
private:
    std::string serve;
    std::string doctor_name;
    int cost;
    int duration;

    public:
    Service();
    Service(std::string serve, std::string doctor_name, int cost, int duration);

    ~Service();

    std::string get_serve_name()const;
    std::string get_doctor_name()const;
    int get_cost() const;
    int get_duration() const;

    void set_name(const std::string& serve);
    void set_doctor_name(const std::string& doctor_name);
    void set_cost(int cost);
    void set_duration(int dur);

    void print();
};

#endif
