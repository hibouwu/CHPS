// structural
package pattern

import (
	"fmt"
)

// 6. Adapter Pattern
type LegacyPrinter interface {
	Print(s string) string
}

type MyLegacyPrinter struct{}

func (p *MyLegacyPrinter) Print(s string) string {
	return fmt.Sprintf("Legacy: %s", s)
}

type ModernPrinter interface {
	PrintModern(s string) string
}

type PrinterAdapter struct {
	OldPrinter LegacyPrinter
}

func (p *PrinterAdapter) PrintModern(s string) string {
	return p.OldPrinter.Print(s)
}

// 7. Bridge Pattern
type DrawAPI interface {
	DrawCircle(x, y, radius int)
}

type RedCircle struct{}
type GreenCircle struct{}

func (r *RedCircle) DrawCircle(x, y, radius int) {
	fmt.Printf("Drawing red circle at (%d,%d) radius %d\n", x, y, radius)
}

func (g *GreenCircle) DrawCircle(x, y, radius int) {
	fmt.Printf("Drawing green circle at (%d,%d) radius %d\n", x, y, radius)
}

type Circle struct {
	api    DrawAPI
	X, Y, Radius int
}

func (c *Circle) SetAPI(api DrawAPI) { c.api = api }
func (c *Circle) Draw() { c.api.DrawCircle(c.X, c.Y, c.Radius) }

// 8. Composite Pattern
type Component interface {
	Operation() string
}

type Leaf struct {
	Name string
}

func (l *Leaf) Operation() string { return l.Name }

type Composite struct {
	children []Component
}

func (c *Composite) Add(child Component) {
	c.children = append(c.children, child)
}

func (c *Composite) Operation() string {
	result := "Branch("
	for i, child := range c.children {
		result += child.Operation()
		if i < len(c.children)-1 {
			result += ", "
		}
	}
	return result + ")"
}

// 9. Decorator Pattern
type Coffee interface {
	Cost() int
	Description() string
}

type SimpleCoffee struct{}

func (s *SimpleCoffee) Cost() int           { return 5 }
func (s *SimpleCoffee) Description() string { return "Simple coffee" }

type MilkDecorator struct {
	Coffee Coffee
}

func (m *MilkDecorator) Cost() int           { return m.Coffee.Cost() + 2 }
func (m *MilkDecorator) Description() string { return m.Coffee.Description() + ", milk" }

// 10. Facade Pattern
type SubsystemA struct{}
func (s *SubsystemA) OperationA() string { return "SubA" }

type SubsystemB struct{}
func (s *SubsystemB) OperationB() string { return "SubB" }

type Facade struct {
	a *SubsystemA
	b *SubsystemB
}

func NewFacade() *Facade {
	return &Facade{&SubsystemA{}, &SubsystemB{}}
}

func (f *Facade) Operation() string {
	return f.a.OperationA() + " + " + f.b.OperationB()
}

// 11. Flyweight Pattern
type CharacterFlyweight struct {
	Char rune
}

type CharacterFactory struct {
	chars map[rune]*CharacterFlyweight
}

func NewCharacterFactory() *CharacterFactory {
	return &CharacterFactory{chars: make(map[rune]*CharacterFlyweight)}
}

func (f *CharacterFactory) GetCharacter(c rune) *CharacterFlyweight {
	if _, ok := f.chars[c]; !ok {
		f.chars[c] = &CharacterFlyweight{Char: c}
	}
	return f.chars[c]
}

// 12. Proxy Pattern
type Subject interface {
	Request() string
}

type RealSubject struct{}

func (s *RealSubject) Request() string { return "RealSubject active" }

type Proxy struct {
	realSubject *RealSubject
}

func (p *Proxy) Request() string {
	if p.realSubject == nil {
		p.realSubject = &RealSubject{}
	}
	return "Proxy: " + p.realSubject.Request()
}