#include "Service.h"

int main() {
    Service service_first;
    service_first.serve_name = "Лечение кариеса";
    service_first.doctor_name = "Иванов Иван Иванович";
    service_first.serve_cost = 5000;
    service_first.duration = 60;

    Service service_second;
    service_second.serve_name = "Протезирование";
    service_second.doctor_name = "Повлеченко Игорь Васильевич";
    service_second.serve_cost = 15000;
    service_second.duration = 120;

    return 0;
}