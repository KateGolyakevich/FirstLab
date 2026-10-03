#ifndef SERVICE_H
#define SERVICE_H

#include <iostream>
#include <string>

class Service{
    private:
    std::string serve;
    int cost;
    int duration;

    public:
    Service();
    Service(std::string serve, int cost, int duration);
    virtual ~Service();

    std::string get_serve()const;
    int get_cost()const;
    int get_duration()const;

    void set_serve(const std::string& serve);
    void set_cost(int cost);
    void set_duration(int duration);

    virtual std::string get_serve_type()const;
    virtual bool is_repeated_service() const;

    friend std::ostream& operator<<(std::ostream& os, const Service& service);
};

#endif
