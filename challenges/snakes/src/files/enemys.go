package files

import (
	"math/rand"
	"time"

	"github.com/hajimehoshi/ebiten"
	"github.com/hajimehoshi/ebiten/ebitenutil"
)

type EnemySnake struct {
	game     *Game
	body     [][]float64
	dotsBody int
	points   int
	pointsW  int
	move     chan int
	lastMov  string
	tail     ebiten.Image
	head     ebiten.Image
	ran      rand.Source
}

func CreateEnemySnake(g *Game) *EnemySnake {
	m := EnemySnake{
		game:     g,
		dotsBody: 0,
		pointsW:  0,
		lastMov:  "right",
	}
	m.move = make(chan int)
	m.ran = rand.NewSource(time.Now().UnixNano())
	random := rand.New(m.ran)
	startX := float64(random.Intn(30) * 20)
	startY := float64(random.Intn(30) * 20)
	m.body = append(m.body, []float64{startX, startY})
	headimg, _, _ := ebitenutil.NewImageFromFile("assets/enemyhead.png", ebiten.FilterDefault)
	tailimg, _, _ := ebitenutil.NewImageFromFile("assets/enemytail.png", ebiten.FilterDefault)
	m.head = *headimg
	m.tail = *tailimg
	return &m
}

func (m *EnemySnake) getPartPos(points int) (float64, float64) {
	return m.body[points+1][0], m.body[points+1][1]
}
func (m *EnemySnake) getHeadPos() (float64, float64) {
	return m.body[0][0], m.body[0][1]
}
func (m *EnemySnake) addPoint() {
	m.points++
	m.pointsW++
}
func (m *EnemySnake) Behavior() error {
	for {
		dotTime := <-m.move
		m.Update(dotTime)
	}
}
func (m *EnemySnake) Update(dotTime int) error {
	if dotTime == 1 {
		random := rand.New(m.ran)
		move := random.Intn(4)
		changeDir := random.Intn(3)
		x, y := m.getHeadPos()
		if changeDir == 0 {
			switch move {
			case 0:
				if x < 560 && m.lastMov != "left" {
					m.lastMov = "right"
				} else {
					m.lastMov = "left"
				}
				return nil
			case 1:
				if y < 560 && m.lastMov != "up" {
					m.lastMov = "down"
				} else {
					m.lastMov = "up"
				}
				return nil
			case 2:
				if y > 20 && m.lastMov != "down" {
					m.lastMov = "up"
				} else {
					m.lastMov = "down"
				}
				return nil
			case 3:
				if x > 20 && m.lastMov != "right" {
					m.lastMov = "left"
				} else {
					m.lastMov = "right"
				}
				return nil
			}
		}
		if x >= 660 {
			m.lastMov = "left"
			return nil
		}
		if x == 20 {
			m.lastMov = "right"
			return nil
		}
		if y == 660 {
			m.lastMov = "up"
			return nil
		}
		if y == 20 {
			m.lastMov = "down"
			return nil
		}
	}

	if dotTime == 1 {
		x, y := m.game.snake.getHeadPos()
		bol := false
		for i := 0; i < len(m.body); i++ {
			if x == m.body[i][0] && y == m.body[i][1] {
				bol = true
			}
		}
		if bol {
			m.game.End()
		}
	}
	return nil
}

func (m *EnemySnake) Draw(screen *ebiten.Image, dotTime int) error {
	if m.game.play {
		m.UpdatePosMov(dotTime)
	}
	drawImage := &ebiten.DrawImageOptions{}
	x, y := m.getHeadPos()
	drawImage.GeoM.Translate(x, y)
	screen.DrawImage(&m.head, drawImage)
	for i := 0; i < m.dotsBody; i++ {
		partDO := &ebiten.DrawImageOptions{}
		x, y := m.getPartPos(i)
		partDO.GeoM.Translate(x, y)
		screen.DrawImage(&m.tail, partDO)
	}
	return nil
}

func (m *EnemySnake) UpdatePosMov(dotTime int) {
	if dotTime == 1 {
		if m.pointsW > 0 {
			m.pointsW--
			m.dotsBody++
		}
		switch m.lastMov {
		case "up":
			m.HeadPosMov(0, -20)
		case "down":
			m.HeadPosMov(0, +20)
		case "right":
			m.HeadPosMov(20, 0)
		case "left":
			m.HeadPosMov(-20, 0)
		}
	}
}

func (m *EnemySnake) HeadPosMov(x, y float64) {
	hX := m.body[0][0] + x
	hY := m.body[0][1] + y
	m.body = append([][]float64{[]float64{hX, hY}}, m.body...)
	m.body = m.body[:m.dotsBody+1]
}
