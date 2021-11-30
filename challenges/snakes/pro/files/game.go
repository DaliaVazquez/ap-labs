package files

import (
	"time"

	"github.com/hajimehoshi/ebiten"
)

type Game struct {
	snake        *Snake
	snakeC       chan int
	hud          *Hud
	play         bool
	points       int
	dotTime      int
	totalMouses  int
	mouses       []*Mouse
	totalEnemies int
	enemies      []*EnemySnake
	enemiesC     []chan int
}

func NewGame(mouses int, enemies int) Game {
	g := Game{
		play:         true,
		points:       0,
		dotTime:      0,
		totalEnemies: enemies,
		totalMouses:  mouses,
	}
	arrayM := make([]*Mouse, g.totalMouses)
	arrayEnemies := make([]*EnemySnake, g.totalEnemies)
	for i := 0; i < g.totalMouses; i++ {
		arrayM[i] = CreateMouse(&g)
		time.Sleep(20)
	}
	for i := 0; i < len(arrayEnemies); i++ {
		arrayEnemies[i] = CreateEnemySnake(&g)
		time.Sleep(20)
	}
	enemiesC := make([]chan int, g.totalEnemies)
	for i := 0; i < len(enemiesC); i++ {
		enemiesC[i] = make(chan int)
		arrayEnemies[i].move = enemiesC[i]
		go arrayEnemies[i].Behavior()
		time.Sleep(20)
	}
	g.mouses = arrayM
	g.enemiesC = enemiesC
	g.enemies = arrayEnemies
	g.snake = CreateSnake(&g)
	g.snakeC = make(chan int)
	go g.snake.Behavior()
	g.hud = CreateHud(&g, mouses)
	return g
}

func (g *Game) Update() error {
	if g.play {
		g.dotTime = (g.dotTime + 1) % 20
		if g.totalMouses == 0 {
			g.play = false
		}
		if err := g.snake.Update(g.dotTime); err != nil {
			g.snakeC <- g.dotTime
		}
		for i := 0; i < len(g.enemiesC); i++ {
			g.enemiesC[i] <- g.dotTime
		}
		xPos, y := g.snake.getHeadPos()
		for i := 0; i < len(g.mouses); i++ {
			if xPos == g.mouses[i].x && y == g.mouses[i].y {
				g.mouses[i].y = -20
				g.mouses[i].x = -20
				g.hud.addPoint()
				g.totalMouses--
				g.snake.addPoint()
				break
			}
		}
		for j := 0; j < len(g.enemies); j++ {
			xPos, y := g.enemies[j].getHeadPos()
			for i := 0; i < len(g.mouses); i++ {
				if xPos == g.mouses[i].x && y == g.mouses[i].y {
					g.mouses[i].y = -20
					g.mouses[i].x = -20
					g.totalMouses--
					g.enemies[j].addPoint()
					break
				}
			}
		}
	}
	for i := 0; i < g.totalMouses; i++ {
		if err := g.mouses[i].Update(g.dotTime); err != nil {
			return err
		}
	}
	return nil
}
func (g *Game) End() {
	g.play = false
}
func (g *Game) Draw(screen *ebiten.Image) error {
	for _, enemy := range g.enemies {
		if err := enemy.Draw(screen, g.dotTime); err != nil {
			return err
		}
	}
	if err := g.snake.Draw(screen, g.dotTime); err != nil {
		return err
	}
	if err := g.hud.Draw(screen); err != nil {
		return err
	}
	for i := 0; i < len(g.mouses); i++ {
		if err := g.mouses[i].Draw(screen, g.dotTime); err != nil {
			return err
		}
	}
	if g.totalMouses == 0 {
		g.hud.End2(screen)
	}
	return nil
}
