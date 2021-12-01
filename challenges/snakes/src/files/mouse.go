package files

import (
	"math/rand"
	"time"

	"github.com/hajimehoshi/ebiten"
	"github.com/hajimehoshi/ebiten/ebitenutil"
)

type Mouse struct {
	game  *Game
	mouse ebiten.Image
	eat   bool
	xW    int
	yW    int
	x     float64
	y     float64
}

func (m *Mouse) Update(dotTime int) error {
	if m.eat == false {
		return nil
	}
	return nil
}
func CreateMouse(g *Game) *Mouse {
	m := Mouse{
		game: g,
		eat:  false,
		xW:   30,
		yW:   30,
	}
	mouse, _, _ := ebitenutil.NewImageFromFile("assets/mouse.png", ebiten.FilterDefault)
	m.mouse = *mouse
	s := rand.NewSource(time.Now().UnixNano())
	random := rand.New(s)
	m.x = float64(random.Intn(m.xW) * 20)
	m.y = float64(random.Intn(m.yW) * 20)
	return &m
}

func (m *Mouse) Draw(screen *ebiten.Image, dotTime int) error {
	drawImage = &ebiten.DrawImageOptions{}
	drawImage.GeoM.Translate(m.x, m.y)
	screen.DrawImage(&m.mouse, drawImage)
	return nil
}
