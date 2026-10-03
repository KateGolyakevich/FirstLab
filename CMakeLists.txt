cmake_minimum_required(VERSION 3.31)
project(Lab_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab_1 src/Patient.cpp
        src/Service.cpp
        src/main.cpp
        include/Doctor.h
        src/Doctor.cpp
        include/TherapeuticService.h
        include/SurgicalService.h
        include/OrthodonticService.h
        src/TherapeuticService.cpp
        src/SurgicalService.cpp
        src/OrthodonticService.cpp
        include/Therapist.h
        include/Surgeon.h
        include/Orthodontist.h
        src/Orthodontist.cpp
        src/Surgeon.cpp
        src/Therapist.cpp
)
