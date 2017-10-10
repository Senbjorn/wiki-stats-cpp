#include <iostream>
#include <fstream>
#include "wiki_graph.hpp"
#include <cmath>

int32_t * bfs(WikiGraph &wg, int32_t source, int32_t target);
int32_t n_redir(WikiGraph &wg);
int32_t min_links_from(WikiGraph &wg);
int32_t n_pages_min_links_from(WikiGraph &wg);
int32_t max_links_from(WikiGraph &wg);
int32_t n_pages_max_links_from(WikiGraph &wg);
int32_t max_links_fp(WikiGraph &wg);
double average_links_from(WikiGraph &wg);
double average_links_diff(WikiGraph &wg);
int32_t min_links_to(WikiGraph &wg);
int32_t n_pages_min_links_to(WikiGraph &wg);
int32_t max_links_to(WikiGraph &wg);
int32_t n_pages_max_links_to(WikiGraph &wg);
int32_t max_links_tp(WikiGraph &wg);
double average_links_to(WikiGraph &wg);
int32_t min_redir(WikiGraph &wg);
int32_t n_pages_min_redir(WikiGraph &wg);
int32_t max_redir(WikiGraph &wg);
int32_t n_pages_max_redir(WikiGraph &wg);
int32_t max_redir_p(WikiGraph &wg);
double average_redir(WikiGraph &wg);
int32_t * get_reversed_links(WikiGraph &wg);
int32_t * get_reversed_redir(WikiGraph &wg);

int main(int argc, char* argv[]){
    if (argc != 2){
        std::cout << utf16_to_utf8(L"Использование: ./wiki <файл с графом статей>") << std::endl;
        return -1;
    }
    auto wg = WikiGraph();
    std::ifstream file(argv[1]);
    if (file){
        std::cout << utf16_to_utf8(L"Загружаю граф из файла: ") << argv[1] << std::endl;;
        wg.load_from_stream(file);
		file.close();
    }
    else
    {
        std::cout << utf16_to_utf8(L"Файл с графом не найден") << std::endl;;
        return -1;
    }
    std::cout << utf16_to_utf8(L"") << std::endl;
    std::cout << utf16_to_utf8(L"Начинаю поиск в ширину") << std::endl;
//    int32_t s = wg.get_id(utf16_to_utf8(L"Python"));
//    int32_t t = wg.get_id(utf16_to_utf8(L"Список_файловых_систем"));
    int32_t *path = bfs(wg, wg.get_id("Python"), wg.get_id(utf16_to_utf8(L"Список_файловых_систем")));
    std::cout << utf16_to_utf8(L"Поиск закончен. ");
    if (path[0] != 0) {
        std::cout << utf16_to_utf8(L"Путь найден:") << std::endl;
        for (int i = 1; i <= path[0]; i ++) {
            std::cout << wg.get_title(path[i]) << std::endl;
        }
    } else {
        std::cout << utf16_to_utf8(L"Путь не найден.") << std::endl;
    }
    delete[] path;
    std::cout << utf16_to_utf8(L"Количество статей с перенаправлением: ") << n_redir(wg) << " (" << ((double) n_redir(wg))/wg.get_number_of_pages() << "%)" << std::endl;
    std::cout << utf16_to_utf8(L"Минимальное количество ссылок из статьи: ") << min_links_from(wg) << std::endl;
    std::cout << utf16_to_utf8(L"Количество статей с минимальным количеством ссылок: ") << n_pages_min_links_from(wg) << std::endl;
    std::cout << utf16_to_utf8(L"Максимальное количество ссылок из статьи: ") << max_links_from(wg) << std::endl;
    std::cout << utf16_to_utf8(L"Количество статей с максимальным количеством ссылок: ") << n_pages_max_links_from(wg) << std::endl;
    std::cout << utf16_to_utf8(L"Статья с наибольшим количеством ссылок: ") << wg.get_title(max_links_fp(wg)) << std::endl;
    std::cout << utf16_to_utf8(L"Среднее количество ссылок в статье: ") << average_links_from(wg) << utf16_to_utf8(L" (ср. откл. ") << average_links_diff(wg) << ")" << std::endl;
    std::cout << utf16_to_utf8(L"Минимальное количество ссылок на статью: ") << min_links_to(wg) << std::endl;
    std::cout << utf16_to_utf8(L"Количество статей с минимальным количеством внешних ссылок: ") << n_pages_min_links_to(wg) << std::endl;
    std::cout << utf16_to_utf8(L"Максимальное количество ссылок на статью: ") << max_links_to(wg) << std::endl;
    std::cout << utf16_to_utf8(L"Количество статей с максимальным количеством внешних ссылок: ") << n_pages_max_links_to(wg) << std::endl;
    std::cout << utf16_to_utf8(L"Статья с наибольшим количеством внешних ссылок: ") << wg.get_title(max_links_tp(wg)) << std::endl;
    std::cout << utf16_to_utf8(L"Среднее количество внешних ссылок на статью: ") << average_links_to(wg) << std::endl;
    std::cout << utf16_to_utf8(L"Минимальное количество перенаправлений на статью: ") << min_redir(wg) << std::endl;
    std::cout << utf16_to_utf8(L"Количество статей с минимальным количеством внешних перенаправлений: ") << n_pages_min_redir(wg) << std::endl;
    std::cout << utf16_to_utf8(L"Максимальное количество перенаправлений на статью: ") << max_redir(wg) << std::endl;
    std::cout << utf16_to_utf8(L"Количество статей с максимальным количеством внешних перенаправлений: ") << n_pages_max_redir(wg) << std::endl;
    std::cout << utf16_to_utf8(L"Статья с наибольшим количеством внешних перенаправлений: ") << wg.get_title(max_redir_p(wg)) << std::endl;
    std::cout << utf16_to_utf8(L"Среднее количество внешних перенаправлений на статью: ") << average_redir(wg) << std::endl;
}


