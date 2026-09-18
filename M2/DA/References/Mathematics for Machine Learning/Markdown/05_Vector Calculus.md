# Vector Calculus

![image](<Images/05_Vector_Calculus_image_001.jpg>)


Many algorithms in machine learning optimize an objective function with respect to a set of desired model parameters that control how well a model explains the data: Finding good parameters can be phrased as an optimization problem (see Sections 8.2 and 8.3). Examples include: (i) lin ear regression (see Chapter 9), where we look at curve-fitting problems and optimize linear weight parameters to maximize the likelihood; (ii) neural-network auto-encoders for dimensionality reduction and data com pression, where the parameters are the weights and biases of each layer, and where we minimize a reconstruction error by repeated application of the chain rule; and (iii) Gaussian mixture models (see Chapter 11) for modeling data distributions, where we optimize the location and shape parameters of each mixture component to maximize the likelihood of the model. Figure 5.1 illustrates some of these problems, which we typically solve by using optimization algorithms that exploit gradient information (Section 7.1). Figure 5.2 gives an overview of how concepts in this chapter are related and how they are connected to other chapters of the book. 

Central to this chapter is the concept of a function. A function $f$ is a quantity that relates two quantities to each other. In this book, these quantities are typically inputs $\pmb { x } \in \mathbb { R } ^ { D }$ and targets (function values) $f ( { \pmb x } )$ which we assume are real-valued if not stated otherwise. Here $\mathbb { R } ^ { D }$ is the domain of $f ,$ and the function values $f ( { \pmb x } )$ are the image/codomain of $f .$ 

![image](<Images/05_Vector_Calculus_image_002.jpg>)



(a) Regression problem: Find parameters, such that the curve explains the observations (crosses) well.


![image](<Images/05_Vector_Calculus_image_003.jpg>)



domain image/codomain Figure 5.1 Vector calculus plays a central role in (a) regression (curve fitting) and (b) density estimation, $\mathrm { i . e . , }$ modeling data distributions.



(b) Density estimation with a Gaussian mixture model: Find means and covariances, such that the data (dots) can be explained well.


139 


Vector Calculus



Figure 5.2 A mind map of the concepts introduced in this chapter, along with when they are used in other parts of the book.


![image](<Images/05_Vector_Calculus_image_004.jpg>)


Section 2.7.3 provides much more detailed discussion in the context of linear functions. We often write 

$$
f: \mathbb {R} ^ {D} \to \mathbb {R}\tag{5.1a}
$$

$$
\boldsymbol {x} \mapsto f (\boldsymbol {x})\tag{5.1b}
$$

to specify a function, where (5.1a) specifies that $f$ is a mapping from $\mathbb { R } ^ { D }$ to R and (5.1b) specifies the explicit assignment of an input x to a function value $f ( { \pmb x } )$ . A function $f$ assigns every input x exactly one function value f(x). 

## Example 5.1

Recall the dot product as a special case of an inner product (Section 3.2). In the previous notation, the function $f ( \pmb { x } ) = \pmb { x } ^ { \top } \pmb { x } , \ \pmb { x } \in \mathbb { R } ^ { 2 }$ , would be specified as 

$$
f: \mathbb {R} ^ {2} \to \mathbb {R}\tag{5.2a}
$$

$$
\boldsymbol {x} \mapsto x _ {1} ^ {2} + x _ {2} ^ {2}.\tag{5.2b}
$$

In this chapter, we will discuss how to compute gradients of functions, which is often essential to facilitate learning in machine learning models since the gradient points in the direction of steepest ascent. Therefore, 

5.1 Differentiation of Univariate Functions 

![image](<Images/05_Vector_Calculus_image_005.jpg>)


Figure 5.3 The average incline of a function $f$ between $x _ { 0 }$ and $x _ { 0 } + \delta x$ is the incline of the secant (blue) through $f ( x _ { 0 } )$ and f(x<sub>0</sub> + δx) and given by $\delta y / \delta x$ 

vector calculus is one of the fundamental mathematical tools we need in machine learning. Throughout this book, we assume that functions are differentiable. With some additional technical definitions, which we do not cover here, many of the approaches presented can be extended to sub-differentials (functions that are continuous but not differentiable at certain points). We will look at an extension to the case of functions with constraints in Chapter 7. 

## 5.1 Differentiation of Univariate Functions

In the following, we briefly revisit differentiation of a univariate function, which may be familiar from high school mathematics. We start with the difference quotient of a univariate function $y = f ( x ) , x , y \in \mathbb { R }$ , which we will subsequently use to define derivatives. 

Definition 5.1 (Difference Quotient). The difference quotient 

$$
\frac {\delta y}{\delta x} := \frac {f (x + \delta x) - f (x)}{\delta x}\tag{5.3}
$$

computes the slope of the secant line through two points on the graph of $f .$ In Figure 5.3, these are the points with x-coordinates $x _ { 0 }$ and $x _ { 0 } + \delta x$ 

The difference quotient can also be considered the average slope of $f$ between x and $x + \delta x$ if we assume $f$ to be a linear function. In the limit for $\delta x  0$ , we obtain the tangent of $f$ at $x ,$ , if $f$ is differentiable. The tangent is then the derivative of $f$ at x. 

Definition 5.2 (Derivative). More formally, for $h > 0$ the derivative of $f$ derivative at x is defined as the limit 

$$
\frac {\mathrm{d} f}{\mathrm{d} x} := \lim _ {h \rightarrow 0} \frac {f (x + h) - f (x)}{h},\tag{5.4}
$$

and the secant in Figure 5.3 becomes a tangent. 

The derivative of $f$ points in the direction of steepest ascent of $f .$ 

## Example 5.2 (Derivative of a Polynomial)

We want to compute the derivative of $f ( x ) = x ^ { n } , n \in \mathbb { N }$ . We may already know that the answer will be $n x ^ { n - 1 }$ , but we want to derive this result using the definition of the derivative as the limit of the difference quotient. 

Using the definition of the derivative in (5.4), we obtain 

$$
\frac {\mathrm{d} f}{\mathrm{d} x} = \lim _ {h \rightarrow 0} \frac {f (x + h) - f (x)}{h}\tag{5.5a}
$$

$$
= \lim _ {h \to 0} \frac {(x + h) ^ {n} - x ^ {n}}{h}\tag{5.5b}
$$

$$
= \lim _ {h \to 0} \frac {\sum_ {i = 0} ^ {n} \binom {n} {i} x ^ {n - i} h ^ {i} - x ^ {n}}{h}.\tag{5.5c}
$$

We see that $x ^ { n } = { \binom { n } { 0 } } x ^ { n - 0 } h ^ { 0 }$ . By starting the sum at 1, the $x ^ { n }$ -term cancels, and we obtain 

$$
\frac {\mathrm{d} f}{\mathrm{d} x} = \lim _ {h \rightarrow 0} \frac {\sum_ {i = 1} ^ {n} \binom {n} {i} x ^ {n - i} h ^ {i}}{h}\tag{5.6a}
$$

$$
= \lim _ {h \to 0} \sum_ {i = 1} ^ {n} {\binom {n} {i}} x ^ {n - i} h ^ {i - 1}\tag{5.6b}
$$

$$
= \lim _ {h \rightarrow 0} \binom {n} {1} x ^ {n - 1} + \underbrace {\sum_ {i = 2} ^ {n} \binom {n} {i}} _ {\text {   }} x ^ {n - i} h ^ {i - 1}\tag{5.6c}
$$

$$
\rightarrow 0 \mathrm{as} h \rightarrow 0
$$

$$
= \frac {n !}{1 ! (n - 1) !} x ^ {n - 1} = n x ^ {n - 1}.\tag{5.6d}
$$

## 5.1.1 Taylor Series

The Taylor series is a representation of a function $f$ as an infinite sum of terms. These terms are determined using derivatives of $f$ evaluated at $x _ { 0 }$ . 

Taylor polynomial We define $t ^ { 0 } : = 1$ for all $t \in \mathbb { R }$ 

Definition 5.3 (Taylor Polynomial). The Taylor polynomial of degree n of $f : \mathbb { R } \to \mathbb { R }$ at $x _ { 0 }$ is defined as 

$$
T _ {n} (x) := \sum_ {k = 0} ^ {n} \frac {f ^ {(k)} \left(x _ {0}\right)}{k !} \left(x - x _ {0}\right) ^ {k},\tag{5.7}
$$

where $f ^ { ( k ) } ( x _ { 0 } )$ is the kth derivative of $f$ at $x _ { 0 }$ (which we assume exists) and $\frac { f ^ { ( k ) } ( x _ { 0 } ) } { k ! }$ are the coefficients of the polynomial. 

Definition 5.4 (Taylor Series). For a smooth function $f \in \mathcal { C } ^ { \infty } , f : \mathbb { R } \to \mathbb { R }$ , the Taylor series of $f$ at $x _ { 0 }$ is defined as 

Taylor series 

5.1 Differentiation of Univariate Functions 

$$
T _ {\infty} (x) = \sum_ {k = 0} ^ {\infty} \frac {f ^ {(k)} \left(x _ {0}\right)}{k !} \left(x - x _ {0}\right) ^ {k}.\tag{5.8}
$$

For $x _ { 0 } = 0$ , we obtain the Maclaurin series as a special instance of the Taylor series. If $f ( x ) = T _ { \infty } ( x )$ , then f is called analytic. 

Remark. In general, a Taylor polynomial of degree n is an approximation of a function, which does not need to be a polynomial. The Taylor polynomial is similar to $f$ in a neighborhood around $x _ { 0 }$ . However, a Taylor polynomial of degree n is an exact representation of a polynomial $f$ of degree k $\leqslant n$ since all derivatives $f ^ { ( i ) } , i > k$ vanish. 

## Example 5.3 (Taylor Polynomial)

We consider the polynomial 

$$
f (x) = x ^ {4}\tag{5.9}
$$

and seek the Taylor polynomial $T _ { 6 }$ , evaluated at $x _ { 0 } = 1$ . We start by computing the coefficients $f ^ { ( k ) } ( 1 )$ for $k = 0 , \ldots , 6 \colon$ 

$$
f (1) = 1\tag{5.10}
$$

$$
f ^ {\prime} (1) = 4\tag{5.11}
$$

$$
f ^ {\prime \prime} (1) = 1 2\tag{5.12}
$$

$$
f ^ {(3)} (1) = 2 4\tag{5.13}
$$

$$
f ^ {(4)} (1) = 2 4\tag{5.14}
$$

$$
f ^ {(5)} (1) = 0\tag{5.15}
$$

$$
f ^ {(6)} (1) = 0\tag{5.16}
$$

Therefore, the desired Taylor polynomial is 

$$
T _ {6} (x) = \sum_ {k = 0} ^ {6} \frac {f ^ {(k)} (x _ {0})}{k !} (x - x _ {0}) ^ {k}\tag{5.17a}
$$

$$
= 1 + 4 (x - 1) + 6 (x - 1) ^ {2} + 4 (x - 1) ^ {3} + (x - 1) ^ {4} + 0.\tag{5.17b}
$$

Multiplying out and re-arranging yields 

$$
T _ {6} (x) = (1 - 4 + 6 - 4 + 1) + x (4 - 1 2 + 1 2 - 4)
$$

$$
+ x ^ {2} (6 - 1 2 + 6) + x ^ {3} (4 - 4) + x ^ {4}\tag{5.18a}
$$

$$
= x ^ {4} = f (x),\tag{5.18b}
$$

i.e., we obtain an exact representation of the original function. 



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



Figure 5.4 Taylor polynomials. The original function $f ( x ) =$ 

$$
(x) + \cos (x)
$$

(black, solid) is approximated by Taylor polynomials (dashed) around $x _ { 0 } = 0 .$ 

Higher-order Taylor polynomials approximate the function $f$ better and more globally. $T _ { 1 0 }$ is already similar to $f$ in [−4, 4]. 

![image](<Images/05_Vector_Calculus_image_006.jpg>)


## Example 5.4 (Taylor Series)

Consider the function in Figure 5.4 given by 

$$
f (x) = \sin (x) + \cos (x) \in \mathcal {C} ^ {\infty}.\tag{5.19}
$$

We seek a Taylor series expansion of $f$ at $x _ { 0 } = 0$ , which is the Maclaurin series expansion of $f$ . We obtain the following derivatives: 

$$
f (0) = \sin (0) + \cos (0) = 1\tag{5.20}
$$

$$
f ^ {\prime} (0) = \cos (0) - \sin (0) = 1\tag{5.21}
$$

$$
f ^ {\prime \prime} (0) = - \sin (0) - \cos (0) = - 1\tag{5.22}
$$

$$
f ^ {(3)} (0) = - \cos (0) + \sin (0) = - 1\tag{5.23}
$$

$$
f ^ {(4)} (0) = \sin (0) + \cos (0) = f (0) = 1\tag{5.24}
$$

We can see a pattern here: The coefficients in our Taylor series are only $\pm 1$ (since sin $( 0 ) = 0 )$ , each of which occurs twice before switching to the other one. Furthermore, $f ^ { ( k + 4 ) } ( 0 ) = f ^ { ( k ) } ( 0 )$ 

Therefore, the full Taylor series expansion of $f$ at $x _ { 0 } = 0$ is given by 

$$
T _ {\infty} (x) = \sum_ {k = 0} ^ {\infty} \frac {f ^ {(k)} (x _ {0})}{k !} (x - x _ {0}) ^ {k}\tag{5.25a}
$$

$$
= 1 + x - \frac {1}{2 !} x ^ {2} - \frac {1}{3 !} x ^ {3} + \frac {1}{4 !} x ^ {4} + \frac {1}{5 !} x ^ {5} - \dots\tag{5.25b}
$$

$$
= 1 - \frac {1}{2 !} x ^ {2} + \frac {1}{4 !} x ^ {4} \mp \dots + x - \frac {1}{3 !} x ^ {3} + \frac {1}{5 !} x ^ {5} \mp \dots\tag{5.25c}
$$

