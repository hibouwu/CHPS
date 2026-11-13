package main

import (
	"fmt"
	"pattern"
)

func main() {
	fmt.Println("--- Démonstration des 23 Patterns GoF ---")

	// 1. Singleton
	s := pattern.GetInstance()
	fmt.Printf("[1] Singleton: %s\n", s)

	// 2. Factory Method
	dog := pattern.CreateAnimal("dog")
	fmt.Printf("[2] Factory Method: Dog says %s\n", dog.Speak())

	// 3. Abstract Factory
	var factory pattern.GUIFactory = &pattern.WinFactory{}
	btn := factory.CreateButton()
	fmt.Print("[3] Abstract Factory: ")
	btn.Paint()

	// 4. Builder
	builder := pattern.NewHouseBuilder()
	house := builder.SetWindows(4).SetDoors(2).SetRoof("Ardoise").Build()
	fmt.Printf("[4] Builder: Maison avec %d fenêtres\n", house.Windows)

	// 5. Prototype
	proto := &pattern.ConcretePrototype{Name: "Original"}
	clone := proto.Clone().(*pattern.ConcretePrototype)
	fmt.Printf("[5] Prototype: Clone name is %s\n", clone.Name)

	// 6. Adapter
	adapter := &pattern.PrinterAdapter{OldPrinter: &pattern.MyLegacyPrinter{}}
	fmt.Printf("[6] Adapter: %s\n", adapter.PrintModern("Message"))

	// 7. Bridge
	red := &pattern.RedCircle{}
	circle := pattern.Circle{X: 10, Y: 10, Radius: 5}
	circle.SetAPI(red)
	fmt.Print("[7] Bridge: ")
	circle.Draw()

	// 8. Composite
	root := &pattern.Composite{}
	root.Add(&pattern.Leaf{Name: "Feuille A"})
	fmt.Printf("[8] Composite: %s\n", root.Operation())

	// 9. Decorator
	coffee := &pattern.SimpleCoffee{}
	milkCoffee := &pattern.MilkDecorator{Coffee: coffee}
	fmt.Printf("[9] Decorator: %s coûte %d\n", milkCoffee.Description(), milkCoffee.Cost())

	// 10. Facade
	facade := pattern.NewFacade()
	fmt.Printf("[10] Facade: %s\n", facade.Operation())

	// 11. Flyweight
	flyFactory := pattern.NewCharacterFactory()
	charA := flyFactory.GetCharacter('A')
	fmt.Printf("[11] Flyweight: Character is %c\n", charA.Char)

	// 12. Proxy
	proxy := &pattern.Proxy{}
	fmt.Printf("[12] Proxy: %s\n", proxy.Request())

	// 13. Chain of Responsibility
	h1 := &pattern.ConcreteHandler1{}
	h2 := &pattern.ConcreteHandler2{}
	h1.SetNext(h2)
	fmt.Printf("[13] Chain: %s\n", h1.Handle("two"))

	// 14. Command
	light := &pattern.Light{}
	cmd := &pattern.LightOnCommand{Light: light}
	fmt.Printf("[14] Command: %s\n", cmd.Execute())

	// 15. Interpreter
	expr := &pattern.TerminalExpression{Data: "Hello"}
	fmt.Printf("[15] Interpreter: Is valid? %v\n", expr.Interpret())

	// 16. Iterator
	coll := &pattern.Collection{Items: []interface{}{1, 2, 3}}
	it := coll.CreateIterator()
	fmt.Print("[16] Iterator: ")
	for it.HasNext() {
		fmt.Printf("%v ", it.Next())
	}
	fmt.Println()

	// 17. Mediator
	m := &pattern.ConcreteMediator{}
	c1 := &pattern.Component1{Mediator: m}
	m.SetComponent1(c1)
	fmt.Print("[17] Mediator: ")
	c1.Trigger()

	// 18. Memento
	originator := &pattern.Originator{State: "On"}
	memento := originator.CreateMemento()
	originator.State = "Off"
	originator.RestoreMemento(memento)
	fmt.Printf("[18] Memento: Restored state: %s\n", originator.State)

	// 19. Observer
	subject := &pattern.Subject2{}
	obs := &pattern.ConcreteObserver{ID: 1}
	subject.Attach(obs)
	fmt.Print("[19] Observer: ")
	subject.SetState("Updated")

	// 20. State
	ctx := &pattern.Context{State: &pattern.ConcreteStateA{}}
	fmt.Printf("[20] State: %s\n", ctx.Request())

	// 21. Strategy
	contextStrat := &pattern.ContextStrat{Strategy: &pattern.ConcreteStrategyA{}}
	fmt.Printf("[21] Strategy: %s\n", contextStrat.Execute())

	// 22. Template Method
	// En Go, on passe l'implémentation spécifique au "Template"
	worker := pattern.NewWorker(&pattern.ConcreteWorker{})
	fmt.Printf("[22] Template Method: %s\n", worker.Execute())

	// 23. Visitor
	element := &pattern.ConcreteElementA{}
	visitor := &pattern.ConcreteVisitor{}
	fmt.Print("[23] Visitor: ")
	element.Accept(visitor)
}
