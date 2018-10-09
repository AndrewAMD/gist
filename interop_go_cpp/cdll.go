package main

/*
typedef struct sDemo{
    int age;
    double height;
} sDemo;
*/
import "C"

import (
	"fmt"
	"unsafe"
)

//export HelloWorld
func HelloWorld() {
	fmt.Println("hello world")
}

func getCIntPtr(pCInt *C.int, pos int) *C.int {
	var sample C.int
	return (*C.int)(unsafe.Pointer((uintptr(unsafe.Pointer(pCInt))) +
		(uintptr(pos) * uintptr(unsafe.Sizeof(sample)))))
}

//export GetTens
func GetTens(tens *C.int, size C.int) {
	for i := 0; i < int(size); i++ {
		ptr := getCIntPtr(tens, i)
		*ptr = (C.int)(i * 10)
	}
}

func getBytePtr(pCChar *C.char, pos int) *byte {
	var sample C.char

	return (*byte)(unsafe.Pointer((uintptr(unsafe.Pointer(pCChar))) +
		(uintptr(pos) * uintptr(unsafe.Sizeof(sample)))))
}

//export OutputString
func OutputString(str *C.char, size C.int) {
	msg := []byte("hello, there!")

	for i, val := range msg {
		ptr := getBytePtr(str, i)
		if i > int(size) {
			return
		} else if i == int(size) {
			*ptr = 0
			return
		} else {
			*ptr = val
		}

	}
}

func getDemoPtr(pCChar *C.sDemo, pos int) *C.sDemo {
	var sample C.sDemo

	return (*C.sDemo)(unsafe.Pointer((uintptr(unsafe.Pointer(pCChar))) +
		(uintptr(pos) * uintptr(unsafe.Sizeof(sample)))))
}

//export Structy
func Structy(pStr *C.sDemo) {
	p := getDemoPtr(pStr, 0)
	p.age = C.int(34)
	p.height = C.double(70.5)

	p = getDemoPtr(pStr, 1)
	p.age = C.int(35)
	p.height = C.double(71.5)

	p = getDemoPtr(pStr, 2)
	p.age = C.int(36)
	p.height = C.double(72.5)

}

func main() {

}
