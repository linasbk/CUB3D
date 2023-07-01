#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

#define IMAGE_WIDTH 800
#define IMAGE_HEIGHT 600
#define PLAYER_SIZE 20

int playerX = 400; // X-coordinate of the player's position
int playerY = 300; // Y-coordinate of the player's position

void draw_player(void *mlx, void *win, int x, int y)
{
    int i, j;

    for (i = x; i < x + PLAYER_SIZE; i++)
    {
        for (j = y; j < y + PLAYER_SIZE; j++)
        {
            mlx_pixel_put(mlx, win, i, j, 0xFFFFFF); // Draw player as white pixels
        }
    }
}

int main()
{
    void *mlx;
    void *win;
    void *img;
    int bits_per_pixel;
    int size_line;
    int endian;

    mlx = mlx_init();
    win = mlx_new_window(mlx, IMAGE_WIDTH, IMAGE_HEIGHT, "Player Image");
    img = mlx_new_image(mlx, IMAGE_WIDTH, IMAGE_HEIGHT);

    // Get the address of the image buffer
    char *image_buffer = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);

    // Clear the image buffer to black
    for (int i = 0; i < IMAGE_WIDTH * IMAGE_HEIGHT * 4; i += 4)
    {
        image_buffer[i] = 0;     // Blue component
        image_buffer[i + 1] = 0; // Green component
        image_buffer[i + 2] = 0; // Red component
        image_buffer[i + 3] = 0; // Alpha component
    }

    draw_player(mlx, win, playerX, playerY); // Draw the player on the image

    // Display the image in the window
    mlx_put_image_to_window(mlx, win, img, 0, 0);

    mlx_loop(mlx);

    return 0;
}