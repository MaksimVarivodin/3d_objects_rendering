#pragma once
#include "text_renderer.h"
class game_window : public RenderWindow
{
    bool show_frame_rate_ = true;
    bool debug_mode_ = true;
    frame_rate frames_per_sec_;

    text_renderer text_renderer_;

public:


    void run();
    void set_frame_rate_show(bool);
    void set_debug_mode(const bool & debug_mode = false){ debug_mode_ = debug_mode;}

    game_window(const VideoMode & mode = VideoMode::getDesktopMode(), const string & w_name = "", const short& flags = Style::Default) :
        RenderWindow(mode, w_name, flags),
        text_renderer_(text_renderer::load_text_renderer(R"(\arial\arial_light.ttf)")){
        text_renderer_.set_text_properties();
    }

    explicit game_window(const int& frame_rate, const VideoMode & mode, const string & w_name, const short& flags): game_window(mode, w_name, flags)  {
        
        setFramerateLimit(frame_rate);
    }

    explicit game_window(const bool& v_sync, const VideoMode & mode, const string & w_name, const short& flags) :game_window(mode, w_name, flags) {
        setVerticalSyncEnabled(v_sync);
    }

    ~game_window() override
    {
       this->RenderWindow::~RenderWindow();
        frames_per_sec_.stop();
    }

};

