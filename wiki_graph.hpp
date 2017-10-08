#include <iostream>
#include <fstream>
#include <string>
#include "utf8.hpp"


class WikiGraph {
    private:
        std::string * titles;
        int32_t *sizes, *links, *redirect, *offset, nlinks;

    public:
        WikiGraph () {nlinks = 0;};
        ~WikiGraph();

        void load_from_stream(istream&);
        int32_t get_number_of_links_from(int32_t);
        int32_t* get_links_from(int32_t);
        int32_t get_id(std::string);
        int32_t get_number_of_pages();
        bool is_redirect(int32_t);
        std::string get_title(int32_t);
        int32_t get_page_size(int32_t);
};
