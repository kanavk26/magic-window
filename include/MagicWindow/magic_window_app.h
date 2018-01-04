#pragma once

// cinder
#include "cinder/Display.h"
#include "cinder/Json.h"
#include "cinder/Log.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

// hexa
#include "MagicWindow/context.h"
#include "MagicWindow/utils.h"
#include "MagicWindow/window_config.h"

namespace magicwindow {
  class magic_window_app : public ci::app::App{
  public:
    ///////////////////////////////////////////////////////////////
    // Methods
    ///////////////////////////////////////////////////////////////
    /**
     * Initializes the application, config and windows
     * configFilename - config file name
     *
     * returns bool indicating that initialization was successful
     */
    bool initialize(std::string config_filename = "cfg.json");
    
    /**
     * Initializes the application, config and windows
     * data - config data as json
     */
    bool initialize(ci::JsonTree data);
    
    /**
     * Create windows based on config variables. This method must be called by a sub-classing application.
     */
    void initialize_window_configuration();
    
    /**
     * The main update call
     */
    void update() override;
    
    /**
     * The main draw call
     */
    void draw() override;
    
    /**
     * Override key and mouse events and pass them to the global emitter
     */
    void fileDrop(ci::app::FileDropEvent e) override;
    void keyDown(ci::app::KeyEvent e) override;
    void keyUp(ci::app::KeyEvent e) override;
    void mouseDown(ci::app::MouseEvent e) override;
    void mouseDrag(ci::app::MouseEvent e) override;
    void mouseMove(ci::app::MouseEvent e) override;
    void mouseUp(ci::app::MouseEvent e) override;
    void mouseWheel(ci::app::MouseEvent e) override;
    void cleanup() override;
    
  protected:
    ///////////////////////////////////////////////////////////////
    // Properties
    ///////////////////////////////////////////////////////////////
    context ctx;
    ci::app::WindowRef params_window;
    bool params_window_is_available;
  };
}