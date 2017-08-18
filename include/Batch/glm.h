//
// Created by chris on 13/08/2017.
//

#ifndef MINECRAFT_CLONE_GLM_H
#define MINECRAFT_CLONE_GLM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>



/*
 * CONSTANTS
 */

const float PI = glm::pi<float>();
const float TWO_PI = 2 * PI;
const float HALF_PI = PI / 2;

namespace glm {
    template <typename genType>
    int argmin(genType const& x) {
        int n = x.length();
        int min = 0;
        for(int i = 1; i < n; ++i) {
            if(x[i] < x[min]) {
                min = i;
            }
        }

        return min;
    }

    template <typename genType>
    int argmax(genType const& x) {
        int n = x.length();
        int max = 0;
        for(int i = 1; i < n; ++i) {
            if(x[i] > x[max]) {
                max = i;
            }
        }

        return max;
    }
}

#endif //MINECRAFT_CLONE_GLM_H
