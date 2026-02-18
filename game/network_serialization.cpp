#include "../main.h"
#include "network.h"
#include <string.h>
#include <stdlib.h>

// Serialize PlayerData to binary format
uint8_t* serializePlayerData(PlayerData* player, uint32_t* outSize) {
    if (!player || !outSize) return NULL;
    
    uint32_t size = sizeof(uint32_t) + sizeof(float) * 6 + sizeof(uint8_t) * 2 + sizeof(uint32_t);
    uint8_t* buffer = (uint8_t*)malloc(size);
    
    if (!buffer) return NULL;
    
    uint32_t offset = 0;
    
    // Serialize playerId
    memcpy(&buffer[offset], &player->playerId, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    
    // Serialize position
    memcpy(&buffer[offset], &player->posX, sizeof(float));
    offset += sizeof(float);
    memcpy(&buffer[offset], &player->posY, sizeof(float));
    offset += sizeof(float);
    memcpy(&buffer[offset], &player->posZ, sizeof(float));
    offset += sizeof(float);
    
    // Serialize rotation
    memcpy(&buffer[offset], &player->rotX, sizeof(float));
    offset += sizeof(float);
    memcpy(&buffer[offset], &player->rotY, sizeof(float));
    offset += sizeof(float);
    memcpy(&buffer[offset], &player->rotZ, sizeof(float));
    offset += sizeof(float);
    
    // Serialize health, armor, weapon
    memcpy(&buffer[offset], &player->health, sizeof(uint8_t));
    offset += sizeof(uint8_t);
    memcpy(&buffer[offset], &player->armor, sizeof(uint8_t));
    offset += sizeof(uint8_t);
    memcpy(&buffer[offset], &player->weapon, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    
    *outSize = size;
    return buffer;
}

// Deserialize PlayerData from binary format
PlayerData* deserializePlayerData(uint8_t* buffer, uint32_t size) {
    if (!buffer || size < sizeof(uint32_t)) return NULL;
    
    PlayerData* player = (PlayerData*)malloc(sizeof(PlayerData));
    if (!player) return NULL;
    
    uint32_t offset = 0;
    
    memcpy(&player->playerId, &buffer[offset], sizeof(uint32_t));
    offset += sizeof(uint32_t);
    
    memcpy(&player->posX, &buffer[offset], sizeof(float));
    offset += sizeof(float);
    memcpy(&player->posY, &buffer[offset], sizeof(float));
    offset += sizeof(float);
    memcpy(&player->posZ, &buffer[offset], sizeof(float));
    offset += sizeof(float);
    
    memcpy(&player->rotX, &buffer[offset], sizeof(float));
    offset += sizeof(float);
    memcpy(&player->rotY, &buffer[offset], sizeof(float));
    offset += sizeof(float);
    memcpy(&player->rotZ, &buffer[offset], sizeof(float));
    offset += sizeof(float);
    
    memcpy(&player->health, &buffer[offset], sizeof(uint8_t));
    offset += sizeof(uint8_t);
    memcpy(&player->armor, &buffer[offset], sizeof(uint8_t));
    offset += sizeof(uint8_t);
    memcpy(&player->weapon, &buffer[offset], sizeof(uint32_t));
    
    return player;
}

// Serialize ChatMessage
uint8_t* serializeChatMessage(ChatMessage* msg, uint32_t* outSize) {
    if (!msg || !outSize) return NULL;
    
    uint32_t size = sizeof(uint32_t) + 128;
    uint8_t* buffer = (uint8_t*)malloc(size);
    
    if (!buffer) return NULL;
    
    memcpy(&buffer[0], &msg->playerId, sizeof(uint32_t));
    memcpy(&buffer[sizeof(uint32_t)], msg->message, 128);
    
    *outSize = size;
    return buffer;
}

// Deserialize ChatMessage
ChatMessage* deserializeChatMessage(uint8_t* buffer, uint32_t size) {
    if (!buffer || size < sizeof(uint32_t) + 128) return NULL;
    
    ChatMessage* msg = (ChatMessage*)malloc(sizeof(ChatMessage));
    if (!msg) return NULL;
    
    memcpy(&msg->playerId, &buffer[0], sizeof(uint32_t));
    memcpy(msg->message, &buffer[sizeof(uint32_t)], 128);
    
    return msg;
}

// Serialize PlayerAction
uint8_t* serializePlayerAction(PlayerAction* action, uint32_t* outSize) {
    if (!action || !outSize) return NULL;
    
    uint32_t size = sizeof(uint32_t) + sizeof(uint8_t) + sizeof(float) * 3;
    uint8_t* buffer = (uint8_t*)malloc(size);
    
    if (!buffer) return NULL;
    
    uint32_t offset = 0;
    
    memcpy(&buffer[offset], &action->playerId, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    memcpy(&buffer[offset], &action->actionType, sizeof(uint8_t));
    offset += sizeof(uint8_t);
    memcpy(&buffer[offset], &action->param1, sizeof(float));
    offset += sizeof(float);
    memcpy(&buffer[offset], &action->param2, sizeof(float));
    offset += sizeof(float);
    memcpy(&buffer[offset], &action->param3, sizeof(float));
    
    *outSize = size;
    return buffer;
}

// Deserialize PlayerAction
PlayerAction* deserializePlayerAction(uint8_t* buffer, uint32_t size) {
    if (!buffer || size < sizeof(uint32_t) + sizeof(uint8_t) + sizeof(float) * 3) return NULL;
    
    PlayerAction* action = (PlayerAction*)malloc(sizeof(PlayerAction));
    if (!action) return NULL;
    
    uint32_t offset = 0;
    
    memcpy(&action->playerId, &buffer[offset], sizeof(uint32_t));
    offset += sizeof(uint32_t);
    memcpy(&action->actionType, &buffer[offset], sizeof(uint8_t));
    offset += sizeof(uint8_t);
    memcpy(&action->param1, &buffer[offset], sizeof(float));
    offset += sizeof(float);
    memcpy(&action->param2, &buffer[offset], sizeof(float));
    offset += sizeof(float);
    memcpy(&action->param3, &buffer[offset], sizeof(float));
    
    return action;
}