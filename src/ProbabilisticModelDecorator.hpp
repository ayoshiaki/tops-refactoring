#include "ProbabilisticModel.hpp"
#include <string>
namespace tops {
  //! Decorator for the probabilistic model
  class ProbabilisticModelDecorator : public ProbabilisticModel {
  private:
    ProbabilisticModelPtr _model;
    std::string _submodelname;
  public:
    ProbabilisticModelDecorator(ProbabilisticModelPtr m) :_model(m){};
    virtual ~ProbabilisticModelDecorator() {};
    //! Calculates the sequence likelihood given this model 
    virtual double evaluate(const Sequence & s, unsigned int begin, unsigned int end) const {
      double result;
      result = _model->evaluate(s,begin,end);
      return result;
    }

    virtual double  log_probability_of(int s) const{
      double result ;
      result = _model->log_probability_of(s);
      return result;
    }    
    //! Choose a symbol
    virtual double choose() const {
      double result;
      result = _model->choose();
      return result;
    }

    virtual Sequence & choose(Sequence & h, int size) const {
      _model->choose(h,size);
      return h;
    }

    virtual Sequence & choose(Sequence &h, int initial_phase, int size) const{
      _model->choose(h,initial_phase, size);
      return h;
    }

    virtual Sequence & choose(Sequence & h, Sequence & path,  int size) const
    {
      _model->choose(h,path, size);
      return h;
    }


    virtual Sequence & choose(Sequence & h, Sequence & path,  int i, int size) const
    {
      _model->choose(h, path, i, size);
      return h;
    }

    virtual Sequence & chooseWithHistory(Sequence & h, int i,  int size) const
    {
      _model-> chooseWithHistory(h,i,size);
      return h;
    }

    virtual Sequence & chooseWithHistory(Sequence & h, int i,  int phase, int size) const{
      _model->chooseWithHistory(h, i, phase,  size);
      return h;
    }

    virtual double prefix_sum_array_compute(int begin , int end) {
      return _model->prefix_sum_array_compute(begin,end);
    }

    virtual double prefix_sum_array_compute(int begin , int end, int phase) {
      return _model->prefix_sum_array_compute(begin,end,phase);
    }

    virtual bool initialize_prefix_sum_array(const Sequence & s, int phase) {
      return initialize_prefix_sum_array(s);
    }
    virtual bool initialize_prefix_sum_array(const Sequence & s) {
      return _model->initialize_prefix_sum_array(s);
    }
    virtual ProbabilisticModelPtr subModel() const {
      return _model;
    }
    virtual void setSubModel(ProbabilisticModelPtr model) {
      _model =model;
    }
    virtual void  subModelName(std::string name) {
      _submodelname = name;
    }
    virtual std::string subModelName() const{
      return _submodelname;
    }

  };
  typedef boost::shared_ptr<ProbabilisticModelDecorator> ProbabilisticModelDecoratorPtr;
}