int32_t * bfs(WikiGraph &wg, int32_t source, int32_t target) {
    int32_t n = wg.get_number_of_pages();
    auto path = new int32_t[n + 1];
    if (source < 0 or source >= n or target < 0 or target >= n) {
        path[0] = -1;
        return path;
    }
    auto path_lengths = new int32_t[n];
    auto predecessors = new int32_t[n];
    auto queue = new int32_t[n];
    int32_t index = 0;
    int32_t qlen = 1;
    for (int i = 0; i < n; i ++) {
        path_lengths[i] = -1;
    }
    queue[0] = source;
    path_lengths[source] = 0;
    predecessors[source] = -1;
    while (qlen > index) {
        int32_t u = queue[index++];
        int32_t *links = wg.get_links_from(u);
        int32_t v;
        for (int i = 0; i < wg.get_number_of_links_from(u); i ++) {
            v = links[i];
            if (path_lengths[v] == -1 or path_lengths[v] > path_lengths[u] + 1) {
                path_lengths[v] = path_lengths[u] + 1;
                predecessors[v] = u;
                queue[qlen++] = v;
            }
        }
        delete[] links;
    }
    path[0] = path_lengths[target] + 1;
    int32_t v = target;
    for (int i = path[0]; i > 0; i--) {
        path[i] = v;
        v = predecessors[v];
    }
    delete[] path_lengths, queue, predecessors;
    return path;
}

int32_t n_redir(WikiGraph &wg) {
    int32_t nr = 0;
    for (int i = 0; i < wg.get_number_of_pages(); i++) {
        if (wg.is_redirect(i)) {
            nr++;
        }
    }
    return nr;
}

int32_t min_links_from(WikiGraph &wg) {
    int32_t mlf = wg.get_number_of_links_from(0);
    for (int i = 0; i < wg.get_number_of_pages(); i++) {
        if (wg.get_number_of_links_from(i) < mlf) {
            mlf = wg.get_number_of_links_from(i);
        }
    }
    return mlf;
}

