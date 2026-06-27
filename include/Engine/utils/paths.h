#pragma once

#include <filesystem>

namespace Engine::Paths
{
   std::filesystem::path get_executable_dir();
   std::filesystem::path get_executable_path();
}
