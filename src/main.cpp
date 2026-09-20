#include <iostream>
#include <string>

#include "../include/Patient.h"
#include "../include/Service.h"

int main() {
    Service serve_first("Удаление кариеса", "Иванов И.И.", 500, 10);
    Service serve_second("Протезирование", "Петров П.П.", 1200, 100);
    Service serve_third("Удаление зуба мудрости", "Сидорова А.А.", 800, 60);

    Patient patient_first("Смирнов Олег Владимирович");
    patient_first.add_serve(serve_first);
    patient_first.add_serve(serve_second);

    Patient patient_second("Корней Ольга Владимировна");
    patient_second.add_serve(serve_third);

    std::cout << "\nИтоговая информация" << std::endl;
    patient_first.print();
    patient_second.print();




    return 0;
}