$$
= \sum_ {k = 0} ^ {\infty} (- 1) ^ {k} \frac {1}{(2 k) !} x ^ {2 k} + \sum_ {k = 0} ^ {\infty} (- 1) ^ {k} \frac {1}{(2 k + 1) !} x ^ {2 k + 1}
$$

$$
= \cos (x) + \sin (x),\tag{5.25d}
$$

(5.25e) 

Draft (2024-01-15) of “Mathematics for Machine Learning”. Feedback: https://mml-book.com. 

where we used the power series representations 

$$
\cos (x) = \sum_ {k = 0} ^ {\infty} (- 1) ^ {k} \frac {1}{(2 k) !} x ^ {2 k},\tag{5.26}
$$

$$
\sin (x) = \sum_ {k = 0} ^ {\infty} (- 1) ^ {k} \frac {1}{(2 k + 1) !} x ^ {2 k + 1}.\tag{5.27}
$$

Figure 5.4 shows the corresponding first Taylor polynomials $T _ { n }$ for $n =$ 0, 1, 5, 10. 

Remark. A Taylor series is a special case of a power series 

$$
f (x) = \sum_ {k = 0} ^ {\infty} a _ {k} (x - c) ^ {k}\tag{5.28}
$$

where $a _ { k }$ are coefficients and c is a constant, which has the special form in Definition 5.4. 

## 5.1.2 Differentiation Rules

In the following, we briefly state basic differentiation rules, where we denote the derivative of f by $f ^ { \prime }$ . 

$$
\text { Product   rule: } \quad (f (x) g (x)) ^ {\prime} = f ^ {\prime} (x) g (x) + f (x) g ^ {\prime} (x)\tag{5.29}
$$

$$
\text { Quotient   rule: } \quad \left(\frac {f (x)}{g (x)}\right) ^ {\prime} = \frac {f ^ {\prime} (x) g (x) - f (x) g ^ {\prime} (x)}{(g (x)) ^ {2}}\tag{5.30}
$$

$$
\text {   Sum   rule:   } \quad (f (x) + g (x)) ^ {\prime} = f ^ {\prime} (x) + g ^ {\prime} (x)\tag{5.31}
$$

$$
\text { Chain   rule: } \quad \left(g (f (x))\right) ^ {\prime} = (g \circ f) ^ {\prime} (x) = g ^ {\prime} (f (x)) f ^ {\prime} (x)\tag{5.32}
$$

Here, $g \circ f$ denotes function composition $x \mapsto f ( x ) \mapsto g ( f ( x ) )$ 

## Example 5.5 (Chain Rule)

Let us compute the derivative of the function $h ( x ) = ( 2 x + 1 ) ^ { 4 }$ using the chain rule. With 

$$
h (x) = (2 x + 1) ^ {4} = g (f (x)),\tag{5.33}
$$

$$
f (x) = 2 x + 1,\tag{5.34}
$$

$$
g (f) = f ^ {4},\tag{5.35}
$$

we obtain the derivatives of $f$ and g as 

$$
f ^ {\prime} (x) = 2,
$$

$$
g ^ {\prime} (f) = 4 f ^ {3},\tag{5.36}
$$

(5.37) 



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



such that the derivative of h is given as 

$$
h ^ {\prime} (x) = g ^ {\prime} (f) f ^ {\prime} (x) = \left(4 f ^ {3}\right) \cdot 2 \stackrel {(5. 3 4)} {=} 4 (2 x + 1) ^ {3} \cdot 2 = 8 (2 x + 1) ^ {3},\tag{5.38}
$$

where we used the chain rule (5.32) and substituted the definition of $f$ in (5.34) in $g ^ { \prime } ( f )$ 

## 5.2 Partial Differentiation and Gradients

Differentiation as discussed in Section 5.1 applies to functions f of a scalar variable $x \in \ \mathbb { R }$ . In the following, we consider the general case where the function $f$ depends on one or more variables $\pmb { x } \in \mathbb { R } ^ { n } , \mathbf { e . g . }$ $f ( \pmb { x } ) = f ( x _ { 1 } , x _ { 2 } )$ . The generalization of the derivative to functions of several variables is the gradient. 

We find the gradient of the function f with respect to x by varying one variable at a time and keeping the others constant. The gradient is then the collection of these partial derivatives. 

Definition 5.5 (Partial Derivative). For a function $f : \mathbb { R } ^ { n }  \mathbb { R } .$ x ↓ $f ( \pmb { x } ) , \pmb { x } \in \mathbb { R } ^ { n }$ of n variables $x _ { 1 } , \ldots , x _ { n }$ we define the partial derivatives as 

$$
\frac {\partial f}{\partial x _ {1}} = \lim _ {h \rightarrow 0} \frac {f (x _ {1} + h , x _ {2} , \dots , x _ {n}) - f (\boldsymbol {x})}{h}\tag{5.39}
$$

$$
\frac {\partial f}{\partial x _ {n}} = \lim _ {h \rightarrow 0} \frac {f (x _ {1} , \dots , x _ {n - 1} , x _ {n} + h) - f (\boldsymbol {x})}{h}
$$

and collect them in the row vector 

$$
\nabla_ {\boldsymbol {x}} f = \operatorname{grad} f = \frac {\mathrm{d} f}{\mathrm{d} \boldsymbol {x}} = \left[ \begin{array}{c c c c} \frac {\partial f (\boldsymbol {x})}{\partial x _ {1}} & \frac {\partial f (\boldsymbol {x})}{\partial x _ {2}} & \dots & \frac {\partial f (\boldsymbol {x})}{\partial x _ {n}} \end{array} \right] \in \mathbb {R} ^ {1 \times n},\tag{5.40}
$$

where n is the number of variables and 1 is the dimension of the image/ range/codomain of $f .$ . Here, we defined the column vector $\pmb { x } = [ x _ { 1 } , \ldots , x _ { n } ] ^ { \top }$ $\in \mathbb { R } ^ { n }$ . The row vector in (5.40) is called the gradient of f or the Jacobian and is the generalization of the derivative from Section 5.1 

Remark. This definition of the Jacobian is a special case of the general definition of the Jacobian for vector-valued functions as the collection of partial derivatives. We will get back to this in Section 5.3. ◇ 

Example 5.6 (Partial Derivatives Using the Chain Rule) For $f ( x , y ) = ( x + 2 y ^ { 3 } ) ^ { 2 }$ , we obtain the partial derivatives 

$$
\frac {\partial f (x , y)}{\partial x} = 2 (x + 2 y ^ {3}) \frac {\partial}{\partial x} (x + 2 y ^ {3}) = 2 (x + 2 y ^ {3}),\tag{5.41}
$$

$$
\frac {\partial f (x , y)}{\partial y} = 2 \left(x + 2 y ^ {3}\right) \frac {\partial}{\partial y} \left(x + 2 y ^ {3}\right) = 1 2 \left(x + 2 y ^ {3}\right) y ^ {2}.\tag{5.42}
$$

where we used the chain rule (5.32) to compute the partial derivatives. 

Remark (Gradient as a Row Vector). It is not uncommon in the literature to define the gradient vector as a column vector, following the convention that vectors are generally column vectors. The reason why we define the gradient vector as a row vector is twofold: First, we can consistently generalize the gradient to vector-valued functions $f : \mathbb { R } ^ { n }  \mathbb { R } ^ { m }$ (then the gradient becomes a matrix). Second, we can immediately apply the multi-variate chain rule without paying attention to the dimension of the gradient. We will discuss both points in Section 5.3. 

Example 5.7 (Gradient) 

For $f ( x _ { 1 } , x _ { 2 } ) = x _ { 1 } ^ { 2 } x _ { 2 } + x _ { 1 } x _ { 2 } ^ { 3 } \in \mathbb { R } ,$ the partial derivatives $( \mathrm { i . e . }$ , the derivatives of $f$ with respect to x<sub>1</sub> and $x _ { 2 } )$ are 

$$
\frac {\partial f (x _ {1} , x _ {2})}{\partial x _ {1}} = 2 x _ {1} x _ {2} + x _ {2} ^ {3}\tag{5.43}
$$

$$
\frac {\partial f (x _ {1} , x _ {2})}{\partial x _ {2}} = x _ {1} ^ {2} + 3 x _ {1} x _ {2} ^ {2}\tag{5.44}
$$

and the gradient is then 

$$
\frac {\mathrm{d} f}{\mathrm{d} \boldsymbol {x}} = \left[ \begin{array}{c c} \frac {\partial f (x _ {1} , x _ {2})}{\partial x _ {1}} & \frac {\partial f (x _ {1} , x _ {2})}{\partial x _ {2}} \end{array} \right] = \left[ \begin{array}{c c} 2 x _ {1} x _ {2} + x _ {2} ^ {3} & x _ {1} ^ {2} + 3 x _ {1} x _ {2} ^ {2} \end{array} \right] \in \mathbb {R} ^ {1 \times 2}.\tag{5.45}
$$

## 5.2.1 Basic Rules of Partial Differentiation

Product rule: 

In the multivariate case, where $\mathbf { x } \in \mathbb { R } ^ { n }$ , the basic differentiation rules that we know from school (e.g., sum rule, product rule, chain rule; see also Section 5.1.2) still apply. However, when we compute derivatives with respect to vectors $\pmb { x } \in \mathbb { R } ^ { n }$ we need to pay attention: Our gradients now involve vectors and matrices, and matrix multiplication is not commutative (Section 2.2.1), i.e., the order matters. 

$$
(f g) ^ {\prime} = f ^ {\prime} g + f g ^ {\prime},
$$

Sum rule: 

$$
(f + g) ^ {\prime} = f ^ {\prime} + g ^ {\prime},
$$

Chain rule: 

$$
(g (f)) ^ {\prime} = g ^ {\prime} (f) f ^ {\prime}
$$

Here are the general product rule, sum rule, and chain rule: 

$$
\text { Product   rule: } \quad \frac {\partial}{\partial \boldsymbol {x}} (f (\boldsymbol {x}) g (\boldsymbol {x})) = \frac {\partial f}{\partial \boldsymbol {x}} g (\boldsymbol {x}) + f (\boldsymbol {x}) \frac {\partial g}{\partial \boldsymbol {x}}\tag{5.46}
$$

$$
\text {   Sum   rule:   } \quad \frac {\partial}{\partial \boldsymbol {x}} (f (\boldsymbol {x}) + g (\boldsymbol {x})) = \frac {\partial f}{\partial \boldsymbol {x}} + \frac {\partial g}{\partial \boldsymbol {x}}\tag{5.47}
$$

©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 

Chain rule: 

$$
\frac {\partial}{\partial \boldsymbol {x}} (g \circ f) (\boldsymbol {x}) = \frac {\partial}{\partial \boldsymbol {x}} \bigl (g (f (\boldsymbol {x})) \bigr) = \frac {\partial g}{\partial f} \frac {\partial f}{\partial \boldsymbol {x}}\tag{5.48}
$$

This is only an intuition, but not mathematically correct since the partial derivative is not a fraction. 

Let us have a closer look at the chain rule. The chain rule (5.48) resembles to some degree the rules for matrix multiplication where we said that neighboring dimensions have to match for matrix multiplication to be defined; see Section 2.2.1. If we go from left to right, the chain rule exhibits similar properties: $\partial f$ shows up in the “denominator” of the first factor and in the “numerator” of the second factor. If we multiply the factors together, multiplication is defined, i.e., the dimensions of $\partial f$ match, and $\partial f$ “cancels”, such that $\partial g / \partial x$ remains. 

## 5.2.2 Chain Rule

Consider a function $f : \mathbb { R } ^ { 2 } $ R of two variables $x _ { 1 } , x _ { 2 }$ . Furthermore, $x _ { 1 } ( t )$ and $x _ { 2 } ( t )$ are themselves functions of t. To compute the gradient of $f$ with respect to $t ,$ we need to apply the chain rule (5.48) for multivariate functions as 

$$
\frac {\mathrm{d} f}{\mathrm{d} t} = \left[ \begin{array}{c c} \frac {\partial f}{\partial x _ {1}} & \frac {\partial f}{\partial x _ {2}} \end{array} \right] \left[ \begin{array}{c} \frac {\partial x _ {1} (t)}{\partial t} \\ \frac {\partial x _ {2} (t)}{\partial t} \end{array} \right] = \frac {\partial f}{\partial x _ {1}} \frac {\partial x _ {1}}{\partial t} + \frac {\partial f}{\partial x _ {2}} \frac {\partial x _ {2}}{\partial t},\tag{5.49}
$$

where d denotes the gradient and $\partial$ partial derivatives. 

## Example 5.8

Consider $f ( x _ { 1 } , x _ { 2 } ) = x _ { 1 } ^ { 2 } + 2 x _ { 2 }$ , where x = sin t and $x _ { 2 } = \cos t ,$ , then 

$$
\frac {\mathrm{d} f}{f} = \frac {\partial f}{f} \frac {\partial x _ {1}}{\partial x _ {1}} + \frac {\partial f}{f} \frac {\partial x _ {2}}{\partial x _ {2}}
$$

$$
\overline {{\mathrm{d} t}} - \overline {{\partial x _ {1}}} \overline {{\partial t}} + \overline {{\partial x _ {2}}} \overline {{\partial t}}\tag{5.50a}
$$

$$
= 2 \sin t \frac {\partial \sin t}{\partial t} + 2 \frac {\partial \cos t}{\partial t}\tag{5.50b}
$$

$$
= 2 \sin t \cos t - 2 \sin t = 2 \sin t (\cos t - 1)\tag{5.50c}
$$

is the corresponding derivative of $f$ with respect to t. 

If $f ( x _ { 1 } , x _ { 2 } )$ is a function of $x _ { 1 }$ and $x _ { 2 } ,$ , where $x _ { 1 } ( s , t )$ and $x _ { 2 } ( s , t )$ are themselves functions of two variables s and $t ,$ the chain rule yields the partial derivatives 

