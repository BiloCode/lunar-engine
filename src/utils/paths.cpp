#include <Engine/utils/paths.h>
#include <string>
#include <iostream>
#include <filesystem>

#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#include <limits.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

std::filesystem::path Project::Paths::get_executable_path()
{
#if defined(_WIN32)
   wchar_t path[MAX_PATH];
   // Retrieves the path of the executable file for the current process
   GetModuleFileNameW(NULL, path, MAX_PATH);
   return std::filesystem::path(path);

#elif defined(__linux__)
   char path[PATH_MAX];
   // Reads the symbolic link pointing to the current executable
   ssize_t count = readlink("/proc/self/exe", path, PATH_MAX);
   if (count == -1) return "";
   return std::filesystem::path(std::string(path, count));

#elif defined(__APPLE__)
   char path[PATH_MAX];
   uint32_t size = sizeof(path);
   // Retrieves the path of the main executable
   if (_NSGetExecutablePath(path, &size) == 0) {
      // Resolve any relative path symbols like "." or ".."
      return std::filesystem::canonical(path);
   }
   return "";
#else
   return ""; // Unsupported platform
#endif
}

std::filesystem::path Project::Paths::get_executable_dir()
{
   return get_executable_path().parent_path();
}
