package files

import (
	"image/color"
	"strconv"

	"github.com/hajimehoshi/ebiten"
	"github.com/hajimehoshi/ebiten/text"
	"golang.org/x/image/font/basicfont"
)

// Hud for the game
type Hud struct {
	game      *Game
	points    int
	maxPoints int
	eMouses   int
	maxScore  int
}

// CreateHud : Constructor
func CreateHud(g *Game, max int) *Hud {
	h := Hud{
		game:      g,
		points:    0,
		maxPoints: max,
		maxScore:  0,
	}

	return &h
}

func (h *Hud) addPoint() {
	h.points++
}

func textDimension(text string) (w int, h int) {
	return 7 * len(text), 13
}

// EndGame shows the final result
func (h *Hud) EndGame(screen *ebiten.Image) { //method that checks the end of the game and the display

	if h.eMouses != h.maxPoints {
		goText := "GAME OVER"
		textW, textH := textDimension(goText)
		screenW := screen.Bounds().Dx()
		screenH := screen.Bounds().Dy()

		text.Draw(screen, goText, basicfont.Face7x13, screenW/2-textW/2, screenH/2+textH/2, color.White)
	} else if h.points == h.maxScore {
		goText := "YOU WIN!!"
		textW, textH := textDimension(goText)
		screenW := screen.Bounds().Dx()
		screenH := screen.Bounds().Dy()

		text.Draw(screen, goText, basicfont.Face7x13, screenW/2-textW/2, screenH/2+textH/2, color.White)
	} else {
		goText := "GAME OVER"
		textW, textH := textDimension(goText)
		screenW := screen.Bounds().Dx()
		screenH := screen.Bounds().Dy()

		text.Draw(screen, goText, basicfont.Face7x13, screenW/2-textW/2, screenH/2+textH/2, color.White)
	}
}

// Draw the hud
func (h *Hud) Draw(screen *ebiten.Image) error {
	text.Draw(screen, "Score: "+strconv.Itoa(h.points), basicfont.Face7x13, 20, 20, color.White)
	if !h.game.play {
		eMouses := 0
		max := 0
		for i := 0; i < len(h.game.enemies); i++ { //update the scorde hud
			eMouses += h.game.enemies[i].points
			if max < h.game.enemies[i].points {
				max = h.game.enemies[i].points
			}
		}

		eMouses += h.game.snake.points
		if max < h.game.snake.points {
			max = h.game.snake.points
		}
		h.maxScore = max
		h.eMouses = eMouses
		h.EndGame(screen)
	}

	return nil
}

func (h *Hud) End2(screen *ebiten.Image) {

	eMouses := 0
	max := 0
	for i := 0; i < len(h.game.enemies); i++ {
		eMouses += h.game.enemies[i].points
		if max < h.game.enemies[i].points {
			max = h.game.enemies[i].points
		}
	}

	eMouses += h.game.snake.points
	if max < h.game.snake.points {
		max = h.game.snake.points
	}
	h.maxScore = max
	h.eMouses = eMouses
	h.EndGame(screen)
}
