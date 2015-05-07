
/**
 * @file utils.h
 * @brief Some useful functions
 * @date Dec 29, 2011
 * @author Pablo F. Alcantarilla
 */

#ifndef _UTILS_H_
#define _UTILS_H_

//******************************************************************************
//******************************************************************************

// OPENCV Includes
#include "opencv2/core/core.hpp"

// System Includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <assert.h>
#include <math.h>

// Other Includes
#include "kaze_ipoint.h"

//*************************************************************************************
//*************************************************************************************

// Declaration of Functions
void Compute_min_32F(const cv::Mat &src, float &value);
void Compute_max_32F(const cv::Mat &src, float &value);
void Convert_Scale(cv::Mat &src);
void Copy_and_Convert_Scale(const cv::Mat &src, cv::Mat &dst);
void Draw_Ipoints(cv::Mat &img, const std::vector<Ipoint> &keypoints);
int fRound(float flt);

namespace detail {

template<typename T, typename U, bool>
struct cast_or_thrower;

template<typename T, typename U>
struct cast_or_thrower<T, U, true>
{
    T operator()(U value) const
    {
        T const new_value = static_cast<T>(value);
        U const cast_back = static_cast<U>(new_value);
        if (cast_back != value)
            throw std::bad_cast();
        return new_value;
    }
};

template<typename T, typename U>
struct cast_or_thrower<T, U, false>
{
    T operator()(U value) const
    {
        T const new_value = static_cast<T>(value);
        U const cast_back = static_cast<U>(new_value);
        if (cast_back != floor(value))
            throw std::bad_cast();
        return new_value;
    }
};

}   // namespace detail

template<typename T, typename U>
T cast_or_throw(U value)
{
    return detail::cast_or_thrower<
        T, U, !(std::is_integral<T>::value  &&  !std::is_integral<U>::value)>()(value);
}


//*************************************************************************************
//*************************************************************************************

#endif
