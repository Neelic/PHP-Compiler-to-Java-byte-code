#include <cstdio>

extern int lexer_main(FILE* file);

int main(int argc, char *argv[]) {
    FILE *file = nullptr;
    if (argc > 1) {
        file = fopen(argv[1], "r");
    }

    if (file == nullptr) {
        printf("File opening error");
        return 1;
    }

    return lexer_main(file);
}