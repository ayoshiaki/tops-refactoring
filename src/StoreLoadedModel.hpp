#ifndef STORE_LOADED_MODEL_HPP
#define STORE_LOADED_MODEL_HPP
#include <boost/shared_ptr.hpp>
#include "ProbabilisticModel.hpp"
namespace tops {

  class StoreLoadedModel;

  class StoreLoadedModel {
  public:

      virtual ~StoreLoadedModel(){};


      virtual ProbabilisticModelPtr add(std::string  name, ProbabilisticModelPtr model) ;

      virtual  ProbabilisticModelPtr get(std::string  name) ;

      static StoreLoadedModel * instance() ;


  protected:
    StoreLoadedModel() {
    };
  private:
      ProbabilisticModelPtr null;
      static StoreLoadedModel * _inst;
      std::map <std::string, ProbabilisticModelPtr> _models;
  };


}


#endif
