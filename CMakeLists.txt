cmake_minimum_required(VERSION 3.31)
project(Lab_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab_1 src/Patient.cpp
        src/Service.cpp
        src/main.cpp
        include/Doctor.h
        src/Doctor.cpp
        include/Therapeutic.h
        include/Surgical.h
        include/Orthodontic.h
        src/Therapeutic.cpp
        src/Surgical.cpp
        src/Orthodontic.cpp
        include/Therapist.h
        include/Surgeon.h
        include/Orthodontis.h
        src/Orthodontis.cpp
        src/Surgeon.cpp
        src/Therapist.cpp
)
