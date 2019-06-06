#include "building.hpp"

#include <glad/glad.h>
#include <stdio.h>

Building::Building(float port, float type) : m_portee(port), m_type(type) {
    printf("Building created !");
}

Building::~Building() {
    printf("Building destructed !");
}

void Building::ActionCircle(){

}

void Building::Ameliorer() {
    
}
