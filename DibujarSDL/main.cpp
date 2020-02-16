#include <SDL2/SDL.h>

void DrawCircle(SDL_Renderer * renderer, int centroX, int centroY, int radio){
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
    int x;
    int y;
    while(radio > 0){
        for (double t = 0; t < 360; t+=0.01){
            x = centroX + radio * cos(t);
            y = centroY + radio * sin(t);
            SDL_RenderDrawPoint(renderer, x, y);
        }
        radio--;
    }
}

void dibujar(SDL_Renderer *renderer, int ancho, int altura) {
    SDL_Rect rectangulo;
    rectangulo.x = 10;
    rectangulo.y = 10;
    rectangulo.w = ancho/2;
    rectangulo.h = altura/2;

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rectangulo);
    SDL_RenderDrawRect(renderer, &rectangulo);

    SDL_RenderDrawLine(renderer, ancho/2, 0, 0, altura);
    SDL_RenderDrawLine(renderer, ancho/2, 0, ancho, altura);
    SDL_RenderDrawLine(renderer, 0, altura-1, ancho, altura-1);
}

int main(int argc, char* argv[]){
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return -1;
    }
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    int ancho = 1000;
    int altura = 1000;
    if(SDL_CreateWindowAndRenderer(ancho, altura, 0, &window, &renderer) != 0){
        return -1;
    }
    bool continuar = true;
    SDL_RenderClear(renderer);
    //dibujar(renderer, ancho, altura);
    DrawCircle(renderer, ancho/2, altura/2, 400);
    SDL_Event event;
    while (continuar) {
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                continuar = false;
            }
        }
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
    return 0;
}
