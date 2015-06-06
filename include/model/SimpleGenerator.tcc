/***********************************************************************/
/*  Copyright 2015 ToPS                                                */
/*                                                                     */
/*  This program is free software; you can redistribute it and/or      */
/*  modify it under the terms of the GNU  General Public License as    */
/*  published by the Free Software Foundation; either version 3 of     */
/*  the License, or (at your option) any later version.                */
/*                                                                     */
/*  This program is distributed in the hope that it will be useful,    */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of     */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the      */
/*  GNU General Public License for more details.                       */
/*                                                                     */
/*  You should have received a copy of the GNU General Public License  */
/*  along with this program; if not, write to the Free Software        */
/*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,         */
/*  MA 02110-1301, USA.                                                */
/***********************************************************************/

#ifndef TOPS_MODEL_SIMPLE_GENERATOR_
#define TOPS_MODEL_SIMPLE_GENERATOR_

// Standard headers
#include <memory>
#include <typeinfo>
#include <exception>

// ToPS headers
#include "model/MemberDetector.hpp"

// ToPS templates
#include "model/Generator.tcc"

namespace tops {
namespace model {

/*
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
 -------------------------------------------------------------------------------
                                    CLASS
 -------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
*/

// Auxiliar tests
GENERATE_HAS_MEMBER(simpleChoose)

template<typename Target, typename Model, bool is_base>
class SimpleGenerator;

/**
 * @typedef SimpleGeneratorPtr
 * @brief Alias of pointer to SimpleGenerator.
 */
template<typename Target, typename Model, bool is_base = false>
using SimpleGeneratorPtr
    = std::shared_ptr<SimpleGenerator<Target, Model, is_base>>;

/**
 * @class SimpleGenerator
 * @brief TODO
 */
template<typename Target, typename Model, bool is_base = false>
class SimpleGenerator
    : public std::conditional<!std::is_void<typename Model::Base>::value,
               SimpleGenerator<Target, typename Model::Base, true>,
               Generator<Target>>::type {
 public:
  // Alias
  using ModelPtr = std::shared_ptr<Model>;

  using Self = SimpleGenerator<Target, Model>;
  using SelfPtr = std::shared_ptr<Self>;

  // Static methods
  template<typename... Ts>
  static SimpleGeneratorPtr<Target, Model> make(Ts... args) {
    return std::shared_ptr<Self>(new Self(std::forward<Ts>(args)...));
  }

  // Overriden methods
  Target choose(unsigned int size, unsigned int phase) override {
    return choose(size, phase, typename has_member_simpleChoose<
      Model, const Target(SelfPtr, unsigned int, unsigned int)>::tag());
  }

 protected:
  // Instace variables
  ModelPtr _model;

  // Constructors
  SimpleGenerator(ModelPtr m = ModelPtr())
      : _model(std::move(m)) {
  }

 private:
  // Concrete methods
  Target choose(unsigned int size, unsigned int phase, no_simpleChoose_tag) {
    static_assert(is_base, "Model does not have method simpleChoose");
    throw std::logic_error("Calling from base with no method simpleChoose");
  }

  Target choose(unsigned int size, unsigned int phase, has_simpleChoose_tag) {
    return _model->simpleChoose(make_shared(), size, phase);
  }

  SimpleGeneratorPtr<Target, Model> make_shared() {
    return std::static_pointer_cast<Self>(this->shared_from_this());
  }
};

}  // namespace model
}  // namespace tops

#endif