$$
\frac {\partial f}{\partial s} = \frac {\partial f}{\partial x _ {1}} \frac {\partial x _ {1}}{\partial s} + \frac {\partial f}{\partial x _ {2}} \frac {\partial x _ {2}}{\partial s},\tag{5.51}
$$

$$
\frac {\partial f}{\partial t} = \frac {\partial f}{\partial x _ {1}} \frac {\partial x _ {1}}{\partial t} + \frac {\partial f}{\partial x _ {2}} \frac {\partial x _ {2}}{\partial t},\tag{5.52}
$$

Draft (2024-01-15) of “Mathematics for Machine Learning”. Feedback: https://mml-book.com. 

## 5.3 Gradients of Vector-Valued Functions

and the gradient is obtained by the matrix multiplication 

$$
\frac {\mathrm{d} f}{\mathrm{d} (s , t)} = \frac {\partial f}{\partial \boldsymbol {x}} \frac {\partial \boldsymbol {x}}{\partial (s , t)} = \underbrace {\left[ \begin{array}{c c} \frac {\partial f}{\partial x _ {1}} & \frac {\partial f}{\partial x _ {2}} \end{array} \right]} _ {= \frac {\partial f}{\partial \boldsymbol {x}}} \underbrace {\left[ \begin{array}{c c} \frac {\partial x _ {1}}{\partial s} & \frac {\partial x _ {1}}{\partial t} \\ \frac {\partial x _ {2}}{\partial s} & \frac {\partial x _ {2}}{\partial t} \end{array} \right]} _ {= \frac {\partial \boldsymbol {x}}{\partial (s, t)}}.\tag{5.53}
$$

This compact way of writing the chain rule as a matrix multiplication only makes sense if the gradient is defined as a row vector. Otherwise, we will need to start transposing gradients for the matrix dimensions to match. This may still be straightforward as long as the gradient is a vector or a matrix; however, when the gradient becomes a tensor (we will discuss this in the following), the transpose is no longer a triviality. 

Remark (Verifying the Correctness of a Gradient Implementation). The definition of the partial derivatives as the limit of the corresponding difference quotient (see (5.39)) can be exploited when numerically checking the correctness of gradients in computer programs: When we compute gradients and implement them, we can use finite differences to numerically test our computation and implementation: We choose the value h to be small $( \mathsf { e } . \mathsf { g } . , h = 1 0 ^ { - 4 } )$ and compare the finite-difference approximation from (5.39) with our (analytic) implementation of the gradient. If the error is small, our gradient implementation is probably correct. “Small” could mean that $\sqrt { \frac { \sum _ { i } ( d h _ { i } - d f _ { i } ) ^ { 2 } } { \sum _ { i } ( d h _ { i } + d f _ { i } ) ^ { 2 } } } < 1 0 ^ { - 6 }$ , where $d h _ { i }$ is the finite-difference approximation and $d f _ { i }$ is the analytic gradient of $f$ with respect to the ith variable $x _ { i }$ $\diamondsuit$ 

## 5.3 Gradients of Vector-Valued Functions

Thus far, we discussed partial derivatives and gradients of functions $f ~ ;$ $\mathbb { R } ^ { n } \to$ R mapping to the real numbers. In the following, we will generalize the concept of the gradient to vector-valued functions (vector fields) $f$ : $\mathbb { R } ^ { n } \to \mathbb { R } ^ { m }$ , where $n \geqslant 1$ and $m > 1$ 

For a function $f : \mathbb { R } ^ { n }  \mathbb { R } ^ { m }$ and a vector $\pmb { x } = [ x _ { 1 } , \ldots , x _ { n } ] ^ { \top } \in \mathbb { R } ^ { n }$ , the corresponding vector of function values is given as 

$$
\boldsymbol {f} (\boldsymbol {x}) = \left[ \begin{array}{c} f _ {1} (\boldsymbol {x}) \\ \vdots \\ f _ {m} (\boldsymbol {x}) \end{array} \right] \in \mathbb {R} ^ {m}.\tag{5.54}
$$

Writing the vector-valued function in this way allows us to view a vectorvalued function $f : \mathbb { R } ^ { n }  \mathbb { R } ^ { m }$ as a vector of functions $[ f _ { 1 } , \ldots , f _ { m } ] ^ { \intercal }$ , $f _ { i } : \mathbb { R } ^ { n }  \mathbb { R }$ that map onto R. The differentiation rules for every $f _ { i }$ are exactly the ones we discussed in Section 5.2. 



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



Therefore, the partial derivative of a vector-valued function $f : \mathbb { R } ^ { n } $ $\mathbb { R } ^ { m }$ with respect to $x _ { i } \in \mathbb { R } , i = 1 , \dots n ,$ , is given as the vector 

$$
\frac {\partial \boldsymbol {f}}{\partial x _ {i}} = \left[ \begin{array}{c} \frac {\partial f _ {1}}{\partial x _ {i}} \\ \vdots \\ \frac {\partial f _ {m}}{\partial x _ {i}} \end{array} \right] = \left[ \begin{array}{c} \lim _ {h \to 0} \frac {f _ {1} (x _ {1} , \ldots , x _ {i - 1} , x _ {i} + h , x _ {i + 1} , \ldots x _ {n}) - f _ {1} (\boldsymbol {x})}{h} \\ \vdots \\ \lim _ {h \to 0} \frac {f _ {m} (x _ {1} , \ldots , x _ {i - 1} , x _ {i} + h , x _ {i + 1} , \ldots x _ {n}) - f _ {m} (\boldsymbol {x})}{h} \end{array} \right] \in \mathbb {R} ^ {m}.\tag{5.55}
$$

From (5.40), we know that the gradient of f with respect to a vector is the row vector of the partial derivatives. In (5.55), every partial derivative $\partial f / \partial x _ { i }$ is itself a column vector. Therefore, we obtain the gradient of $f$ : $\mathbb { R } ^ { n } \to \mathbb { R } ^ { m }$ with respect to x $\mathbf { \Psi } \in \mathbb { R } ^ { n }$ by collecting these partial derivatives: 

$$
\begin{array}{l} \frac {\mathrm{d} \boldsymbol {f} (\boldsymbol {x})}{\mathrm{d} \boldsymbol {x}} = \left[ \begin{array}{c c c} \boxed {\frac {\partial \boldsymbol {f} (\boldsymbol {x})}{\partial x _ {1}}} & \dots & \boxed {\frac {\partial \boldsymbol {f} (\boldsymbol {x})}{\partial x _ {n}}} \\ \hline \end{array} \right] \\ = \left[ \begin{array}{c c c} \boxed {\frac {\partial f _ {1} (\boldsymbol {x})}{\partial x _ {1}}} & \dots & \boxed {\frac {\partial f _ {1} (\boldsymbol {x})}{\partial x _ {n}}} \\ \vdots & & \vdots \\ \frac {\partial f _ {m} (\boldsymbol {x})}{\partial x _ {1}} & \dots & \boxed {\frac {\partial f _ {m} (\boldsymbol {x})}{\partial x _ {n}}} \end{array} \right] \in \mathbb {R} ^ {m \times n}. \end{array}\tag{5.56a}
$$

(5.56b) 

Definition 5.6 (Jacobian). The collection of all first-order partial derivatives of a vector-valued function $f : \mathbb { R } ^ { n }  \mathbb { R } ^ { m }$ is called the Jacobian. The Jacobian J is an $m \times n$ matrix, which we define and arrange as follows: 

(5.57) 

$$
\begin{array}{l} \boldsymbol {J} = \nabla_ {\boldsymbol {x}} \boldsymbol {f} = \frac {\mathrm{d} \boldsymbol {f} (\boldsymbol {x})}{\mathrm{d} \boldsymbol {x}} = \left[ \begin{array}{c c c} \frac {\partial \boldsymbol {f} (\boldsymbol {x})}{\partial x _ {1}} & \dots & \frac {\partial \boldsymbol {f} (\boldsymbol {x})}{\partial x _ {n}} \end{array} \right] \\ = \left[ \begin{array}{c c c} \frac {\partial f _ {1} (\boldsymbol {x})}{\partial x _ {1}} & \dots & \frac {\partial f _ {1} (\boldsymbol {x})}{\partial x _ {n}} \\ \vdots & & \vdots \\ \frac {\partial f _ {m} (\boldsymbol {x})}{\partial x _ {1}} & \dots & \frac {\partial f _ {m} (\boldsymbol {x})}{\partial x _ {n}} \end{array} \right], \\ \boldsymbol {x} = \left[ \begin{array}{c} x _ {1} \\ \vdots \\ x _ {n} \end{array} \right], J (i, j) = \frac {\partial f _ {i}}{\partial x _ {j}}. \end{array}\tag{5.58}
$$

(5.59) 

As a special case of (5.58), a function $f : \mathbb { R } ^ { n } \to \mathbb { R } ^ { 1 }$ , which maps a vector $\pmb { x } \in \mathbb { R } ^ { n }$ onto a scalar $\begin{array} { r } { ( \mathbf { e } . \mathbf { g } . , f ( \pmb { x } ) = \sum _ { i = 1 } ^ { n } x _ { i } ) } \end{array}$ , possesses a Jacobian that is a row vector (matrix of dimension $1 \times n )$ ; see (5.40). 

Remark. In this book, we use the numerator layout of the derivative, i.e., the derivative $\mathrm { d } f / \mathrm { d } x$ of $\pmb { f } \in \mathbb { R } ^ { m }$ with respect to $\pmb { x } \in \mathbb { R } ^ { n }$ is an $m \ \times$ n matrix, where the elements of $f$ define the rows and the elements of x define the columns of the corresponding Jacobian; see (5.58). There exists also the denominator layout, which is the transpose of the numerator layout. In this book, we will use the numerator layout. ◇ 

![image](<Images/05_Vector_Calculus_image_007.jpg>)



Figure 5.5 The determinant of the Jacobian of f can be used to compute the magnifier between the blue and orange area.


denominator layout 

We will see how the Jacobian is used in the change-of-variable method for probability distributions in Section 6.7. The amount of scaling due to the transformation of a variable is provided by the determinant. 

In Section 4.1, we saw that the determinant can be used to compute the area of a parallelogram. If we are given two vectors $ { b _ { 1 } } ~ = ~ [ 1 , 0 ] ^ { \top }$ ， $\pmb { b } _ { 2 } = [ 0 , 1 ] ^ { \top }$ as the sides of the unit square (blue; see Figure 5.5), the area of this square is 

$$
\left| \det \left(\left[ \begin{array}{c c} 1 & 0 \\ 0 & 1 \end{array} \right]\right) \right| = 1.\tag{5.60}
$$

If we take a parallelogram with the sides $\mathbf { { c } } _ { 1 } = [ - 2 , 1 ] ^ { \top } , \mathbf { { c } } _ { 2 } = [ 1 , 1 ] ^ { \top }$ (orange in Figure 5.5), its area is given as the absolute value of the determinant (see Section 4.1) 

$$
\left| \det \left(\left[ \begin{array}{c c} - 2 & 1 \\ 1 & 1 \end{array} \right]\right) \right| = | - 3 | = 3  ,\tag{5.61}
$$

i.e., the area of this is exactly three times the area of the unit square. We can find this scaling factor by finding a mapping that transforms the unit square into the other square. In linear algebra terms, we effectively perform a variable transformation from $( b _ { 1 } , b _ { 2 } )$ to $( c _ { 1 } , c _ { 2 } )$ . In our case, the mapping is linear and the absolute value of the determinant of this mapping gives us exactly the scaling factor we are looking for. 

We will describe two approaches to identify this mapping. First, we exploit that the mapping is linear so that we can use the tools from Chapter 2 to identify this mapping. Second, we will find the mapping using partial derivatives using the tools we have been discussing in this chapter. 

Approach 1 To get started with the linear algebra approach, we identify both $\{ b _ { 1 } , b _ { 2 } \}$ and $\{ c _ { 1 } , c _ { 2 } \}$ as bases of $\mathbb { R } ^ { 2 }$ (see Section 2.6.1 for a recap). What we effectively perform is a change of basis from $( b _ { 1 } , b _ { 2 } )$ to $( c _ { 1 } , c _ { 2 } )$ , and we are looking for the transformation matrix that implements the basis change. Using results from Section 2.7.2, we identify the desired basis change matrix as 

$$
\boldsymbol {J} = \left[ \begin{array}{c c} - 2 & 1 \\ 1 & 1 \end{array} \right],\tag{5.62}
$$

such that $J b _ { 1 } = c _ { 1 }$ and $J b _ { 2 } = c _ { 2 }$ . The absolute value of the determinant of $J ,$ , which yields the scaling factor we are looking for, is given as $| \mathrm { d e t } ( J ) | = 3 .$ , i.e., the area of the square spanned by $( c _ { 1 } , c _ { 2 } )$ is three times greater than the area spanned by $( b _ { 1 } , b _ { 2 } )$ 

Approach 2 The linear algebra approach works for linear transformations; for nonlinear transformations (which become relevant in Section 6.7), we follow a more general approach using partial derivatives. 

For this approach, we consider a function $f : \mathbb { R } ^ { 2 } \to \mathbb { R } ^ { 2 }$ that performs a variable transformation. In our example, f maps the coordinate representation of any vector $\pmb { x } \in \mathbb { R } ^ { 2 }$ with respect to $( b _ { 1 } , b _ { 2 } )$ onto the coordinate representation $\boldsymbol { y } \in \mathbb { R } ^ { 2 }$ with respect to $( c _ { 1 } , c _ { 2 } )$ . We want to identify the mapping so that we can compute how an area (or volume) changes when it is being transformed by $f .$ . For this, we need to find out how ${ \pmb f } ( { \pmb x } )$ changes if we modify x a bit. This question is exactly answered by the Jacobian matrix $\frac { \mathrm { d } f } { \mathrm { d } x } \in \mathbb { R } ^ { 2 \times 2 }$ . Since we can write 

