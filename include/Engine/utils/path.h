#pragma once

#include <filesystem>

namespace Engine::Path
{
   std::filesystem::path get_executable_dir();
   std::filesystem::path get_executable_path();
}