int32_t n_pages_min_links_from(WikiGraph &wg) {
    int32_t mlf = min_links_from(wg);
    int32_t npmlf = 0;
    for (int i = 0; i < wg.get_number_of_pages(); i++) {
        if (wg.get_number_of_links_from(i) == mlf) {
            npmlf++;
        }
    }
    return npmlf;
}

int32_t max_links_from(WikiGraph &wg) {
    int32_t mlf = wg.get_number_of_links_from(0);
    for (int i = 0; i < wg.get_number_of_pages(); i++) {
        if (wg.get_number_of_links_from(i) > mlf) {
            mlf = wg.get_number_of_links_from(i);
        }
    }
    return mlf;
}

int32_t n_pages_max_links_from(WikiGraph &wg) {
    int32_t mlf = max_links_from(wg);
    int32_t npmlf = 0;
    for (int i = 0; i < wg.get_number_of_pages(); i++) {
        if (wg.get_number_of_links_from(i) == mlf) {
            npmlf++;
        }
    }
    return npmlf;
}

int32_t max_links_fp(WikiGraph &wg) {
    int32_t mlf = max_links_from(wg);
    for (int i = 0; i < wg.get_number_of_pages(); i++) {
        if (wg.get_number_of_links_from(i) == mlf) {
            return i;
        }
    }
    return -1;
}

double average_links_from(WikiGraph &wg) {
    double alf = 0;
    double total = 0;
    for (int i = 0; i < wg.get_number_of_pages(); i++) {
        if (not wg.is_redirect(i)) {
            total++;
            alf += wg.get_number_of_links_from(i);
        }
    }
    return alf/total;
}

double average_links_diff(WikiGraph &wg) {
    double alf = average_links_from(wg);
    double ald = 0;
    double total = 0;
    double x;
    for (int i = 0; i < wg.get_number_of_pages(); i++) {
        if (not wg.is_redirect(i)) {
            total++;
            x = wg.get_number_of_links_from(i) - alf;
            ald += x * x;
        }
    }
    return sqrt(ald/(total - 1));
}

int32_t min_links_to(WikiGraph &wg) {
    int32_t *nlt = get_reversed_links(wg);
    int32_t mlt;
    mlt = nlt[0];
    for (int i = 0; i < wg.get_number_of_pages(); i++) {
        if (nlt[i] < mlt) {
            mlt = nlt[i];
        }
    }
    delete[] nlt;
    return mlt;
}

int32_t n_pages_min_links_to(WikiGraph &wg) {
    int32_t mlt = min_links_to(wg);
    int32_t npmlt = 0;
    int32_t *nlt = get_reversed_links(wg);
    for (int i = 0; i < wg.get_number_of_pages(); i++) {
        if (nlt[i] == mlt) {
            npmlt++;
        }
    }
    delete[] nlt;
    return npmlt;
}

int32_t max_links_to(WikiGraph &wg) {
    int32_t *nlt = get_reversed_links(wg);
    int32_t mlt;
    mlt = nlt[0];
    for (int i = 0; i < wg.get_number_of_pages(); i++) {
        if (nlt[i] > mlt) {
            mlt = nlt[i];
        }
    }
    delete[] nlt;
    return mlt;
}

int32_t n_pages_max_links_to(WikiGraph &wg) {
    int32_t mlt = max_links_to(wg);
    int32_t npmlt = 0;
    int32_t *nlt = get_reversed_links(wg);
    for (int i = 0; i < wg.get_number_of_pages(); i++) {
        if (nlt[i] == mlt) {
            if (not wg.is_redirect(i)) npmlt++;
        }
    }
    delete[] nlt;
    return npmlt;
}

