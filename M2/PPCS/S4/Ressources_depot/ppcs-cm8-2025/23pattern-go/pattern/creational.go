// creational
package pattern

import (
	"sync"
)

// 1. Singleton Pattern
type singleton struct {
	Data string
}

var (
	instance *singleton
	once     sync.Once
)

func GetInstance() *singleton {
	once.Do(func() {
		instance = &singleton{Data: "I am singleton"}
	})
	return instance
}

// 2. Factory Method Pattern
type Animal interface {
	Speak() string
}

type Dog struct{}
type Cat struct{}

func (d *Dog) Speak() string { return "Woof!" }
func (c *Cat) Speak() string { return "Meow!" }

func CreateAnimal(animalType string) Animal {
	switch animalType {
	case "dog":
		return &Dog{}
	case "cat":
		return &Cat{}
	default:
		return nil
	}
}

// 3. Abstract Factory Pattern
type Button interface {
	Paint()
}

type WinButton struct{}
type MacButton struct{}

func (w *WinButton) Paint() { println("Windows button") }
func (m *MacButton) Paint() { println("Mac button") }

type GUIFactory interface {
	CreateButton() Button
}

type WinFactory struct{}
type MacFactory struct{}

func (w *WinFactory) CreateButton() Button { return &WinButton{} }
func (m *MacFactory) CreateButton() Button { return &MacButton{} }

// 4. Builder Pattern
type House struct {
	Windows int
	Doors   int
	Roof    string
}

type HouseBuilder struct {
	house *House
}

func NewHouseBuilder() *HouseBuilder {
	return &HouseBuilder{house: &House{}}
}

func (b *HouseBuilder) SetWindows(count int) *HouseBuilder {
	b.house.Windows = count
	return b
}

func (b *HouseBuilder) SetDoors(count int) *HouseBuilder {
	b.house.Doors = count
	return b
}

func (b *HouseBuilder) SetRoof(style string) *HouseBuilder {
	b.house.Roof = style
	return b
}

func (b *HouseBuilder) Build() *House {
	return b.house
}

// 5. Prototype Pattern
type Prototype interface {
	Clone() Prototype
}

type ConcretePrototype struct {
	Name string
}

func (p *ConcretePrototype) Clone() Prototype {
	return &ConcretePrototype{Name: p.Name}
}
