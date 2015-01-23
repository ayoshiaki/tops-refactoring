/*
 *       SequenceEntry.cpp
 *
 *       Copyright 2011 Andre Yoshiaki Kashiwabara <akashiwabara@usp.br>
 *                      �gor Bonadio <ibonadio@ime.usp.br>
 *                      Vitor Onuchic <vitoronuchic@gmail.com>
 *                      Alan Mitchell Durham <aland@usp.br>
 *
 *       This program is free software; you can redistribute it and/or modify
 *       it under the terms of the GNU  General Public License as published by
 *       the Free Software Foundation; either version 3 of the License, or
 *       (at your option) any later version.
 *
 *       This program is distributed in the hope that it will be useful,
 *       but WITHOUT ANY WARRANTY; without even the implied warranty of
 *       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *       GNU General Public License for more details.
 *
 *       You should have received a copy of the GNU General Public License
 *       along with this program; if not, write to the Free Software
 *       Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *       MA 02110-1301, USA.
 */

#include "SequenceEntry.hpp"
#include <istream>
#include <ostream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include "util.hpp"
namespace tops {
  //! Save the sequence
  std::ostream & operator << (std::ostream & stream, SequenceEntry & out) {
    return out._format->saveSequence(stream, out);
  }

  //! Load the sequence
  std::istream & operator >> (std::istream & stream, SequenceEntry &in){
    return in._format->readSequence(stream, in);
  }
}
