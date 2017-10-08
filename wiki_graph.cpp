#include "wiki_graph.hpp"

WikiGraph::~WikiGraph(){
    if (nlinks > 0){
        delete[] titles;
        delete[] sizes;
        delete[] links;
        delete[] redirect;
        delete[] offset;
    }
}

void  WikiGraph::load_from_stream(std::istream &file)
{

    int32_t n;
     n = nlinks = 0; //FIXIT: прочитать из файла
        
    titles = new std::string [n];
    sizes = new int32_t [n];
    links = new int32_t [nlinks];
    redirect = new int32_t [n];
    offset = new int32_t [n+1];
     //FIXIT прочитать граф из файла
     std::cout << utf16_to_utf8(L"Граф загружен") << std::endl;
}

int32_t  WikiGraph::get_number_of_links_from(int32_t id)
{
    //FIXIT
    return 0;
};

int32_t*  WikiGraph::get_links_from(int32_t id)
{
    //FIXIT
    return links;
};

int32_t  WikiGraph::get_id(std::string title)
{
    //FIXIT
    return 0;
};

int32_t  WikiGraph::get_number_of_pages()
{
    //FIXIT
    return 0;
};

bool  WikiGraph::is_redirect(int32_t id)
{
    //FIXIT
    return true;
};

std::string  WikiGraph::get_title(int32_t id)
{
    //FIXIT
    return "";
};

int32_t  WikiGraph::get_page_size(int32_t id)
{
    //FIXIT
    return 0;
};
