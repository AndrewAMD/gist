package main

/*
#include <string.h>
typedef struct sDemo{
    int age;
    double height;
} sDemo;
typedef void(__cdecl * pTask)(void);
static void dotask(pTask task){
	task();
}
*/
import "C"

import (
	"fmt"
	"time"
	"unsafe"
)

//export HelloWorld
func HelloWorld() {
	fmt.Println("hello world")
}

//export GetTens
func GetTens(tens *C.int, size C.int) {
	for i := 0; i < int(size); i++ {
		ptr := getCIntPtr(tens, i)
		*ptr = (C.int)(i * 10)
	}
}

//export OutputString
func OutputString(str *C.char, size C.int) {
	msg := "hello, there!!!"
	strcpy(str, msg)
}

func strcpy(pDest *C.char, Src string) {
	C.strcpy(pDest, (*C.char)(unsafe.Pointer(&([]byte(Src)[0]))))
}
func memcpy(pDest unsafe.Pointer, pSrc unsafe.Pointer, numSize uintptr) {
	C.memcpy(pDest, pSrc, (C.size_t)(numSize))
}

func getCIntPtr(pInput *C.int, pos int) *C.int {
	var sample C.int
	return (*C.int)(getPtr(unsafe.Pointer(pInput), pos, unsafe.Sizeof(sample)))
}

func getBytePtr(pInput *C.char, pos int) *byte {
	var sample C.char
	return (*byte)(getPtr(unsafe.Pointer(pInput), pos, unsafe.Sizeof(sample)))
}
func getDemoPtr(pInput *C.sDemo, pos int) *C.sDemo {
	var sample C.sDemo
	return (*C.sDemo)(getPtr(unsafe.Pointer(pInput), pos, unsafe.Sizeof(sample)))
}

func getPtr(pInput unsafe.Pointer, pos int, elementSize uintptr) unsafe.Pointer {

	return unsafe.Pointer(uintptr(pInput) + (uintptr(pos) * elementSize))
}

//export Structy
func Structy(pStr *C.sDemo) {
	var a [2]C.sDemo
	a[0].age = C.int(34)
	a[0].height = C.double(70.5)
	a[1].age = C.int(35)
	a[1].height = C.double(71.5)
	p := getDemoPtr(pStr, 0)
	var sample C.sDemo
	memcpy(unsafe.Pointer(p), unsafe.Pointer(&a),
		uintptr(2*unsafe.Sizeof(sample)))

	p = getDemoPtr(pStr, 2)
	p.age = C.int(36)
	p.height = C.double(200.1)
}

func countOutLoud() {
	for i := 0; i <= 10; i++ {
		fmt.Println(i)
		duration := time.Second
		time.Sleep(duration)
	}
}

//export DoGoroutine
func DoGoroutine() {
	go countOutLoud()
}

//export GiveMeTask
func GiveMeTask(task unsafe.Pointer) {
	fmt.Println("doing task...")
	C.dotask((C.pTask)(task))
	fmt.Println("task completed...")
}

func main() {

}
