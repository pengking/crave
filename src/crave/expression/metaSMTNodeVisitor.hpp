#ifndef METASMTNODEVISITOR_HPP_
#define METASMTNODEVISITOR_HPP_

#include "../AssignResult.hpp"
#include "Node.hpp"
#include "NodeVisitor.hpp"

namespace crave {

class metaSMTVisitor : public NodeVisitor {
public:
  virtual void makeAssertion( Node const & ) = 0;
  virtual void makeAssumption( Node const & ) = 0;
  virtual bool solve() = 0;
  virtual bool read(Node const&, AssignResult&) = 0;
};

} //end namespace crave

#endif /* METASMTNODEVISITOR_HPP_ */
