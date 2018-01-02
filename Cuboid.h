//
// Created by Kuba on 02.01.2018.
//

#ifndef AAL_OPENGL_VISUALIZATION_CUBOID_H
#define AAL_OPENGL_VISUALIZATION_CUBOID_H


#include <vector>
#include <iostream>

class Cuboid {
public:
    Cuboid();
    Cuboid(Cuboid&& cuboid) noexcept;
    ~Cuboid();
    std::vector<double>& getSizes();
    std::vector<double>& getDisplacement();
    friend std::istream& operator>>(std::istream& str, Cuboid& data);
    friend std::ostream& operator<<(std::ostream &str, Cuboid &data);
    float *getColor() const;
    void setColor(float *color);
    bool isEmpty();

private:
    std::vector<double> sizes;
    std::vector<double> displacement;
    float* color;
};


#endif //AAL_OPENGL_VISUALIZATION_CUBOID_H