$$
y _ {1} = - 2 x _ {1} + x _ {2}\tag{5.63}
$$

$$
y _ {2} = x _ {1} + x _ {2}\tag{5.64}
$$

we obtain the functional relationship between x and $^ { y , }$ which allows us to get the partial derivatives 

$$
\frac {\partial y _ {1}}{\partial x _ {1}} = - 2, \quad \frac {\partial y _ {1}}{\partial x _ {2}} = 1, \quad \frac {\partial y _ {2}}{\partial x _ {1}} = 1, \quad \frac {\partial y _ {2}}{\partial x _ {2}} = 1\tag{5.65}
$$

and compose the Jacobian as 

$$
\boldsymbol {J} = \left[ \begin{array}{c c} \frac {\partial y _ {1}}{\partial x _ {1}} & \frac {\partial y _ {1}}{\partial x _ {2}} \\ \frac {\partial y _ {2}}{\partial x _ {1}} & \frac {\partial y _ {2}}{\partial x _ {2}} \end{array} \right] = \left[ \begin{array}{c c} - 2 & 1 \\ 1 & 1 \end{array} \right].\tag{5.66}
$$

The Jacobian represents the coordinate transformation we are looking for. It is exact if the coordinate transformation is linear (as in our case), and (5.66) recovers exactly the basis change matrix in (5.62). If the coordinate transformation is nonlinear, the Jacobian approximates this nonlinear transformation locally with a linear one. The absolute value of the Jacobian determinant $| \mathrm { d e t } ( J ) |$ is the factor by which areas or volumes are scaled when coordinates are transformed. Our case yields $| \mathrm { d e t } ( J ) | = 3$ 

Figure 5.6 Dimensionality of (partial) derivatives. 

The Jacobian determinant and variable transformations will become relevant in Section 6.7 when we transform random variables and probability distributions. These transformations are extremely relevant in machine learning in the context of training deep neural networks using the reparametrization trick, also called infinite perturbation analysis. 

![image](<Images/05_Vector_Calculus_image_008.jpg>)


In this chapter, we encountered derivatives of functions. Figure 5.6 summarizes the dimensions of those derivatives. If $f : \mathbb { R } \to$ R the gradient is simply a scalar (top-left entry). For $f : \mathbb { R } ^ { D } $ R the gradient is a $1 \times D$ row vector (top-right entry). For $f : \mathbb { R } \to \mathbb { R } ^ { E }$ , the gradient is an $E \times 1$ column vector, and for $f : \mathbb { R } ^ { D }  \mathbb { R } ^ { E }$ the gradient is an $E \times D$ matrix. 

## Example 5.9 (Gradient of a Vector-Valued Function)

We are given 

$$
\boldsymbol {f} (\boldsymbol {x}) = \boldsymbol {A} \boldsymbol {x}, \quad \boldsymbol {f} (\boldsymbol {x}) \in \mathbb {R} ^ {M}, \quad \boldsymbol {A} \in \mathbb {R} ^ {M \times N}, \quad \boldsymbol {x} \in \mathbb {R} ^ {N}.
$$

To compute the gradient $\mathrm { d } f / \mathrm { d } x$ we first determine the dimension of $\mathrm { d } f / \mathrm { d } x \mathrm { : }$ Since $f : \mathbb { R } ^ { N } \to \mathbb { R } ^ { M }$ , it follows that $\mathrm { d } f / \mathrm { d } x \in \mathbb { R } ^ { M \times N }$ . Second, to compute the gradient we determine the partial derivatives of $f$ with respect to every $x _ { j }$ 

$$
f _ {i} (\boldsymbol {x}) = \sum_ {j = 1} ^ {N} A _ {i j} x _ {j} \implies \frac {\partial f _ {i}}{\partial x _ {j}} = A _ {i j}\tag{5.67}
$$

We collect the partial derivatives in the Jacobian and obtain the gradient 

$$
\frac {\mathrm{d} \boldsymbol {f}}{\mathrm{d} \boldsymbol {x}} = \left[ \begin{array}{c c c} \frac {\partial f _ {1}}{\partial x _ {1}} & \dots & \frac {\partial f _ {1}}{\partial x _ {N}} \\ \vdots & & \vdots \\ \frac {\partial f _ {M}}{\partial x _ {1}} & \dots & \frac {\partial f _ {M}}{\partial x _ {N}} \end{array} \right] = \left[ \begin{array}{c c c} A _ {1 1} & \dots & A _ {1 N} \\ \vdots & & \vdots \\ A _ {M 1} & \dots & A _ {M N} \end{array} \right] = \boldsymbol {A} \in \mathbb {R} ^ {M \times N}\tag{5.68}
$$

Example 5.10 (Chain Rule) 

Consider the function $h : \mathbb { R } \to \mathbb { R } , h ( t ) = ( f \circ g ) ( t )$ with 

$$
f: \mathbb {R} ^ {2} \to \mathbb {R}\tag{5.69}
$$

$$
g: \mathbb {R} \to \mathbb {R} ^ {2}\tag{5.70}
$$

$$
f (\pmb {x}) = \exp (x _ {1} x _ {2} ^ {2}),\tag{5.71}
$$

$$
\boldsymbol {x} = \left[ \begin{array}{c} x _ {1} \\ x _ {2} \end{array} \right] = g (t) = \left[ \begin{array}{c} t \cos t \\ t \sin t \end{array} \right]\tag{5.72}
$$

and compute the gradient of $h$ with respect to t. Since $f : \mathbb { R } ^ { 2 } \to \mathbb { I }$ and $g : \mathbb { R } \to \mathbb { R } ^ { 2 }$ we note that 

$$
\frac {\partial f}{\partial \boldsymbol {x}} \in \mathbb {R} ^ {1 \times 2}, \quad \frac {\partial g}{\partial t} \in \mathbb {R} ^ {2 \times 1}.\tag{5.73}
$$

The desired gradient is computed by applying the chain rule: 

$$
\frac {\mathrm{d} h}{\mathrm{d} t} = \frac {\partial f}{\partial \boldsymbol {x}} \frac {\partial \boldsymbol {x}}{\partial t} = \left[ \begin{array}{c c} \frac {\partial f}{\partial x _ {1}} & \frac {\partial f}{\partial x _ {2}} \end{array} \right] \left[ \begin{array}{c} \frac {\partial x _ {1}}{\partial t} \\ \frac {\partial x _ {2}}{\partial t} \end{array} \right]\tag{5.74a}
$$

$$
= \left[ \begin{array}{c c} \exp (x _ {1} x _ {2} ^ {2}) x _ {2} ^ {2} & 2 \exp (x _ {1} x _ {2} ^ {2}) x _ {1} x _ {2} \end{array} \right] \left[ \begin{array}{c} \cos t - t \sin t \\ \sin t + t \cos t \end{array} \right]\tag{5.74b}
$$

$$
= \exp (x _ {1} x _ {2} ^ {2}) \big (x _ {2} ^ {2} (\cos t - t \sin t) + 2 x _ {1} x _ {2} (\sin t + t \cos t) \big),\tag{5.74c}
$$

where $x _ { 1 } = t \cos t$ and $x _ { 2 } = t$ sin $t ;$ see (5.72). 



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



We will discuss this model in much more detail in Chapter 9 in the context of linear regression, where we need derivatives of the least-squares loss L with respect to the parameters θ. 

Example 5.11 (Gradient of a Least-Squares Loss in a Linear Model) Let us consider the linear model 

$$
\boldsymbol {y} = \boldsymbol {\Phi} \boldsymbol {\theta},\tag{5.75}
$$

where $\pmb { \theta } \in \mathbb { R } ^ { D }$ is a parameter vector, $\Phi \in \mathbb { R } ^ { N \times D }$ are input features and $\boldsymbol { y } \in \mathbb { R } ^ { N }$ are the corresponding observations. We define the functions 

$$
L (\boldsymbol {e}) := \left\| \boldsymbol {e} \right\| ^ {2},
$$

least-squares loss 

(5.76) 

$$
e (\boldsymbol {\theta}) := \boldsymbol {y} - \Phi \boldsymbol {\theta}.\tag{5.77}
$$

We seek $\frac { \partial L } { \partial \pmb { \theta } }$ , and we will use the chain rule for this purpose. L is called a least-squares loss function. 

Before we start our calculation, we determine the dimensionality of the gradient as 

$$
\frac {\partial L}{\partial \boldsymbol {\theta}} \in \mathbb {R} ^ {1 \times D}.\tag{5.78}
$$

The chain rule allows us to compute the gradient as 

$$
\frac {\partial L}{\partial \pmb {\theta}} = \frac {\partial L}{\partial \pmb {e}} \frac {\partial \pmb {e}}{\partial \pmb {\theta}},\tag{5.79}
$$

dLdtheta = np.einsum( ’n,nd’, dLde,dedtheta) 

where the dth element is given by 

$$
\frac {\partial L}{\partial \boldsymbol {\theta}} [ 1, d ] = \sum_ {n = 1} ^ {N} \frac {\partial L}{\partial \boldsymbol {e}} [ n ] \frac {\partial \boldsymbol {e}}{\partial \boldsymbol {\theta}} [ n, d ].\tag{5.80}
$$

We know that $\lVert e \rVert ^ { 2 } = e ^ { \top } e$ (see Section 3.2) and determine 

$$
\frac {\partial L}{\partial \boldsymbol {e}} = 2 \boldsymbol {e} ^ {\top} \in \mathbb {R} ^ {1 \times N}.\tag{5.81}
$$

Furthermore, we obtain 

$$
\frac {\partial e}{\partial \theta} = - \Phi \in \mathbb {R} ^ {N \times D},\tag{5.82}
$$

such that our desired derivative is 

$$
\frac {\partial L}{\partial \boldsymbol {\theta}} = - 2 \boldsymbol {e} ^ {\top} \boldsymbol {\Phi} \stackrel {(5. 7 7)} {=} - \underbrace {2 (\boldsymbol {y} ^ {\top} - \boldsymbol {\theta} ^ {\top} \boldsymbol {\Phi} ^ {\top})} _ {1 \times N} \underbrace {\boldsymbol {\Phi}} _ {N \times D} \in \mathbb {R} ^ {1 \times D}.\tag{5.83}
$$

Remark. We would have obtained the same result without using the chain rule by immediately looking at the function 

$$
L _ {2} (\boldsymbol {\theta}) := \left\| \boldsymbol {y} - \boldsymbol {\Phi} \boldsymbol {\theta} \right\| ^ {2} = \left(\boldsymbol {y} - \boldsymbol {\Phi} \boldsymbol {\theta}\right) ^ {\top} \left(\boldsymbol {y} - \boldsymbol {\Phi} \boldsymbol {\theta}\right).\tag{5.84}
$$

This approach is still practical for simple functions like $L _ { 2 }$ but becomes impractical for deep function compositions. ◇ 

## 5.4 Gradients of Matrices

![image](<Images/05_Vector_Calculus_image_009.jpg>)



Partial derivatives:


![image](<Images/05_Vector_Calculus_image_010.jpg>)



(a) Approach 1: We compute the partial derivative $\frac { \partial A } { \partial x _ { 1 } } , \frac { \partial A } { \partial x _ { 2 } } , \frac { \partial A } { \partial x _ { 3 } }$ , each of which is $\mathrm { ~ a ~ 4 ~ } \times \mathrm { ~ 2 ~ }$ matrix, and col late them in $\mathbb { 1 } \mathbb { a } \mathbb { 4 } \times 2 \mathbb { \times } 3$ tensor.


![image](<Images/05_Vector_Calculus_image_011.jpg>)


![image](<Images/05_Vector_Calculus_image_012.jpg>)



(b) Approach 2: We re-shape (flatten) $\pmb { A } \in \mathbb { R } ^ { 4 \times 2 }$ into a vector $\tilde { \boldsymbol { A } } \in \mathbb { R } ^ { 8 }$ . Then, we compute the gradient $\frac { \mathrm { d } \tilde { A } } { \mathrm { d } x } \in \mathbb { R } ^ { 8 \times 3 }$ We obtain the gradient tensor by re-shaping this gradient as illustrated above.


## 5.4 Gradients of Matrices

We will encounter situations where we need to take gradients of matrices with respect to vectors (or other matrices), which results in a multidimensional tensor. We can think of this tensor as a multidimensional array that 

Figure 5.7 Visualization of gradient computation of a matrix with respect to a vector. We are interested in computing the gradient of $\pmb { A } \in \mathbb { R } ^ { 4 \times 2 }$ with respect to a vector x $\in \mathbb { R } ^ { 3 }$ . We know that gradient $\frac { \mathrm { d } \boldsymbol { A } } { \mathrm { d } \boldsymbol { r } } \bar { \in } \mathrm { I R } ^ { 4 \times 2 \times 3 } .$ . We follow two equivalent approaches to arrive there: (a) collating partial derivatives into a Jacobian tensor; (b) flattening of the matrix into a vector, computing the Jacobian matrix, re-shaping into a Jacobian tensor. 

We can think of a tensor as a multidimensional array. 

collects partial derivatives. For example, if we compute the gradient of an $m \times n$ matrix A with respect to a $p \times q$ matrix $B ,$ , the resulting Jacobian would be $( m \times n ) \times ( p \times q )$ , i.e., a four-dimensional tensor $J ,$ whose entries are given as $J _ { i j k l } = \partial A _ { i j } / \partial B _ { k l }$ 

Since matrices represent linear mappings, we can exploit the fact that there is a vector-space isomorphism (linear, invertible mapping) between the space $\mathbb { R } ^ { m \times n }$ of $m \times n$ matrices and the space $\mathbb { R } ^ { m n }$ of mn vectors. Therefore, we can re-shape our matrices into vectors of lengths mn and $p q .$ , respectively. The gradient using these mn vectors results in a Jacobian of size $m n \times p q .$ . Figure 5.7 visualizes both approaches. In practical applications, it is often desirable to re-shape the matrix into a vector and continue working with this Jacobian matrix: The chain rule $_ { ( 5 . 4 8 ) }$ boils down to simple matrix multiplication, whereas in the case of a Jacobian tensor, we will need to pay more attention to what dimensions we need to sum out. 

