#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "quickcg.h"
using namespace QuickCG;

/*
g++ *.cpp -lSDL -O3 -W -Wall -ansi -pedantic
g++ *.cpp -lSDL
*/

//place the example code below here:

#define mapWidth 24
#define mapHeight 24

int map[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int main(int /*argc*/, char * /*argv*/[])
{
  double pos_x = 22, pos_y = 12;  //x and y start position
  double dir_x = -1, dir_y = 0; //initial direction vector
  double plane_x = 0, plane_y = 0.66; //the 2d raycaster version of camera plane
  double time = 0; //time of current frame
  double oldTime = 0; //time of previous frame

  while(!done())
  {
    for(int x = 0; x < w; x++)
    {
      //calculate ray position and direction
      double cam_x = 2 * x / double(w) - 1; //x-coordinate in camera space
      double ray_dir_x = dir_x + plane_x * cam_x;
      double ray_dir_y = dir_y + plane_y * cam_x;
      //which box of the map we're in
      int map_x = int(pos_x);
      int map_y = int(pos_y);

      //length of ray from current position to next x or y-side
      double side_d_x;
      double side_d_y;

       //length of ray from one x or y-side to next x or y-side
      double dx = std::abs(1 / ray_dir_x);
      double dy = std::abs(1 / ray_dir_y);
      double wall_dist;

      //what direction to step in x or y-direction (either +1 or -1)
      int step_x;
      int step_y;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist
      if (ray_dir_x < 0)
      {
        step_x = -1;
        side_d_x = (pos_x - map_x) * dx;
      }
      else
      {
        step_x = 1;
        side_d_x = (map_x + 1.0 - pos_x) * dx;
      }
      if (ray_dir_y < 0)
      {
        step_y = -1;
        side_d_y = (pos_y - map_y) * dy;
      }
      else
      {
        step_y = 1;
        side_d_y = (map_y + 1.0 - pos_y) * dy;
      }
      //perform DDA
      while (hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
        if (side_d_x < side_d_y)
        {
          side_d_x += dx;
          map_x += step_x;
          side = 0;
        }
        else
        {
          side_d_y += dy;
          map_y += step_y;
          side = 1;
        }
        //Check if ray has hit a wall
        if (map[map_x][map_y] > 0) hit = 1;
      }
      //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
      if (side == 0) wall_dist = (map_x - pos_x + (1 - step_x) / 2) / ray_dir_x;
      else           wall_dist = (map_y - pos_y + (1 - step_y) / 2) / ray_dir_y;

      //Calculate height of line to draw on screen
      int line_h = (int)(h / wall_dist);

      //calculate lowest and highest pixel to fill in current stripe
      int draw_a = -line_h / 2 + h / 2;
      if(draw_a < 0)draw_a = 0;
      int draw_b = line_h / 2 + h / 2;
      if(draw_b >= h)draw_b = h - 1;

      //choose wall color
      ColorRGB color;
      switch(map[map_x][map_y])
      {
        case 1:  color = RGB_Red;  break; //red
        case 2:  color = RGB_Green;  break; //green
        case 3:  color = RGB_Blue;   break; //blue
        case 4:  color = RGB_White;  break; //white
        default: color = RGB_Yellow; break; //yellow
      }

      //give x and y sides different brightness
      if (side == 1) {color = color / 2;}

      //draw the pixels of the stripe as a vertical line
      verLine(x, draw_a, draw_b, color);
    }




    //timing for input and FPS counter
    oldTime = time;
    time = getTicks();
    double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
    print(1.0 / frameTime); //FPS counter
    redraw();
    cls();

    //speed modifiers
    double speed = frameTime * 5.0; //the constant value is in squares/second
    double rot = frameTime * 3.0; //the constant value is in radians/second
    readKeys();
    //move forward if no wall in front of you
    if (keyDown(SDLK_UP))
    {
      if(map[int(pos_x + dir_x * speed)][int(pos_y)] == false) pos_x += dir_x * speed;
      if(map[int(pos_x)][int(pos_y + dir_y * speed)] == false) pos_y += dir_y * speed;
    }
    //move backwards if no wall behind you
    if (keyDown(SDLK_DOWN))
    {
      if(map[int(pos_x - dir_x * speed)][int(pos_y)] == false) pos_x -= dir_x * speed;
      if(map[int(pos_x)][int(pos_y - dir_y * speed)] == false) pos_y -= dir_y * speed;
    }
    //rotate to the right
    if (keyDown(SDLK_RIGHT))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = dir_x;
      dir_x = dir_x * cos(-rot) - dir_y * sin(-rot);
      dir_y = oldDirX * sin(-rot) + dir_y * cos(-rot);
      double oldPlaneX = plane_x;
      plane_x = plane_x * cos(-rot) - plane_y * sin(-rot);
      plane_y = oldPlaneX * sin(-rot) + plane_y * cos(-rot);
    }
    //rotate to the left
    if (keyDown(SDLK_LEFT))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = dir_x;
      dir_x = dir_x * cos(rot) - dir_y * sin(rot);
      dir_y = oldDirX * sin(rot) + dir_y * cos(rot);
      double oldPlaneX = plane_x;
      plane_x = plane_x * cos(rot) - plane_y * sin(rot);
      plane_y = oldPlaneX * sin(rot) + plane_y * cos(rot);
    }
  }
}

