package main

import (
	"image"
	"image/color"

	"golang.org/x/tour/pic"
)

type Image struct{}

func imageFunction(x, y int) uint8 {
	return uint8(float64(x+y) / 2.0)
}

func (i Image) At(x, y int) color.Color {
	c1, c2 := imageFunction(x, y), uint8(255)
	return color.RGBA{c1, c1, c2, c2}
}

func (i Image) Bounds() image.Rectangle {
	return image.Rect(0, 0, 256, 256)
}

func (i Image) ColorModel() color.Model {
	return color.RGBAModel
}

func main() {
	m := Image{}
	pic.ShowImage(m)
}
