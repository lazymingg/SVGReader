#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "TransformStragetry.h"

using namespace std;

class Transform
{
    private:
        TransformStragetry *stragetry;        
    public:
        Transform();
        Transform(string str);
        /**
         * @brief Transform the tag using mutiple matrix 
         * 
         * @param matrix the matrix to transform
         * 
         * @return void
         * 
         */
        void transform(MyMatrix::Matrix &matrix);
        // void setTransform(string str);
        ~Transform()
        {
            // delete stragetry;
        }
};

#endif