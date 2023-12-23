#pragma once
#include "frame_rate_renderer.h"
class game_window : public RenderWindow
{
    bool show_frame_rate_ = true;
    frame_rate f_per_sec_;

    text_renderer t_renderer_;
    frame_rate_renderer f_r_renderer_;
    

    Mutex w_mutex_;

    mesh_loader object_loader_;

    mesh calculate_points(mesh object, const float& angle1, const float& angle2, const float& angle3) const;

public:


    void run();
    void set_frame_rate_show(bool);


    game_window() :
        t_renderer_(text_renderer::create_any_text_renderer()),
        f_r_renderer_(t_renderer_)
    {
    }

    explicit game_window(const int& frame_rate):game_window() {
        setFramerateLimit(frame_rate);
    }

    explicit game_window(const bool& v_sync) :game_window() {
        setVerticalSyncEnabled(v_sync);
    }
    game_window(const int & frame_rate, const VideoMode & mode, const string & w_name, const short& flags):RenderWindow(mode, w_name, flags)
    {
	    t_renderer_ = text_renderer::create_any_text_renderer();
        f_r_renderer_ = frame_rate_renderer( t_renderer_);
    	setFramerateLimit(frame_rate);
    }
     game_window(const bool & sync, const VideoMode & mode, const string & w_name, const short& flags):RenderWindow(mode, w_name, flags)
    {
	    t_renderer_ = text_renderer::create_any_text_renderer();
        f_r_renderer_ = frame_rate_renderer( t_renderer_);
    	setVerticalSyncEnabled(sync);
     
    }
    ~game_window() override
    {
       this->RenderWindow::~RenderWindow();
        f_per_sec_.stop();
    }

};

