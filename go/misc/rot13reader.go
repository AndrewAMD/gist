package main

import (
	"io"
	"os"
	"strings"
)

type rot13Reader struct {
	r io.Reader
}

func rot13(bIn byte) byte {
	switch {
	case (bIn >= 'A') && (bIn <= 'M'):
		return bIn + 13
	case (bIn >= 'N') && (bIn <= 'Z'):
		return bIn - 13
	case (bIn >= 'a') && (bIn <= 'm'):
		return bIn + 13
	case (bIn >= 'n') && (bIn <= 'z'):
		return bIn - 13
	default:
		return bIn
	}

}

func (r13 *rot13Reader) Read(b []byte) (n int, err error) {
	n1, err1 := r13.r.Read(b)
	for i := 0; i < n1; i++ {
		b[i] = rot13(b[i])
	}
	return n1, err1
}

func main() {
	s := strings.NewReader("Lbh penpxrq gur pbqr!")
	r := rot13Reader{s}
	io.Copy(os.Stdout, &r)
}
