#include "raylib.h"
#include <math.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 740
#define screenHeight 580


int worldMap[mapWidth][mapHeight]=
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


int main()
{
	InitWindow(screenWidth, screenHeight, "raycaster");

	double posX = 3.5, posY = 3.5; //X AND Y STARTING POSITION
	double dirX = 1.0, dirY = 0.0; //INITAL DIRECTION VECTOR
	double planeX = 0, planeY = 0.66; //2D RAYCASTER VERSION OF CAMERA PLANE


	while(!WindowShouldClose())
	{
    BeginDrawing();
    ClearBackground(BLACK);

    //----------------Handle Input---------------------
    double movSpeed = 0.02f;
    double rotSpeed = 0.01f;

    if(IsKeyDown(KEY_UP)) //forward if no wall is there
    {
        if(worldMap[(int)(posX + dirX * movSpeed)][(int)posY] == false) posX += dirX * movSpeed;
        if(worldMap[(int)posX][(int)(posY + dirY * movSpeed)] == false) posY += dirY * movSpeed;
    }

    if(IsKeyDown(KEY_DOWN))
    {
      if(worldMap[(int)(posX - dirX * movSpeed)][(int)posY] == false) posX -= dirX * movSpeed;
      if(worldMap[(int)posX][(int)(posY - dirY * movSpeed)] == false) posY -= dirY * movSpeed;
    }

    if(IsKeyDown(KEY_LEFT))
    {
        double oldDirX = dirX;
        dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
        dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
        
        double oldplaneX = planeX;
        planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
        planeY = oldplaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    }

    if(IsKeyDown(KEY_RIGHT))
    {
      double oldDirX = dirX;
      dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
      dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
      
      double oldplaneX = planeX;
      planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
      planeY = oldplaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    }
    

		
    for(int x = 0; x < screenWidth; x++)
		{
      double cameraX = 2* x /(double)screenWidth - 1;  //this is used to make x be in range [-1,0,1], it is a point on camera plane
      double rayDirX = dirX + planeX * cameraX; //direction of ray in x
      double rayDirY = dirY + planeY * cameraX; //direction of ray in y

      //which of the box in map we are in
      int mapX = (int)posX; 
      int mapY = (int)posY; 

      //lenght of the ray from current position to the next x or y line
      double SideDistX;
      double SideDistY;

      //lenght of the ray from currrent x position to the next x or y line
      double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
      double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
      double perWallDist; //will be used to calculate lenght of the ray

      //what direction to step in x or y direction
      int stepX;
      int stepY;

      int hit = 0; //will be used to see if wall is hit
      int side; //used to check if a x-side or y-side of a wall was hit. if x-side then side = 0, if y-side then side = 1 
		
      
      //-----------calculating the step and initial sideDist-------------//
      if(rayDirX < 0) //ray is going left
      {
          stepX = -1;
          SideDistX = (posX - mapX) * deltaDistX; //here we get to the closest border of cell and multiply the deltaDistX to get it to next x-line.

      }

      else //ray is going right
      {
        stepX = 1;
        SideDistX = (mapX + 1.0 - posX) * deltaDistX;

      }

      if(rayDirY < 0) //ray is going up
      {
          stepY = -1;
          SideDistY = (posY - mapY) * deltaDistY;
      }

      else //ray is going down
      {
        stepY = 1;
        SideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }

      //--------Perform DDA --------//
      while(hit == 0)
      {
        if(SideDistX < SideDistY)
        {
          SideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }

        else
        {
          SideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }

        if(worldMap[mapX][mapY] > 0) hit = 1;

      }

      //--------calculate-distance------------//
      if(side == 0) perWallDist = (SideDistX - deltaDistX);
      else perWallDist = (SideDistY - deltaDistY);


      //height of vertical strip of wall
      int lineHeight = (int) (screenHeight/perWallDist);

      //lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + screenHeight / 2;
      if(drawStart < 0 ) drawStart = 0;
      int drawEnd = lineHeight / 2 + screenHeight / 2;
      if(drawEnd >= screenHeight) drawEnd =screenHeight - 1;

      //--------chose wall Color----------------
      Color color;
      switch ( worldMap[mapX][mapY])
      {
        case 1: color = RED; break;
        case 2: color = GREEN; break;
        case 3: color = BLUE; break;
        case 4: color = WHITE; break;
        default: color = YELLOW; break;
      }

      //give x and y side different brightness
      if (side == 1)
      {
        color.a /= 2;
        color.b /= 2;
        color.g /= 2;
        color.r /= 2;
      }

      DrawLine(x, drawStart, x, drawEnd, color); //draw wall (start from drawstar till drawend in column x)
      DrawLine(x, drawEnd, x, screenHeight, DARKGRAY); //sraw floor (start from drawEnd(end of wall) till screen end

    }
    DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 20, WHITE);


    EndDrawing();
	}

  CloseWindow();
  return 0;

}