#ifndef DECODABLE_MODEL_HPP
#define DECODABLE_MODEL_HPP


#include "ProbabilisticModel.hpp"
#include "Sequence.hpp"
#include "util.hpp"
#include <boost/shared_ptr.hpp>

namespace tops {
  //! Interface defining probabilistic model with the viterbi, forward and backward algorithm
  class DecodableModel : public ProbabilisticModel  {
  public:
    DecodableModel(){};
    virtual ~DecodableModel(){};

    virtual double evaluate(const Sequence & s, unsigned int begin, unsigned int end) const; 
    
    virtual Sequence & choose(Sequence & h, int size) const;

    virtual Sequence & choose(Sequence & h, Sequence & path,  int size) const;

    virtual Sequence & choose(Sequence & h, Sequence & path,  int i, int size) const;

    
    //! Forward algorithm
    virtual double forward(const Sequence & s, Matrix &alpha) const = 0;

    //! Backward algorithm
    virtual double backward(const Sequence & s, Matrix &beta) const = 0;

    //! Viterbi algorithm
    virtual double viterbi (const Sequence &s, Sequence &path, Matrix & gamma) const = 0;
    
    //! Posterior Probabilities: P(yi=k|x)
    virtual void posteriorProbabilities (const Sequence &s, Matrix & probabilities) const = 0;
    
    //! Posterior Decoding: ^yi = argmax_k P(yi=k|x)
    virtual void posteriorDecoding (const Sequence &s, Sequence &path, Matrix & probabilities) const = 0;

    //! Choose the observation given a state 
    /*!\param h is the history */
    virtual Sequence &  chooseObservation ( Sequence & h,int i, int state ) const = 0;

    //! Choose a state
    virtual int chooseState(int state ) const = 0;

    //! Choose the initial state
    virtual int chooseFirstState() const = 0;

    //! Get state name
    virtual std::string getStateName(int state) const = 0;

    //! Get the state names
    virtual AlphabetPtr getStateNames() const = 0;

    virtual DecodableModel* decodable() {
      return this;
    }
  };
  typedef boost::shared_ptr<DecodableModel>  DecodableModelPtr;
}

#endif
