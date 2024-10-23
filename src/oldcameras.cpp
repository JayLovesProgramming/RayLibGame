// TODO: Implement these when the game is at a good playing stage
// void (*cameraUpdaters[])(Camera2D *, Player *, EnvItem *, int, float, int, int) = {
//     UpdateCameraCenterInsideMap,
//     // UpdateCameraEvenOutOnLanding,
//     // UpdateCameraCenter,
//     // UpdateCameraCenterSmoothFollow,
//     // UpdateCameraPlayerBoundsPush
// };

// void UpdateCameraCenter(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float deltaTime, int width, int height)
// {
//     std::cout << "UpdateCameraCenter" << std::endl;
//     camera->offset = Vector2{ width/2.0f, height/2.0f };
//     camera->target = player->position;
// }

// void UpdateCameraCenterSmoothFollow(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float deltaTime, int width, int height)
// {
//     std::cout << "UpdateCameraCenterSmoothFollow" << std::endl;
//     static float minSpeed = 30;
//     static float minEffectLength = 10;
//     static float fractionSpeed = 0.8f;
//     camera->offset = Vector2{ width/2.0f, height/2.0f };
//     Vector2 diff = Vector2Subtract(player->position, camera->target);
//     float length = Vector2Length(diff);
//     if (length > minEffectLength)
//     {
//         float speed = fmaxf(fractionSpeed*length, minSpeed);
//         camera->target = Vector2Add(camera->target, Vector2Scale(diff, speed*deltaTime/length));
//     }
// }

// void UpdateCameraEvenOutOnLanding(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float deltaTime, int width, int height)
// {
//     std::cout << "UpdateCameraEvenOutOnLanding" << std::endl;
//     static float evenOutSpeed = 700;
//     static int eveningOut = false;
//     static float evenOutTarget;
//     camera->offset = Vector2{ width/2.0f, height/2.0f };
//     camera->target.x = player->position.x;
//     if (eveningOut)
//     {
//         if (evenOutTarget > camera->target.y)
//         {
//             camera->target.y += evenOutSpeed*deltaTime;
//             if (camera->target.y > evenOutTarget)
//             {
//                 camera->target.y = evenOutTarget;
//                 eveningOut = 0;
//             }
//         }
//         else
//         {
//             camera->target.y -= evenOutSpeed*deltaTime;
//             if (camera->target.y < evenOutTarget)
//             {
//                 camera->target.y = evenOutTarget;
//                 eveningOut = 0;
//             }
//         }
//     }
//     else
//     {
//         if (player->canJump && (player->speed == 0) && (player->position.y != camera->target.y))
//         {
//             eveningOut = 1;
//             evenOutTarget = player->position.y;
//         }
//     }
// }

// void UpdateCameraPlayerBoundsPush(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float deltaTime, int width, int height)
// {
//     std::cout << "UpdateCameraPlayerBoundsPush" << std::endl;
//     static Vector2 bbox = { 0.2f, 0.2f };
//     Vector2 bboxWorldMin = GetScreenToWorld2D(Vector2{ (1 - bbox.x) * 0.5f * width, (1 - bbox.y) * 0.5f * height }, *camera);
//     Vector2 bboxWorldMax = GetScreenToWorld2D(Vector2{ (1 + bbox.x) * 0.5f * width, (1 + bbox.y) * 0.5f * height }, *camera);
//     if (player->position.x < bboxWorldMin.x) camera->target.x = player->position.x;
//     if (player->position.y < bboxWorldMin.y) camera->target.y = player->position.y;
//     if (player->position.x > bboxWorldMax.x) camera->target.x = player->position.x;
//     if (player->position.y > bboxWorldMax.y) camera->target.y = player->position.y;
//     camera->offset = Vector2{ width * 0.2f, height * 0.2f };
// }
