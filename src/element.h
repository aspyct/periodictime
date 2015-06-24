#pragma once

enum element_state {
    solid = 0,
    liquid,
    gas,
    unknown
};
    
struct element {
    char *code;
    char *name;
    char *number;
    char *mass;
    int radioactive;
    enum element_state natural_state;
};
    