Example 5.12 (Gradient of Vectors with Respect to Matrices) Let us consider the following example, where 

$$
\boldsymbol {f} = \boldsymbol {A} \boldsymbol {x}, \quad \boldsymbol {f} \in \mathbb {R} ^ {M}, \quad \boldsymbol {A} \in \mathbb {R} ^ {M \times N}, \quad \boldsymbol {x} \in \mathbb {R} ^ {N}\tag{5.85}
$$

and where we seek the gradient d $1 f / \mathrm { d } A$ . Let us start again by determining the dimension of the gradient as 

$$
\frac {\mathrm{d} \boldsymbol {f}}{\mathrm{d} \boldsymbol {A}} \in \mathbb {R} ^ {M \times (M \times N)}.\tag{5.86}
$$

By definition, the gradient is the collection of the partial derivatives: 

$$
\frac {\mathrm{d} \boldsymbol {f}}{\mathrm{d} \boldsymbol {A}} = \left[ \begin{array}{c} \frac {\partial f _ {1}}{\partial \boldsymbol {A}} \\ \vdots \\ \frac {\partial f _ {M}}{\partial \boldsymbol {A}} \end{array} \right], \quad \frac {\partial f _ {i}}{\partial \boldsymbol {A}} \in \mathbb {R} ^ {1 \times (M \times N)}.\tag{5.87}
$$

To compute the partial derivatives, it will be helpful to explicitly write out the matrix vector multiplication: 

$$
f _ {i} = \sum_ {j = 1} ^ {N} A _ {i j} x _ {j}, \quad i = 1, \dots , M,\tag{5.88}
$$

and the partial derivatives are then given as 

$$
\frac {\partial f _ {i}}{\partial A _ {i q}} = x _ {q}.\tag{5.89}
$$

This allows us to compute the partial derivatives of $f _ { i }$ with respect to a row of A, which is given as 

$$
\frac {\partial f _ {i}}{\partial A _ {i , :}} = \boldsymbol {x} ^ {\top} \in \mathbb {R} ^ {1 \times 1 \times N},\tag{5.90}
$$



Draft (2024-01-15) of “Mathematics for Machine Learning”. Feedback: https://mml-book.com. 



$$
\frac {\partial f _ {i}}{\partial A _ {k \neq i , :}} = \mathbf {0} ^ {\top} \in \mathbb {R} ^ {1 \times 1 \times N}\tag{5.91}
$$

where we have to pay attention to the correct dimensionality. Since $f _ { i }$ maps onto R and each row of A is of size $1 \times N$ , we obtain a $1 \times 1 \times N .$ sized tensor as the partial derivative of $f _ { i }$ with respect to a row of A. 

We stack the partial derivatives (5.91) and get the desired gradient in (5.87) via 

$$
\frac {\partial f _ {i}}{\partial \boldsymbol {A}} = \left[ \begin{array}{c} \boldsymbol {0} ^ {\top} \\ \vdots \\ \boldsymbol {0} ^ {\top} \\ \boldsymbol {x} ^ {\top} \\ \boldsymbol {0} ^ {\top} \\ \vdots \\ \boldsymbol {0} ^ {\top} \end{array} \right] \in \mathbb {R} ^ {1 \times (M \times N)}.\tag{5.92}
$$

Example 5.13 (Gradient of Matrices with Respect to Matrices) Consider a matrix $\pmb { R } \in \mathbb { R } ^ { M \times N }$ and $\pmb { f } : \mathbb { R } ^ { M \times N } \overset { \textstyle ^ { \cdot } } { \to } \mathbb { R } ^ { N \times N }$ with 

$$
\boldsymbol {f} (\boldsymbol {R}) = \boldsymbol {R} ^ {\top} \boldsymbol {R} =: \boldsymbol {K} \in \mathbb {R} ^ {N \times N},\tag{5.93}
$$

where we seek the gradient d $\scriptstyle K / \mathrm { d } R$ 

To solve this hard problem, let us first write down what we already know: The gradient has the dimensions 

$$
\frac {\mathrm{d} \boldsymbol {K}}{\mathrm{d} \boldsymbol {R}} \in \mathbb {R} ^ {(N \times N) \times (M \times N)},\tag{5.94}
$$

which is a tensor. Moreover, 

$$
\frac {\mathrm{d} K _ {p q}}{\mathrm{d} \boldsymbol {R}} \in \mathbb {R} ^ {1 \times M \times N}\tag{5.95}
$$

for $p , q = 1 , \ldots , N$ , where $K _ { p q }$ is the $( p , q )$ th entry of $K = f ( R )$ . Denoting the ith column of R by $\mathbf { \nabla } r _ { i } .$ every entry of $\kappa$ is given by the dot product of two columns of R, i.e., 

$$
K _ {p q} = \boldsymbol {r} _ {p} ^ {\top} \boldsymbol {r} _ {q} = \sum_ {m = 1} ^ {M} R _ {m p} R _ {m q}.\tag{5.96}
$$

When we now compute the partial derivative $\frac { \partial K _ { p q } } { \partial R _ { i j } }$ we obtain 

$$
\frac {\partial K _ {p q}}{\partial R _ {i j}} = \sum_ {m = 1} ^ {M} \frac {\partial}{\partial R _ {i j}} R _ {m p} R _ {m q} = \partial_ {p q i j},\tag{5.97}
$$



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



