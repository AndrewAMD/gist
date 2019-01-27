#include<iostream>
#include <emscripten.h>

// extern "C" {
//     extern void print_numbers(float a, float b, float c);
// }

EM_JS(float, print_numbers, (float a, float b, float c), {
  console.log(a);
  console.log(b);
  console.log(c);
  return a + b + c;
});

EM_JS(void, say, (const char* word, int wordlen), {
  let jword = Pointer_stringify(word, wordlen);
  console.log(jword);
});

extern "C"{
  void c_say_hello(){
      printf("i am saying hello\n");
  }
  void c_say_jstring(const char* word){
      printf("%s\n",word);
  }
  float counter(){
    static float ctr = 0;
    ctr += 1.0;
    return ctr;
  }
}

EM_JS(void, js_make_c_say_hello, (), {
    _c_say_hello();
});

EM_JS(void, js_make_c_say_jstring, (), {
    let jstring = "Hello from javascript, but saying from C!!";
    let buf = _malloc(jstring.length + 1);
    Module.stringToUTF8(jstring, buf, jstring.length+1); // make room for null pointer, else this function will shorten your string!!
    _c_say_jstring(buf);
    _free(buf);
});

EM_JS(void, js_make_c_say_jstring2, (char* output), {
    let jstring = "Hello again from javascript, but saying from C!!";
    Module.stringToUTF8(jstring, output, jstring.length+1); // make room for null pointer, else this function will shorten your string!!
});

EM_JS(void, jscount, (),{
  let i = 0;
  for(i=0; i<10; i++){
    console.log(_counter());
  }
});


void the_buffer_is_in_c(){
    char msg[256];
    memset(msg,0,256);
    js_make_c_say_jstring2(msg);
    printf("%s\n",msg);
}


int main(){
    float sum = print_numbers(500, 30, 1);
    
    printf("sum: %0.2f\n", sum);
    const char* word = "This is the complete word.";
    say(word, strlen(word));
    js_make_c_say_hello();
    js_make_c_say_jstring();
    the_buffer_is_in_c();
    jscount();

    return 0;
}
