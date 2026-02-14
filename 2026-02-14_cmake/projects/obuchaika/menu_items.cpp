#include "menu_items.hpp"

#include <cstddef>

#include "menu_functions.hpp"

const biv::MenuItem biv::STUDY_SUMM = {
    "1 - Хочу научиться складывать!", biv::study_summ, &biv::STUDY
};
const biv::MenuItem biv::STUDY_SUBSTRACT = {
    "2 - Хочу научиться вычитать!", biv::study_substract, &biv::STUDY
};
const biv::MenuItem biv::STUDY_MULTIPLY = {
    "3 - Хочу научиться умножать!", biv::study_multiply, &biv::STUDY
};
const biv::MenuItem biv::STUDY_DIVIDE = {
    "4 - Хочу научиться делить!", biv::study_divide, &biv::STUDY
};
const biv::MenuItem biv::STUDY_GO_BACK = {
    "0 - Выйти в главное меню", biv::study_go_back, &biv::STUDY
};

namespace {
    const biv::MenuItem* const study_children[] = {
        &biv::STUDY_GO_BACK,
        &biv::STUDY_SUMM,
        &biv::STUDY_SUBSTRACT,
        &biv::STUDY_MULTIPLY,
        &biv::STUDY_DIVIDE
    };
    const int study_size = sizeof(study_children) / sizeof(study_children[0]);
}

const biv::MenuItem biv::STUDY = {
    "1 - Хочу учиться математике!", biv::show_menu, &biv::MAIN, study_children, study_size
};
const biv::MenuItem biv::EXIT = {
    "0 - Я лучше пойду полежу...", biv::exit, &biv::MAIN
};

namespace {
    const biv::MenuItem* const main_children[] = {
        &biv::EXIT,
        &biv::STUDY
    };
    const int main_size = sizeof(main_children) / sizeof(main_children[0]);
}

const biv::MenuItem biv::MAIN = {
    nullptr, biv::show_menu, nullptr, main_children, main_size
};
