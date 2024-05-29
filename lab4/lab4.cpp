#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <regex>
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#endif

namespace fs = std::filesystem;
using namespace std;

void print_help() {
    cout << "Usage: count_subdirs [options] <directory>\n";
    cout << "Options:\n";
    cout << "  -h, --help              Show this help message\n";
    cout << "  -p, --pattern <pattern> Count files matching the pattern (e.g., *.exe)\n";
    cout << "  -a, --attributes        Include hidden, read-only, and archive attributes\n";
}

bool has_attributes(const fs::directory_entry& entry) {
#ifdef _WIN32
    DWORD attrs = GetFileAttributes(entry.path().c_str());
    if (attrs == INVALID_FILE_ATTRIBUTES) {
        return false;
    }
    return (attrs & FILE_ATTRIBUTE_HIDDEN) || (attrs & FILE_ATTRIBUTE_READONLY) || (attrs & FILE_ATTRIBUTE_ARCHIVE);
#else
    auto perms = entry.status().permissions();
    return (perms & fs::perms::owner_read) || (perms & fs::perms::owner_write) || (perms & fs::perms::owner_exec);
#endif
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_help();
        return EXIT_FAILURE;
    }

    string directory;
    string pattern = ".*";  
    bool include_attributes = false;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            print_help();
            return EXIT_SUCCESS;
        }
        else if (arg == "-p" || arg == "--pattern") {
            if (i + 1 < argc) {
                pattern = argv[++i];
            }
            else {
                cerr << "Error: Missing argument for --pattern option\n";
                return EXIT_FAILURE;
            }
        }
        else if (arg == "-a" || arg == "--attributes") {
            include_attributes = true;
        }
        else {
            directory = arg;
        }
    }

    if (directory.empty()) {
        cerr << "Error: No directory specified\n";
        return EXIT_FAILURE;
    }

    try {
        if (!fs::exists(directory) || !fs::is_directory(directory)) {
            cerr << "Error: Directory does not exist or is not a directory\n";
            return EXIT_FAILURE;
        }

        regex file_pattern(pattern);
        size_t subdir_count = 0;
        size_t matching_file_count = 0;

        for (const auto& entry : fs::recursive_directory_iterator(directory)) {
            if (entry.is_directory()) {
                subdir_count++;
            }
            else if (entry.is_regular_file() && regex_match(entry.path().filename().string(), file_pattern)) {
                if (include_attributes || has_attributes(entry)) {
                    matching_file_count++;
                }
            }
        }

        cout << "Number of subdirectories " << subdir_count << endl;
        cout << "Number of matching files " << matching_file_count << endl;
    }
    catch (const fs::filesystem_error& e) {
        cerr << "Filesystem error " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    catch (const exception& e) {
        cerr << "Error " << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
