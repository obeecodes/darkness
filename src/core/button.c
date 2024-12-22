//#include "../../include/core/button.h"
/*
void MainMenuButton::initButton(){

    TTF_Font* buttonFont = TTF_OpenFont("assets/fonts/pixel.ttf", 10);

    if (!font) {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    this->textTexture = SDL_CreateTextureFromSurface(Renderer::Instance()->getRenderer(), textSurface);
    
    TTF_CloseFont(buttonFont);

    SDL_FreeSurface(textSurface);
}


void MainMenuButton::update(){
    SDL_Rect viewport;
    SDL_RenderGetViewport(Renderer::Instance()->getRenderer(), &viewport);
    this->dest = { viewport.x + (viewport.w - BUTTON_WIDTH) / 2, offset + viewport.y + (viewport.h - BUTTON_HEIGHT) / 2, BUTTON_WIDTH, BUTTON_HEIGHT};
    this->original = this->dest;
    
    bool leftMouseButton = InputSystem::Instance()->getMouseButtonState(LEFT);

    if(leftMouseButton && !selected){
        pressedPosition = InputSystem::Instance()->getMousePosition();
        selected = true;
        pressed = true;
        released = false;
    } else if(!leftMouseButton && pressed){
        pressed = false;
        released = true;
        selected = false;
    }

    if(isHovered()){
        
        hovered = true;
        
        if (released && selectedButton()){
            callback();
            released = false;
            pressed = false;
        }

    }else{
        hovered = false;
    }
    if(released)
        pressedPosition = Vec2{};
    updateButton();
}


void MainMenuButton::initButton(){

    TTF_Font* font = TTF_OpenFont("assets/fonts/pixel.ttf", 10);

    if (!font) {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    this->textTexture = SDL_CreateTextureFromSurface(Renderer::Instance()->getRenderer(), textSurface);
    
    TTF_CloseFont(font);

    SDL_FreeSurface(textSurface);
}
*/