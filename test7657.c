void render() {
    // Clear the screen
    SDL_SetRenderDrawColor(state.renderer, 115, 206, 225, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(state.renderer);

    int r = randgen(400);

    int cord = get_ball_cord(b.x, b.y, b.x1, b.y1, ticks);
    
    b.y3 = cord;
    int xcord = ticks;

    if (!b.dir){
        xcord = abs(xcord-600);
    }
    printf("%d\n", xcord);

    render_comp();
    render_player(); //Render the player

    SDL_RenderDrawCircle(state.renderer, xcord, cord, 15);


    //SDL_RenderDrawLine(state.renderer, 10, player1.y, 600, r);

    
    
    // Update the screen
    SDL_RenderPresent(state.renderer);
     
    if (ticks == 600){
        b.dir = !b.dir;
        b.y = b.y1;
        b.y1 = r;

        
    }

    if (ticks == SCREEN_WIDTH){
        ticks == -1;
    }
    ticks++;
}