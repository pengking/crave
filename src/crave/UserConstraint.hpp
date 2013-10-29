#pragma once

#include "Context.hpp"
#include "ConstrainedRandom.hpp"
#include "expression/Node.hpp"
#include "expression/ReplaceVisitor.hpp"

#include <boost/intrusive_ptr.hpp>
#include <boost/foreach.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/lexical_cast.hpp>

#include <ostream>
#include <string>
#include <vector>

namespace crave {

struct UserConstraint {

  typedef NodePtr expression;
  typedef std::string string;

  UserConstraint(unsigned const id, expression const expr, string const& name)
  : expr_(expr), name_(name), soft_(false), enabled_(true) { }
  UserConstraint(unsigned const id, expression const expr, string const& name, bool const soft)
  : expr_(expr), name_(name), soft_(soft), enabled_(true) { }
  UserConstraint(unsigned const id, expression const expr, string const& name, bool const soft, bool const enabled)
  : expr_(expr), name_(name), soft_(soft), enabled_(enabled) { }
  UserConstraint(UserConstraint const& other)
  : id_(other.id()), expr_(other.get_expression()), name_(other.get_name()),
    soft_(other.is_soft()), enabled_(other.is_enabled()) { }

  template<typename ostream>
  friend ostream& operator<<(ostream& os, UserConstraint constr) {
    os << constr.name_ << " is " << (constr.soft_?"soft":"hard") << " constraint and " << (constr.enabled_?"enabled":"disabled");
    return os;
  }

  inline unsigned id() const {
    return id_;
  }

  inline expression const & get_expression() const {
    return expr_;
  }

  inline string get_name() const {
    return name_;
  }

  inline bool is_soft() const {
    return soft_;
  }

  inline bool is_enabled() const {
    return enabled_;
  }
  inline void enable() {
    enabled_ = true;
  }
  inline void disable() {
    enabled_ = false;
  }

 protected:
  unsigned id_;
  expression expr_;
  string name_;
  bool soft_;
  bool enabled_;
};

struct ConstraintSet {

  typedef std::string string;
  typedef std::vector<UserConstraint> ConstraintsVector;
  typedef ConstraintsVector::iterator iterator;
  typedef ConstraintsVector::const_iterator const_iterator;
  typedef ConstraintsVector::reference reference;
  typedef ConstraintsVector::const_reference const_reference;
  typedef ConstraintsVector::size_type size_type;
  typedef ConstraintsVector::value_type value_type;

  typedef boost::intrusive_ptr<VariableExpr> VariablePtr;
  typedef std::vector<VariablePtr> VectorElements;

  ConstraintSet()
  : constraints_(), changed_(false), unique_(false), has_soft_(false), vec_elements_() { }

  template<typename ostream>
  friend ostream& operator<<(ostream& os, ConstraintSet set) {
    os << "Set is " << (set.changed_?"":"not ") << "changed and " << (set.unique_?"":"not ") << "unique\n"; 
    os << "Size is " << set.constraints_.size() << "\n";

    BOOST_FOREACH (value_type item, set.constraints_) {
      os << item << "\n";
    }
    os << std::flush;
    return os;
  }

  reference operator[](size_type n) {
    changed_ = true;
    return constraints_[n];
  }
  const_reference operator[](size_type n) const {
    return constraints_[n];
  }
  reference at(size_type n) {
    changed_ = true;
    return constraints_.at(n);
  }
  const_reference at(size_type n) const {
    return constraints_.at(n);
  }

  iterator begin() {
    changed_ = true;
    return constraints_.begin();
  }
  const_iterator begin() const {
    return constraints_.begin();
  }
  iterator end() {
    changed_ = true;
    return constraints_.end();
  }
  const_iterator end() const {
    return constraints_.end();
  }

  void push_back(value_type const& value) {
    changed_ = true;
    has_soft_ |= value.is_soft();
    constraints_.push_back(value);
  }
  void pop_back() {
    changed_ = true;
    constraints_.pop_back();
  }

  iterator insert(iterator position, value_type const& value) {
    changed_ = true;
    has_soft_ |= value.is_soft();
    return constraints_.insert(position, value);
  }
  template<typename InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last) {
    changed_ = true;
    constraints_.insert(position, first, last);
  }

  iterator erase(iterator position) {
    changed_ = true;
    return constraints_.erase(position);
  }
  iterator erase(iterator first, iterator last) {
    changed_ = true;
    return constraints_.erase(first, last);
  }

  size_type size() const {
    return constraints_.size();
  }

  void clear() {
    changed_ = true;
    constraints_.clear();
  }

  bool enable_constraint(string const& key) {
    BOOST_FOREACH (value_type& c, constraints_) {
      if (0 == c.get_name().compare(key)) {
        c.enable();
        changed_ = true;
        return true;
      }
    }
    return false;
  }
  bool disable_constraint(string const& key) {
    BOOST_FOREACH (value_type& c, constraints_) {
      if (0 == c.get_name().compare(key)) {
        c.disable();
        changed_ = true;
        return true;
      }
    }
    return false;
  }
  bool is_constraint_enabled(string const& key) {
    BOOST_FOREACH (value_type const& c, constraints_)
      if (0 == c.get_name().compare(key))
        return c.is_enabled();

    return false;
  }

  bool is_changed() const {
    return changed_;
  }
  void set_synced() {
    changed_ = false;
  }

  bool is_unique() const {
    return unique_;
  }
  void set_unique(bool const val) {
    changed_ = true;
    unique_ = val;
  }

  bool has_soft() const {
    return has_soft_;
  }

  VectorElements& get_vec_vars() {
    return vec_elements_;
  }

private:
  ConstraintsVector constraints_;
  bool changed_;
  bool unique_;
  bool has_soft_;

  VectorElements vec_elements_;
};

namespace ConstraintBuilder {

namespace {

unsigned int contraintID = 0;

}

template<typename Expr>
inline UserConstraint makeConstraint(std::string const& name, Expr e, Context& ctx,
                                     bool const soft) {
    NodePtr n(boost::proto::eval(FixWidth()(e), ctx));
    return UserConstraint(contraintID++, n, name, soft);
}

template<typename Expr>
inline UserConstraint makeConstraint(std::string const& name, Expr e, Context& ctx) {
    return makeConstraint(name, e, ctx, false);
}

template<typename Expr>
inline UserConstraint makeConstraint(Expr e, Context& ctx, bool const soft) {
    return makeConstraint("constraint_" + boost::lexical_cast<std::string>(contraintID),
                          e, ctx, soft);
}

template<typename Expr>
inline UserConstraint makeConstraint(Expr e, Context& ctx) {
    return makeConstraint(e, ctx, false);
}

} // end namespace ConstraintBuilder
} // end namespace crave
