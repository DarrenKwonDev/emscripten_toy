#include <emscripten.h>
#include <stdio.h>
#include <string.h>

// emcc lib/demo.c -s WASM=1 -o public/demo.js

EM_JS(void, jsFunctionTest, (int n), {
    console.log("called by EM_JS");
})

// wasm에선 main도 일반 함수처럼 취급됨.
// 그러나 emcc로 컴파일되면 일반 C의 작동을 mimic 하기에 자동으로 main 함수가 트리거 됨.
// 단, 컴파일에서 EXPORTED_FUNCTIONS 옵션을 활용하면 main도 수동 export 해야 함.
int main(void) {

    // buffer flush를 위해 \n를 잊지 말자.
    printf("WASM READY\n");

    // write js and called in browser.
    emscripten_run_script("console.log('called by eval in browser')");

    emscripten_async_run_script("alert('yup')", 2000);

    int jsVal = emscripten_run_script_int("getAnyNum()");
    printf("get js value : %d\n", jsVal);

    jsFunctionTest(155);

    return 0;
}

int getNum() {
    return 42;
}
int getDoubleNum(int n) {
    return n * 2;
}

char greeting[50];

char* greet(char* name) {
    if (strlen(name) > 30) {
        return "Name too long";
    }
    strcpy(greeting, "Hello ");
    return strcat(greeting, name);
}
