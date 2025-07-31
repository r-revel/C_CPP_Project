#include <emscripten.h>

extern "C" {  // Отключает C++ name mangling
    EMSCRIPTEN_KEEPALIVE  // Гарантирует, что функция не будет удалена
    int add(int a, int b) {
        return a + b;
    }
}

int main() {
    return 0;
}