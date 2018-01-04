#pragma once

#include <stdio.h>

// boost
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

// cinder
#include "cinder/Buffer.h"
#include "cinder/Json.h"
#include "cinder/Log.h"
#include "cinder/gl/gl.h"
#include "cinder/app/App.h"

namespace magicwindow {
  class env {
  public:
    static std::string get(std::string key, std::string default_value) {
      auto val = std::getenv(key.c_str());
      if (val == NULL) {
        return default_value;
      }
      else {
        return std::string(val);
      }
    }
  };
  
  class json {
  public:
    ///////////////////////////////////////////////////////////////
    // static methods
    ///////////////////////////////////////////////////////////////
    /**
     * Get a value from a JsonTree
     * @param tree - The JsonTree to get the data from
     * @param path - A string representation of the path to node containing the desired data
     * @param defaultValue - A default value, returned if the node is not defined
     * @return a value of type T from a JsonTree
     */
    template <typename T>
    static T get(const ci::JsonTree & tree, const std::string & path, T default_value, std::string separators = "/.:|") {
      std::vector<std::string> parts;
      boost::split(parts, path, boost::is_any_of(separators));
      if (parts.size() && tree.hasChild(parts[0])) {
        int i = 0;
        ci::JsonTree child = tree;
        while (i < parts.size()) {
          if (child.hasChild(parts[i])) {
            ci::JsonTree c = child.getChild(parts[i]);
            child = c;
            i++;
          } else {
            return default_value;
          }
        }
        
        if (child.getNodeType() == cinder::JsonTree::NodeType::NODE_NULL) {
          return default_value;
        }
        
        try {
          return child.getValue<T>();
        }
        catch(std::exception exc) {
          CI_LOG_EXCEPTION("Type conversion was not possible for: " + path + ". Returning supplied default value.", exc);
          return default_value;
        }
        
      }
      return default_value;
    }
    
    /**
     * Returns an RGB color
     * Supplied data should be formatted as such: {r: 1.0, g: 1.0, b: 1.0}
     */
    static ci::Color get_color(const ci::JsonTree & data);
    
    /**
     * Returns an RGBA color
     * Supplide data should be formatted as such: {r: 1.0, g: 1.0, b: 1.0, a: 1.0}
     */
    static ci::ColorA get_color_a(const ci::JsonTree & data);
    
    /**
     * Takes a JsonTree containing x, y coordinate data and returns a Vec2f
     * @param data - A JsonTree with the following format {x : 0, y : 0}
     * @param x - The key for the x value (defaults to x)
     * @param y - The key for the y value (defaults to y)
     */
    static ci::vec2 get_vec2(const ci::JsonTree & data, std::string x = "x", std::string y = "y");
    
    /**
     * Takes a JsonTree containing x, y, z coordinate data and returns a Vec3f
     * @param data - A JsonTree with the following format {x : 0, y : 0, z : 0}
     * @param x - The key for the x value (defaults to x)
     * @param y - The key for the y value (defaults to y)
     * @param z - The key for the z value (defaults to z)
     */
    static ci::vec3 get_vec3(const ci::JsonTree & data, std::string x = "x", std::string y = "y", std::string z = "z");
    
    /**
     * Merges json multiple trees into one tree
     * @param trees - A vector of JsonTree objects to be merged
     * @return A single JsonTree consisting of the supplied trees
     */
    static ci::JsonTree merge_trees(std::vector<ci::JsonTree> & trees);
  };
  
  class loader {
  public:
    /**
     * Blocking download method. Downloads any file from a valid url to the specified destination. 
     * Replaces existing files of the same name
     * @param src - The path to load the file from
     * @param destination - The path to save the file to
     */
    static void download(ci::fs::path src, ci::fs::path destination);
  };
}