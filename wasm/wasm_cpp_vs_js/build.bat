call C:\Users\normal\source\repos\emsdk\emsdk_env.bat
call emcc hellojs.cpp -s WASM=1 -o hellojs.html -s "EXPORTED_FUNCTIONS=['_main','_c_say_hello','_c_say_jstring','_counter','_malloc','_free','_strcpy','_memcpy']" -s "EXTRA_EXPORTED_RUNTIME_METHODS=['cwrap','ccall','stringToUTF8']"
call pause