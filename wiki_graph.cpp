#include "wiki_graph.hpp"

WikiGraph::~WikiGraph(){
    if (n_links > 0){
        delete[] titles;
        delete[] sizes;
        delete[] links;
        delete[] redirect;
        delete[] offset;
    }
}

void  WikiGraph::load_from_stream(std::istream &file)
{
    file >> n_pages >> n_links;
    titles = new std::string [n_pages];
    sizes = new int32_t [n_pages];
    links = new int32_t [n_links];
    redirect = (bool *) new int32_t [n_pages];
    offset = new int32_t [n_pages + 1];

    for (int i = 0; i < n_pages; i ++) {
        int nlinks;
        file >> titles[i] >> sizes[i] >> redirect[i] >> nlinks;
        offset[i + 1] += offset[i] + nlinks;
        for (int j = offset[i]; j < offset[i + 1]; j ++) {
            file >> links[j];
        }
    }

    std::cout << utf16_to_utf8(L"Граф загружен") << std::endl;
}

int32_t  WikiGraph::get_number_of_links_from(int32_t id)
{
    return offset[id + 1] - offset[id];
};

int32_t*  WikiGraph::get_links_from(int32_t id)
{
    auto links_from = new int32_t[get_number_of_links_from(id)];
    for (int i = offset[id]; i < offset[id + 1]; i ++) {
        links_from[i - offset[id]] = links[i];
    }
    return links_from;
};

int32_t  WikiGraph::get_id(std::string title)
{
    for (int i = 0; i < n_pages; i ++) {
        if (titles[i] == title) {
            return i;
        }
    }
    return -1;
};

int32_t  WikiGraph::get_number_of_pages()
{
    return n_pages;
};

bool  WikiGraph::is_redirect(int32_t id)
{
    return redirect[id];
};

std::string  WikiGraph::get_title(int32_t id)
{
    return titles[id];
};

int32_t  WikiGraph::get_page_size(int32_t id)
{
    return sizes[id];
};
