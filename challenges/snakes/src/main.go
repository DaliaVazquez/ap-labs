package main

import (
	"fmt"
	_ "image/png"
	"log"
	"os"
	"snake/files"
	"strconv"

	"github.com/hajimehoshi/ebiten"
)

var game files.Game
var ene int
var mouses int

func init() {
	var err error
	var err2 error
	if len(os.Args) != 3 {
		fmt.Println("Error; incorrect number of arguments")
		os.Exit(3)
	}
	ene, err2 = strconv.Atoi(os.Args[2])
	mouses, err = strconv.Atoi(os.Args[1])
	if err != nil || err2 != nil {
		fmt.Println("Error; should be numeric values")
		os.Exit(3)
	}
	game = files.NewGame(mouses, ene)
}

type Game struct {
}

func (g *Game) Update(screen *ebiten.Image) error {
	if err := game.Update(); err != nil {
		return err
	} else {
		return nil
	}
}
func (g *Game) Layout(outsideWidth, outsideHeight int) (screenWidth, screenHeight int) {
	return 700, 700
}

func (g *Game) Draw(screen *ebiten.Image) {
	/*draw := &ebiten.DrawImageOptions{}
	draw.GeoM.Translate(0, 0)
	background, _, _ := ebitenutil.NewImageFromFile("assets/grass.png", ebiten.FilterLinear)
	screen.DrawImage(background, draw)*/
	if err := game.Draw(screen); err != nil {
		fmt.Println(err)
	}
}
func main() {
	ebiten.SetWindowSize(700, 700)
	ebiten.SetWindowTitle("Snakes")
	if err := ebiten.RunGame(&Game{}); err != nil {
		log.Fatal(err)
	}
}
