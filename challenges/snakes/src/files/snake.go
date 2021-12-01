package files

import (
	"github.com/hajimehoshi/ebiten"
	"github.com/hajimehoshi/ebiten/ebitenutil"
)

var drawImage *ebiten.DrawImageOptions

type Snake struct {
	game      *Game
	bodyParts int
	lastMov   string
	head      ebiten.Image
	tail      ebiten.Image
	body      [][]float64
	pointsW   int
	points    int
	move      chan int
}

func CreateSnake(g *Game) *Snake {
	s := Snake{
		game:      g,
		bodyParts: 0,
		lastMov:   "right",
		pointsW:   0,
	}
	s.move = make(chan int)
	s.body = append(s.body, []float64{300, 300})
	headimg, _, _ := ebitenutil.NewImageFromFile("assets/snakehead.png", ebiten.FilterDefault)
	tailimg, _, _ := ebitenutil.NewImageFromFile("assets/snaketail.png", ebiten.FilterDefault)
	s.head = *headimg
	s.tail = *tailimg
	return &s
}

func (s *Snake) Behavior() error {
	dotTime := <-s.move
	for {
		s.Update(dotTime)
		dotTime = <-s.move
	}
}

func (s *Snake) Update(dotTime int) error {
	if ebiten.IsKeyPressed(ebiten.KeyRight) && s.lastMov != "left" {
		s.lastMov = "right"
		return nil
	} else if ebiten.IsKeyPressed(ebiten.KeyDown) && s.lastMov != "up" {
		s.lastMov = "down"
		return nil
	} else if ebiten.IsKeyPressed(ebiten.KeyUp) && s.lastMov != "down" {
		s.lastMov = "up"
		return nil
	} else if ebiten.IsKeyPressed(ebiten.KeyLeft) && s.lastMov != "right" {
		s.lastMov = "left"
		return nil
	}

	if dotTime == 1 {
		x, y := s.getHeadPos()
		if x < 0 || x > 670 || y < 0 || y > 670 || s.collisionWithHimself() {
			s.game.End()
		}
	}
	return nil
}

func (s *Snake) Draw(screen *ebiten.Image, dotTime int) error {
	if s.game.play {
		s.UpdatePos(dotTime)
	}
	drawImage = &ebiten.DrawImageOptions{}

	x, y := s.getHeadPos()
	drawImage.GeoM.Translate(x, y)

	screen.DrawImage(&s.head, drawImage)

	for i := 0; i < s.bodyParts; i++ {
		DrawIma := &ebiten.DrawImageOptions{}
		x, y := s.getPartPos(i)
		DrawIma.GeoM.Translate(x, y)
		screen.DrawImage(&s.tail, DrawIma)
	}

	return nil
}

func (s *Snake) UpdatePos(dotTime int) {
	if dotTime == 1 {
		if s.pointsW > 0 {
			s.bodyParts++
			s.pointsW--
		}
		switch s.lastMov {
		case "up":
			s.translateHeadPos(0, -20)
		case "down":
			s.translateHeadPos(0, +20)
		case "right":
			s.translateHeadPos(20, 0)
		case "left":
			s.translateHeadPos(-20, 0)
		}

	}
}

func (s *Snake) addPoint() {
	s.points++
	s.pointsW++
}

func (s *Snake) getHeadPos() (float64, float64) {
	return s.body[0][0], s.body[0][1]
}

func (s *Snake) getPartPos(pos int) (float64, float64) {
	return s.body[pos+1][0], s.body[pos+1][1]
}

func (s *Snake) translateHeadPos(newXPos, newYPos float64) {
	newX := s.body[0][0] + newXPos
	newY := s.body[0][1] + newYPos
	s.updateBody(newX, newY)
}

func (s *Snake) updateBody(newX, newY float64) {
	s.body = append([][]float64{[]float64{newX, newY}}, s.body...)
	s.body = s.body[:s.bodyParts+1]
}

func (s *Snake) collisionWithHimself() bool {
	x, y := s.getHeadPos()
	for i := 1; i < len(s.body); i++ {
		if x == s.body[i][0] && y == s.body[i][1] {
			return true
		}
	}
	return false
}
