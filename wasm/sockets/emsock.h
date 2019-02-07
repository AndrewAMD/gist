#include <emscripten.h>

/*
This header creates these usable functions for use in C:

void websocket_connect(const char* host, int hostlen, int buffer_length); // 
void websocket_send(const void* msg, int msglen);

These C functions must be supplied by users of this header.

extern "C"{
    void on_open();
    void on_message(const void* msg, int msglen);
    void on_error(int readystate);
    void on_close(int code, int wasClean, const char* reason);
}

Example build command:

emcc --std=c++17 input.cpp -Os -s WASM=1 -o ./bin/output.html -s "EXPORTED_FUNCTIONS=['_main','_on_open','_on_message','_on_error','_on_close']"

*/

EM_JS(void, websocket_connect, (const char* host, int hostlen, int buffer_length), {
    var buffer_length_default = 262144; // for when no buffer length is supplied
    if(!window.socket_initialized){
        if(window.socket_uninitialize)
            window.socket_uninitialize(); // avoid leaks
        window.socket_initialized = true;
        if(buffer_length>0)
            window.socket_buffer_length = buffer_length;
        else
            window.socket_buffer_length = buffer_length_default;
        window.socket_buffer = Module._malloc(window.socket_buffer_length); // never free, this is a fixed buffer.
    }
    window.socket_uninitialize = function(){
         if(!window.socket_initialized) 
            return; // avoid double-calling free
         window.socket_initialized = false;
         Module._free(window.socket_buffer);
    };
    
    var jhost = Pointer_stringify(host, hostlen);
    window.socket = new WebSocket(jhost);
    window.socket.binaryType = 'arraybuffer'; // 'blob' or 'arraybuffer'

        // Connection opened
    window.socket.addEventListener('open', function (event) {
        _on_open();
    });
    
    // Listen for messages
    window.socket.addEventListener('message', function (event) {
        var jview = new Uint8Array(event.data);
        var jlen = jview.length; // received message length

        var i = 0;
        for(i=0; i<jlen; ){
            var clen = Math.min(jlen, window.socket_buffer_length);
            var cview = new Uint8Array(Module.HEAPU8.buffer, window.socket_buffer + i, clen);
            var j = 0;
            for(j=0; j<clen; j++){
                cview[j] = jview[j];
            }
            _on_message(window.socket_buffer + i, clen);
            i += clen;
        }
    });

    // Connection opened
    window.socket.addEventListener('error', function (event) {
        _on_error(event.readystate);
    });

    // Connection opened
    window.socket.addEventListener('close', function (event) {
        var jmsg = event.reason;
        var jview = new Uint8Array(jmsg);
        var cview = new Uint8Array(Module.HEAPU8.buffer, window.socket_buffer, jview.length+1);
        var i = 0;
        for(i=0; i<(jview.length+1); i++){
            cview[i] = jview[i];
        }
        _on_close(event.code, event.wasClean, window.socket_buffer);
        window.socket_uninitialize(); // avoid leaks
    });
});

EM_JS(void, websocket_send, (const void* msg, int msglen), {
    var cview = new Uint8Array(Module.HEAPU8.buffer, msg, msglen);
    var jbuffer = new ArrayBuffer(msglen);
    var jview = new Uint8Array(jbuffer);
    var i = 0;
    for(i=0; i<msglen; i++){
        jview[i] = cview[i];
    }
    window.socket.send(jbuffer);
});
