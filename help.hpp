/*
 * help.hpp
 *
 *  Created on: 2018. szept. 29.
 *      Author: Boda Mihaly HMH3MV
 */

#ifndef HELP_HPP_
#define HELP_HPP_

#include <iostream>
#include <sstream>

template<class T>
T change(string s){
   stringstream ss;
    T temp;
    ss << s;
    ss >> temp;
    ss.clear();
    return temp;
}


#endif /* HELP_HPP_ */