$$
\partial_ {p q i j} = \left\{ \begin{array}{l l} R _ {i q} & \text {if} j = p, p \neq q \\ R _ {i p} & \text {if} j = q, p \neq q \\ 2 R _ {i q} & \text {if} j = p, p = q \\ 0 & \text {otherwise} \end{array} \right..\tag{5.98}
$$

From (5.94), we know that the desired gradient has the dimension $( N \times$ $N ) \times ( M \times N )$ , and every single entry of this tensor is given by $\partial _ { p q i j }$ in (5.98), where $p , q , j = 1 , \ldots , N$ and $i = 1 , \ldots , M$ 

## 5.5 Useful Identities for Computing Gradients

In the following, we list some useful gradients that are frequently required in a machine learning context (Petersen and Pedersen, 2012). Here, we use $\operatorname { t r } ( \cdot )$ as the trace (see Definition 4.4), det( ) as the determinant (see Section 4.1) and $f ( \pmb { X } ) ^ { - 1 }$ as the inverse of $f ( X )$ , assuming it exists. 

$$
\frac {\partial}{\partial \boldsymbol {X}} \boldsymbol {f} (\boldsymbol {X}) ^ {\top} = \left(\frac {\partial \boldsymbol {f} (\boldsymbol {X})}{\partial \boldsymbol {X}}\right) ^ {\top}\tag{5.99}
$$

$$
\frac {\partial}{\partial \boldsymbol {X}} \operatorname{tr} (\boldsymbol {f} (\boldsymbol {X})) = \operatorname{tr} \left(\frac {\partial \boldsymbol {f} (\boldsymbol {X})}{\partial \boldsymbol {X}}\right)\tag{5.100}
$$

$$
\frac {\partial}{\partial \boldsymbol {X}} \det (\boldsymbol {f} (\boldsymbol {X})) = \det (\boldsymbol {f} (\boldsymbol {X})) \operatorname{tr} \left(\boldsymbol {f} (\boldsymbol {X}) ^ {- 1} \frac {\partial \boldsymbol {f} (\boldsymbol {X})}{\partial \boldsymbol {X}}\right)\tag{5.101}
$$

$$
\frac {\partial}{\partial \boldsymbol {X}} \boldsymbol {f} (\boldsymbol {X}) ^ {- 1} = - \boldsymbol {f} (\boldsymbol {X}) ^ {- 1} \frac {\partial \boldsymbol {f} (\boldsymbol {X})}{\partial \boldsymbol {X}} \boldsymbol {f} (\boldsymbol {X}) ^ {- 1}\tag{5.102}
$$

$$
\frac {\partial \boldsymbol {a} ^ {\top} \boldsymbol {X} ^ {- 1} \boldsymbol {b}}{\partial \boldsymbol {X}} = - (\boldsymbol {X} ^ {- 1}) ^ {\top} \boldsymbol {a b} ^ {\top} (\boldsymbol {X} ^ {- 1}) ^ {\top}\tag{5.103}
$$

$$
\frac {\partial \boldsymbol {x} ^ {\top} \boldsymbol {a}}{\partial \boldsymbol {x}} = \boldsymbol {a} ^ {\top}\tag{5.104}
$$

$$
\frac {\partial \boldsymbol {a} ^ {\top} \boldsymbol {x}}{\partial \boldsymbol {x}} = \boldsymbol {a} ^ {\top}\tag{5.105}
$$

$$
\frac {\partial \boldsymbol {a} ^ {\top} \boldsymbol {X} \boldsymbol {b}}{\partial \boldsymbol {X}} = \boldsymbol {a} \boldsymbol {b} ^ {\top}\tag{5.106}
$$

$$
\frac {\partial \boldsymbol {x} ^ {\top} \boldsymbol {B} \boldsymbol {x}}{\partial \boldsymbol {x}} = \boldsymbol {x} ^ {\top} (\boldsymbol {B} + \boldsymbol {B} ^ {\top})\tag{5.107}
$$

$$
\frac {\partial}{\partial \boldsymbol {s}} (\boldsymbol {x} - \boldsymbol {A} \boldsymbol {s}) ^ {\top} \boldsymbol {W} (\boldsymbol {x} - \boldsymbol {A} \boldsymbol {s}) = - 2 (\boldsymbol {x} - \boldsymbol {A} \boldsymbol {s}) ^ {\top} \boldsymbol {W} \boldsymbol {A}\tag{5.108}
$$

Remark. In this book, we only cover traces and transposes of matrices. However, we have seen that derivatives can be higher-dimensional tensors, in which case the usual trace and transpose are not defined. In these cases, the trace of a $D \times D \times E \times F$ tensor would be an $E \times F _ { - }$ dimensional matrix. This is a special case of a tensor contraction. Similarly, when we “transpose” a tensor, we mean swapping the first two dimensions. Specifically, in (5.99) through (5.102), we require tensor-related computations when we work with multivariate functions $f ( \cdot )$ and compute derivatives with respect to matrices (and choose not to vectorize them as discussed in Section 5.4). 

## 5.6 Backpropagation and Automatic Differentiation

In many machine learning applications, we find good model parameters by performing gradient descent (Section 7.1), which relies on the fact that we can compute the gradient of a learning objective with respect to the parameters of the model. For a given objective function, we can obtain the gradient with respect to the model parameters using calculus and applying the chain rule; see Section 5.2.2. We already had a taste in Section 5.3 when we looked at the gradient of a squared loss with respect to the parameters of a linear regression model. 

Consider the function 

$$
f (x) = \sqrt {x ^ {2} + \exp (x ^ {2})} + \cos \left(x ^ {2} + \exp (x ^ {2})\right).\tag{5.109}
$$

By application of the chain rule, and noting that differentiation is linear, we compute the gradient 

$$
\begin{array}{c} \frac {\mathrm{d} f}{\mathrm{d} x} = \frac {2 x + 2 x \exp (x ^ {2})}{2 \sqrt {x ^ {2} + \exp (x ^ {2})}} - \sin \left(x ^ {2} + \exp (x ^ {2})\right) \left(2 x + 2 x \exp (x ^ {2})\right) \\ = 2 x \left(\frac {1}{2 \sqrt {x ^ {2} + \exp (x ^ {2})}} - \sin \left(x ^ {2} + \exp (x ^ {2})\right)\right) \left(1 + \exp (x ^ {2})\right). \end{array}\tag{5.110}
$$

Writing out the gradient in this explicit way is often impractical since it often results in a very lengthy expression for a derivative. In practice, it means that, if we are not careful, the implementation of the gradient could be significantly more expensive than computing the function, which imposes unnecessary overhead. For training deep neural network models, the backpropagation algorithm (Kelley, 1960; Bryson, 1961; Dreyfus, 1962; Rumelhart et al., 1986) is an efficient way to compute the gradient of an error function with respect to the parameters of the model. 

## 5.6.1 Gradients in a Deep Network

An area where the chain rule is used to an extreme is deep learning, where the function value y is computed as a many-level function composition 

$$
\boldsymbol {y} = \left(f _ {K} \circ f _ {K - 1} \circ \dots \circ f _ {1}\right) (\boldsymbol {x}) = f _ {K} \left(f _ {K - 1} \left(\dots \left(f _ {1} (\boldsymbol {x})\right) \dots\right)\right),\tag{5.111}
$$

where x are the inputs $( \boldsymbol { \mathrm { e . g . } }$ , images), y are the observations (e.g., class labels), and every function $f _ { i } , i = 1 , \dots , K$ , possesses its own parameters. 

Figure 5.8 Forward pass in a multi-layer neural network to compute the loss L as a function of the inputs x and the parameters $A _ { i } , ~ b _ { i } .$ 

We discuss the case, where the activation functions are identical in each layer to unclutter notation. 

![image](<Images/05_Vector_Calculus_image_013.jpg>)


In neural networks with multiple layers, we have functions $f _ { i } ( { \pmb x } _ { i - 1 } ) =$ $\sigma ( A _ { i - 1 } { \pmb x } _ { i - 1 } + { \pmb b } _ { i - 1 } )$ in the ith layer. Here $\mathbf { \delta _ { x - 1 } }$ is the output of layer $i - 1$ and σ an activation function, such as the logistic sigmoid $\frac { 1 } { 1 + e ^ { - x } } .$ , tanh or a rectified linear unit (ReLU). In order to train these models, we require the gradient of a loss function L with respect to all model parameters $A _ { j } , b _ { j }$ for $j = 1 , \ldots , K$ . This also requires us to compute the gradient of L with respect to the inputs of each layer. For example, if we have inputs x and observations y and a network structure defined by 

$$
\boldsymbol {f} _ {i} := \sigma_ {i} (\boldsymbol {A} _ {i - 1} \boldsymbol {f} _ {i - 1} + \boldsymbol {b} _ {i - 1}), \quad i = 1, \ldots , K,\tag{5.112}
$$

(5.113) 

see also Figure 5.8 for a visualization, we may be interested in finding $A _ { j } , b _ { j }$ for $j = 0 , \ldots , K - 1$ , such that the squared loss 

$$
L (\pmb {\theta}) = \| \pmb {y} - \pmb {f} _ {K} (\pmb {\theta}, \pmb {x}) \| ^ {2}\tag{5.114}
$$

is minimized, where $\pmb \theta = \{ A _ { 0 } , \pmb b _ { 0 } , \dots , \pmb A _ { K - 1 } , \pmb b _ { K - 1 } \} ,$ 

To obtain the gradients with respect to the parameter set $\theta ,$ we require the partial derivatives of L with respect to the parameters $\pmb { \theta } _ { j } = \{ { \pmb { A } } _ { j } , { \pmb { b } } _ { j } \}$ of each layer $j = 0 , \ldots , K - 1$ . The chain rule allows us to determine the partial derivatives as 

A more in-depth discussion about gradients of neural networks can be found in Justin Domke’s lecture notes 

$$
\frac {\partial L}{\partial \pmb {\theta} _ {K - 1}} = \frac {\partial L}{\partial \pmb {f} _ {K}} \frac {\partial \pmb {f} _ {K}}{\partial \pmb {\theta} _ {K - 1}}\tag{5.115}
$$

https://tinyurl. com/yalcxgtv. 

$$
\frac {\partial L}{\partial \boldsymbol {\theta} _ {K - 2}} = \frac {\partial L}{\partial \boldsymbol {f} _ {K}} \boxed {\frac {\partial \boldsymbol {f} _ {K}}{\partial \boldsymbol {f} _ {K - 1}} \frac {\partial \boldsymbol {f} _ {K - 1}}{\partial \boldsymbol {\theta} _ {K - 2}}}\tag{5.116}
$$

$$
\frac {\partial L}{\partial \boldsymbol {\theta} _ {K - 3}} = \frac {\partial L}{\partial \boldsymbol {f} _ {K}} \frac {\partial \boldsymbol {f} _ {K}}{\partial \boldsymbol {f} _ {K - 1}} \boxed {\frac {\partial \boldsymbol {f} _ {K - 1}}{\partial \boldsymbol {f} _ {K - 2}} \frac {\partial \boldsymbol {f} _ {K - 2}}{\partial \boldsymbol {\theta} _ {K - 3}}}\tag{5.117}
$$

$$
\frac {\partial L}{\partial \boldsymbol {\theta} _ {i}} = \frac {\partial L}{\partial \boldsymbol {f} _ {K}} \frac {\partial \boldsymbol {f} _ {K}}{\partial \boldsymbol {f} _ {K - 1}} \dots \boxed {\frac {\partial \boldsymbol {f} _ {i + 2}}{\partial \boldsymbol {f} _ {i + 1}} \frac {\partial \boldsymbol {f} _ {i + 1}}{\partial \boldsymbol {\theta} _ {i}}}\tag{5.118}
$$

The orange terms are partial derivatives of the output of a layer with respect to its inputs, whereas the blue terms are partial derivatives of the output of a layer with respect to its parameters. Assuming, we have already computed the partial derivatives $\partial L / \partial \pmb { \theta } _ { i + 1 }$ , then most of the computation can be reused to compute $\partial L / \partial \pmb \theta _ { i }$ . The additional terms that we 

![image](<Images/05_Vector_Calculus_image_014.jpg>)



need to compute are indicated by the boxes. Figure 5.9 visualizes that the gradients are passed backward through the network.



Figure 5.9 Backward pass in a multi-layer neural network to compute the gradients of the loss function.



Figure 5.10 Simple graph illustrating the flow of data from x to y via some intermediate variables a, b.


## 5.6.2 Automatic Differentiation

It turns out that backpropagation is a special case of a general technique in numerical analysis called automatic differentiation. We can think of automatic differentation as a set of techniques to numerically (in contrast to symbolically) evaluate the exact (up to machine precision) gradient of a function by working with intermediate variables and applying the chain rule. Automatic differentiation applies a series of elementary arithmetic operations, e.g., addition and multiplication and elementary functions, e.g., sin, cos, exp, log. By applying the chain rule to these operations, the gradient of quite complicated functions can be computed automatically. Automatic differentiation applies to general computer programs and has forward and reverse modes. Baydin et al. (2018) give a great overview of automatic differentiation in machine learning. 

Figure 5.10 shows a simple graph representing the data flow from inputs x to outputs $y$ via some intermediate variables $a ,$ , b. If we were to compute the derivative dy/dx, we would apply the chain rule and obtain 

$$
{\frac {\mathrm{d} y}{\mathrm{d} x}} = {\frac {\mathrm{d} y}{\mathrm{d} b}} {\frac {\mathrm{d} b}{\mathrm{d} a}} {\frac {\mathrm{d} a}{\mathrm{d} x}}.\tag{5.119}
$$

Intuitively, the forward and reverse mode differ in the order of multiplication. Due to the associativity of matrix multiplication, we can choose between 

$$
{\frac {\mathrm{d} y}{\mathrm{d} x}} = \left({\frac {\mathrm{d} y}{\mathrm{d} b}} {\frac {\mathrm{d} b}{\mathrm{d} a}}\right) {\frac {\mathrm{d} a}{\mathrm{d} x}},\tag{5.120}
$$

$$
\frac {\mathrm{d} y}{\mathrm{d} x} = \frac {\mathrm{d} y}{\mathrm{d} b} \left(\frac {\mathrm{d} b}{\mathrm{d} a} \frac {\mathrm{d} a}{\mathrm{d} x}\right).\tag{5.121}
$$

Equation (5.120) would be the reverse mode because gradients are propagated backward through the graph, i.e., reverse to the data flow. Equation (5.121) would be the forward mode, where the gradients flow with the data from left to right through the graph. 

Automatic differentiation is different from symbolic differentiation and numerical approximations of the gradient, e.g., by using finite differences. 

In the following, we will focus on reverse mode automatic differentiation, which is backpropagation. In the context of neural networks, where the input dimensionality is often much higher than the dimensionality of the labels, the reverse mode is computationally significantly cheaper than the forward mode. Let us start with an instructive example. 

## Example 5.14

Consider the function 

$$
f (x) = \sqrt {x ^ {2} + \exp (x ^ {2})} + \cos \left(x ^ {2} + \exp (x ^ {2})\right)\tag{5.122}
$$

from (5.109). If we were to implement a function f on a computer, we would be able to save some computation by using intermediate variables: 

$$
a = x ^ {2},\tag{5.123}
$$

$$
b = \exp (a),\tag{5.124}
$$

$$
c = a + b,\tag{5.125}
$$

$$
d = \sqrt {c},\tag{5.126}
$$

$$
e = \cos (c),\tag{5.127}
$$

$$
f = d + e.\tag{5.128}
$$

Figure 5.11 Computation graph with inputs x, function values $f ,$ and intermediate variables a, b, c, d, e. 

![image](<Images/05_Vector_Calculus_image_015.jpg>)


This is the same kind of thinking process that occurs when applying the chain rule. Note that the preceding set of equations requires fewer operations than a direct implementation of the function $f ( x )$ as defined in (5.109). The corresponding computation graph in Figure 5.11 shows the flow of data and computations required to obtain the function value $f .$ 

The set of equations that include intermediate variables can be thought of as a computation graph, a representation that is widely used in implementations of neural network software libraries. We can directly compute the derivatives of the intermediate variables with respect to their corresponding inputs by recalling the definition of the derivative of elementary functions. We obtain the following: 

$$
\frac {\partial a}{\partial x} = 2 x\tag{5.129}
$$

$$
\frac {\partial b}{\partial a} = \exp (a)\tag{5.130}
$$



Draft (2024-01-15) of “Mathematics for Machine Learning”. Feedback: https://mml-book.com. 



$$
\frac {\partial c}{\partial a} = 1 = \frac {\partial c}{\partial b}\tag{5.131}
$$

$$
{\frac {\partial d}{\partial c}} = {\frac {1}{2 \sqrt {c}}}\tag{5.132}
$$

$$
\frac {\partial e}{\partial c} = - \sin (c)\tag{5.133}
$$

$$
{\frac {\partial f}{\partial d}} = 1 = {\frac {\partial f}{\partial e}}.\tag{5.134}
$$

By looking at the computation graph in Figure 5.11, we can compute $\partial f / \partial x$ by working backward from the output and obtain 

$$
{\frac {\partial f}{\partial c}} = {\frac {\partial f}{\partial d}} {\frac {\partial d}{\partial c}} + {\frac {\partial f}{\partial e}} {\frac {\partial e}{\partial c}}\tag{5.135}
$$

$$
\partial f \quad \partial f \partial c
$$

$$
\overline {{\partial b}} = \overline {{\partial c}} \overline {{\partial b}}\tag{5.136}
$$

$$
\frac {\partial f}{\partial a} = \frac {\partial f}{\partial b} \frac {\partial b}{\partial a} + \frac {\partial f}{\partial c} \frac {\partial c}{\partial a}\tag{5.137}
$$

$$
{\frac {\partial f}{\partial x}} = {\frac {\partial f}{\partial a}} {\frac {\partial a}{\partial x}}.\tag{5.138}
$$

Note that we implicitly applied the chain rule to obtain $\partial f / \partial x$ . By substituting the results of the derivatives of the elementary functions, we get 

$$
{\frac {\partial f}{\partial c}} = 1 \cdot {\frac {1}{2 {\sqrt {c}}}} + 1 \cdot (- \sin (c))\tag{5.139}
$$

$$
\frac {\partial f}{\partial b} = \frac {\partial f}{\partial c} \cdot 1\tag{5.140}
$$

$$
{\frac {\partial f}{\partial a}} = {\frac {\partial f}{\partial b}} \exp (a) + {\frac {\partial f}{\partial c}} \cdot 1\tag{5.141}
$$

$$
{\frac {\partial f}{\partial x}} = {\frac {\partial f}{\partial a}} \cdot 2 x.\tag{5.142}
$$

By thinking of each of the derivatives above as a variable, we observe that the computation required for calculating the derivative is of similar complexity as the computation of the function itself. This is quite counterintuitive since the mathematical expression for the derivative $\frac { \partial f } { \partial x } ~ ( 5 . 1 1 0 )$ is significantly more complicated than the mathematical expression of the function $f ( x )$ in (5.109). 

Automatic differentiation is a formalization of Example 5.14. Let $x _ { 1 } , \ldots , x _ { d }$ be the input variables to the function, $x _ { d + 1 } , \dots , x _ { D - 1 }$ be the intermediate variables, and $x _ { D }$ the output variable. Then the computation graph can be expressed as follows: 

$$
\text { For   } i = d + 1, \dots , D: \quad x _ {i} = g _ {i} (x _ {\mathrm{Pa} (x _ {i})}),\tag{5.143}
$$



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



where the $g _ { i } ( \cdot )$ are elementary functions and $x _ { \operatorname* { P a } ( x _ { i } ) }$ are the parent nodes of the variable $x _ { i }$ in the graph. Given a function defined in this way, we can use the chain rule to compute the derivative of the function in a stepby-step fashion. Recall that by definition $f = x _ { D }$ and hence 

$$
\frac {\partial f}{\partial x _ {D}} = 1.\tag{5.144}
$$

For other variables $x _ { i } ,$ we apply the chain rule 

$$
\frac {\partial f}{\partial x _ {i}} = \sum_ {x _ {j}: x _ {i} \in \mathrm{Pa} (x _ {j})} \frac {\partial f}{\partial x _ {j}} \frac {\partial x _ {j}}{\partial x _ {i}} = \sum_ {x _ {j}: x _ {i} \in \mathrm{Pa} (x _ {j})} \frac {\partial f}{\partial x _ {j}} \frac {\partial g _ {j}}{\partial x _ {i}},\tag{5.145}
$$

where $\mathrm { P a } ( x _ { j } )$ is the set of parent nodes of $x _ { j }$ in the computation graph. Equation (5.143) is the forward propagation of a function, whereas (5.145) is the backpropagation of the gradient through the computation graph. For neural network training, we backpropagate the error of the prediction with respect to the label. 

The automatic differentiation approach above works whenever we have a function that can be expressed as a computation graph, where the elementary functions are differentiable. In fact, the function may not even be a mathematical function but a computer program. However, not all computer programs can be automatically differentiated, e.g., if we cannot find differential elementary functions. Programming structures, such as for loops and if statements, require more care as well. 

## 5.7 Higher-Order Derivatives

So far, we have discussed gradients, i.e., first-order derivatives. Sometimes, we are interested in derivatives of higher order, e.g., when we want to use Newton’s Method for optimization, which requires second-order derivatives (Nocedal and Wright, 2006). In Section 5.1.1, we discussed the Taylor series to approximate functions using polynomials. In the multivariate case, we can do exactly the same. In the following, we will do exactly this. But let us start with some notation. 

Consider a function $f : \mathbb { R } ^ { 2 }  \mathbb { R }$ of two variables x, y. We use the following notation for higher-order partial derivatives (and for gradients): 

1 $\frac { \partial ^ { 2 } f } { \partial x ^ { 2 } }$ is the second partial derivative of f with respect to x. 

$\frac { \partial ^ { n } f } { \partial x ^ { n } }$ is the nth partial derivative of $f$ with respect to x. 

1 $\begin{array} { r } { \frac { \partial ^ { 2 } f } { \partial y \partial x } = \frac { \partial } { \partial y } \left( \frac { \partial f } { \partial x } \right) } \end{array}$ is the partial derivative obtained by first partial differentiating with respect to x and then with respect to $y .$ 

$\frac { \partial ^ { 2 } f } { \partial x \partial y }$ is the partial derivative obtained by first partial differentiating by y and then x. 

The Hessian is the collection of all second-order partial derivatives. 

Draft (2024-01-15) of “Mathematics for Machine Learning”. Feedback: https://mml-book.com. 

![image](<Images/05_Vector_Calculus_image_016.jpg>)



Figure 5.12 Linear approximation of a function. The original function $f$ is linearized at $x _ { 0 } = - 2$ using a first-order Taylor series expansion.



If $f ( x , y )$ is a twice (continuously) differentiable function, then


$$
\frac {\partial^ {2} f}{\partial x \partial y} = \frac {\partial^ {2} f}{\partial y \partial x},\tag{5.146}
$$

i. $\mathbf { . e . }$ , the order of differentiation does not matter, and the corresponding Hessian matrix 

$$
\boldsymbol {H} = \left[ \begin{array}{c c} \frac {\partial^ {2} f}{\partial x ^ {2}} & \frac {\partial^ {2} f}{\partial x \partial y} \\ \frac {\partial^ {2} f}{\partial x \partial y} & \frac {\partial^ {2} f}{\partial y ^ {2}} \end{array} \right]\tag{5.147}
$$

is symmetric. The Hessian is denoted as $\nabla _ { x , y } ^ { 2 } f ( x , y )$ . Generally, for $\mathbf { x } \in \mathbb { R } ^ { n }$ and $f : \mathbb { R } ^ { n }  \mathbb { R }$ , the Hessian is an $n \times n$ matrix. The Hessian measures the curvature of the function locally around $( x , y )$ 

Remark (Hessian of a Vector Field). If $f : \mathbb { R } ^ { n }  \mathbb { R } ^ { m }$ is a vector field, the Hessian is an $( m \times n \times n )$ )-tensor. $\diamondsuit$ 

