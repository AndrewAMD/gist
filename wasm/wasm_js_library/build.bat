call C:\Users\normal\source\repos\emsdk\emsdk_env.bat
call emcc hellojs.cpp -s WASM=1 -o hellojs.html --js-library print_numbers.js
call pause