// behavioral
package pattern

import "fmt"

// 13. Chain of Responsibility
type Handler interface {
	SetNext(handler Handler)
	Handle(request string) string
}

type BaseHandler struct {
	next Handler
}

func (b *BaseHandler) SetNext(h Handler) { b.next = h }

type ConcreteHandler1 struct{ BaseHandler }

func (h *ConcreteHandler1) Handle(req string) string {
	if req == "one" { return "Handled by 1" }
	if h.next != nil { return h.next.Handle(req) }
	return "Not handled"
}

type ConcreteHandler2 struct{ BaseHandler }

func (h *ConcreteHandler2) Handle(req string) string {
	if req == "two" { return "Handled by 2" }
	if h.next != nil { return h.next.Handle(req) }
	return "Not handled"
}

// 14. Command
type Command interface { Execute() string }

type Light struct{}
func (l *Light) On() string { return "Light On" }

type LightOnCommand struct { Light *Light }
func (c *LightOnCommand) Execute() string { return c.Light.On() }

// 15. Interpreter
type Expression interface { Interpret() bool }
type TerminalExpression struct { Data string }
func (t *TerminalExpression) Interpret() bool { return len(t.Data) > 0 }

// 16. Iterator
type Iterator interface {
	HasNext() bool
	Next() interface{}
}

type Collection struct { Items []interface{} }
func (c *Collection) CreateIterator() Iterator {
	return &CollectionIterator{collection: c}
}

type CollectionIterator struct {
	collection *Collection
	index      int
}

func (i *CollectionIterator) HasNext() bool { return i.index < len(i.collection.Items) }
func (i *CollectionIterator) Next() interface{} {
	item := i.collection.Items[i.index]
	i.index++
	return item
}

// 17. Mediator
type Mediator interface { Notify(sender interface{}, event string) }

type ConcreteMediator struct {
	c1 *Component1
}

func (m *ConcreteMediator) SetComponent1(c *Component1) { m.c1 = c }
func (m *ConcreteMediator) Notify(s interface{}, e string) {
	fmt.Printf("Mediator: reacting to %s\n", e)
}

type Component1 struct { Mediator Mediator }
func (c *Component1) Trigger() { c.Mediator.Notify(c, "click") }

// 18. Memento
type Memento struct { State string }
type Originator struct { State string }
func (o *Originator) CreateMemento() *Memento { return &Memento{State: o.State} }
func (o *Originator) RestoreMemento(m *Memento) { o.State = m.State }

// 19. Observer
type Observer interface { Update(string) }
type Subject2 struct {
	observers []Observer
	state     string
}

func (s *Subject2) Attach(o Observer) { s.observers = append(s.observers, o) }
func (s *Subject2) SetState(st string) {
	s.state = st
	for _, o := range s.observers { o.Update(st) }
}

type ConcreteObserver struct{ ID int }
func (o *ConcreteObserver) Update(s string) { fmt.Printf("Observer %d: state is %s\n", o.ID, s) }

// 20. State
type State interface { Handle() string }
type Context struct { State State }
func (c *Context) Request() string { return c.State.Handle() }

type ConcreteStateA struct{}
func (s *ConcreteStateA) Handle() string { return "State A" }

// 21. Strategy
type Strategy interface { Execute() string }
type ConcreteStrategyA struct{}
func (s *ConcreteStrategyA) Execute() string { return "Strategy A" }

type ContextStrat struct { Strategy Strategy }
func (c *ContextStrat) Execute() string { return c.Strategy.Execute() }

// 22. Template Method (Idiomatique Go)
type WorkerInterface interface {
	Work() string
}

type TemplateWorker struct {
	provider WorkerInterface
}

func NewWorker(p WorkerInterface) *TemplateWorker { return &TemplateWorker{provider: p} }
func (t *TemplateWorker) Execute() string {
	return "Prep -> " + t.provider.Work() + " -> Clean"
}

type ConcreteWorker struct{}
func (w *ConcreteWorker) Work() string { return "Specific Task" }

// 23. Visitor
type Visitor interface {
	VisitA(*ConcreteElementA)
}

type Element interface { Accept(Visitor) }

type ConcreteElementA struct{}
func (e *ConcreteElementA) Accept(v Visitor) { v.VisitA(e) }

type ConcreteVisitor struct{}
func (v *ConcreteVisitor) VisitA(e *ConcreteElementA) { fmt.Println("Visited Element A") }