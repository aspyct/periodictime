#pragma once

enum element_group {
    unknown = 0,
    alkali_metals,
    alkaline_earth_metals,
    transition_metals,
    other_metals,
    other_non_metals,
    halogens,
    inert_gases,
    lanthanides,
    actinides,
    trans_actinides
};

struct element {
    char *code;
    char *name;
    char *number;
    char *mass;
    enum element_group element_group;
};
