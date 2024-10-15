#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>

#include "SDL.h" 



//text rendering vars
#define NUM_ROWS 5
#define NUM_COLS 5
#define DIGIT_WIDTH 6
#define RECT_SIZE 4
#define MAX_DIGITS 3


int nums[10][NUM_ROWS][NUM_COLS] = {
    // Number 0
    {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}},
    // Number 1
    {
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1}},
    // Number 2
    {
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1}},
    // Number 3
    {
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}},
    // Number 4
    {
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1}},
    // Number 5
    {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}},
    // Number 6
    {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}},
    // Number 7
    {
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1}},
    // Number 8
    {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}},
    // Number 9
    {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}}};


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define TILE_SIZE 10

#define SPEED 2


int speed = 5;
int char_pos[2] = {100, 100};

int draw_x[SCREEN_WIDTH];
int draw_y[SCREEN_HEIGHT];

int score = 0;

bool pause = false;


typedef struct {
    int y; // Player position
    int speed; // Player movement speed
} Player;

typedef struct 
{
    int x;
    int y;
    int x1;
    int y1;
    int y3;
    bool dir;
} Ball;

//true left to right flase rigth to left
Ball b = {10,40,610,220,40, false};

//typedef struct {
//    int y; // Player position
//    int speed; // Player movement speed
//} ball;

struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool quit;
} state;

//player initalization
Player player1 = {100, 5};

//runs once at when the window opens
void init(){
    //x, y
    score = 0;
}

int randgen(ra){
    int r = rand() % ra;
    if (r < 8){
        r = r + 8;
    }
    return r;
}
void drawPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetRenderDrawColor(state.renderer, r, g, b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawPoint(state.renderer, x, y);
}

void handleKeyPress(SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN)
    {
        switch (event->key.keysym.sym)
        {
        case SDLK_UP:
            printf("Up arrow key pressed\n");
            //char_pos[1] = char_pos[1] - speed;
            if (player1.y - player1.speed > 0 && !pause){
                player1.y -= player1.speed;
            }
            break;
        case SDLK_DOWN:
            printf("Down arrow key pressed\n");
            //char_pos[1] = char_pos[1] + speed;
            //printf("%d", player1.y);
            if (player1.y + player1.speed +80 < 480 && !pause){
                player1.y += player1.speed;
            }
            break;
        case SDLK_SPACE:
            if (pause){
                pause = false;
                break;;
            }
            pause = true;
            break;
        case SDLK_ESCAPE:
            state.quit = true;
            break;
        }
    }
}

void draw_rect(int x, int y, int x1, int y1, Uint8 r, Uint8 g, Uint8 b)
{
    // Ensure the coordinates are within the screen boundaries
    x = (x < 0) ? 0 : x;
    y = (y < 0) ? 0 : y;
    x1 = (x1 >= SCREEN_WIDTH) ? SCREEN_WIDTH - 1 : x1;
    y1 = (y1 >= SCREEN_HEIGHT) ? SCREEN_HEIGHT - 1 : y1;

    // Draw the rectangle within the updated boundaries
    for (int i = x; i <= x1; i++)
    {
        for (int z = y; z <= y1; z++)
        {
            drawPixel(i, z, r, g, b);
        }
    }
}


void clear_area(int x, int y, int width, int height) {
    // Set the render color to the background color (black)
    SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    // Fill the specified area with the background color
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderFillRect(state.renderer, &rect);
}

void draw_digit(int digit, int x, int y) {
    // Draw the given digit at the specified position (x, y)
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (nums[digit][i][j] == 1) {
                // Calculate coordinates for the pixel
                int px = x + j * RECT_SIZE;
                int py = y + i * RECT_SIZE;
                // Draw the enlarged rectangle
                draw_rect(px, py, px + RECT_SIZE - 1, py + RECT_SIZE - 1, 255, 255, 255);
            }
        }
    }
}

void render_nums(int num, int x, int y) {
    // Calculate the maximum possible width for the numbers to clear
    int numDigits = 0;
    int temp = num;
    while (temp != 0) {
        temp /= 10;
        numDigits++;
    }
    if (numDigits == 0) {
        numDigits = 1; // If num is 0, it still has one digit
    }
    int max_width = numDigits * DIGIT_WIDTH * RECT_SIZE;

    // Clear the area where numbers will be rendered
    clear_area(x - max_width / 2, y, max_width, NUM_ROWS * RECT_SIZE);

    // Store digits in an array
    int digits[MAX_DIGITS] = {0}; // Initialize array with 0s
    temp = num;
    int i = MAX_DIGITS - 1; // Start from the end of the array
    while (temp != 0 && i >= 0) {
        digits[i] = temp % 10; // Store the last digit in the array
        temp /= 10; // Remove the last digit from the number
        i--; // Move to the next position in the array
    }

    // Calculate initial x position
    int xPos = x - DIGIT_WIDTH * RECT_SIZE * numDigits / 2;

    // Render each digit
    for (int u = MAX_DIGITS - numDigits; u < MAX_DIGITS; u++) {
        draw_digit(digits[u], xPos, y);
        // Update x position for the next digit
        xPos += DIGIT_WIDTH * RECT_SIZE;
    }
}
int SDL_RenderDrawCircle(SDL_Renderer *renderer, int x, int y, int radius) {
    int offsetx, offsety, d;
    int status = 0;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0) {
            return -1;
        }

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        } else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        } else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return 0;
}