## 5.8 Linearization and Multivariate Taylor Series

The gradient $\nabla f$ of a function f is often used for a locally linear approximation of $f$ around $\scriptstyle { \mathbf { x } _ { 0 } } \colon$ : 

$$
f (\boldsymbol {x}) \approx f (\boldsymbol {x} _ {0}) + (\nabla_ {\boldsymbol {x}} f) (\boldsymbol {x} _ {0}) (\boldsymbol {x} - \boldsymbol {x} _ {0}).\tag{5.148}
$$

Here $( \nabla _ { \pmb { x } } f ) ( \pmb { x } _ { 0 } )$ is the gradient of $f$ with respect to $^ { x , }$ evaluated at $\scriptstyle { \mathbf { \mathscr { x } } } _ { \mathrm { 0 } }$ Figure 5.12 illustrates the linear approximation of a function $f$ at an input $x _ { 0 }$ . The original function is approximated by a straight line. This approximation is locally accurate, but the farther we move away from $x _ { 0 }$ the worse the approximation gets. Equation (5.148) is a special case of a mul tivariate Taylor series expansion of $f$ at $\scriptstyle { \mathbf { x } } _ { 0 } .$ , where we consider only the first two terms. We discuss the more general case in the following, which will allow for better approximations. 

©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 

Figure 5.13 Visualizing outer products. Outer products of vectors increase the dimensionality of the array by 1 per term. (a) The outer product of two vectors results in a matrix; (b) the outer product of three vectors yields a third-order tensor. 

![image](<Images/05_Vector_Calculus_image_017.jpg>)



(a) Given a vector $\delta \in \mathbb { R } ^ { 4 }$ , we obtain the outer product $\delta ^ { 2 } : = \delta \otimes \delta = \delta \delta ^ { \top } \in$ $\mathbb { R } ^ { 4 \times 4 }$ as a matrix.


![image](<Images/05_Vector_Calculus_image_018.jpg>)



(b) An outer product $\delta ^ { 3 } : = \delta \otimes \delta \otimes \delta \in \mathbb { R } ^ { 4 \times 4 \times 4 }$ results in a third-order tensor (“three dimensional matrix”), i.e., an array with three indexes.


Definition 5.7 (Multivariate Taylor Series). We consider a function 

$$
f: \mathbb {R} ^ {D} \to \mathbb {R}\tag{5.149}
$$

$$
\boldsymbol {x} \mapsto f (\boldsymbol {x}), \quad \boldsymbol {x} \in \mathbb {R} ^ {D},\tag{5.150}
$$

that is smooth at $\scriptstyle { \pmb x } _ { 0 }$ . When we define the difference vector $\pmb { \delta } : = \pmb { x } - \pmb { x } _ { 0 }$ 44 the multivariate Taylor series of $f$ at $\scriptstyle \left( { \pmb x } _ { 0 } \right)$ is defined as 

$$
f (\boldsymbol {x}) = \sum_ {k = 0} ^ {\infty} \frac {D _ {\boldsymbol {x}} ^ {k} f (\boldsymbol {x} _ {0})}{k !} \boldsymbol {\delta} ^ {k},\tag{5.151}
$$

where $D _ { x } ^ { k } f ( { \pmb x } _ { 0 } )$ is the k-th (total) derivative of f with respect to ${ \mathbf { } } ^ { \mathbf { } } \mathbf { { \mathbf { { x } } } } ,$ evaluated at $\scriptstyle { \mathbf { { \mathit { x } } } } _ { 0 }$ 

Definition 5.8 (Taylor Polynomial). The Taylor polynomial of degree n of $f$ at $\scriptstyle { \pmb x } _ { 0 }$ contains the first $n + 1$ components of the series in (5.151) and is defined as 

$$
T _ {n} (\boldsymbol {x}) = \sum_ {k = 0} ^ {n} \frac {D _ {\boldsymbol {x}} ^ {k} f (\boldsymbol {x} _ {0})}{k !} \delta^ {k}.\tag{5.152}
$$

In (5.151) and (5.152), we used the slightly sloppy notation of $\delta ^ { k }$ which is not defined for vectors $\pmb { x } \in \mathbb { R } ^ { D } , D > 1$ , and $k > 1$ . Note that both $D _ { x } ^ { k } f$ and $\delta ^ { k }$ are k-th order tensors, i.e., k-dimensional arrays. The k times 

kth-order tensor $\delta ^ { k } \in \mathbb { R } ^ { \widehat { D \times D \times \ldots \times D } }$ is obtained as a k-fold outer product, denoted by , of the vector $\pmb { \delta } \in \mathbb { R } ^ { D }$ . For example, 

$$
\boldsymbol {\delta} ^ {2} := \boldsymbol {\delta} \otimes \boldsymbol {\delta} = \boldsymbol {\delta} \boldsymbol {\delta} ^ {\top}, \quad \boldsymbol {\delta} ^ {2} [ i, j ] = \delta [ i ] \delta [ j ]\tag{5.153}
$$

Draft (2024-01-15) of “Mathematics for Machine Learning”. Feedback: https://mml-book.com. 

5.8 Linearization and Multivariate Taylor Series 

$$
\boldsymbol {\delta} ^ {3} := \boldsymbol {\delta} \otimes \boldsymbol {\delta} \otimes \boldsymbol {\delta}, \quad \boldsymbol {\delta} ^ {3} [ i, j, k ] = \delta [ i ] \delta [ j ] \delta [ k ].\tag{5.154}
$$

Figure 5.13 visualizes two such outer products. In general, we obtain the terms 

$$
D _ {\boldsymbol {x}} ^ {k} f (\boldsymbol {x} _ {0}) \boldsymbol {\delta} ^ {k} = \sum_ {i _ {1} = 1} ^ {D} \dots \sum_ {i _ {k} = 1} ^ {D} D _ {\boldsymbol {x}} ^ {k} f (\boldsymbol {x} _ {0}) [ i _ {1}, \dots , i _ {k} ] \delta [ i _ {1} ] \dots \delta [ i _ {k} ]\tag{5.155}
$$

in the Taylor series, where $D _ { x } ^ { k } f ( x _ { 0 } ) \delta ^ { k }$ contains k-th order polynomials. Now that we defined the Taylor series for vector fields, let us explicitly write down the first terms $D _ { x } ^ { k } f ( x _ { 0 } ) \delta ^ { k }$ of the Taylor series expansion for $k = 0 , \ldots , 3$ and $\pmb { \delta } : = \pmb { x } - \pmb { x } _ { 0 } ;$ 

$$
k = 0: D _ {\boldsymbol {x}} ^ {0} f (\boldsymbol {x} _ {0}) \boldsymbol {\delta} ^ {0} = f (\boldsymbol {x} _ {0}) \in \mathbb {R}\tag{5.156}
$$

$$
k = 1: D _ {\boldsymbol {x}} ^ {1} f (\boldsymbol {x} _ {0}) \boldsymbol {\delta} ^ {1} = \underbrace {\nabla_ {\boldsymbol {x}} f (\boldsymbol {x} _ {0})} _ {1 \times D} \underbrace {\boldsymbol {\delta}} _ {D \times 1} = \sum_ {i = 1} ^ {D} \nabla_ {\boldsymbol {x}} f (\boldsymbol {x} _ {0}) [ i ] \delta [ i ] \in \mathbb {R}\tag{5.157}
$$

$$
k = 2: D _ {\boldsymbol {x}} ^ {2} f (\boldsymbol {x} _ {0}) \boldsymbol {\delta} ^ {2} = \operatorname{tr} \bigl (\underbrace {\boldsymbol {H} (\boldsymbol {x} _ {0})} _ {D \times D} \underbrace {\boldsymbol {\delta}} _ {D \times 1} \underbrace {\boldsymbol {\delta} ^ {\top}} _ {1 \times D} \bigr) = \boldsymbol {\delta} ^ {\top} \boldsymbol {H} (\boldsymbol {x} _ {0}) \boldsymbol {\delta}\tag{5.158}
$$

$$
= \sum_ {i = 1} ^ {D} \sum_ {j = 1} ^ {D} H [ i, j ] \delta [ i ] \delta [ j ] \in \mathbb {R}\tag{5.159}
$$

$$
k = 3: D _ {\boldsymbol {x}} ^ {3} f (\boldsymbol {x} _ {0}) \boldsymbol {\delta} ^ {3} = \sum_ {i = 1} ^ {D} \sum_ {j = 1} ^ {D} \sum_ {k = 1} ^ {D} D _ {x} ^ {3} f (\boldsymbol {x} _ {0}) [ i, j, k ] \delta [ i ] \delta [ j ] \delta [ k ] \in \mathbb {R}\tag{5.160}
$$

Here, ${ \pmb H } ( { \pmb x } _ { 0 } )$ is the Hessian of f evaluated at $\scriptstyle { \pmb x } _ { 0 }$ . 

Example 5.15 (Taylor Series Expansion of a Function with Two Variables) 

Consider the function 

$$
f (x, y) = x ^ {2} + 2 x y + y ^ {3}.\tag{5.161}
$$

We want to compute the Taylor series expansion of f at $( x _ { 0 } , y _ { 0 } ) = ( 1 , 2 )$ Before we start, let us discuss what to expect: The function in (5.161) is a polynomial of degree 3. We are looking for a Taylor series expansion, which itself is a linear combination of polynomials. Therefore, we do not expect the Taylor series expansion to contain terms of fourth or higher order to express a third-order polynomial. This means that it should be sufficient to determine the first four terms of (5.151) for an exact alternative representation of (5.161). 

To determine the Taylor series expansion, we start with the constant term and the first-order derivatives, which are given by 

$$
f (1, 2) = 1 3\tag{5.162}
$$



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 





Draft (2024-01-15) of “Mathematics for Machine Learning”. Feedback: https://mml-book.com. 



$$
\frac {\partial f}{\partial x} = 2 x + 2 y \implies \frac {\partial f}{\partial x} (1, 2) = 6\tag{5.163}
$$

$$
\frac {\partial f}{\partial y} = 2 x + 3 y ^ {2} \implies \frac {\partial f}{\partial y} (1, 2) = 1 4.\tag{5.164}
$$

Therefore, we obtain 

$$
D _ {x, y} ^ {1} f (1, 2) = \nabla_ {x, y} f (1, 2) = \left[ \begin{array}{c c} \frac {\partial f}{\partial x} (1, 2) & \frac {\partial f}{\partial y} (1, 2) \end{array} \right] = \left[ \begin{array}{c c} 6 & 1 4 \end{array} \right] \in \mathbb {R} ^ {1 \times 2}\tag{5.165}
$$

such that 

$$
\frac {D _ {x , y} ^ {1} f (1 , 2)}{1 !} \boldsymbol {\delta} = \left[ \begin{array}{c c} 6 & 1 4 \end{array} \right] \left[ \begin{array}{c} x - 1 \\ y - 2 \end{array} \right] = 6 (x - 1) + 1 4 (y - 2).\tag{5.166}
$$

Note that $D _ { x , y } ^ { 1 } f ( 1 , 2 ) \delta$ contains only linear terms, i.e., first-order polynomials. 

The second-order partial derivatives are given by 

$$
\frac {\partial^ {2} f}{\partial x ^ {2}} = 2 \implies \frac {\partial^ {2} f}{\partial x ^ {2}} (1, 2) = 2\tag{5.167}
$$

$$
\frac {\partial^ {2} f}{\partial y ^ {2}} = 6 y \implies \frac {\partial^ {2} f}{\partial y ^ {2}} (1, 2) = 1 2\tag{5.168}
$$

$$
\frac {\partial^ {2} f}{\partial y \partial x} = 2 \implies \frac {\partial^ {2} f}{\partial y \partial x} (1, 2) = 2\tag{5.169}
$$

$$
\frac {\partial^ {2} f}{\partial x \partial y} = 2 \implies \frac {\partial^ {2} f}{\partial x \partial y} (1, 2) = 2.\tag{5.170}
$$

