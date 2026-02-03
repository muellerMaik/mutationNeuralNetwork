#ifndef ENUM_H
#define ENUM_H
enum activation {
    LINEAR = 0,
    RELU = 1,
    SIGMOID = 2,
    TANH = 3
};

enum kind {
    INPUT = 0,
    HIDDEN = 1,
    OUTPUT = 2
};

enum connectionSetting {
    ALLRANDOM = 0,
    LEFTRANDOM = 1,
    RIGHTRANDOM = 2,
    NONERANDOM = 3
};
#endif
