//
// Created by Alex on 8/14/2023.
//

#ifndef RUEIEGAME_TEXTURELIST_H
#define RUEIEGAME_TEXTURELIST_H

#define TEXTURE_ATTACK_PORTAL   1
#define TEXTURE_BORDER          2
#define TEXTURE_BUILD_MODE      3
std::map<uint32_t, std::string> TextureList{
        {TEXTURE_ATTACK_PORTAL, "Resources/Textures/attack_portals.png"},
        {TEXTURE_BORDER, "Resources/Textures/borders.png"},
        {TEXTURE_BUILD_MODE, "Resources/Textures/build_mode.png"},
};


#endif //RUEIEGAME_TEXTURELIST_H