When we collect the second-order partial derivatives, we obtain the Hessian 

$$
\boldsymbol {H} = \left[ \begin{array}{c c} \frac {\partial^ {2} f}{\partial x ^ {2}} & \frac {\partial^ {2} f}{\partial x \partial y} \\ \frac {\partial^ {2} f}{\partial y \partial x} & \frac {\partial^ {2} f}{\partial y ^ {2}} \end{array} \right] = \left[ \begin{array}{c c} 2 & 2 \\ 2 & 6 y \end{array} \right],\tag{5.171}
$$

such that 

$$
\boldsymbol {H} (1, 2) = \left[ \begin{array}{c c} 2 & 2 \\ 2 & 1 2 \end{array} \right] \in \mathbb {R} ^ {2 \times 2}.\tag{5.172}
$$

Therefore, the next term of the Taylor-series expansion is given by 

$$
\frac {D _ {x , y} ^ {2} f (1 , 2)}{2 !} \boldsymbol {\delta} ^ {2} = \frac {1}{2} \boldsymbol {\delta} ^ {\top} \boldsymbol {H} (1, 2) \boldsymbol {\delta}\tag{5.173a}
$$

$$
= \frac {1}{2} \left[ \begin{array}{c c} x - 1 & y - 2 \end{array} \right] \left[ \begin{array}{c c} 2 & 2 \\ 2 & 1 2 \end{array} \right] \left[ \begin{array}{c} x - 1 \\ y - 2 \end{array} \right]\tag{5.173b}
$$

$$
= (x - 1) ^ {2} + 2 (x - 1) (y - 2) + 6 (y - 2) ^ {2}.\tag{5.173c}
$$

Here, $D _ { x , y } ^ { 2 } f ( 1 , 2 ) \delta ^ { 2 }$ contains only quadratic terms, i.e., second-order polynomials. 

The third-order derivatives are obtained as 

$$
D _ {x, y} ^ {3} f = \left[ \begin{array}{c c} \frac {\partial \boldsymbol {H}}{\partial x} & \frac {\partial \boldsymbol {H}}{\partial y} \end{array} \right] \in \mathbb {R} ^ {2 \times 2 \times 2},\tag{5.174}
$$

$$
D _ {x, y} ^ {3} f [:,:, 1 ] = \frac {\partial \boldsymbol {H}}{\partial x} = \left[ \begin{array}{c c} \frac {\partial^ {3} f}{\partial x ^ {3}} & \frac {\partial^ {3} f}{\partial x ^ {2} \partial y} \\ \frac {\partial^ {3} f}{\partial x \partial y \partial x} & \frac {\partial^ {3} f}{\partial x \partial y ^ {2}} \end{array} \right],\tag{5.175}
$$

$$
D _ {x, y} ^ {3} f [:,:, 2 ] = \frac {\partial \pmb {H}}{\partial y} = \left[ \begin{array}{c c} \frac {\partial^ {3} f}{\partial y \partial x ^ {2}} & \frac {\partial^ {3} f}{\partial y \partial x \partial y} \\ \frac {\partial^ {3} f}{\partial y ^ {2} \partial x} & \frac {\partial^ {3} f}{\partial y ^ {3}} \end{array} \right].\tag{5.176}
$$

Since most second-order partial derivatives in the Hessian in (5.171) are constant, the only nonzero third-order partial derivative is 

$$
\frac {\partial^ {3} f}{\partial y ^ {3}} = 6 \implies \frac {\partial^ {3} f}{\partial y ^ {3}} (1, 2) = 6.\tag{5.177}
$$

Higher-order derivatives and the mixed derivatives of degree 3 (e.g., $\textstyle { \frac { \partial f ^ { 3 } } { \partial x ^ { 2 } \partial y } } )$ vanish, such that 

$$
D _ {x, y} ^ {3} f [:,:, 1 ] = \left[ \begin{array}{c c} 0 & 0 \\ 0 & 0 \end{array} \right], \quad D _ {x, y} ^ {3} f [:,:, 2 ] = \left[ \begin{array}{c c} 0 & 0 \\ 0 & 6 \end{array} \right]\tag{5.178}
$$

and 

$$
\frac {D _ {x , y} ^ {3} f (1 , 2)}{3 !} \delta^ {3} = (y - 2) ^ {3},\tag{5.179}
$$

which collects all cubic terms of the Taylor series. Overall, the (exact) Taylor series expansion of $f$ at $( x _ { 0 } , y _ { 0 } ) = ( 1 , 2 )$ is 

$$
f (x) = f (1, 2) + D _ {x, y} ^ {1} f (1, 2) \pmb {\delta} + \frac {D _ {x , y} ^ {2} f (1 , 2)}{2 !} \pmb {\delta} ^ {2} + \frac {D _ {x , y} ^ {3} f (1 , 2)}{3 !} \pmb {\delta} ^ {3}\tag{5.180a}
$$

$$
\begin{array}{l} = f (1, 2) + \frac {\partial f (1 , 2)}{\partial x} (x - 1) + \frac {\partial f (1 , 2)}{\partial y} (y - 2) \\ \quad + \frac {1}{2 !} \left(\frac {\partial^ {2} f (1 , 2)}{\partial x ^ {2}} (x - 1) ^ {2} + \frac {\partial^ {2} f (1 , 2)}{\partial y ^ {2}} (y - 2) ^ {2} \right. \\ \quad \left. + 2 \frac {\partial^ {2} f (1 , 2)}{\partial x \partial y} (x - 1) (y - 2)\right) + \frac {1}{6} \frac {\partial^ {3} f (1 , 2)}{\partial y ^ {3}} (y - 2) ^ {3} \\ = 1 3 + 6 (x - 1) + 1 4 (y - 2) \\ \quad + (x - 1) ^ {2} + 6 (y - 2) ^ {2} + 2 (x - 1) (y - 2) + (y - 2) ^ {3} \end{array}\tag{5.180b}
$$

(5.180c) 

In this case, we obtained an exact Taylor series expansion of the polynomial in (5.161), i.e., the polynomial in (5.180c) is identical to the original polynomial in (5.161). In this particular example, this result is not surprising since the original function was a third-order polynomial, which we expressed through a linear combination of constant terms, first-order, second-order, and third-order polynomials in (5.180c). 



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



## 5.9 Further Reading

Further details of matrix differentials, along with a short review of the required linear algebra, can be found in Magnus and Neudecker (2007). Automatic differentiation has had a long history, and we refer to Griewank and Walther (2003), Griewank and Walther (2008), and Elliott (2009) and the references therein. 

In machine learning (and other disciplines), we often need to compute expectations, i.e., we need to solve integrals of the form 

$$
\mathbb {E} _ {\boldsymbol {x}} [ f (\boldsymbol {x}) ] = \int f (\boldsymbol {x}) p (\boldsymbol {x}) d \boldsymbol {x}.\tag{5.181}
$$

Even if $p ( { \pmb x } )$ is in a convenient form (e.g., Gaussian), this integral generally cannot be solved analytically. The Taylor series expansion of f is one way of finding an approximate solution: Assuming $p ( { \pmb x } ) = \mathcal { N } ( { \pmb \mu } , { \pmb \Sigma } )$ is Gaussian, then the first-order Taylor series expansion around $\pmb { \mu }$ locally linearizes the nonlinear function $f .$ For linear functions, we can compute the mean (and the covariance) exactly if $p ( { \pmb x } )$ is Gaussian distributed (see Section 6.5). This property is heavily exploited by the extended Kalman filter (Maybeck, 1979) for online state estimation in nonlinear dynamical systems (also called “state-space models”). Other deterministic ways to approximate the integral in (5.181) are the unscented transform (Julier and Uhlmann, 1997), which does not require any gradients, or the Laplace approximation (MacKay, 2003; Bishop, 2006; Murphy, 2012), which uses a second-order Taylor series expansion (requiring the Hessian) for a local Gaussian approximation of $p ( { \pmb x } )$ around its mode. 

## Exercises

5.1 Compute the derivative $f ^ { \prime } ( x )$ for 

$$
f (x) = \log (x ^ {4}) \sin (x ^ {3}).
$$

5.2 Compute the derivative $f ^ { \prime } ( x )$ of the logistic sigmoid 

$$
f (x) = \frac {1}{1 + \exp (- x)}.
$$

5.3 Compute the derivative $f ^ { \prime } ( x )$ of the function 

$$
f (x) = \exp (- \frac {1}{2 \sigma^ {2}} (x - \mu) ^ {2}),
$$

where $\mu , \sigma \in \mathbb { R }$ are constants. 

5.4 Compute the Taylor polynomials $T _ { n } , n = 0 , \ldots , 5$ of $f ( x ) = \sin ( x ) + \cos ( x )$ at $x _ { 0 } = 0 .$ 

5.5 Consider the following functions: 

$$
f _ {1} (\boldsymbol {x}) = \sin (x _ {1}) \cos (x _ {2}), \quad \boldsymbol {x} \in \mathbb {R} ^ {2}
$$

$$
f _ {2} (\pmb {x}, \pmb {y}) = \pmb {x} ^ {\top} \pmb {y}, \quad \pmb {x}, \pmb {y} \in \mathbb {R} ^ {n}
$$

$$
f _ {3} (\pmb {x}) = \pmb {x x} ^ {\top}, \qquad \pmb {x} \in \mathbb {R} ^ {n}
$$

Draft (2024-01-15) of “Mathematics for Machine Learning”. Feedback: https://mml-book.com. 

a. What are the dimensions of $\begin{array} { r } { \frac { \partial f _ { i } } { \partial { \bf x } } ~ \vdots } \end{array}$ 

b. Compute the Jacobians. 

5.6 Differentiate f with respect to t and g with respect to X, where 

$$
\begin{array}{l l} f (\boldsymbol {t}) = \sin (\log (\boldsymbol {t} ^ {\top} \boldsymbol {t}))  , & t \in \mathbb {R} ^ {D} \\ g (\boldsymbol {X}) = \operatorname{tr} (\boldsymbol {A X B})  , & \boldsymbol {A} \in \mathbb {R} ^ {D \times E}, \boldsymbol {X} \in \mathbb {R} ^ {E \times F}, \boldsymbol {B} \in \mathbb {R} ^ {F \times D}  , \end{array}
$$

where $\operatorname { t r } ( \cdot )$ denotes the trace. 

Compute the derivatives $\mathrm { d } f / \mathrm { d } x$ of the following functions by using the chain rule. Provide the dimensions of every single partial derivative. Describe your steps in detail. 

a. 

$$
f (z) = \log (1 + z), \quad z = \boldsymbol {x} ^ {\top} \boldsymbol {x}, \quad \boldsymbol {x} \in \mathbb {R} ^ {D}
$$

b. 

$$
f (\boldsymbol {z}) = \sin (\boldsymbol {z}), \quad \boldsymbol {z} = \boldsymbol {A} \boldsymbol {x} + \boldsymbol {b}, \quad \boldsymbol {A} \in \mathbb {R} ^ {E \times D}, \boldsymbol {x} \in \mathbb {R} ^ {D}, \boldsymbol {b} \in \mathbb {R} ^ {E}
$$

where sin(·) is applied to every element of $_ { z , }$ 

5.8 Compute the derivatives $\mathrm { d } f / \mathrm { d } x$ of the following functions. Describe your steps in detail. 

a. Use the chain rule. Provide the dimensions of every single partial derivative. 

$$
\begin{array}{r l} & f (z) = \exp (- \frac {1}{2} z) \\ & \quad z = g (\pmb {y}) = \pmb {y} ^ {\top} \pmb {S} ^ {- 1} \pmb {y} \\ & \quad \pmb {y} = h (\pmb {x}) = \pmb {x} - \pmb {\mu} \end{array}
$$

where $\boldsymbol { \mathsf { s } } , \pmb { \mu } \in \mathbb { R } ^ { D } , \pmb { S } \in \mathbb { R } ^ { D \times D }$ 

b. 

$$
f (\boldsymbol {x}) = \operatorname{tr} \left(\boldsymbol {x} \boldsymbol {x} ^ {\top} + \sigma^ {2} \boldsymbol {I}\right), \quad \boldsymbol {x} \in \mathbb {R} ^ {D}
$$

Here $\operatorname { t r } ( A )$ is the trace of $A , \mathrm { i . e . }$ , the sum of the diagonal elements $A _ { i i }$ Hint: Explicitly write out the outer product. 

c. Use the chain rule. Provide the dimensions of every single partial derivative. You do not need to compute the product of the partial derivatives explicitly. 

$$
\begin{array}{l} \boldsymbol {f} = \tanh (\boldsymbol {z}) \in \mathbb {R} ^ {M} \\ \boldsymbol {z} = \boldsymbol {A x} + \boldsymbol {b}, \quad \boldsymbol {x} \in \mathbb {R} ^ {N}, \boldsymbol {A} \in \mathbb {R} ^ {M \times N}, \boldsymbol {b} \in \mathbb {R} ^ {M}. \end{array}
$$

Here, tanh is applied to every component of z. 

5.9 We define 

$$
\begin{array}{c} g (\boldsymbol {x}, \boldsymbol {z}, \boldsymbol {\nu}) := \log p (\boldsymbol {x}, \boldsymbol {z}) - \log q (\boldsymbol {z}, \boldsymbol {\nu}) \\ \boldsymbol {z} := t (\boldsymbol {\epsilon}, \boldsymbol {\nu}) \end{array}
$$

for differentiable functions $p , q , t$ and x $\in \mathbb { R } ^ { D } , z \in \mathbb { R } ^ { E } , \pmb { \nu } \in \mathbb { R } ^ { F } , \pmb { \epsilon } \in \mathbb { R } ^ { G }$ . By using the chain rule, compute the gradient 

$$
\frac {\mathrm{d}}{\mathrm{d} \pmb {\nu}} g (\pmb {x}, \pmb {z}, \pmb {\nu}).
$$



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 

