SOLID stands for:

S - Single-responsibility Principle<br/>
O - Open-closed Principle<br/>
L - Liskov Substitution Principle<br/>
I - Interface Segregation Principle<br/>
D - Dependency Inversion Principle<br/>

S : A class should have one and only one reason to change, meaning that a class should have only one job.

O : Objects or entities should be open for extension but closed for modification.

L : Let q(x) be a property provable about objects of x of type T. Then q(y) should be provable for objects y of type S where S is a subtype of T.  <b>This means that every subclass or derived class should be substitutable for their base or parent class.</b>

I : A client should never be forced to implement an interface that it doesn’t use, or clients shouldn’t be forced to depend on methods they do not use.

D : Entities must depend on abstractions, not on concretions. It states that the high-level module must not depend on the low-level module, but they should depend on abstractions.
