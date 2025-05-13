#include <exception>
#include <filesystem>
#include <iostream>

#include <mpg123xx/mpg123.hpp>


using std::cout;
using std::endl;
using std::cerr;


void
show_id3_tag(const std::filesystem::path& filename)
{
    try {
        cout << "Reading ID3 tag from " << filename << endl;
        mpg123::handle h;
        h.open(filename);
        auto format = h.get_format();
        cout << "Format: " << format << endl;
        unsigned meta = h.meta_check();
        if (meta & MPG123_ID3) {
            auto id3 = h.get_id3();
            if (id3.v1) {
                auto& tag = *id3.v1;
                cout << "[ID3v1]\n";
                cout << "Title: \"" << tag.title << "\"\n";
                cout << "Artist: \"" << tag.artist << "\"\n";
                cout << "Album: \"" << tag.album << "\"\n";
                cout << "Year: \"" << tag.year << "\"\n";
                cout << "Comment: " << tag.comment << "\"\n";
                if (tag.track)
                    cout << "Track: " << unsigned(tag.track) << '\n';
                cout << "Genre: " << unsigned(tag.genre) << endl;
            }
            if (id3.v2) {
                auto& tag = *id3.v2;
                cout << "[ID3v2]\n";
                cout << "Version: " << unsigned(tag.version) << '\n';
                cout << "Title: \"" << tag.title << "\"\n";
                cout << "Artist: \"" << tag.artist << "\"\n";
                cout << "Album: \"" << tag.album << "\"\n";
                cout << "Year: \"" << tag.year << "\"\n";
                cout << "Genre: \"" << tag.genre << "\"\n";

                // TODO: show the list fields
            }
        } else {
            cout << "No ID3 tags found" << endl;
        }
        h.close();
    }
    catch (std::exception& e) {
        cout << "Failed: " << e.what() << endl;
    }
}


int main(int argc, char* argv[])
{
    try {
        for (int i = 1; i < argc; ++i)
            show_id3_tag(argv[i]);
    }
    catch (std::exception& e) {
        cerr << "Error: " << e.what() << endl;
        return -1;
    }
}
