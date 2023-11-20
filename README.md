# WASM_C_DEMO

## simple flow

```mermaid
flowchart LR

CODE(CODE) --> FILE(.wasm) --> TARGET(WASM RUNTIME)
```

## emscripten

https://github.com/emscripten-core/emscripten

LLVM-to-JS compiler.

```bash
# gen wasm, js
emcc lib/demo.c -s WASM=1 -o public/demo.js

# gen html, wasm, js
emcc lib/demo.c -s WASM=1 -o public/demo.html

# only generate .wasm
emcc lib/demo.c -s WASM=1 -o public/demo.wasm

# optimize level 2 compile. (-O2)
emcc lib/demo.c -s WASM=1 -O2 -o public/demo.js

# --post-js, --pre-js
emcc lib/demo.c -s WASM=1 --post-js public/post.js --pre-js public/pre.js -o public/demo.js

# EXPORTED_FUNCTIONS
emcc lib/demo.c -s WASM=1 -s EXPORTED_FUNCTIONS="['_getNum', '_main']"  --post-js public/post.js --pre-js public/pre.js -o public/demo.js

emcc lib/demo.c -s WASM=1 -s EXPORTED_FUNCTIONS="['_getNum', '_main', '_getDoubleNum', '_greet']" -s EXPORTED_RUNTIME_METHODS='["cwrap", "ccall"]' --post-js public/post.js --pre-js public/pre.js -o public/demo.js
```

### preamble.js

https://emscripten.org/docs/api_reference/preamble.js.html

C 코드와의 연결을 위한 js 헬퍼 함수들. emcc로 컴파일 시 자동으로 추가된다. (버전 따라 동작이 좀 다른 듯)

ccall, cwrap이 대표적이며, 그 외의 다양한 helper 함수들이 존재한다.

```bash

ccall(ident, returnType, argTypes, args, opts)

ccall('getNum')
ccall('greet', 'string')
ccall('getDoubleNum', 'number', ['number'], [12])
ccall('greet', 'string', ['string'], ['darren'])

```

### emscripten.h

https://emscripten.org/docs/api_reference/emscripten.h.html

## etc

browser WASM API 를 통해서 js 함수를 wasm에서 가져다 사용하는 방법이 있지만, emcc에서는 해당 방식이 WASM의 본 의도와 맞지 않다고 생각. (emscripten.h를 통해서 사용하는 것이 더 좋다고 여기는 듯)
