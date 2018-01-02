//
// Created by Kuba on 02.01.2018.
//

#include <cmath>
#include "Cuboid.h"

std::vector<double> &Cuboid::getSizes() {
    return sizes;
}

std::vector<double> &Cuboid::getDisplacement() {
    return displacement;
}

Cuboid::Cuboid()
:   sizes({0.0, 0.0, 0.0})
,   displacement({0.0, 0.0, 0.0})
{}

std::istream &operator>>(std::istream &str, Cuboid &data) {
    for(int i = 0; i < 3; ++i) {
        str >> data.sizes[i];
    }
    for(int i = 0; i < 3; ++i) {
        str >> data.displacement[i];
    }
    return str;
}

float *Cuboid::getColor() const {
    return color;
}

void Cuboid::setColor(float *color) {
    this->color = color;
}

Cuboid::~Cuboid() {
//    delete color;
}

Cuboid::Cuboid(Cuboid &&cuboid) noexcept {
    for(auto element : cuboid.sizes) {
        sizes.push_back(element);
    }
    for(auto element : cuboid.displacement) {
        sizes.push_back(element);
    }
    color = cuboid.color;
    cuboid.color = nullptr;
}

bool Cuboid::isEmpty() {
    for(auto x : sizes) {
        if(std::fabs(x - 0.0) > 0.00001 ) {
            return false;
        }
    }
    return true;
}

std::ostream &operator<<(std::ostream &str, Cuboid &data) {
    str << data.sizes[0] << " " << data.sizes[1] << " " << data.sizes[2] << std::endl;
    str << data.displacement[0] << " " << data.displacement[1] << " " <<data.displacement[2] << std::endl;
}
