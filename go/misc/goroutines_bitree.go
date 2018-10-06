package main

import (
	"fmt"

	"golang.org/x/tour/tree"
)

func subwalk(t *tree.Tree, n *int, max *int, ch chan int) {
	if *n >= *max {
		return
	}
	ch <- t.Value
	*n++
	if t.Left != nil {
		subwalk(t.Left, n, max, ch)
	}
	if t.Right != nil {
		subwalk(t.Right, n, max, ch)
	}
}

// Walk walks the tree t sending all values
// from the tree to the channel ch.
func Walk(t *tree.Tree, ch chan int) {

	n, max := 0, 10
	subwalk(t, &n, &max, ch)
	close(ch)
	return
}

// Same determines whether the trees
// t1 and t2 contain the same values.
func Same(t1, t2 *tree.Tree) bool {
	ch1 := make(chan int, 10)
	ch2 := make(chan int, 10)
	go Walk(t1, ch1)
	go Walk(t2, ch2)
	m := make(map[int]bool, 10)

	n := 0
	for val := range ch1 {
		m[val] = true
		n++
	}
	for val := range ch2 {
		_, ok := m[val]
		if ok == false {
			return false
		}
	}

	return true
}

func main() {
	var ptr *int
	fmt.Println(ptr)

	ch1 := make(chan int, 10)
	go Walk(tree.New(1), ch1)
	for i := range ch1 {
		fmt.Println(i)
	}
	fmt.Printf("...\n")
	ch2 := make(chan int, 10)
	go Walk(tree.New(1), ch2)
	for i := range ch2 {
		fmt.Println(i)
	}
	fmt.Println(Same(tree.New(1), tree.New(1)))
	fmt.Println(Same(tree.New(1), tree.New(2)))
}