//void move_ball()

void draw_char()
{
    int x = char_pos[0];
    int y = char_pos[1];
    int i;
    draw_rect(x, y, x + 5, y + 5, 255, 0, 0);
}

void render_player() {
    //draw_rect(player1.y, 50, player1.y + TILE_SIZE, 50 + TILE_SIZE, 255, 0, 0);
    //checks col
    draw_rect(15, player1.y, 15 + TILE_SIZE, player1.y + 80, 255, 0, 0);
}

int y_c = 0;
int ticks = 0;

void render_comp(){
    y_c = b.y3;
    if (y_c > 35 && y_c < 440){
        y_c -= 30;
    }
    draw_rect(600, y_c, 10 + 600, y_c + 80, 255, 0, 0);
}


int get_ball_cord(int x1, int y1, int x2, int y2, int target_x) {
  // Check for division by zero (parallel line with infinite slope)
  if (x1 == x2) {
    return -2147483648; // Integer equivalent of NAN, indicates error
  }

  // Check for horizontal line (special case)
  if (y1 == y2) {
    return y1; // All points on the line have the same y-coordinate
  }

  // Calculate slope (m) with integer arithmetic (avoid floating-point)
  int delta_y = y2 - y1;
  int delta_x = x2 - x1;

  // Check for potential overflow due to large coordinates
 

  // Calculate y-intercept (b) with integer arithmetic
  int y_intercept = y1 - (delta_y * x1 / delta_x);


  // Calculate y value for target_x with integer arithmetic
  int target_y = y_intercept + (delta_y * target_x) / delta_x;

  return target_y;
}


int r_save = 0;


void render() {
    // Clear the screen
    SDL_SetRenderDrawColor(state.renderer, 115, 206, 225, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(state.renderer);

    int r = randgen(400);

    int cord = get_ball_cord(b.x, b.y, b.x1, b.y1, ticks);
    
    b.y3 = cord;
    int xcord = ticks;

    if (!b.dir){
        xcord = abs(xcord - 600);
        //if xcord
    }
    

    render_comp();
    render_player(); // Render the player

    SDL_RenderDrawCircle(state.renderer, xcord, cord, 15);

    //collision detector
    if (xcord == 15){
        if (b.dir){
            score++;
        }
        if (!(cord > player1.y && player1.y + 80 > cord)){
            score = 0;
            pause = true;
    }
    }

    render_nums(score, 80, 10);

    // Update the screen
    SDL_RenderPresent(state.renderer);

    if (ticks >= 600){
        b.dir = !b.dir;
        b.y = b.y1;
        b.y1 = r;
        ticks = 0; // Reset ticks to start from the beginning
    }

    if (ticks >= SCREEN_WIDTH){
        ticks = -1;
    }
    ticks += 3;
}

//double floor(double x) {
//    if (x >= 0.0) {
//        return (double)((int)x);
//    } else {
//        double int_part = (double)((int)x);
//        return (int_part == x) ? int_part : int_part - 1.0;
//    }
//}



int main(int argc, char *argv[])
{
    srand(time(NULL));
    init();

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create window and renderer
    state.window = SDL_CreateWindow("Fun Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (state.window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit(); // Clean up before exiting
        return 1;
    }
    state.renderer = SDL_CreateRenderer(state.window, -1, SDL_RENDERER_ACCELERATED);
    if (state.renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(state.window); // Clean up before exiting
        SDL_Quit(); // Clean up before exiting
        return 1;
    }
    //pipes[i] = set_new_pipes(pipes[i], 40);
    //pipes[i]1 = set_new_pipes(pipes[i]1, 200);

    bool running = true;
    while (running) {
        Uint64 start = SDL_GetPerformanceCounter();

        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                state.quit = true;
                running = false; // Set running to false to exit the loop
            }
            handleKeyPress(&event);
        }

        // Game logic and rendering
        if (pause != true){
            render();
        }
    

        // Calculate elapsed time since the frame started
        Uint64 end = SDL_GetPerformanceCounter();
        float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

        // Cap to 60 FPS
        //SDL_Delay(floor(16.666f - elapsedMS));
        float delayTime = 16.666f - elapsedMS;
        if (delayTime > 0) {
            SDL_Delay(delayTime);
        }
    }

    // Clean up and exit
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
    return 0;
}