'#include "../main.h"
#include "network.h"
#include <string.h>
#include <stdlib.h>

#define MAX_REMOTE_PLAYERS 32
static PlayerData remotePlayerList[MAX_REMOTE_PLAYERS];
static uint8_t remotePlayerCount = 0;

// Synchronize local player position to a specific peer
void syncPlayerPosition(ENetPeer* peer, PlayerData* player) {
    if (!peer || !player) return;
    
    uint32_t packetSize = 0;
    uint8_t* serialized = serializePlayerData(player, &packetSize);
    
    if (serialized) {
        ENetPacket* packet = enet_packet_create(NULL, packetSize + 1, ENET_PACKET_FLAG_RELIABLE);
        if (packet) {
            packet->data[0] = PACKET_PLAYER_MOVE;
            memcpy(&packet->data[1], serialized, packetSize);
            enet_peer_send(peer, 0, packet);
        }
        free(serialized);
    }
}

// Broadcast player sync to all connected peers
void broadcastPlayerSync(ENetHost* server, uint32_t playerId, PlayerData* player) {
    if (!server || !player) return;
    
    uint32_t packetSize = 0;
    uint8_t* serialized = serializePlayerData(player, &packetSize);
    
    if (serialized) {
        ENetPacket* packet = enet_packet_create(NULL, packetSize + 1, ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
        if (packet) {
            packet->data[0] = PACKET_PLAYER_SYNC;
            memcpy(&packet->data[1], serialized, packetSize);
            enet_host_broadcast(server, 0, packet);
        }
        free(serialized);
    }
}

// Update remote player data in local list
void updateRemotePlayer(uint32_t playerId, PlayerData* data) {
    if (!data) return;
    
    // Find existing player or add new one
    for (uint8_t i = 0; i < remotePlayerCount; i++) {
        if (remotePlayerList[i].playerId == playerId) {
            memcpy(&remotePlayerList[i], data, sizeof(PlayerData));
            return;
        }
    }
    
    // Add new player if not found and space available
    if (remotePlayerCount < MAX_REMOTE_PLAYERS) {
        memcpy(&remotePlayerList[remotePlayerCount], data, sizeof(PlayerData));
        remotePlayerCount++;
    }
}

// Synchronize all players every frame
void synchronizeAllPlayers(ENetHost* server) {
    if (!server) return;
    
    // This would be called from your game loop to sync all active players
    for (uint32_t i = 0; i < server->peerCount; i++) {
        if (server->peers[i].state == ENET_PEER_STATE_CONNECTED) {
            PlayerData* player = (PlayerData*)server->peers[i].data;
            if (player) {
                broadcastPlayerSync(server, player->playerId, player);
            }
        }
    }
}

// Get remote player by ID
PlayerData* getRemotePlayer(uint32_t playerId) {
    for (uint8_t i = 0; i < remotePlayerCount; i++) {
        if (remotePlayerList[i].playerId == playerId) {
            return &remotePlayerList[i];
        }
    }
    return NULL;
}

// Get all remote players
PlayerData* getAllRemotePlayers(uint8_t* outCount) {
    if (outCount) *outCount = remotePlayerCount;
    return remotePlayerList;
}

// Clear remote player list
void clearRemotePlayerList() {
    remotePlayerCount = 0;
    memset(remotePlayerList, 0, sizeof(remotePlayerList));
}''