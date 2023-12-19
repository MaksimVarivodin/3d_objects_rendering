#pragma once
#include "frame_rate_renderer.h"
class game_window : public RenderWindow
{
    bool show_frame_rate_ = true;
    frame_rate f_per_sec_;

    text_renderer t_renderer_;
    frame_rate_renderer f_r_renderer_;
    

    Mutex w_mutex_;

    projection projection_;
    mesh cube_;
    void draw_cube();
public:


    void run();
    void set_frame_rate_show(bool);
    void init_cube(vector<Vector3f> points, vector<triangle> tr, const float& scale_x, const float& scale_y , const float& scale_z);


    game_window() :
        RenderWindow(VideoMode::getDesktopMode(), "Space Traveler"),
        t_renderer_(text_renderer::create_any_text_renderer()),
        f_r_renderer_(t_renderer_),
        projection_(getSize().y, getSize().x, 90, 1000, 0.1f)
    {
    }

    explicit game_window(const int& frame_rate):game_window() {
        setFramerateLimit(frame_rate);
    }

    explicit game_window(const bool& v_sync) :game_window() {
        setVerticalSyncEnabled(v_sync);
    }
    
    game_window(const bool& v_sync, const int& frame_rate) :
        game_window(frame_rate)
    {
        setVerticalSyncEnabled(v_sync);
    }
    ~game_window() override
    {
       this->RenderWindow::~RenderWindow();
        f_per_sec_.stop();
    }

};

