#include <iostream>
#include <fstream>
#include <string>
#include "utf8.hpp"


class WikiGraph {
    private:
        std::string * titles;
        int32_t *sizes, *links, *offset, n_links, n_pages;
        bool * redirect;

    public:
        WikiGraph () {
            n_links = 0;
            n_pages = 0;
            links = nullptr;
            offset = nullptr;
            sizes = nullptr;
            redirect = nullptr;
            titles = nullptr;
        }
        ~WikiGraph();

        void load_from_stream(std::istream&);
        int32_t get_number_of_links_from(int32_t);
        int32_t* get_links_from(int32_t);
        int32_t get_id(std::string);
        int32_t get_number_of_pages();
        bool is_redirect(int32_t);
        std::string get_title(int32_t);
        int32_t get_page_size(int32_t);
};
