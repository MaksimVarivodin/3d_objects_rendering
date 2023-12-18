#pragma once
#include "FrameRateRenderer.h"
class GameWindow : public RenderWindow
{
    bool showFrameRate = true;
    FrameRate fPerSec;

    TextRenderer tRenderer;
    FrameRateRenderer fRRenderer;
    

    Mutex wMutex;

    Mesh cube;

public:


    void run();
    void setFrameRateShow(bool);
    void initCube(vector<Triangle> tr);


    GameWindow() :
        RenderWindow(VideoMode::getDesktopMode(), "Space Traveler"),
        tRenderer(TextRenderer::createAnyTextRenderer()),
        fRRenderer(tRenderer)
    {

    };
    GameWindow(const int& frameRate):GameWindow() {
        setFramerateLimit(frameRate);
    }
    GameWindow(const bool& vSync) :GameWindow() {
        setVerticalSyncEnabled(vSync);
    }
    
    GameWindow(const bool& vSync, const int& frameRate) :
        GameWindow(frameRate)
    {
        setVerticalSyncEnabled(vSync);
    }
    ~GameWindow()
    {
        fPerSec.stop();
    }

};

