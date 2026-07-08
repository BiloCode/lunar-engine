#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include <map>
#include <string>
#include <iostream>
#include <filesystem>

class FontManager
{
public:
    FontManager();
    ~FontManager();
    FontManager(const FontManager&) = delete;
    FontManager& operator=(const FontManager&) = delete;
    const TTF_Font* get(const std::string& key);

private:
    std::map<std::string, TTF_Font*> font_files;
    std::map<std::string, std::filesystem::path> font_paths;
};