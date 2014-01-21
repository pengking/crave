#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <fstream>
#include <set>
#include <string>

namespace crave {

class Setting {
protected:
  typedef boost::property_tree::ptree ptree;

public:
  Setting(std::string const& filename) : filename_(filename) { }

  void load() {
    ptree tree = read_setting_file_();
    load_(tree);
  }
  void save() const {

    ptree tree = read_setting_file_();
    save_(tree);

    boost::property_tree::xml_writer_settings<char> settings('\t', 1);
    write_xml(filename_, tree, std::locale(), settings);
  }

private:
  virtual void load_(ptree&) = 0;
  virtual void save_(ptree&) const = 0;

  ptree read_setting_file_() const {
    ptree tree;

    std::ifstream cfg_file(filename_.c_str());
    if (cfg_file.is_open())
      read_xml(cfg_file, tree, boost::property_tree::xml_parser::trim_whitespace);

    cfg_file.close();
    return tree;
  }

protected:
  std::string module_name_;   // stores module name for config file
private:
  std::string filename_;      // stores file name of config file
};

class LoggerSetting : public Setting {
public:
  LoggerSetting(std::string const& filename)
  : Setting(filename), module_name_("logger"), file_(), dir_(), s_level_(), file_size_(), modules_() { }

private:
  virtual void load_(ptree& tree) {
    file_ = tree.get(module_name_ + ".filename", "crave.log");
    dir_ = tree.get(module_name_ + ".directory", "./logs");
    s_level_ = tree.get(module_name_ + ".level", 0);
    file_size_ = tree.get(module_name_ + ".filesize", 100);
  }
  virtual void save_(ptree& tree) const {
    tree.put(module_name_ + ".filename", file_);
    tree.put(module_name_ + ".directory", dir_);
    tree.put(module_name_ + ".level", s_level_);
    tree.put(module_name_ + ".filesize", file_size_);
  }

public:
  std::string const& filename() const {
    return file_;
  }
  std::string const& dirname() const {
    return dir_;
  }
  int s_level() const {
    return s_level_;
  }
  int filesize() const {
    return file_size_;
  }

private:
  std::string module_name_;
private:
  std::string file_;              // log filename
  std::string dir_;               // logs directory
  int s_level_;                   // severity level
  int file_size_;                 // maximum size of logfile
  std::set<std::string> modules_; // modules where logging is enabled
};

class RandObjGenSetting : public Setting {
public:
  RandObjGenSetting(std::string const& filename)
  : Setting(filename), module_name_("rand_obj_gen"), num_gens_() { }

private:
  virtual void load_(ptree& tree) {
    num_gens_ = tree.get(module_name_ + ".num_generations", 1000);
  }
  virtual void save_(ptree& tree) const {
    tree.put(module_name_ + ".num_generations", num_gens_);
  }

public:
  unsigned int num_generations() const {
    return num_gens_;
  }

private:
  std::string module_name_;
private:
  unsigned int num_gens_;
};

} // end namespace crave