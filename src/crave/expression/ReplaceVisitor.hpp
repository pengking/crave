#pragma once

#include "Node.hpp"
#include "NodeVisitor.hpp"

#include <map>
#include <stack>
#include <vector>

namespace crave {

class ReplaceVisitor : public NodeVisitor {
public:
  ReplaceVisitor(std::vector<boost::intrusive_ptr<VariableExpr> >& vars)
  : vec_idx_(), okay_(true), result_(), aux_stack_(), subscript_stack_(),
    variables_(vars), terminals_() { }

  virtual void visitNode( Node const & );
  virtual void visitTerminal( Terminal const & );
  virtual void visitUnaryExpr( UnaryExpression const & );
  virtual void visitUnaryOpr( UnaryOperator const & );
  virtual void visitBinaryExpr( BinaryExpression const & );
  virtual void visitBinaryOpr( BinaryOperator const & );
  virtual void visitTernaryExpr( TernaryExpression const & );
  virtual void visitPlaceholder( Placeholder const & );
  virtual void visitVariableExpr( VariableExpr const & );
  virtual void visitConstant( Constant const & );
  virtual void visitVectorExpr( VectorExpr const & );
  virtual void visitNotOpr( NotOpr const & );
  virtual void visitNegOpr( NegOpr const & );
  virtual void visitComplementOpr( ComplementOpr const & );
  virtual void visitInside( Inside const & );
  virtual void visitExtendExpr( ExtendExpression const & );
  virtual void visitAndOpr( AndOpr const & );
  virtual void visitOrOpr( OrOpr const & );
  virtual void visitLogicalAndOpr( LogicalAndOpr const & );
  virtual void visitLogicalOrOpr( LogicalOrOpr const & );
  virtual void visitXorOpr( XorOpr const & );
  virtual void visitEqualOpr( EqualOpr const & );
  virtual void visitNotEqualOpr( NotEqualOpr const & );
  virtual void visitLessOpr( LessOpr const & );
  virtual void visitLessEqualOpr( LessEqualOpr const & );
  virtual void visitGreaterOpr( GreaterOpr const & );
  virtual void visitGreaterEqualOpr( GreaterEqualOpr const & );
  virtual void visitPlusOpr( PlusOpr const & );
  virtual void visitMinusOpr( MinusOpr const & );
  virtual void visitMultipliesOpr( MultipliesOpr const & );
  virtual void visitDevideOpr( DevideOpr const & );
  virtual void visitModuloOpr( ModuloOpr const & );
  virtual void visitShiftLeftOpr( ShiftLeftOpr const & );
  virtual void visitShiftRightOpr( ShiftRightOpr const & );
  virtual void visitVectorAccess( VectorAccess const & );
  virtual void visitIfThenElse( IfThenElse const & );

  void reset();
  inline bool okay() {
    return okay_;
  }
  inline NodePtr result() {
    return result_;
  }
  inline void set_vec_idx(unsigned int const idx) {
    vec_idx_ = idx;
  }
private:
  void updateResult();
  void evalUnaryExpr(UnaryExpression const&, NodePtr&);
  void evalBinExpr(BinaryExpression const&, NodePtr&, NodePtr&);
  void evalTernExpr(TernaryExpression const&, NodePtr&, NodePtr&, NodePtr&);
  void evalBinSubscript(int&, int&);
  void evalTernSubscript(int&, int&, int&);

private:
  unsigned int vec_idx_;
  bool okay_;
  NodePtr result_;
  std::stack<NodePtr> aux_stack_;
  std::stack<int> subscript_stack_;
  std::vector<boost::intrusive_ptr<VariableExpr> >& variables_;
  std::map<int, NodePtr> terminals_;
};

} // end namespace crave