#include "../../include/core/renderer.h"
#include "../../include/core/render.h"
#include "../../include/core/sprite.h"
#include "../../include/core/globals.h"

void menuStateRender(GameState* state){
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, state->textures[BACKGROUND], NULL, NULL);

    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderFillRect(renderer, &state->button);

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderCopy(renderer, state->textures[PLAYBUTTON], NULL, &state->button);
    
    SDL_RenderPresent(renderer);

}

void playStateRender(GameState* state){
    SDL_SetRenderDrawColor(renderer, 38, 38, 38, 255);
    SDL_RenderClear(renderer);

    renderMap(state->map, state->camera);
    renderEntities(state);
    renderProjectiles(state);
    renderHUD(state);

    SDL_RenderPresent(renderer);

}

void pauseStateRender(GameState* state){
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderClear(renderer);
    if(state->stack->top == 2){
        GameState* prev = gameStates.data[gameStates.top - 1];

        renderMap(prev->map, prev->camera);
        renderEntities(prev);
        renderProjectiles(prev);
        renderHUD(prev);
    }

    SDL_RenderCopy(renderer, state->textures[PAUSESCREEN], NULL, NULL);
    
    SDL_RenderPresent(renderer);

}

void gameOverStateRender(GameState* state){
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderClear(renderer);

    GameState* prev = gameStates.data[gameStates.top - 1];

    renderMap(prev->map, prev->camera);
    renderEntities(prev);
    renderProjectiles(prev);
    renderHUD(prev);

    SDL_RenderCopy(renderer, state->textures[GAMEOVERSCREEN], NULL, NULL);
    
    SDL_RenderPresent(renderer);

}

void renderEntities(GameState* state){
    Camera* camera = state->camera;
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    
    int x = state->player->position.x - camera->position.x;
    int y = state->player->position.y - camera->position.y;

    SDL_Rect rect = {x, y, 16, 16};

    SDL_RenderCopy(renderer, state->textures[PLAYER], &state->player->sprite, &rect);
            
    SDL_Rect tmp = rect;
    tmp.w = 8;
    tmp.x = state->player->collider.x - camera->position.x;
    tmp.y = state->player->collider.y - camera->position.y;

    int n = state->demons->size;
    for(int i = 0; i < n; i++){
        Demon* demons = state->demons->array;
        Demon demon = demons[i];

        /*
        int x = demon.position.x;
        int y = demon.position.y;

        SDL_Rect rect = {x, y, 16, 16};

        SDL_RenderCopy(renderer, state->textures[DEMON], &demon.sprite, &rect);
        SDL_RenderDrawRect(renderer, &demon.collider);  
        */

        int x = demon.position.x - camera->position.x;
        int y = demon.position.y- camera->position.y;
        int w = 16;
        int h = 16;

        SDL_Rect rect = {x, y, w, h};
        SDL_RenderCopy(renderer, state->textures[DEMON], &demon.sprite, &rect);

        tmp = rect;
        tmp.w = 8;
        tmp.x = demon.collider.x - camera->position.x;
        tmp.y = demon.collider.y - camera->position.y;
        //SDL_RenderDrawRect(renderer, &tmp);  


    }
    

}

void renderProjectiles(GameState* state){
    Camera* camera = state->camera;
    for(int i = 0; i < state->hailIndex; i++){
        SDL_Rect dst;
        dst.x = state->hails[i].position.x - camera->position.x;
        dst.y = state->hails[i].position.y - camera->position.y;
        dst.w = 16;
        dst.h = 16;
        if(state->hails[i].flip){
            SDL_RenderCopy(renderer, state->textures[PLAYER], &state->hails[i].sprite, &dst);
        }else{
            SDL_RenderCopyEx(renderer, state->textures[PLAYER], &state->hails[i].sprite, &dst, 0.0, NULL, SDL_FLIP_HORIZONTAL);
        }
        
        SDL_Rect tmp = state->hails[i].collider;
        tmp.x = state->hails[i].collider.x - camera->position.x;
        tmp.y = state->hails[i].collider.y - camera->position.y;
        //SDL_RenderDrawRect(renderer, &tmp); 

    }

    for(int i = 0; i < state->fireIndex; i++){
        SDL_Rect dst;
        dst.x = state->fires[i].position.x - camera->position.x;
        dst.y = state->fires[i].position.y - camera->position.y;
        dst.w = 16;
        dst.h = 16;
        if(state->fires[i].flip){
            SDL_RenderCopy(renderer, state->textures[PLAYER], &state->fires[i].sprite, &dst);
        }else{
            SDL_RenderCopyEx(renderer, state->textures[PLAYER], &state->fires[i].sprite, &dst, 0.0, NULL, SDL_FLIP_HORIZONTAL);
        }
        
        SDL_Rect tmp = state->fires[i].collider;
        tmp.x = state->fires[i].collider.x - camera->position.x;
        tmp.y = state->fires[i].collider.y - camera->position.y;
        //SDL_RenderDrawRect(renderer, &tmp); 

    }
}

void renderHUD(GameState* state){
    Player* player = state->player;
    float healthPercentage = (float)player->health / player->maxHealth;
    int current = player->health;
    int max = player->maxHealth;

    int barWidth = 50;
    int barHeight = 10;
    int barX = 2;
    int barY = 2;

    float currentWidth = (float)(barWidth * healthPercentage );

    SDL_Rect backgroundRect = {barX-1, barY-1, barWidth+2, barHeight+2};
    
    //SDL_Rect healthRect = {barX, barY, (int)currentWidth, barHeight};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &backgroundRect);

    int r, g, b;
    int a = 255;

    // Change health bar color based on current health
    if(current == max){
      r = 100;
      g = 255;
      b = 175;
    } else if( current < max && healthPercentage > 0.25) {
      r = 255;
      g = 255;
      b = 175;
    } else{
      r = 255;
      g = 100;
      b = 100;
    }

    
    SDL_Rect healthRect = {barX, barY, (int)currentWidth, barHeight};
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &healthRect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect square = {barWidth + 4, barY-1, 12, 12};
    SDL_Rect port = {barWidth + 4+1, barY-1+1, 12-2, 12-2};
    SDL_Rect demonSquare = {barWidth + 20, barY-1, 12, 12};
    SDL_Rect demonPort = {barWidth + 20 + 1, barY-2, 12-2, 12-2};
    SDL_RenderFillRect(renderer, &square);
    //SDL_RenderDrawRect(renderer, &demonSquare);
    //SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
    //SDL_RenderDrawRect(renderer, &port);
    if(!player->fireToIce){
        SDL_Rect hail = {16 * 4, 16 * 4, 16, 16};
        SDL_RenderCopy(renderer, state->textures[PLAYER], &hail, &port);
    }else{
        SDL_Rect fire = {16 * 0, 16 * 4, 16, 16};
        SDL_RenderCopy(renderer, state->textures[PLAYER], &fire, &port);
    }
    SDL_Rect demonHead = {0, 0, 16, 9};
    SDL_RenderCopy(renderer, state->textures[DEMON], &demonHead, &demonPort);
    
    SDL_Color white = {255, 255, 255, 255};
    char str[20];
    sprintf(str, "%d", state->deadDemons);
    SDL_Surface* textSurface = TTF_RenderText_Solid(state->font, str, white);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    
    int w;
    int h;

    SDL_QueryTexture(textTexture, NULL, NULL, &w, &h);

    SDL_Rect dest = {barWidth + 20+12, barY, w, h};
    SDL_RenderCopy(renderer, textTexture, NULL, &dest);

    

}