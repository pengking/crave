#pragma once

#include "Context.hpp"
#include "Node.hpp"

namespace crave {

struct expr_tag : public Constraint<boost::proto::terminal<NodePtr>::type> {
  typedef Constraint<boost::proto::terminal<NodePtr>::type> base_type;
  expr_tag(NodePtr n) : base_type(boost::proto::make_expr<boost::proto::tag::terminal>(n)) {}
};

typedef typename boost::proto::result_of::make_expr<boost::proto::tag::terminal, Constraint_Domain, NodePtr>::type
    expression;

template <typename Expr>
expression make_expression(Expr e) {
  static Context ctx(crave::variables);
  return boost::proto::make_expr<boost::proto::tag::terminal, Constraint_Domain>(boost::proto::eval(e, ctx));
}

template <typename Integer>
expression value_to_expression(Integer const& i) {
  return boost::proto::make_expr<boost::proto::tag::terminal, Constraint_Domain>(Context::new_value(i));
}

}  // end namespace crave