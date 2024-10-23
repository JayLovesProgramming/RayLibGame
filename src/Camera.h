#pragma once
#include "raylib.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

// class Camera
// {
// public:
//     void UpdateCamera(Camera2D &camera, Player &player, EnvItem *envItems, int envItemsLength, float deltaTime, int width, int height)
//     {
//         camera.target = player.position;
//         camera.offset = Vector2{width / 2.0f, height / 2.0f};
//         float minX = 0, minY = 0, maxX = 0, maxY = 0;
//         for (int i = 0; i < envItemsLength; i++)
//         {
//             EnvItem *ei = &envItems[i];
//             if (ei->blocking)
//             {
//                 minX = fminf(ei->rect.x, minX);
//                 maxX = fmaxf(ei->rect.x + ei->rect.width, maxX);
//                 minY = fminf(ei->rect.y, minY);
//                 maxY = fmaxf(ei->rect.y + ei->rect.height, maxY);
//             }
//         }
//         // Clamp camera within the environment
//         if (camera.target.x < minX + width / 2)
//             camera.target.x = minX + width / 2;
//         if (camera.target.x > maxX - width / 2)
//             camera.target.x = maxX - width / 2;
//         if (camera.target.y < minY + height / 2)
//             camera.target.y = minY + height / 2;
//         if (camera.target.y > maxY - height / 2)
//             camera.target.y = maxY - height / 2;

//         camera.zoom += ((float)GetMouseWheelMove() * 0.05f);
//         // Use std::clamp instead here
//         if (camera.zoom >= 1.26f)
//             camera.zoom = 1.26f;
//         else if (camera.zoom < 0.54f)
//             camera.zoom = 0.54f;
//     };
// };


void UpdateCamera(Camera2D &camera, Player &player, EnvItem *envItems, int envItemsLength, float deltaTime, int width, int height);