int32_t max_links_tp(WikiGraph &wg) {
    int32_t mlt = max_links_to(wg);
    int32_t *nlt = get_reversed_links(wg);
    for (int i = 0; i < wg.get_number_of_pages(); i++) {
        if (nlt[i] == mlt) {
            delete[] nlt;
            return i;
        }
    }
    delete[] nlt;
    return -1;
}

double average_links_to(WikiGraph &wg) {
    double alt = 0;
    for (int i = 0; i < wg.get_number_of_pages(); i++) {
        int32_t *llinks = wg.get_links_from(i);
        if (wg.is_redirect(i)) {
            delete[] llinks;
            continue;
        }
        for (int j = 0; j < wg.get_number_of_links_from(i); j++) {
            alt++;
        }
        delete[] llinks;
    }
    return alt / wg.get_number_of_pages();
}

int32_t min_redir(WikiGraph &wg) {
    int32_t *rlt = get_reversed_redir(wg);
    int32_t mr;
    mr = rlt[0];
    for (int i = 0; i < wg.get_number_of_pages(); i++) {
        if (rlt[i] < mr) {
            mr = rlt[i];
        }
    }
    delete[] rlt;
    return mr;
}

int32_t n_pages_min_redir(WikiGraph &wg) {
    int32_t *rlt = get_reversed_redir(wg);
    int32_t mr = min_redir(wg);
    int32_t nmr = 0;
    for (int i = 0; i < wg.get_number_of_pages(); i++) {
        if (rlt[i] == mr) {
            nmr++;
        }
    }
    delete[] rlt;
    return nmr;
}

int32_t max_redir(WikiGraph &wg) {
    int32_t *rlt = get_reversed_redir(wg);
    int32_t mr;
    mr = rlt[0];
    for (int i = 0; i < wg.get_number_of_pages(); i++) {
        if (rlt[i] > mr) {
            mr = rlt[i];
        }
    }
    delete[] rlt;
    return mr;
}

int32_t n_pages_max_redir(WikiGraph &wg) {
    int32_t *rlt = get_reversed_redir(wg);
    int32_t mr = max_redir(wg);
    int32_t nmr = 0;
    for (int i = 0; i < wg.get_number_of_pages(); i++) {
        if (rlt[i] == mr) {
            nmr++;
        }
    }
    delete[] rlt;
    return nmr;
}

int32_t max_redir_p(WikiGraph &wg) {
    int32_t *rlt = get_reversed_redir(wg);
    int32_t mr = max_redir(wg);
    for (int i = 0; i < wg.get_number_of_pages(); i++) {
        if (rlt[i] == mr) {
            delete[] rlt;
            return i;
        }
    }
    delete[] rlt;
    return -1;
}

double average_redir(WikiGraph &wg) {
    double r = 0;
    for (int i = 0; i < wg.get_number_of_pages(); i++) {
        if (wg.is_redirect(i)) r++;
    }
    return r / wg.get_number_of_pages();
}

int32_t * get_reversed_links(WikiGraph &wg) {
    auto nlt = new int32_t[wg.get_number_of_pages()];
    for (int i = 0; i < wg.get_number_of_pages(); i++) {
        nlt[i] = 0;
    }
    for (int i = 0; i < wg.get_number_of_pages(); i++) {
        if (wg.is_redirect(i)) continue;
        int32_t *llinks = wg.get_links_from(i);
        for (int j = 0; j < wg.get_number_of_links_from(i); j++) {
            nlt[llinks[j]]++;
        }
        delete[] llinks;
    }
    return nlt;
}

int32_t * get_reversed_redir(WikiGraph &wg) {
    auto rlt = new int32_t[wg.get_number_of_pages()];
    for (int i = 0; i < wg.get_number_of_pages(); i++) {
        rlt[i] = 0;
    }
    for (int i = 0; i < wg.get_number_of_pages(); i++) {
        if (not wg.is_redirect(i)) continue;
        int32_t *llinks = wg.get_links_from(i);
        rlt[llinks[0]]++;
        delete[] llinks;
    }
    return rlt;
}