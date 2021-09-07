// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 156.

// Package geometry defines simple types for plane geometry.
//!+point
package main

import (
	"fmt"
	"math"
	"math/rand"
	"os"
	"strconv"
	"time"
)

type Point struct{ x, y float64 }

func (p Point) X() float64 {
	return p.x
}

func (p Point) Y() float64 {
	return p.y
}

// traditional function
func Distance(p, q Point) float64 {
	return math.Hypot(q.X()-p.X(), q.Y()-p.Y())
}

// same thing, but as a method of the Point type
func (p Point) Distance(q Point) float64 {
	return math.Hypot(q.X()-p.X(), q.Y()-p.Y())
}

//!-point

//!+path

// A Path is a journey connecting the points with straight lines.
type Path []Point

// Distance returns the distance traveled along the path.
func (path Path) Distance() float64 {
	sum := 0.0
	for i := range path {
		if i > 0 {
			num := path[i-1].Distance(path[i])
			sum += num
			fmt.Printf(" + %.2f",num)
		}else if i == 0 {
			num := path[i].Distance(path[len(path)-1])
			sum += num
			fmt.Printf("%.2f",num)
		}
	}
	return sum
}
func (num Path) choca() bool {
	var ans bool
	for i := 0; i < len(num)-3 && !ans; i++ {
		ans = doIntersect(num[i], num[i+1], num[i+2], num[i+3])
	}
	return ans
}
func doIntersect(p1, q1, p2, q2 Point) bool{
	//traduccion del link que envio el profe
    o1 := orientation(p1, q1, p2);
    o2 := orientation(p1, q1, q2);
    o3 := orientation(p2, q2, p1);
    o4 := orientation(p2, q2, q1);
  
    if (o1 != o2 && o3 != o4){
        return true;
	}
    if (o1 == 0 && onSegment(p1, p2, q1)) {
		return true;
	}
    if (o2 == 0 && onSegment(p1, q2, q1)) {
		return true;
	}
    if (o3 == 0 && onSegment(p2, p1, q2)) {
		 return true;
	}
    if (o4 == 0 && onSegment(p2, q1, q2)) {
		 return true;
	}

    return false; 
}
func orientation(p, q , r Point) float64 {//traduccion del link que envio el profe
    val := (q.Y() - p.Y()) * (r.X() - q.X()) - (q.X() - p.X()) * (r.Y() - q.Y());
    if (val == 0){
		return 0;
	} 
	if (val > 0){
		return 1;
	}
	return 2;
}
func onSegment(p Point, q Point, r Point) bool{//traduccion del link que envio el profe
    if (q.X() <= math.Max(p.X(), r.X()) && (q.X() >= math.Min(p.X(), r.X()) && (q.Y() <= math.Max(p.Y(), r.Y()) && (q.Y() >= math.Min(p.Y(), r.Y()))))) {
		return true	
	}
	return false
}
func main() {
	if len(os.Args) == 2 {
		val := make([]int, 0, 100)
		for i := 1; i < len(os.Args); i++ {
			n, c := strconv.Atoi(os.Args[i])
			if c == nil {
				val = append(val, n)
			} else {
				fmt.Println("Character no valido")
				return
			}
		}
		sides, _ := strconv.Atoi(os.Args[1])
		if sides > 2 {
			fmt.Printf("- Generating a [%d] sides figure\n", sides)
			nums := Path{}
			for i := 0; i < sides; i++ {
				azar := rand.NewSource(time.Now().UnixNano())
				ran := rand.New(azar)
				nums = append(nums, Point{ran.Float64()*100 - (-100) + (-100), ran.Float64()*100 - (-100) + (-100)})
				for nums.choca() {
					nums[i] = Point{ran.Float64()*100 - (-100) + (-100), ran.Float64()*100 - (-100) + (-100)}
				}
			}
			fmt.Printf("- Figure's vertices\n")
			for i := range nums {
				fmt.Printf("   -( %.2f, %.2f)\n", nums[i].X(), nums[i].Y())
			}
			fmt.Println("- Figure's Perimeter")
			fmt.Printf("  - ")
			perimetro := nums.Distance()
			fmt.Printf(" = %.2f", perimetro)
			fmt.Println("")
		} else {
			fmt.Println("Lados deben ser mayores a 2")
			return
		}
	} else {
		fmt.Println("Num de argumentos invalido")
	}
}

//!-path
