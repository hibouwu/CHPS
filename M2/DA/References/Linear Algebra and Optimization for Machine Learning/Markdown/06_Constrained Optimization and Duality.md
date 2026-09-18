# Chapter 6

# Constrained Optimization and Duality

“Virtuous people often revenge themselves for the constraints to which they submit by the boredom that they inspire.”– Confucius 

## 6.1 Introduction

In many machine learning settings, such as nonnegative regression and box regression, the optimization variables are constrained. Therefore, one needs to find an optimal solution only over the region of the optimization space that satisfies these constraints. This region is referred to as the feasible region in optimization parlance. The straightforward use of a gradient-descent procedure does not work, because an unconstrained step might move the optimization variables outside the feasible region of the optimization problem. In general, there are two approaches to addressing optimization constraints: 

1. Primal approach: In the primal approach, one attempts to modify gradient descent so as to stay within the feasible regions of the space. Many of the methods discussed in the previous chapters, such as gradient descent, coordinate descent, and Newton’s method, can be modified to stay within feasible regions of the space. 

2. Dual approach: The dual approach uses Lagrangian relaxation in order to create a new dual problem in which primal constraints are converted into dual variables. In many cases, the structure of the dual problem is simpler to solve. However, the dual problem is often constrained as well, and might require similar optimization methods (to the primal methods above) that can work with constraints. 

This chapter discusses both primal and the dual methods for constrained optimization. Some techniques like penalty methods incorporate aspects of both primal and dual methods. 

The complexity of an optimization problem depends on the structure of its constraints. Luckily, many machine learning applications involve two simple types of constraints: 

1. Linear and convex constraints: Linear constraints are of the form $F ( { \overline { { w } } } ) \leq b$ or of the form $G ( { \overline { { w } } } ) = c ,$ where $F ( \overline { { w } } )$ and $G ( \overline { { w } } )$ are linear functions. A more general type of constraint is the convex constraint of the form $H ( \overline { { w } } ) \leq d ,$ where $H ( \overline { { w } } )$ is convex. 

2. Norm constraints: Many machine learning problems are norm constrained, where we wish to minimize or maximize $F ( \overline { { w } } )$ subject to the constraint that $\| \overline { { w } } \| ^ { 2 } = 1$ . This problem arises in spectral clustering and principal component analysis. 

This chapter is organized as follows. The next section will introduce constrained methods for (primal) gradient descent. Methods for coordinate descent are discussed in Section 6.3. The approach of Lagrangian relaxation is introduced in Section 6.4. Penalty methods are discussed in Section 6.5. Methods for norm-constrained optimization are discussed in Section 6.6. A discussion of the relative advantages of primal and dual methods is provided in Section 6.7. A summary is given in Section 6.8. 

## 6.2 Primal Gradient Descent Methods

The projected gradient-descent method is also referred to as the feasible direction method. Such methods either make steps along a projection of the gradient-descent direction (that retains feasibility), or they immediately “repair” a movement outside the feasible space to a feasible solution. In its most basic form, an unconstrained steepest-descent update is first performed. However, such an update might move the current optimization variables outside the feasible space. At this point, one projects the parameter vector to the closest point in the feasible space. A key point is that this sequence of two steps works well, as long as the optimization problem has the following convex structure: 

Definition 6.2.1 (Convex Objective Function Over a Convex Set) The problem of minimizing a convex objective function over a convex set is defined as follows: 

$$
\text { Minimize } F (\overline {{w}})
$$

subject to: 

$$
\overline {{w}} \in C
$$

Here, $F ( \overline { { w } } )$ is a convex function, and C is a convex set. 

The above definition is the most general form of this type of optimization problem. However, there are many special cases of the set C that arise commonly in machine learning: 

1. Linear constraints: The set C is the intersection of linear constraints of the form $f _ { i } ( \overline { { w } } ) \leq 0$ or of the form $f _ { i } ( \overline { { w } } ) = 0$ . The value of i can range from $1 \ldots m$ . Here, each $f _ { i } ( \overline { { w } } )$ is a linear function. Note that an equality constraint can be expressed as the intersection of two linear inequality constraints $f _ { i } ( \overline { { w } } ) \leq 0$ and $- f _ { i } ( \overline { { w } } ) \leq 0$ . Therefore, inequality constraints are more general than equality constraints, although inequality constraints create a more challenging optimization problem. 

2. Convex constraints: The set C is the intersection of convex constraints of the form $f _ { i } ( \overline { { w } } ) \leq 0$ , where $i \in \{ 1 \ldots m \}$ . Here, each $f _ { i } ( \overline { { w } } )$ is a convex function (including the possibility of a linear function). 

We will present a general algorithm for the feasible direction method, and then present its simplifications in special cases. For the general optimization formulation of Definition 6.2.1, the feasible direction method repeats the following two steps iteratively: 

1. At the current parameter vector $\overline { { w } }$ perform the following steepest-descent update: 

$$
\overline {{w}} \Leftarrow \overline {{w}} - \alpha \nabla F (\overline {{w}})
$$

Here, $\alpha > 0$ is the step-size. This step might move $\overline { { w } }$ outside the feasible set $C .$ 

![image](<Images/06_Constrained_Optimization_and_Duality_image_001.jpg>)



Figure 6.1: The projected gradient-descent method. Steepest descent first moves outside the feasible region and then projects back to nearest point inside feasible region


2. Project w onto its nearest point in the set C. This projection can be expressed as an optimization problem of the following form: 

$$
\overline {{w}} \Leftarrow \operatorname{argmin} _ {\overline {{v}} \in C} \left\| \overline {{w}} - \overline {{v}} \right\| ^ {2}
$$

This step is required only when the first step moves w outside the feasible region. 

These two steps are iterated to convergence. When the set C is convex and the objective function $F ( \overline { { w } } )$ is convex, this approach can be shown to converge to an optimal solution. Note that the second step is itself an optimization problem, albeit with a simpler structure. The projected gradient descent method is pictorially illustrated in Figure 6.1. 

## 6.2.1 Linear Equality Constraints

Certain types of optimization problems with linear constraints arise frequently in machine learning. A common example is that of quadratic programming, in which the objective function contains quadratic and linear terms of the form $\overline { { w } } ^ { T } Q \overline { { w } } + \overline { { c } } ^ { T } \overline { { w } }$ and the constraints are linear. Here, w is a d-dimensional parameter vector, c is a d-dimensional column vector, and Q is a $d \times$ d matrix. When the objective function is linear, the resulting formulation is referred to as linear programming. 

Linear equality constraints can be considered almost equivalent to the unconstrained version of the problem, because one can eliminate the variables of an equality-constrained problem in order to create an unconstrained objective function. This type of elimination cannot be achieved in inequality constrained problems. In general, equality constraints in optimization problems are simpler to address than are inequality constraints (whether the constraints are linear or not). This is because equality constraints always allow the possibility of eliminating some subsets of the variables and constraints. 

Observation 6.2.1 One can use Gaussian elimination to convert a linear-equalityconstrained optimization problem into an unconstrained form by eliminating a subset of the variables and constraints from the optimization problem. 

In order to understand this point, consider the case in which we wish to minimize the objective function $x ^ { 2 } + y ^ { 2 }$ subject to the constraint $x + y = 1$ . In this case, we substitute $y = 1 - x$ , and drop both y and the constraint to create the following unconstrained objective function: 

![image](<Images/06_Constrained_Optimization_and_Duality_image_002.jpg>)



Figure 6.2: Projected gradient descent with different types of linear constraints


$$
J = x ^ {2} + (1 - x) ^ {2}
$$

It is easy to verify that the optimal value of $x$ is $1 / 2$ . When we have a larger number of constraints, it is necessary to use row reduction in order to create row echelon form. Subsequently, one can express the variables for which leading non-zero entries exist in the row-reduced form of A in terms of all the remaining free variables (for which leading non-zero entries do not exist). As a result, an unconstrained objective function can be expressed only in terms of the free variables. An example of this type of elimination is shown in Section 2.5.4 of Chapter 2. Subsequently, one can use simple gradient descent on the unconstrained objective in order to solve the optimization problem 

In spite of the possibility of eliminating a subset of the variables (and the constraints) using Gaussian elimination, one can also use projected gradient descent with equality con straints. An example of a 2-dimensional hyperplane space in three dimensions is shown in Figure 6.2. Note that one need not separate out the two iterative steps of steepest direction movement and projection in this special case. Rather, the gradient can be directly projected onto the linear hyperplane in order to perform the descent. The corresponding projection of the steepest-descent direction on the 2-dimensional hyperplane is illustrated in Figure 6.2. 

It is helpful to work out what the steepest-descent direction means in algebraic terms. Consider a situation where one is minimizing $F ( \overline { { w } } )$ subject to the constraint system $A { \overline { { w } } } = { \overline { { b } } }$ Here, w is a d-dimensional column vector, and A is an $m \times d$ matrix with $m \leq d .$ . Therefore, the vector $\bar { b }$ is m-dimensional. Note that it is important for $m \ \leq \ d .$ , or else the set of constraints might be infeasible. For simplicity, we will assume that the rows of A are linearly independent. 

Consider the situation where the current parameter vector $\overline { { w } } = \overline { { w } } _ { t }$ . Assume that $\overline { { w } } _ { t }$ is already feasible and therefore it satisfies the constraints $A { \overline { { w } } } _ { t } = { \bar { b } }$ of the optimization problem. Then, the current steepest-descent direction is given by $\overline { { g } } _ { t } = \nabla F ( \overline { { w } } _ { t } )$ . Note that if $A \overline { { g } } _ { t } \neq \overline { { 0 } }$ , then the point $\overline { { w } } _ { t } - \alpha \overline { { g } } _ { i }$ will no longer be feasible. This is because we will have $A [ \overline { { w } } _ { t } - \alpha \overline { { g } } _ { t } ] = \bar { b } - \alpha A \overline { { g } } _ { t } \neq \bar { b }$ . This situation is shown in Figure 6.2, where the steepest-descent direction moves of the feasible hyperplane. 

Therefore, in order for the steepest-descent step to stay feasible, the vector $\overline { { g } } _ { t }$ needs to be projected onto the hyperplane $A \overline { { w } } = \overline { { 0 } }$ , so that the projected vector $\overline { { g } } _ { t } ^ { \prime }$ satisfies $A \overline { { g } } _ { t } ^ { \prime } = 0$ In other words, projected steepest descent needs to project $\overline { { g } } _ { t }$ onto the right null space of A. 

This is achieved by expressing $\overline { { g } } _ { t } = \overline { { g } } _ { \parallel } + \overline { { g } } _ { \perp }$ in terms of the portion $\overline { { g } } _ { \parallel }$ lying in the subspace corresponding to the rows of A and the portion $\overline { { g } } _ { \perp }$ in its orthogonal complementary subspace (cf. Definition 2.3.10 of Chapter 2). Note that it is the portion $\overline { { g } } _ { \perp }$ that lies on $A { \overline { { w } } } = { \overline { { 0 } } }$ . An example of a projected vector $\overline { { g } } _ { t } ^ { \prime } = \overline { { g } } _ { \perp }$ is shown in Figure 6.2. Note that the notation refers to the fact that the vector $\overline { { g } } _ { \perp }$ is perpendicular to the subspace defined by the rows of $A ,$ , even though such a vector is actually parallel to the hyperplane $A { \overline { { w } } } = { \overline { { 0 } } }$ . We mention this point because the reader might find it confusing to see a vector parallel to the hyperplane being annotated by $^ { 6 6 } \bot , ^ { 9 9 }$ Here, it is important to note that even though the vector is parallel to the hyperplane $A { \overline { { w } } } = { \bar { b } } ,$ it needs to lie in the orthogonal complementary subspace of the rows of A to do so. In general, the coordinates w of all points on the hyperplane $A \overline { { w } } = \overline { { 0 } }$ form a vector space orthogonal to the rows of A. Therefore, the notation $^ { 6 } \perp ^ { 5 }$ refer to the linear algebra concept of orthogonal complementary subspace, rather than the more intuitive or geometric concept of being parallel to a hyperplane. Therefore, we need to subtract the component $\overline { { g } } _ { \parallel }$ from $\overline { { g } } _ { t }$ that lies in the span of the rows of A. The simplest approach is to use the row-wise<sup>1</sup> projection matrix discussed in Equation 2.17 of Chapter 2, although this result assumes that the rows of A are linearly independent (i.e., no redundant constraints). In other words, one can simply express $\overline { { g } } _ { t } ^ { \prime }$ in closed form as follows: 

$$
\overline {{g}} _ {t} ^ {\prime} = \overline {{g}} _ {t} - \overline {{g}} _ {\parallel} = [ I - A ^ {T} (A A ^ {T}) ^ {- 1} A ] \overline {{g}} _ {t}\tag{6.1}
$$

In cases when the rows of A are not linearly independent, the computation of $\overline { { g } } _ { t } ^ { \prime } = \overline { { g } } _ { \perp }$ can also be achieved easily by Gram-Schmidt orthogonalization (cf. Section 2.7.1 of Chapter 2) of the m rows of A to create $r < m$ orthonormal vectors $\overline { { v } } _ { 1 } \ldots \overline { { v } } _ { r }$ . Then, $\overline { { g } } _ { \perp }$ can be computed as follows: 

$$
\begin{array}{l} \overline {{g}} _ {\parallel} = \sum_ {i = 1} ^ {r} \left[ \overline {{g}} _ {t} \cdot \overline {{v}} _ {i} \right] \overline {{v}} _ {i} \\ \overline {{g}} _ {\perp} = \overline {{g}} _ {t} - \overline {{g}} _ {\parallel} \end{array}
$$

Subsequently, the iterative projected gradient descent steps can be written as follows: 

1. Compute $\overline { { g } } _ { t } = \nabla F ( \overline { { w } } _ { t } )$ and compute $\overline { { g } } _ { \perp }$ from $\overline { { g } } _ { t }$ as discussed above. 

2. Update $\overline { { w } } _ { t + 1 } \Leftarrow \overline { { w } } _ { t } - \alpha \overline { { g } } _ { \perp }$ and increment t by 1. 

The above two steps are repeated to convergence. The procedure can be initialized with any feasible value of the vector $\overline { { w } } = \overline { { w } } _ { 0 }$ . The initial feasible value can be found by solving the system of equations $A { \overline { { w } } } = { \overline { { b } } }$ using any of the methods discussed in Chapter 2. 

Problem 6.2.1 Suppose that you use line search to determine the step-size α in each iteration for projected gradient descent in convex functions and linear equality constraints. Show that successive directions of projected descent are always orthogonal to one another. 

## 6.2.1.1 Convex Quadratic Program with Equality Constraints

We have already addressed the problem of unconstrained quadratic programming in Section 4.6.2.1 of Chapter 4. In this section, we will discuss quadratic programming with equality constraints. The quadratic programming problem is defined as follows: 

$$
\begin{array}{c} \text {Minimize} J (\overline {{w}}) = \frac {1}{2} \overline {{w}} ^ {T} Q \overline {{w}} + \overline {{p}} ^ {T} \overline {{w}} + q \\ \text {subject to:} \\ A \overline {{w}} = \overline {{b}} \end{array}
$$

Here, $Q$ is a $d \times d$ positive definite matrix, $\overline { { p } }$ and $\overline { { w } }$ are d-dimensional column vectors, and $q$ is a scalar. This objective function is strictly convex, since it has a positive-definite Hessian $Q$ everywhere. For simplicity in discussion, we assume that the matrix A has linearly independent rows. Therefore, A is an $m \times d$ matrix with $m \leq d .$ , and the vector $\bar { b }$ is m dimensional. 

We already know from Section 4.6.2.1 that unconstrained quadratic programs with positive definite Hessians have closed-form solutions. Since equality constraints can always be eliminated with the Gaussian method, it stands to reason that one should be able to find a closed-form solution in this case as well. After all, the projection of a strictly convex function on a linear hyperplane $A { \overline { { w } } } = { \overline { { b } } }$ will continue to be strictly convex as well, and therefore we should be able to find a closed form solution in this case. However, to achieve this goal, we need to use a variable transformation so that the objective function contains linearly separable variables (cf. Section 3.4.4 of Chapter 3). This process is similar to that of converting a univariate quadratic function into vertex form. First we express $Q = P \Delta P ^ { T } ;$ where $\Delta$ is a diagonal matrix with strictly positive entries. Therefore, both the matrix $\sqrt { \Delta }$ and $\Delta ^ { - 1 / 2 }$ can be defined. The objective function can be rewritten as follows: 

$$
\begin{array}{l} J (\overline {{w}}) = \frac {1}{2} \overline {{w}} ^ {T} Q \overline {{w}} + \overline {{p}} ^ {T} \overline {{w}} + q \\ \qquad = \frac {1}{2} \overline {{w}} ^ {T} [ P \Delta P ^ {T} ] \overline {{w}} + \overline {{p}} ^ {T} \overline {{w}} + q \\ \qquad = \frac {1}{2} \| \sqrt {\Delta} P ^ {T} \overline {{w}} + \Delta^ {- 1 / 2} P ^ {T} \overline {{p}} \| ^ {2} + [ q - \frac {1}{2} \overline {{p}} ^ {T} \underbrace {[ P \Delta^ {- 1} P ^ {T} ]} _ {Q ^ {- 1}} \overline {{p}} ] \end{array}
$$

Note that the modified constant term is defined by $\begin{array} { r } { q ^ { \prime } = q - \frac { 1 } { 2 } \overline { { p } } ^ { T } [ P \Delta ^ { - 1 } P ^ { T } ] \overline { { p } } } \end{array}$ . In order to solve the problem, we make the following variable transformation: 

$$
\overline {{w}} ^ {\prime} = \sqrt {\Delta} P ^ {T} \overline {{w}} + \Delta^ {- 1 / 2} P ^ {T} \overline {{p}}\tag{6.2}
$$

This variable transformation is invertible, since we can express $\overline { { w } }$ in terms of $\overline { { w } } ^ { \prime }$ as well by left-multiplying both sides with $P \Delta ^ { - 1 / 2 }$ 

$$
\begin{array}{r} P \Delta^ {- 1 / 2} \overline {{w}} ^ {\prime} = \overline {{w}} + P \Delta^ {- 1} P ^ {T} \overline {{p}} \\ = \overline {{w}} + Q ^ {- 1} \overline {{p}} \end{array}
$$

In other words, $\overline { { w } }$ can be expressed in terms of $\overline { { w } } ^ { \prime }$ as follows: 

$$
\overline {{w}} = P \Delta^ {- 1 / 2} \overline {{w}} ^ {\prime} - Q ^ {- 1} \overline {{p}}\tag{6.3}
$$

The linear constraints $A { \overline { { w } } } = { \overline { { b } } }$ can be expressed in terms of the new variables $\overline { { w } } ^ { \prime }$ as follows: 

$$
\begin{array}{l} A \overline {{w}} = \overline {{b}} \\ A [ P \Delta^ {- 1 / 2} \overline {{w}} ^ {\prime} - Q ^ {- 1} \overline {{p}} ] = \overline {{b}} \\ \underbrace {[ A P \Delta^ {- 1 / 2} ]} _ {A ^ {\prime}} \overline {{w}} ^ {\prime} = \underbrace {\overline {{b}} + A Q ^ {- 1} \overline {{p}}} _ {\overline {{b}} ^ {\prime}} \end{array}
$$

Therefore, we again obtain linear constraints with new matrices/vectors $A ^ { \prime }$ and $\overline { { b } } ^ { \prime } .$ . In other words, the optimization problem can be expressed in the following form: 

$$
\begin{array}{c} \text {Minimize} J (\overline {{w}} ^ {\prime}) = \frac {1}{2} \| \overline {{w}} ^ {\prime} \| ^ {2} + q ^ {\prime} \\ \text {subject to:} \\ A ^ {\prime} \overline {{w}} ^ {\prime} = \overline {{b}} ^ {\prime} \end{array}
$$

Note that the rows of $A ^ { \prime }$ are linearly independent like those of A because $A ^ { \prime }$ is obtained by multiplying A with square matrices of full rank. This is exactly the optimization problem discussed in Section 2.8 of Chapter 2, where the right-inverse of $A ^ { \prime }$ can be used to find a solution for $\overline { { w } } ^ { \prime }$ : 

$$
\overline {{w}} ^ {\prime} = A ^ {\prime T} (A ^ {\prime} A ^ {\prime T}) ^ {- 1} \overline {{b}} ^ {\prime}\tag{6.4}
$$

What does this mean in terms of the original coefficients and optimization variables? By substituting $A ^ { \prime } = A P \Delta ^ { - 1 / 2 }$ , it can be shown that $A ^ { \prime } A ^ { \prime T } = A ( \hat { P } \Delta ^ { - 1 } P ^ { T } ) A ^ { T } = A Q ^ { - 1 } A ^ { \dot { T } }$ One can therefore obtain w in terms of the original coefficients: 

$$
\begin{array}{r l} & {\overline {{w}} = P \Delta^ {- 1 / 2} \overline {{w}} ^ {\prime} - Q ^ {- 1} \overline {{p}}} \\ & {\quad = P \Delta^ {- 1 / 2} [ \Delta^ {- 1 / 2} P ^ {T} A ^ {T} (A Q ^ {- 1} A ^ {T}) ^ {- 1} \overline {{b}} ^ {\prime} ] - Q ^ {- 1} \overline {{p}}} \\ & {\quad = Q ^ {- 1} A ^ {T} [ A Q ^ {- 1} A ^ {T} ] ^ {- 1} \overline {{b}} ^ {\prime} - Q ^ {- 1} \overline {{p}}} \\ & {\quad = Q ^ {- 1} \{A ^ {T} [ A Q ^ {- 1} A ^ {T} ] ^ {- 1} [ \overline {{b}} + A Q ^ {- 1} \overline {{p}} ] - \overline {{p}} \}} \end{array}
$$

One can also express this solution in the following form: 

$$
\overline {{w}} = - Q ^ {- 1} \overline {{p}} + \underbrace {Q ^ {- 1} A ^ {T} [ A Q ^ {- 1} A ^ {T} ] ^ {- 1} [ \overline {{b}} + A Q ^ {- 1} \overline {{p}} ]} _ {\text { Adjustment   caused   by   constraints }}\tag{6.5}
$$

As discussed in Section 4.6.2.1 of Chapter 4 (with different notations), the solution to the unconstrained version of the problem is $- Q ^ { - 1 } { \overline { { p } } } .$ . This is the same as the first part of the above solution. The second part of the above solution is the adjustment caused by the equality constraints. It is noteworthy that the adjustment contains $\overrightharpoon { b } - A [ \overline { { z } } ]$ as a factor, where ${ \overline { { z } } } = - Q ^ { - 1 } { \overline { { p } } }$ is the solution to the unconstrained problem. In other words, the adjustment from the unconstrained solution also depends directly on how far the unconstrained solution is from feasibility. 

## 6.2.1.2 Application: Linear Regression with Equality Constraints

The fact that one can find a closed-form solution to the problem of convex quadratic programming with equality constraints implies that one can also solve the problem of leastsquares regression with equality constraints. After all, the objective function of linear regression is a convex quadratic function as well. Consider an $n \times d$ data matrix $D$ containing the feature variables, and an n-dimensional response vector ${ \overline { { y } } } .$ . Assume that we have some domain-specific insight about the data because of which the d-dimensional coefficient vector $\overline { { w } }$ is subject to the linear system of constraints $A { \overline { { w } } } = { \overline { { b } } } .$ . Here, A is an $m \times d$ matrix with $m \leq d$ and $\bar { b }$ is an m-dimensional vector. In such a case, the optimization problem may be expressed as follows: 

$$
\begin{array}{r l} & {\mathrm{Minimize} J (\overline {{w}}) = \frac {1}{2} \| D \overline {{w}} - \overline {{y}} \| ^ {2} + \frac {\lambda}{2} \| \overline {{w}} \| ^ {2}} \\ & {\qquad \mathrm{subjectto:}} \\ & {\qquad A \overline {{w}} = \overline {{b}}} \end{array}
$$

This objective function is exactly in the same form as the convex quadratic program of Section 6.2.1.1. This implies that we can use the closed-form solution of Equation 6.5. The key point is to able to transform the problem to the same form. We leave this transformation as an exercise. 

Problem 6.2.2 Show that one can express the solution to equality-constrained linear regression in the same form as the solution to the quadratic optimization formulation of Section 6.2.1.1 by using $Q = D ^ { T } D + \lambda I$ and $\overline { { p } } = \overline { { D } } ^ { T } \overline { { y } }$ in Equation 6.5. 

## 6.2.1.3 Application: Newton Method with Equality Constraints

One can adapt the Newton method to any convex function with linear equality constraints (even if the objective function is not quadratic). The overall idea is the same as that discussed in Chapter 5. Consider the case where we are trying to minimize the arbitrary convex function $J ( \overline { { w } } )$ subject to the equality constraints $A { \overline { { w } } } = { \overline { { b } } }$ . Here, A is an $m \times d$ matrix, and w is a d-dimensional vector of optimization variables. The Newton method first initializes $\overline { { w } } = \overline { { w } } _ { 0 }$ to a feasible point on the hyperplane $A { \overline { { w } } } = { \overline { { b } } }$ . Then, we start with $t = 0$ and perform the following steps iteratively: 

1. Compute the second-order Taylor approximation of the function $J ( \overline { { w } } )$ centered at $\overline { { w } } = \overline { { w } } _ { t }$ (cf. Section 1.5.1 of Chapter 1). 

2. Compute $\overline { { w } } _ { t + 1 }$ using Equation 6.5 on the Taylor approximation. 

3. Increment t by 1 and go to step 1. 

Note that the second-order Taylor approximation can always be expressed in the form of Equation 6.5, and therefore its closed-form solution can be plugged in directly. This iterative approach can converge to the optimal solution in fewer steps than gradient descent. 

## 6.2.2 Linear Inequality Constraints

Linear inequality constraints are much harder to address than linear equality constraints. This is because one can no longer use Gaussian elimination to get rid of sets of variables and constraints simultaneously. Inequality constraints are handled by formulating the conditional gradient optimization problem. Consider the case where $\overline { { w } } _ { t }$ is the current value of the parameter vector, and one wishes to move to a new value $\overline { { w } } _ { t + 1 }$ that reduces the ob jective function as much as possible while satisfying the feasibility constraints. This value of $\overline { { w } } _ { t + 1 }$ is approximately obtained by using an objective function based on the first-order Taylor expansion: 

$$
\begin{array}{l} \overline {{w}} _ {t + 1} = \operatorname * {a r g m i n} _ {\overline {{w}}} \underbrace {F (\overline {{w}} _ {t}) + [ \nabla F (\overline {{w}} _ {t}) ] \cdot [ \overline {{w}} - \overline {{w}} _ {t} ]} _ {\text { First - order   Taylor   expansion }} \\ \text { subject   to: } \\ A \overline {{w}} \leq \overline {{b}} \end{array}
$$

Here, it is important to note that we are solving one optimization problem as a subproblem of another; clearly, the subproblem has to be simple for the approach to make sense. As it turns out, this subproblem is indeed much easier than the original problem because it is a linear programming problem; it has a linear objective function and linear constraints. Such problems can be solved efficiently with of-the-shelf solvers, and we refer the reader to [16] for an introduction to linear optimization. Therefore, the conditional gradient method simply solves the above optimization problem repeatedly to convergence. 

The main issue with the above optimization problem is that minimizing the objective function does not necessarily lead to the optimum point, as we are using the instantaneous gradient at $\overline { { w } } _ { t }$ in order to determine $\overline { { w } } _ { t + 1 }$ . Obviously, the gradient will change as we move from $\overline { { w } } _ { t }$ to $\overline { { w } } _ { t + 1 }$ , and the objective function might even start worsening as one approaches $\overline { { w } } _ { t + 1 }$ . This problem can be partially addressed as follows. We first solve the above optimization problem to find a tentative value of $\overline { { w } } _ { t + 1 }$ . At this point, we only obtain a direction of movement $\overline { { q } } _ { t } = \overline { { w } } _ { t + 1 } - \overline { { w } } _ { t }$ . Subsequently, the update is modified to $\overline { { w } } _ { t } + \alpha _ { t } \overline { { q } } _ { t }$ , where $\alpha _ { t }$ is selected using line search. However, in this case, $\alpha _ { t }$ would need to selected to ensure both feasibility and an optimum solution. 

## 6.2.2.1 The Special Case of Box Constraints

Box constraints arise frequently in machine learning, and they represent a special case of linear constraints of the form $A { \overline { { w } } } \leq { \bar { b } }$ . All box constraints are of the form $l _ { i } \le w _ { i } \le u _ { i }$ Therefore, the feasible region is a hypercube in d-dimensional space (although the box might be an open set when $l _ { i } = - \infty \ \mathrm { o r } \ u _ { i } = \infty )$ . Box constraints are relatively easy to handle because of the ease in projecting an infeasible solution to its nearest point on a box. We show examples of violation of box constraints in Figure 6.3. In each case, the closest point on the box is obtained by simply setting the variable values of the violated constraints to the bounds that are violated. Figure 6.3 shows two cases. In the first case, only one constraint is violated by a gradient-descent step, whereas in the second case, two constraints are violated by a gradient descent step. In each case, the variable values for the violated constraints are set to their bounds by the projection step. Therefore, the computational algorithm is as follows: 

1. Perform the gradient-descent step $\overline { { w } } \Leftarrow \overline { { w } } - \alpha \left[ \nabla F ( \overline { { w } } ) \right]$ 

2. Find the components in $\overline { { w } }$ for which the interval bounds (box constraints) are violated, and set the component value to the end-point of the interval that is violated. 

The above two steps are applied iteratively to convergence. One must take care to select the initialization points within the feasible box. 

Problem 6.2.3 (Linear Regression with Box Constraints) The linear regression problem optimizes the following objective function: 

$$
J = \left\| D \overline {{w}} - \overline {{y}} \right\| ^ {2}
$$

![image](<Images/06_Constrained_Optimization_and_Duality_image_003.jpg>)



Figure 6.3: Violation of box constraints


Here, D is an $n \times d$ data matrix, $\overline { { w } } = [ w _ { 1 } \ : . . . w _ { d } ] ^ { T }$ contains the optimization variables, and y is an n-dimensional column vector of response variables. Suppose that we add box constraints of the form $l _ { i } \le w _ { i } \le u _ { i }$ for each optimization variable $w _ { i }$ . Discuss how you will apply projected gradient descent in this case. 

The dual problem for support vector machines is also a convex optimization problem with box constraints. This problem is discussed in Section 6.4.4.1. 

Problem 6.2.4 Consider the problem in which you want to use the $L _ { 2 }$ -loss SVM as the objective function (see page 184). However, you have the additional domain-specific knowledge that all coefficients are nonnegative (possibly because of known positive correlations between features and class label). Discuss how you would solve the $L _ { 2 } { - } S V M$ optimization problem. 

## 6.2.2.2 General Conditions for Projected Gradient Descent to Work

Box constraints represent a simple case in which it is relatively easy to find the nearest points of projection by using the violated constraints. All that one needs to do is to set all the variables to their nearest feasible points on the box. In the case of box constraints, this amounts to finding the closest point to the current point, so that all the violated box constraints are satisfied at equality. 

The success of this approach in the case of box constraints leads one to wonder whether one can apply this approach to the general case. In other words, consider a problem in which we are minimizing $J ( \overline { { w } } )$ subject to $A { \overline { { w } } } \leq { \overline { { b } } } .$ Consider a situation where we have used unconstrained gradient descent to move from a feasible point $\overline { { w } } _ { t }$ to a (possibly infeasible) point $\overline { { w } } _ { t + 1 }$ . Suppose that the subset of the violated constraints is $A _ { v } \overline { { w } } \leq \overline { { b } } _ { v }$ , where $A _ { v }$ and $\overline { { b } } _ { v }$ are respectively obtained by extracting the corresponding rows from A and b. As in the case of box constraints, can we simply find the closest point w to $\overline { { w } } _ { t + 1 }$ that satisfies the violated constraints $A _ { v } \overline { { w } } = \bar { b } _ { v }$ at equality? Unfortunately, this is not the case when the rows of $A _ { v }$ are linearly dependent. Box constraints have the property that all the violated hyperplanes are mutually orthogonal; therefore, this situation does not arise. Furthermore, this problem also does not arise in linear equality constraints where one can use Gaussian elimination to remove linearly dependent constraints. Unfortunately, such elimination methods cannot be used when working with linear inequality constraints. 

![image](<Images/06_Constrained_Optimization_and_Duality_image_004.jpg>)



Figure 6.4: Linearly dependent violations can create challenges


In order to understand why linearly dependent inequality constraints can create chal lenges, we will use an example of a convex region in 2-dimensional space, which is created by six inequality constraints. This convex region is illustrated in Figure 6.4. Note that any set of three constraints are linearly dependent, when working in 2-dimensional space. As shown in Figure 6.4, it is possible to project back to the closest point on the intersection of the violated constraints when these constraints are linearly independent. This situation corresponds to the left and the middle example of Figure 6.4. However, at the right side of Figure 6.4, we have a case where three constraints are violated, and these constraints are linearly dependent. Unfortunately, the constraints do not intersect, and selecting only two of these constraints leads to an infeasible solution. In general, we can make the following observation: 

Observation 6.2.2 The optimization problem of minimizing $J ( \overline { { w } } )$ subject to $A \overline { { w } } \le \bar { b }$ is much simpler to solve when the rows of A are linearly independent. One can simply use projected gradient descent by first making an unconstrained gradient descent step, identifying the violated constraints, and projecting to the closest point that satisfies the violated constraints with strict equality. 

In other words, we start from a feasible point $\overline { { w } } _ { 0 }$ , and then make the following gradientdescent steps starting with $t = 0$ : 

1. Make the step $\overline { { w } } _ { t + 1 } ^ { \prime }  \overline { { w } } _ { t } - \alpha _ { t } \nabla J ( \overline { { w } } _ { t } )$ . Here, $\alpha _ { t }$ is the step-size. 

2. Extract the violated constraints $A _ { v } \overline { { w } } \leq \overline { { b } } _ { v }$ . We assume that the rows of $A _ { v }$ are linearly independent because the rows of A are linearly independent. 

3. Update $\overline { { w } } _ { t + 1 }  \overline { { w } } _ { t + 1 } ^ { \prime } + A _ { v } ^ { T } ( A _ { v } A _ { v } ^ { T } ) ^ { - 1 } [ \overline { { b } } _ { v } - A _ { v } \overline { { w } } _ { t + 1 } ^ { \prime } ]$ . Note that $A _ { v } \overline { { w } } _ { t + 1 }$ can be shown to be exactly equal to $\bar { b } _ { v }$ by multiplying both sides of the above equation by $A _ { v }$ . This update can also be derived by applying an origin translation to $\overline { { w } } _ { t + 1 } ^ { \prime }$ in order to use the right-inverse results of Section 2.8 in Chapter $2 ;$ then one can add back $\overline { { w } } _ { t + 1 } ^ { \prime }$ . We need to translate the origin to $\overline { { w } } _ { t + 1 } ^ { \prime }$ because we want to find the closest point to $\overline { { w } } _ { t + 1 } ^ { \prime }$ on $A _ { v } \overline { { w } } = \overline { { b } } _ { v }$ , whereas the right-inverse in Section 2.8 finds the most concise solution to $A _ { v } \overline { { w } } = \bar { b } _ { v }$ (i.e., closest point to the origin). However, translating the origin in this way transforms the vector $\bar { b } _ { v }$ to $[ \overline { { b } } _ { v } - A _ { v } \overline { { w } } _ { t + 1 } ^ { \prime } ]$ , and therefore the weight vector in translated space is $A _ { v } ^ { T } ( A _ { v } A _ { v } ^ { T } ) ^ { - 1 } [ \overline { { b } } _ { v } - A _ { v } \overline { { w } } _ { t + 1 } ^ { \prime } ]$ . Adding back $\overline { { w } } _ { t + 1 } ^ { \prime }$ yields the update. 

## 4. Increment t by 1 and go back to step 1.

These steps are iterated to convergence. Here, a key point is that the projection step does not result in violation of the other (already satisfied) constraints. This is because the nearest point in a convex set is guaranteed to lie on the intersection of all the violated constraints, when the constraints are linearly independent. 

A key question arises as to how one can use the approach when the rows of the matrix A are not linearly independent. Here, an important observation is that we only need each violated set $A _ { v }$ to contain linearly independent rows rather than the much stronger criterion of requiring this from the full set A. Therefore, the approach will often work even in cases where there is a modest level of linear dependence between rows of $A ,$ , and one never encounters any matrix $A _ { v }$ containing linearly dependent rows. One way of discouraging the rows of $A _ { v }$ to be linearly independent is to use line search on $\alpha _ { t } .$ , and restrict the step size so that the violated constraints are never linearly dependent. With this modification, the aforementioned approach can be used directly. However, convergence to an optimal solution is not guaranteed by such an approach, although the approach tends to work well in practice. 

## 6.2.2.3 Sequential Linear Programming

So far this section has only considered the case where we have linear inequality constraints of the form $A \overline { { w } } \le \overline { { b } }$ . However, what happens in cases where the constraints are not linear, but they might be arbitrary, convex constraints of the form $f _ { i } ( \overline { { w } } ) \leq 0$ for $i \in \{ 1 \ldots m \}$ The objective function $F ( \overline { { w } } )$ is assumed to be convex. In such a case, one can linearize not only the objective function, but also the constraints. In other words, we use the first-order Taylor expansion of both the objective function and the constraints. Therefore, if the current feasible solution to the problem is $\overline { { w } } _ { t }$ , then one can pose the following linearized model for solving the problem: 

$$
\begin{array}{l} \overline {{w}} _ {t + 1} = \operatorname * {a r g m i n} _ {\overline {{w}}} \underbrace {F (\overline {{w}} _ {t}) + [ \nabla F (\overline {{w}} _ {t}) ] \cdot [ \overline {{w}} - \overline {{w}} _ {t} ]} _ {\text { First - order   Taylor   expansion }} \\ \text { subject   to: } \\ \underbrace {f _ {i} (\overline {{w}} _ {t}) + \nabla f _ {i} (\overline {{w}} _ {t}) [ \overline {{w}} - \overline {{w}} _ {t} ]} _ {\text { Taylor   expansion }} \leq 0, \quad \forall i \in \{1 \ldots m \} \end{array}
$$

One problem with this approach is that the linear constraints need not be a bounded convex region. For example, if the constraint is of the form $\overline { w } ^ { 2 } \le 1$ (which is a bounded circle of radius one), then its linearized approximation is $\overline { { w } } _ { t } ^ { 2 } + 2 \overline { { w } } _ { t } ( \overline { { w } } - \overline { { w } } _ { t } ) \leq 1$ . In other words, the linearized constraint is simply the tangent to the concentric circle passing through $\overline { { w } } _ { t }$ and the side containing the center of the circle (which is the origin in this case) is included as the feasible space. Depending on the nature of the objective function, the solution to the subproblem might be unbounded because of feasible region on one side of the tangent is unbounded. One can handle this issue in several ways, such as adding additional box constraints in order to limit the step-size. However, even adding box constraints might sometimes result in a value of $\overline { { w } } _ { t + 1 }$ that does not satisfy the original constraints. In such cases, one possible solution is to perform a linear search on the region between $\overline { { w } } _ { t }$ and $\overline { { w } } _ { t + 1 }$ and reduce the step size, so that the solution stays feasible. There are, however, many other ways in which these issues are handled, and we refer the reader to [99] for a detailed discussion. 

## 6.2.3 Sequential Quadratic Programming

Sequential quadratic programming is the natural generalization of sequential linear pro gramming, in which the second-order Taylor expansion is used at each point, instead of the first-order Taylor expansion in the objective function. Furthermore, the constraints are linearized in order to keep the problem reasonably simple. The solution to quadratic programs with linear constraints is relatively simple, if one were to use techniques for Lagrangian relaxation. Such methods are discussed later in this chapter, and Exercise 7 provides a path to applying these techniques in quadratic programs. 

Consider an optimization problem in which we are trying to minimize the convex function $F ( \overline { { w } } )$ , subject to the convex constraints $f _ { i } ( \overline { { w } } ) \leq 0$ for $i \in \{ 1 \ldots m \}$ . Also assume that we have equality constraints of the form $h _ { i } ( \overline { { w } } ) = 0$ for $i \in \{ 1 \ldots k \}$ . Then, the second-order approximation to the problem is as follows: 

$$
\begin{array}{l} \overline {{w}} _ {t + 1} = \operatorname * {a r g m i n} _ {\overline {{w}}} \underbrace {F (\overline {{w}} _ {t}) + [ \nabla F (\overline {{w}} _ {t}) ] \cdot [ \overline {{w}} - \overline {{w}} _ {t} ] + [ \overline {{w}} - \overline {{w}} _ {t} ] ^ {T} H _ {F} ^ {t} [ \overline {{w}} - \overline {{w}} _ {t} ]} _ {\text {Second - order Taylor expansion}} \\ \text {subject to:} \\ \underbrace {f _ {i} (\overline {{w}} _ {t}) + \nabla f _ {i} (\overline {{w}} _ {t}) [ \overline {{w}} - \overline {{w}} _ {t} ]} _ {\text {First - order Taylor expansion}} \leq 0, \quad \forall i \in \{1 \ldots m \} \\ \underbrace {h _ {i} (\overline {{w}} _ {t}) + \nabla h _ {i} (\overline {{w}} _ {t}) [ \overline {{w}} - \overline {{w}} _ {t} ]} _ {\text {First - order Taylor expansion}} = 0, \quad \forall i \in \{1 \ldots k \} \end{array}
$$

Here, $H _ { F } ^ { t }$ represents the Hessian of $F ( \cdot )$ at the point $\overline { { w } } _ { t }$ . This Hessian is positive semi definite, since we are only dealing with convex functions. If the Hessian $H _ { F } ^ { t }$ is positive definite, the problem will have a bounded global minimum even without constraints. Although quadratic programs are harder to solve as subproblems than linear programs, they are much easier to solve than many other linear programs (see Exercise 7). Many of the methods discussed in later sections (such as Lagrangian relaxation) can be used for solving convex quadratic programs effectively. The main issue is that the solution to the linearized problem may not be feasible for the original constraints to the problem. We refer the reader to [21, 99] for a detailed discussion of solution methods. In particular, a practical line-search method discussed by [99] is very useful in this context. 

## 6.3 Primal Coordinate Descent

The coordinate descent method is discussed in Section 4.10 of Chapter 4. The basic idea in coordinate descent is to perform the optimization one variable at a time. Consider an objective function $F ( \overline { { w } } )$ , which is a function of a d-dimensional vector of variables. In coordinate descent, we optimize a single variable $w _ { i }$ from the vector w, while holding all the other parameters fixed to their values $\overline { { w } } ^ { t }$ in the tth iteration. This leads to the following update in the tth iteration: 

![image](<Images/06_Constrained_Optimization_and_Duality_image_005.jpg>)



Figure 6.5: Fixing variables results in an interval constraint over remaining variable when the feasible region is convex


w<sup>t+1</sup> = argmin<sub>[ith</sub> <sub>component</sub> <sub>of</sub> <sub>w</sub> <sub>]</sub> F(w) [All parameters except $w _ { i }$ are fixed to $\overline { { w } } ^ { t } ]$ 

Here, i is the index of the ith variable, and other variables are fixed to the corresponding values in $\overline { { w } } ^ { t }$ . One cycles through the variables one at a time, until convergence is achieved. For example, if no improvement occurs during a cycle of optimizing each variable, then it means that the solution is a global optimum. In block coordinate descent, a block of variables is optimized at a given time, and one cycles through the different blocks one at a time. 

Coordinate descent is particularly suitable for constrained optimization. This is because the variable-at-a-time optimization significantly simplifies the structure of the resulting sub problem; in fact, the problem reduces to the univariate case. Although block coordinate descent does not yield univariate optimization problems, it still results in significant simplification. Very often, the constraints that tie together different variables can be dropped in an iteration, since some of the variable values are fixed in an iteration. A specific example of this situation is the k-means algorithm discussed in Section 4.10.3 of Chapter 4. 

## 6.3.1 Coordinate Descent for Convex Optimization Over Convex Set

Coordinate descent reduces a multivariate optimization problem into a sequence of univariate optimization problems. When using coordinate descent over a convex set, a very useful observation is that any univariate convex set is a continuous interval, and the corresponding variable w can be expressed in the form of the box constraint $l _ { i } \le w \le u _ { i }$ . This fact follows from the fact that a convex set is defined as any set such that any line passing through it must have exactly one continuous region belonging to the set. Therefore, if a horizontal or vertical line is passed through a convex set, as shown in Figure 6.5, the feasible region already corresponds to a continuous interval. 

For example, consider the case where we are trying to optimize some function $F ( w _ { 1 } , w _ { 2 } , w _ { 3 } )$ , over a feasible region in 3-dimensions. This 3-dimensional region is defined by the following constraints: 

$$
\begin{array}{l} w _ {1} ^ {2} - w _ {1} \cdot w _ {2} + w _ {2} ^ {2} / 4 + 3 w _ {2} \cdot w _ {3} + 4 w _ {3} ^ {2} \leq 4 \\ 2 w _ {1} + w _ {2} - 3 w _ {3} \leq 4 \end{array}
$$

Note that the constraints are both quadratic and linear, and therefore the problem is more complex than the linear constraints considered in the previous section. Now consider the case in which one is performing coordinate descent, and we are trying to compute the optimum value $w _ { 1 }$ so that $F ( w _ { 1 } , w _ { 2 } , w _ { 3 } )$ is minimized (while holding $w _ { 2 }$ and $w _ { 3 }$ fixed). The values of $w _ { 2 }$ and $w _ { 3 }$ are set to 2 and 0, respectively. Plugging in these values of $w _ { 2 }$ and $w _ { 3 }$ we obtain the following pair of constraints: 

$$
\begin{array}{l} w _ {1} ^ {2} - 2 w _ {1} - 3 = (w _ {1} - 3) (w _ {1} + 1) \leq 0 \\ w _ {1} \leq 1 \end{array}
$$

Note that the first constraint implies that $w _ { 1 } \in [ - 1 , 3 ]$ and the second constraint implies that $w _ { 1 } \in ( - \infty , 1 ]$ . Therefore, by combining the constraints, we obtain the fact that the variable $w _ { 1 }$ must lie in $[ - 1 , + 1 ]$ . Furthermore, the objective function can be simplified to $G ( w _ { 1 } ) = F ( w _ { 1 } , 2 , 0 )$ . Therefore, the subproblem reduces to optimizing a univariate convex function $G ( w _ { 1 } )$ over an interval. 

How does one optimize a univariate convex function over an interval? One possibility is to simply set the derivative of the convex function (with respect to the only variable w being optimized) to 0, and obtain a value of the variable w by solving the resulting equation. At this point, one must check the two ends of the interval in order to check whether the optimum lies at one of the two ends. The reason that one is able to use this simple approach is because of the convexity of the optimization function. Alternatively, one can use the line search methods discussed in Section 4.4.3 of Chapter 4. One cycles through the variables using this iterative approach, until convergence is reached. 

Depending on the structure of the objective function and optimization variables, the univariate subproblem in coordinate descent often has a very simple structure. Therefore, even when one is faced with an arbitrarily complex problem, it is worthwhile trying ideas from coordinate descent for the purposes of optimization. In some cases, coordinate descent can even provide good heuristic solutions to difficult optimization problems like mixed integer programs. This is because the subproblems are often much easier to solve than the original formulation. A specific example is the case of the k-means algorithm, which has integer constraints on the variables (cf. Section 4.10.3 of Chapter 4). However, there are also cases in which coordinate descent fails (see Exercise 19). 

## 6.3.2 Machine Learning Application: Box Regression

The box regression problem is an enhancement of the linear regression problem in which constraints are added to the regression variables. As evident from Problem 6.2.3, the box regression problem can be addressed using projected gradient descent methods. In this section, we address this problem with the use of coordinate descent. 

The linear regression problem with box constraints can be posed as follows: 

$$
\mathrm{Minimize} J = \frac {1}{2} \| D \overline {{w}} - \overline {{y}} \| ^ {2} + \frac {\lambda}{2} \| \overline {{w}} \| ^ {2}
$$

subject to: 

$$
l _ {i} \leq w _ {i} \leq u _ {i}, \forall i \in \{1 \dots d \}
$$

Here, $D$ is an $n \times d$ matrix of feature values, $\overline { { w } } = [ w _ { 1 } , \ldots , w _ { d } ] ^ { T }$ is a d-dimensional vector of coefficients, and $\overline { { y } } = [ y _ { 1 } \ldots y _ { n } ] ^ { T }$ is an n-dimensional vector of response values. 

In the case of unconstrained linear regression, the value of $w _ { i }$ is updated using the following formula (cf. Problem 4.10.1 of Chapter 4): 

$$
w _ {i} \Leftarrow \frac {w _ {i} \| \overline {{d}} _ {i} \| ^ {2} + \overline {{d}} _ {i} ^ {T} \overline {{r}}}{\| \overline {{d}} _ {i} \| ^ {2} + \lambda}
$$

Here, $\overline { { r } } = \overline { { y } } - D \overline { { w } }$ is the n-dimensional vector of residuals. In this case, the only difference is that we use the additional truncation operator $T _ { i } ( \cdot )$ after each coordinate descent step in order to bring the variable back into the relevant bounds. 

$$
w _ {i} \Leftarrow T _ {i} \left[ \frac {w _ {i} \| \overline {{d}} _ {i} \| ^ {2} + \overline {{d}} _ {i} ^ {T} \overline {{r}}}{\| \overline {{d}} _ {i} \| ^ {2} + \lambda} \right]
$$

Here, the truncation operator $T _ { i } ( \cdot )$ is defined as follows: 

$$
T _ {i} (x) = \left\{ \begin{array}{l l} l _ {i} & x <   l _ {i} \\ x & l _ {i} \leq x \leq u _ {i} \\ u _ {i} & u _ {i} <   x \end{array} \right.
$$

In other words, each coordinate is immediately truncated to its lower and upper bounds after the coordinate update. We also make the following observation: 

Observation 6.3.1 Nonnegative least-squares regression is a special case of box regression in which all coefficients have a lower bound of zero, but no upper bound. Nonnegative regression can be directly implemented as a special case of the above algorithm. 

## 6.4 Lagrangian Relaxation and Duality

Lagrangian relaxation is an approach whereby the constraints of an optimization problem are relaxed, while penalizing their violation within the objective function. The magnitudes of the penalties depend on factors referred to as the Lagrange multipliers. For a minimization problem, the Lagrangian relaxation always provides a lower bound on the optimal solution, no matter what the value of the Lagrange multipliers might be. A key point is that for certain types of optimization problems, such as convex objective functions with convex constraints, the exact optimal solution to the original solution can be obtained with the appropriate choice of multipliers on the relaxed problem. 

Consider a minimization problem of the following form: 

$$
\begin{array}{c} P = \text {Minimize} F (\overline {{w}}) \\ \text {subject to:} \\ f _ {i} (\overline {{w}}) \leq 0, \quad \forall i \in \{1 \ldots m \} \end{array}
$$

This problem is referred to as the primal problem in optimization parlance, and we introduce the notation $P$ to denote its optimal solution. The Lagrangian relaxation methodology is particularly useful when the functions $F ( \overline { { w } } )$ and each $f _ { i } ( \overline { { w } } )$ are convex. The Lagrangian relaxation is defined with the use of nonnegative Lagrangian multipliers $\overline { { \alpha } } = [ \alpha _ { 1 } \ldots \alpha _ { m } ] ^ { T }$ 

$$
\begin{array}{c} L (\overline {{\alpha}}) = \text { Minimize } _ {\overline {{w}}} F (\overline {{w}}) + \sum_ {i = 1} ^ {m} \alpha_ {i} f _ {i} (\overline {{w}}) \\ \text { subject   to: } \\ \text { No   constraints   on } \overline {{w}} \end{array}
$$

We have introduced the notation $L ( \overline { { \alpha } } )$ to indicate the solution to the relaxed problem at any particular value of the parameter vector α. Note that the minimization is only with respect to the parameters in w and not the parameters in ${ \overline { { \alpha } } } ,$ which is fixed (and therefore a part of the argument of $L ( \overline { { \alpha } } ) )$ ). It is important to note that each $\alpha _ { i }$ is nonnegative to ensure that violations of the constraints are penalized. When a constraint is violated, we will have $f _ { i } ( \overline { { w } } ) > 0$ , and the penalty $\alpha _ { i } f _ { i } ( \overline { { w } } )$ will also be nonnegative. Although $L ( \overline { { \alpha } } )$ is defined over any value of ${ \overline { { \alpha } } } ,$ , it makes sense to consider only nonnegative values of α. For example, if the value of $\alpha _ { i }$ is negative, then violation of the ith constraint will be rewarded. 

In the case of equality constraints, the Lagrange multipliers do not have any nonnega tivity constraints. Consider the following equality-constrained optimization problem: 

$$
\begin{array}{l} \text {Minimize F(\overline {{w}})} \\ \text {subject to:} \\ f _ {i} (\overline {{w}}) = 0, \forall i \in \{1 \ldots m \} \end{array}
$$

Each equality constraint can be converted to a pair of inequality constraints $f _ { i } ( \overline { { w } } ) \leq 0$ and $- f _ { i } ( \overline { { w } } ) \leq 0$ with nonnegative Lagrangian multipliers $\alpha _ { i , 1 }$ and $\alpha _ { i , 2 } .$ , respectively. Then, the Lagrangian relaxation contains terms of the form $f _ { i } ( \overline { { w } } ) ( \alpha _ { i , 1 } - \alpha _ { i , 2 } )$ . One can instead treat $\alpha _ { i } = \alpha _ { i , 1 } - \alpha _ { i , 2 }$ as the sign unconstrained Lagrange multiplier. Most of the discussion in this chapter will, however, be centered around inequality constraints. 

Let us examine why the Lagrangian relaxation problem provides a lower bound on the solution to the original optimization problem. Let $\overline { { w } } ^ { \ast }$ be the optimal solution to the original optimization problem, and α be any nonnegative vector of Lagrangian parameters. Since $\overline { { w } } ^ { \ast }$ is also a feasible solution to the original problem, it follows that each $f _ { i } ( \overline { { w } } ^ { * } )$ is no larger than zero. Therefore, the “penalty” $\alpha _ { i } f _ { i } ( \overline { { w } } ^ { * } ) \leq 0$ . In other words, the penalties can become rewards for primal-feasible solutions like $w ^ { * }$ , if the penalties are non-zero. Therefore, we have: 

$$
\begin{array}{l} L (\overline {{\alpha}}) = \text {Minimize} _ {\overline {{w}}} F (\overline {{w}}) + \sum_ {i = 1} ^ {m} \alpha_ {i} f _ {i} (\overline {{w}}) \\ \quad \leq F (\overline {{w}} ^ {*}) + \underbrace {\sum_ {i = 1} ^ {m} \alpha_ {i} f _ {i} (\overline {{w}} ^ {*})} _ {\leq 0} [ w ^ {*} \text {might not be optimal for relaxation} ] \\ \quad \leq F (\overline {{w}} ^ {*}) = P \end{array}
$$

In other words, the value of $L ( \overline { { \alpha } } )$ for any nonnegative vector $\overline { \alpha }$ is always no larger than the optimal solution to the primal. One can tighten this bound by maximizing $L ( \overline { { \alpha } } )$ over all nonnegative $\overline { \alpha }$ and formulating the dual problem with objective function $D \colon$ : 

![image](<Images/06_Constrained_Optimization_and_Duality_image_006.jpg>)



(a) H(x, y) = sin(x + y)



min-max>max-min


![image](<Images/06_Constrained_Optimization_and_Duality_image_007.jpg>)



(b) $H ( x , y ) = x ^ { 2 } - y ^ { 2 }$



min-max=max-min



Figure 6.6: Examples of two minimax functions with a single minimization variable and a single maximization variable. The first is neither concave nor convex in either variable. The second is convex in the minimization variable and concave in the maximization variable, and has a well-defined saddle point


$$
\begin{array}{l} D = \text { Maximize } _ {\overline {{\alpha}} \geq 0} L (\overline {{\alpha}}) \\ = \text { Maximize } _ {\overline {{\alpha}} \geq 0} \text { Minimize } _ {\overline {{w}}} [ F (\overline {{w}}) + \sum_ {i = 1} ^ {m} \alpha_ {i} f _ {i} (\overline {{w}}) ] \end{array}
$$

We summarize the relationship between the primal and the dual as follows: 

$$
D = L (\overline {{\alpha}} ^ {*}) \leq P
$$

This result is referred to as that of weak duality. It is noteworthy that the Lagrangian opti mization problem is a minimax problem containing disjoint minimization and maximization variables. The minimization and maximization is done in a specific order. The ordering of the minimization and maximization for any minimax optimization problem does matter. 

Problem 6.4.1 Consider the 2-dimensional function $G ( x , y ) ~ = ~ s i n ( x + y )$ . Show that $m i n _ { x } m a x _ { y } G ( x , y ) = 1$ and ma $x _ { y } m i n _ { x } G ( x , y ) = - 1$ 

The ordering effects of minimization and maximization in minimax problems can be for malized in terms of John von Neumann’s minimax theorem [37] in mathematics. It states that “min-max” is an upper bound on “max-min” of a function containing both minimization and maximization variables. Furthermore, strict equality occurs when the function is convex in its minimization variables and also concave in the maximization variables. For example, the function $H ( x , y ) = \sin ( x + y )$ is neither concave nor convex in either x or y. The corresponding plot is shown in Figure 6.6(a). As shown in Problem 6.4.1, the order of minimization and maximization matters in this case. On the other hand, the function $H ( x , y ) = x ^ { 2 } - y ^ { 2 }$ is convex in the minimization variable x and concave in the maximization variable y. This function is shown in Figure 6.6(b). Therefore, this function has a single saddle point, which is the optimal solution to both minimax problems. 

Armed with this understanding of the importance of ordering of minimization and maxi mization in minimax problems, we revisit the effect of this ordering on the Lagrangian relax ation. We denote the minimax optimization function of Lagrangian relaxation as $H ( \overline { { w } } , \overline { { \alpha } } )$ 

$$
H (\overline {{w}}, \overline {{\alpha}}) = F (\overline {{w}}) + \sum_ {i = 1} ^ {m} \alpha_ {i} f _ {i} (\overline {{w}})\tag{6.6}
$$

Here, $\overline { { w } }$ contains the minimization variables and α contains the maximization variables. While the dual computes $\operatorname { m a x } _ { \overline { { \alpha } } \geq 0 }$ min<sub>w</sub> $H ( \overline { { w } } , \overline { { \alpha } } )$ (which is a lower bound on the primal), reversing the order to min<sub>w</sub> $m a x _ { \overline { { { \alpha } } } \geq 0 } H ( \overline { { { w } } } , \overline { { { \alpha } } } )$ always yields the original (primal) optimization problem irrespective of whether the original problem has a convex objective function or convex constraints. We summarize this result below: 

Lemma 6.4.1 (Minimax Primal Formulation) Let $H ( \overline { { w } } , \overline { { \alpha } } )$ of Equation 6.6 represent the Lagrangian relaxation of the unrelaxed primal formulation with constraints. Then, the unconstrained minimax problem min $m a x _ { \overline { { { \alpha } } } \geq 0 } H ( \overline { { { w } } } , \overline { { { \alpha } } } )$ is equivalent to the original, unrelaxed primal formulation irrespective of the convexity structure of the original problem. 

Proof: Consider the Lagrangian objective function $H ( \overline { { w } } , \overline { { \alpha } } )$ of Equation 6.6. Then, the value of $\operatorname* { m a x } _ { \overline { { \alpha } } \geq 0 } H ( \overline { { w } } , \overline { { \alpha } } )$ is at any fixed value of w that violates one or more of the original primal constraints. This is achieved by setting the corresponding $\alpha _ { i }$ of the violated constraint to $\infty .$ . Therefore, the primal problem of min ${ \overline { { w } } } \operatorname* { m a x } _ { \overline { { \alpha } } \geq 0 } H ( \overline { { w } } , \overline { { \alpha } } )$ ) will never yield a solution for w at (minimax) optimality that violates constraints of the form $f _ { i } ( \overline { { w } } ) \leq 0$ In other words, minimax optimality of min $\operatorname* { m a x } _ { \overline { { \alpha } } \geq 0 } H ( \overline { { w } } , \overline { { \alpha } } )$ always yields solutions for w satisfying each $f _ { i } ( \overline { { w } } ) \leq 0$ 

For any value of w satisfying each $f _ { i } ( \overline { { w } } ) \leq 0$ , the contribution of the penalty term to $H ( \overline { { w } } , \overline { { \alpha } } )$ is non-positive because $\alpha _ { i } f _ { i } ( \overline { { w } } ) \leq 0$ for each i. Therefore, for any such fixed value of w satisfying primal constraints, the function $H ( \overline { { w } } , \overline { { \alpha } } )$ will be maximized with respect to α only when the value of $\alpha _ { i }$ is set to zero for each i satisfying $f _ { i } ( \overline { { w } } ) < 0$ . This ensures that the corresponding value of $\alpha _ { i } f _ { i } ( \overline { { w } } )$ is zero, and therefore the contribution of the penalty term $\scriptstyle \sum _ { i = 1 } ^ { m } \alpha _ { i } f _ { i } ( { \overline { { w } } } )$ to $H ( \overline { { w } } , \overline { { \alpha } } )$ is 0 at minimax optimality. 

The above two facts imply that the optimization of $F ( \overline { { w } } )$ with respect to the primalconstraints is the same problem as mi $\mathfrak { l } _ { \overline { { w } } } \operatorname* { m a x } _ { \overline { { \alpha } } } H ( \overline { { w } } , \overline { { \alpha } } )$ . At optimality of the second problem,the primal constraints are satisfied, and the objective function is the same as well (since thepenalty contribution drops to 0). 厂

We make some key observations about the Lagrangian relaxation $H ( \overline { { w } } , \overline { { \alpha } } )$ of Equation 6.6: 

1. Dual is a minimax problem: The dual problem of Lagrangian optimization is based on the relaxation of Equation 6.6 in which the minimax optimization is done in a specific order: 

$$
D = \max _ {\overline {{\alpha}} \geq 0} \min _ {\overline {{w}}} H (\overline {{w}}, \overline {{\alpha}})\tag{6.7}
$$

2. Primal is a minimax problem of the same objective function as dual (but in different order): The unrelaxed primal formulation with constraints can also be expressed in terms of minimax optimization of the function $H ( \overline { { w } } , \overline { { \alpha } } )$ of Equation 6.6, but in a different order than the dual: 

$$
P = \min _ {\overline {{w}}} \max _ {\overline {{\alpha}} \geq 0} H (\overline {{w}}, \overline {{\alpha}})\tag{6.8}
$$

3. Duality results of Lagrangian relaxation can be derived from the more general minimax theorem in mathematics: The weak duality result that $D \leq P$ can also be derived from John von Neumann’s minimax theorem of optimization [37]. The minimax theorem of optimization is designed for general minimax functions containing a disjoint set of minimization and maximization variables (of which the Lagrangian relaxation is a special case). The theorem states that max-min is always bounded above by min-max, which implies that $D \leq P$ . Furthermore, the minimax theorem also states that strict equality $D = P$ occurs when the optimization function is convex in the minimization (primal) variables and concave in the maximization (dual) variables. 

What types of optimization problems are such that their Lagrangian relaxations show strict equality between primal and dual solutions? First, the function $H ( \overline { { w } } , \overline { { \alpha } } )$ is linear in the maximization variables, and therefore concavity with respect to maximization variables is always satisfied. Second, the function $H ( \overline { { w } } , \overline { { \alpha } } )$ is a sum of $F ( \overline { { w } } )$ and nonnegative multiples of the various $f _ { i } ( \overline { { w } } )$ for $i \in \{ 1 \ldots m \}$ . Therefore, if $F ( \overline { { w } } )$ and each of $f _ { i } ( \overline { { w } } )$ are convex in ${ \overline { { w } } } .$ then $H ( \overline { { w } } , \overline { { \alpha } } )$ will be convex in the minimization variables. This is the primary pre-condition for strong duality: 

Lemma 6.4.2 (Strong Duality) Consider the following optimization problem: 

$$
\begin{array}{c} P = \text {Minimize} F (\overline {{w}}) \\ \text {subject to:} \\ f _ {i} (\overline {{w}}) \leq 0, \quad \forall i \in \{1 \ldots m \} \end{array}
$$

Let $F ( \overline { { w } } )$ and each $f _ { i } ( \overline { { w } } )$ be convex functions. Then, the optimal objective function value of the dual problem created using Lagrangian relaxation is almost always the same as that of the primal. 

We use the qualification “almost always,” because we also need a relatively weak condition referred to as Slater’s condition, which states that at least one strictly feasible point exists satisfying $f _ { i } ( \overline { { w } } ) < 0$ for each i. For most machine learning problems, these conditions hold by default. For simplicity in presentation, we will drop this condition in the subsequent exposition. Many optimization problems in machine learning such as support vector machines and logistic regression satisfy strong duality. 

## 6.4.1 Kuhn-Tucker Optimality Conditions

We start by repeating the primal and dual minimax optimization problems: 

$$
\begin{array}{l} P = \min _ {\overline {{w}}} \max _ {\overline {{\alpha}} \geq 0} H (\overline {{w}}, \overline {{\alpha}}) \quad \text {(OP1)} \\ D = \max _ {\overline {{\alpha}} \geq 0} \min _ {\overline {{w}}} H (\overline {{w}}, \overline {{\alpha}}) \quad \text {(OP2)} \end{array}
$$

We refer to these primal and dual optimization problems as OP1 and OP2, respectively. We make the following observation, which is true irrespective of the convexity structure of the primal optimization problem: 

For a solution $( \overline { { w } } , \overline { { \alpha } } )$ to be optimal to the primal minimax problem (OP1), w must be a feasible solution satisfying $f _ { i } ( \overline { { w } } ) \leq 0$ for each i (see Lemma 6.4.1). Furthermore, if any constraint $f _ { i } ( \overline { { w } } ) \leq 0$ is satisfied with strict inequality, then setting $\alpha _ { i } = 0$ ensures maximization of (OP1) with respect to α. This ensures that we have $\alpha _ { i } f _ { i } ( \overline { { w } } ) = 0$ for each i for any optimal solution to (OP1). 

The condition $\alpha _ { i } f _ { i } ( \overline { { w } } ) = 0$ is referred to as the complementary slackness condition. The (general) minimax theorem of mathematics tells us that the optimal pairs $( \overline { { w } } , \overline { { \alpha } } )$ are the same in the two cases of the primal and the dual minimax problems [i.e., (OP1) and (OP2)], when the function $H ( \overline { { w } } , \overline { { \alpha } } )$ is convex in w and concave in α. Although we have shown the complementary slackness condition only for (OP1), any solution (w, α) that is optimal for $( \mathrm { O P 1 } )$ must also be optimal for (OP2) and vice versa for problems with convex structure. Therefore, the complementary slackness condition must hold for both (OP1) and (OP2) in such problems. The primal constraints are of the form $f _ { i } ( \overline { { w } } ) \leq 0$ and the corresponding dual constraints are of the form $\alpha _ { i } \geq 0$ . The complementary slackness condition implies that at most one of these complementary conditions can be “slack” (i.e., satisfied at strict inequality). 

Another important condition that needs to be satisfied is that the gradient of $H ( \overline { { w } } , \overline { { \alpha } } )$ with respect to the primal variables w need to be set to 0 in the dual because we are minimizing this objective function at each fixed value of α. This leads to the stationarity conditions: 

$$
\nabla_ {\overline {{w}}} H (\overline {{w}}, \overline {{\alpha}}) = \nabla F (\overline {{w}}) + \sum_ {i = 1} ^ {m} \alpha_ {i} \nabla f _ {i} (\overline {{w}}) = \overline {{0}}
$$

The Kuhn-Tucker conditions are obtained by combining the primal feasibility conditions, dual feasibility conditions, complementary slackness conditions, and stationarity conditions. For convex objective functions, these represent the first-order conditions that are both necessary and sufficient for optimality: 

Theorem 6.4.1 (Kuhn-Tucker Optimality Conditions) Consider an optimization problem in which we wish to minimize the convex objective function $F ( \overline { { w } } )$ , subject to convex constraints of the form $f _ { i } ( \overline { { w } } ) \leq 0$ for $i \in \{ 1 \ldots m \}$ . Then, a solution w is optimal for the primal and a solution α is optimal for the dual, if and only if: 

Feasibility: w is feasible for the primal by satisfying each $f _ { i } ( \overline { { w } } ) \leq 0$ and α is feasible for the dual by being nonnegative. 

Complementary slackness: We have $\alpha _ { i } f _ { i } ( \overline { { w } } ) = 0$ for each $i \in \{ 1 \ldots m \}$ 

Stationarity: The primal and dual variables are related as follows: 

$$
\nabla F (\overline {{w}}) + \sum_ {i = 1} ^ {m} \alpha_ {i} \nabla f _ {i} (\overline {{w}}) = 0
$$

Note that one does not have to worry about second-order optimality conditions in the case of convex optimization problems. The Kuhn-Tucker optimality conditions are useful because they provide an alternative approach to solving the optimization problem by simply finding a feasible solution to a set of constraints as follows: 

Observation 6.4.1 For a convex optimization problem, any pair $( \overline { { w } } , \overline { { \alpha } } )$ that satisfies primal feasibility $f _ { i } ( \overline { { w } } ) \leq 0$ , dual feasibility $\alpha _ { i } \geq 0$ , complementary slackness $\alpha _ { i } f _ { i } ( \overline { { w } } ) = 0$ , and the stationarity conditions is an optimal solution to the original optimization problem. 

The stationarity conditions relate the primal and dual variables, and therefore they are often useful for eliminating primal variables from the Lagrangian. We will also refer to them as primal-dual $( P D )$ constraints, because they relate primal and dual variables at optimality. The stationarity conditions are often used to formulate the minimax dual purely in terms of the dual variable (and therefore create a pure maximization problem). We discuss this general procedure in the next section. 

## 6.4.2 General Procedure for Using Duality

The general procedure for using duality in constrained optimization is somewhat similar across problems. The first step is to formulate $L ( \overline { { \alpha } } )$ which is the objective function of the dual problem (OP2), after eliminating primal variables: 

$$
L (\overline {{\alpha}}) = \min _ {\overline {{w}}} H (\overline {{w}}, \overline {{\alpha}})\tag{6.9}
$$

The primal variables $\overline { { w } }$ can often be eliminated from $L ( \overline { { \alpha } } )$ by setting the gradients of $H ( \overline { { w } } , \overline { { \alpha } } )$ with respect to the primal variables $\overline { { w } }$ to zero. Setting the gradient with respect to primal variables to zero will result in exactly as many conditions as the number of primal variables. These are exactly the stationarity conditions of the previous section, which represent a subset of the Kuhn-Tucker optimality conditions. We also refer to these conditions as primal-dual (PD) constraints, because they relate the primal and dual variables. The (PD) constraints can be used to substitute for (and eliminate) the primal variables ${ \overline { { w } } } ,$ and obtain a pure maximization objective function $L ( \overline { { \alpha } } )$ , which is expressed in terms of $\overline { { \alpha } } .$ . In some cases, the feasibility and complementary slackness conditions are also used in the elimination process. At the end of the day, the process of generating the dual from the primal is almost purely a mechanical and algebraic process based on the Kuhn-Tucker conditions. While the specific mechanics might vary somewhat at the detailed level, the basic principle remains the same across different problems. In Section 6.4.3, we will provide an example of this procedure with the $L _ { 1 }$ -loss support vector machine. Furthermore, guided exercises $( \mathrm { i . e . , }$ exercises broken up into simpler steps), are also available on the $L _ { \mathrm { { 2 ^ { - } } } } \mathrm { { l o s s } }$ SVM and logistic regression, and the reader is advised to work them out in the same sequence as they occur. 

## 6.4.2.1 Inferring the Optimal Primal Solution from Optimal Dual Solution

One needs to compute the optimal primal variables in order to have an interpretable solution. Therefore, a natural question arises as to how one can infer an optimal primal solution w from the optimal dual solution α. In this context, the (PD) constraints $( { \mathrm { i . e . } }$ , the stationarity conditions) are very helpful, because they can be used to substitute in the values of the optimal dual variables and solve for the primal variables (although the algebraic approach might vary slightly across problems). 

## 6.4.3 Application: Formulating the SVM Dual

In order to illustrate how duality is used in machine learning, we will revisit the support vector machine (SVM). We have already shown how the primal stochastic gradient descent approach can be used for the SVM in Section 4.8.2 of Chapter 4. We repeat the objective function of Equation 4.51: 

$$
J = \frac {1}{\lambda} \sum_ {i = 1} ^ {n} \max \{0, (1 - y _ {i} [ \overline {{W}} \cdot \overline {{X}} _ {i} ^ {T} ]) \} + \frac {1}{2} \| \overline {{W}} \| ^ {2} \quad [ \mathrm{Hinge-lossSVM} ]
$$

Note that this objective function is cosmetically different from Equation 4.51 by the scaling factor of $1 / \lambda$ . We have made this cosmetic adjustment because one often uses the notation corresponding to the slack penalty $C = 1 / \lambda$ in the literature on dual SVM optimization, which is what we will use in subsequent restatements of this formulation. In order to create the dual, we would like to reformulate the problem as a constrained optimization problem, while simplifying the objective function without the maximization operator. This is achieved with the use of slack variables $\xi _ { 1 } \ldots \xi _ { n }$ as follows: 

$$
\begin{array}{l} \text {Minimize} J = \frac {1}{2} \| \overline {{W}} \| ^ {2} + C \sum_ {i = 1} ^ {n} \xi_ {i} \\ \text {subject to:} \\ \xi_ {i} \geq 1 - y _ {i} [ \overline {{W}} \cdot \overline {{X}} _ {i} ^ {T} ] \forall i \in \{1 \ldots n \} [ \text {Margin Constraints} ] \\ \xi_ {i} \geq 0 \forall i \in \{1 \ldots n \} [ \text {Nonnegativity Constraints} ] \end{array}
$$

Ideally, we would like $\xi _ { i } = \operatorname* { m a x } \{ 0 , ( 1 - y _ { i } [ \overline { { W } } \cdot \overline { { X } } _ { i } ^ { T } ] ) \}$ . Note that the constraints do allow values of $\xi _ { i }$ larger than max $\{ 0 , ( 1 - y _ { i } [ \overline { { W } } \cdot \overline { { X } } _ { i } ^ { T } ] ) \}$ , but such values can never be optimal. The first set of constraints is referred to as the set of “margin” constraints, because they define the margins for the predicted values of $y _ { i }$ beyond which points are not penalized. For example, if $\overline { { W } } \cdot \overline { { X } } _ { i } ^ { T }$ has the same sign as $y _ { i }$ and its absolute value is “sufficiently” positive by a margin of $1 , \xi _ { i }$ will drop to 0. Therefore, the point is not penalized. Strictly speaking, the constraints need to be converted to $^ { 6 6 } \leq ^ { 9 }$ form by multiplying with 1, but we can take care of it during the relaxation by multiplying the penalties with 1. We introduce the Lagrangian multiplier $\alpha _ { i }$ for the ith of n margin constraints and the multiplier $\gamma _ { i }$ for the ith nonnegativity constraint on $\xi _ { i }$ . With these notations, the Lagrangian relaxation is as follows: 

$$
L _ {D} (\overline {{\alpha}}, \overline {{\gamma}}) = \text {Minimize} J _ {r} = \frac {1}{2} \| \overline {{W}} \| ^ {2} + C \sum_ {i = 1} ^ {n} \xi_ {i} - \underbrace {\sum_ {i = 1} ^ {n} \alpha_ {i} (\xi_ {i} - 1 + y _ {i} (\overline {{W}} \cdot \overline {{X}} _ {i} ^ {T}))} _ {\text {Relax margin constraint}} - \underbrace {\sum_ {i = 1} ^ {n} \gamma_ {i} \xi_ {i}} _ {\text {Relax} \xi_ {i} \geq 0}
$$

Here, $J _ { r }$ is the relaxed objective function. Since the relaxed constraints are inequalities, it follows that both $\alpha _ { i }$ and $\gamma _ { i }$ must be nonnegative for the relaxation to make sense. Therefore, when we optimize over the dual variables such as $\alpha _ { i }$ and $\gamma _ { i }$ , the optimization problem has a box constraint structure, which makes it somewhat simpler to solve. In this type of dual problem, one first minimizes over primal variables (with dual variables fixed) to obtain $L _ { D } ( \overline { { \alpha } } , \overline { { \gamma } } )$ and then maximizes $L _ { D } ( \overline { { \alpha } } , \overline { { \gamma } } )$ over the dual variables, while imposing box constraints on them. One can express this type of minimax optimization problem as follows: 

$$
L _ {D} ^ {*} = \max _ {\alpha_ {i}, \gamma_ {i} \geq 0} L _ {D} (\overline {{\alpha}}, \overline {{\gamma}}) = \max _ {\alpha_ {i}, \gamma_ {i} \geq 0} \min _ {\overline {{W}}, \xi_ {i}} J _ {r}
$$

As discussed in the previous section, the general approach to solving the dual is to use the (PD) constraints to eliminate the primal variables in order to create a pure maximization problem in terms of the dual variables. The (PD) constraints are obtained by setting the gradient of the minimax objective with respect to the primal variables to 0. This gives us exactly as many constraints as the number of primal variables, which is precisely what we need for eliminating all of them: 

$$
\frac {\partial J _ {r}}{\partial \overline {{W}}} = \overline {{W}} - \sum_ {i = 1} ^ {n} \alpha_ {i} y _ {i} \overline {{X}} _ {i} ^ {T} = \overline {{0}}, [ \text { Gradient   with   respect   to } \overline {{W}} \text { is } 0 ]\tag{6.10}
$$

$$
\frac {\partial J _ {r}}{\partial \xi_ {i}} = C - \alpha_ {i} - \gamma_ {i} = 0, \forall i \in \{1 \dots n \}\tag{6.11}
$$

The equations resulting from the partial derivatives with respect to $\xi _ { i }$ are independent of $\xi _ { i }$ , but the resulting equations are still useful in eliminating $\xi _ { i }$ from $J _ { r }$ . This is because the coefficient of $\xi _ { i }$ in $J _ { r }$ is $\left( C - \alpha _ { i } - \gamma _ { i } \right)$ , which turns out to be 0 based on Equation 6.11. The ability to drop $\xi _ { i }$ is a direct result of the linearity of the $J _ { r }$ in $\xi _ { i } ;$ the linear coefficient of $\xi _ { i }$ in $J _ { r }$ is also its derivative, which is set to 0 as an optimality condition. Furthermore, based on Equation 6.10, we can substitute $\begin{array} { r } { \overline { { W } } = \sum _ { i = 1 } ^ { n } \alpha _ { i } y _ { i } \overline { { X } } _ { i } ^ { T } } \end{array}$ everywhere it occurs in $J _ { r }$ By dropping the terms involving $\xi _ { i }$ and substituting for $\overline { { W } } , J _ { r }$ is simplified as follows: 

$$
\begin{array}{l} J _ {r} = \frac {1}{2} \| \overline {{W}} \| ^ {2} + \sum_ {i = 1} ^ {n} \alpha_ {i} (1 - y _ {i} (\overline {{W}} \cdot \overline {{X}} _ {i} ^ {T})), \quad [ \text {Dropping terms with} \xi_ {i} ] \\ = \frac {1}{2} \| \sum_ {j = 1} ^ {n} \alpha_ {j} y _ {j} \overline {{X}} _ {j} ^ {T} \| ^ {2} + \sum_ {i = 1} ^ {n} \alpha_ {i} (1 - y _ {i} \sum_ {j = 1} ^ {n} \alpha_ {j} y _ {j} \overline {{X}} _ {i} \cdot \overline {{X}} _ {j}), \quad [ \text {Substituting} \overline {{W}} = \sum_ {j = 1} ^ {n} \alpha_ {j} y _ {j} \overline {{X}} _ {j} ^ {T} ] \\ = \sum_ {i = 1} ^ {n} \alpha_ {i} - \frac {1}{2} \sum_ {i = 1} ^ {n} \sum_ {j = 1} ^ {n} \alpha_ {i} \alpha_ {j} y _ {i} y _ {j} \overline {{X}} _ {i} \cdot \overline {{X}} _ {j}, \quad [ \text {Algebraic simplification} ] \end{array}
$$

This objective function is expressed purely in terms of the dual variables. Furthermore, the variable $\gamma _ { i }$ has dropped out of the optimization formulation. Nevertheless, the constraint $\gamma _ { i } \geq 0$ also needs to be modified by substituting $\gamma _ { i }$ as $C - \alpha _ { i }$ (cf. Equation 6.11): 

$$
\gamma_ {i} = C - \alpha_ {i} \geq 0
$$

Therefore, the variables $\alpha _ { i }$ satisfy the box constraints $0 \leq \alpha _ { i } \leq C$ . We can multiply the objective function by 1 in order to turn the maximization problem into a minimization problem: 

$$
\text { Minimize } _ {0 \leq \overline {{\alpha}} \leq C} \frac {1}{2} \sum_ {i = 1} ^ {n} \sum_ {j = 1} ^ {n} \alpha_ {i} \alpha_ {j} y _ {i} y _ {j} \overline {{X}} _ {i} \cdot \overline {{X}} _ {j} - \sum_ {i = 1} ^ {n} \alpha_ {i}
$$

Beyond the fact that the dual problem (in minimization form) is always convex (see Exercise 12), one can show that the leading term in the quadratic is of the form $\overline { { \alpha } } ^ { T } H \overline { { \alpha } }$ , where H is a positive semidefinite matrix of similarities between points. This makes the dual problem convex. To this effect, we assert the following result: 

Observation 6.4.2 The quadratic term $\begin{array} { r } { \sum _ { i = 1 } ^ { n } \sum _ { j = 1 } ^ { n } \alpha _ { i } \alpha _ { j } y _ { i } y _ { j } \overline { { X } } _ { i } \cdot \overline { { X } } _ { j } } \end{array}$ in the dual SVM can be expressed in the form $\overline { { \alpha } } ^ { T } B B ^ { T } \overline { { \alpha } } .$ , where B is an $n \times d$ matrix in which the ith row of B contains $y _ { i } { \overline { { X } } } _ { i }$ . In other words, the ith row of B simply contains the ith data instance, after multiplying it with the class label $y _ { i } \in \{ - 1 , + 1 \}$ 

This result can be shown by simply expanding the $( i , j )$ th term of $\overline { { \alpha } } ^ { T } B B ^ { T } \overline { { \alpha } }$ . As shown in Lemma 3.3.14 of Chapter 3, matrices of the form $\dot { B } \dot { B } ^ { T }$ are always positive semidefinite. Therefore, this is a convex optimization problem. 

## 6.4.3.1 Inferring the Optimal Primal Solution from Optimal Dual Solution

As discussed in Section 6.4.2.1, the (PD) constraints can be used to infer the primal variables from the dual variables. In the particular case of the SVM, the constraints correspond to Equations 6.10–6.11. Among these constraints, Equation 6.10 is in a particularly useful form, because it directly yields all the primal variables in terms of the dual variables: 

$$
\overline {{W}} = \sum_ {i = 1} ^ {n} \alpha_ {i} y _ {i} \overline {{X}} _ {i} ^ {T}
$$

One can obtain the slack variables $\xi _ { i }$ by using the constraints among the primal variables and substituting the inferred value of $\overline { W }$ 

## 6.4.4 Optimization Algorithms for the SVM Dual

The dual is a constrained optimization problem, albeit a simple one because of the use of box constraints. The dual can be solved using almost all the primal optimization techniques discussed earlier in this chapter. Therefore, we still need the primal algorithms for constrained optimization, even though we are working with the dual! In the following, we provide some examples of computational algorithms. 

## 6.4.4.1 Gradient Descent

We state the dual problem in minimization form with box constraints: 

$$
\begin{array}{l} \text {Minimize} L _ {D} = \frac {1}{2} \sum_ {i = 1} ^ {n} \sum_ {j = 1} ^ {n} \alpha_ {i} \alpha_ {j} y _ {i} y _ {j} \overline {{X}} _ {i} \cdot \overline {{X}} _ {j} - \sum_ {i = 1} ^ {n} \alpha_ {i} \\ \text {subject to:} \\ 0 \leq \alpha_ {i} \leq C \quad \forall i \in \{1 \dots n \} \end{array}
$$

The partial derivative of $L _ { D }$ with respect to $\alpha _ { k }$ is as follows: 

$$
\frac {\partial L _ {D}}{\partial \alpha_ {k}} = y _ {k} \sum_ {s = 1} ^ {n} y _ {s} \alpha_ {s} \overline {{X}} _ {k} \cdot \overline {{X}} _ {s} - 1 \forall k \in \{1 \dots n \}\tag{6.12}
$$

One can use the standard gradient-descent procedure: 

$$
\overline {{\alpha}} \Leftarrow \overline {{\alpha}} - \eta \left[ \frac {\partial L _ {D}}{\partial \overline {{\alpha}}} \right]
$$

One problem is that an update might lead to some of the values of $\alpha _ { k }$ violating the feasibility constraints. In such a case, we project such infeasible components of α to the feasible box, as shown in Figure 6.3. In other words, the value of each $\alpha _ { k }$ is reset to 0 if it becomes negative, and it is reset to C if it exceeds C. Therefore, one starts by setting the vector of Lagrangian parameters $\overline { { \alpha } } = [ \alpha _ { 1 } \ldots \alpha _ { n } ]$ to an n-dimensional vector of 0s and uses the following update steps with learning rate η: 

repeat
Update $\alpha_{k}\Leftarrow\alpha_{k}+\eta\left[1-y_{k}\sum_{s=1}^{n}y_{s}\alpha_{s}\overline{X}_{k}\cdot\overline{X}_{s}\right]$ for each $k\in\{1\ldots n\}$ ; $\left\{\text{Update is equivalent to } \overline{\alpha} \Leftarrow \overline{\alpha} - \eta \left[\frac{\partial L_{D}}{\partial \overline{\alpha}}\right]\right\}$ for each $k \in \{1 \ldots n\}$ do begin $\alpha_{k} \Leftarrow \min\{\alpha_{k}, C\};$ $\alpha_{k} \Leftarrow \max\{\alpha_{k}, 0\};$ endfor;
until convergence 

It is noteworthy that the gradient-descent procedure updates all the components $\alpha _ { 1 } \ldots \alpha _ { n }$ at a time. This is the main difference from coordinate descent, which updates a single component at a time, and it chooses a specific learning rate for that component, so that that particular value of $\alpha _ { k }$ is optimized. This is the point of discussion in the next section. 

## 6.4.4.2 Coordinate Descent

In coordinate descent, the update for $\alpha _ { k }$ should be such that the updated value is optimized. In other words, the partial derivative of the dual objective function $L _ { D }$ with respect to $\alpha _ { k }$ should be set to 0. By using Equation 6.12 to set the partial derivative with respect to $\alpha _ { k }$ to 0, we obtain the following condition: 

$$
y _ {k} \sum_ {s = 1} ^ {n} y _ {s} \alpha_ {s} \overline {{X}} _ {k} \cdot \overline {{X}} _ {s} - 1 = 0
$$

On bringing all the terms involving $\alpha _ { k }$ to one side, we obtain: 

$$
\alpha_ {k} \| \overline {{X}} _ {k} \| ^ {2} y _ {k} ^ {2} = 1 - y _ {k} \sum_ {s \neq k} y _ {s} \alpha_ {s} \overline {{X}} _ {k} \cdot \overline {{X}} _ {s}
$$

We can set $y _ { k } ^ { 2 } = 1$ because each $y _ { k } \in \{ - 1 , + 1 \}$ 

$$
\alpha_ {k} = \frac {1 - y _ {k} \sum_ {s \neq k} y _ {s} \alpha_ {s} \overline {{X}} _ {k} \cdot \overline {{X}} _ {s}}{\| \overline {{X}} _ {k} \| ^ {2}} = \alpha_ {k} + \frac {1 - y _ {k} \sum_ {s = 1} ^ {n} y _ {s} \alpha_ {s} \overline {{X}} _ {k} \cdot \overline {{X}} _ {s}}{\| \overline {{X}} _ {k} \| ^ {2}}
$$

In the very final simplification, we added and subtracted $\alpha _ { k }$ on the right-hand side. One can simply treat the above as an iterative update (like gradient-descent) in which $\alpha _ { k }$ is updated at learning rate $\eta _ { k } = 1 / \Vert \overline { { X } } _ { k } \Vert ^ { 2 }$ 

$$
\begin{array}{l} \alpha_ {k} \Leftarrow \alpha_ {k} + \eta_ {k} \left[ 1 - y _ {k} \sum_ {s = 1} ^ {n} y _ {s} \alpha_ {s} \overline {{X}} _ {k} \cdot \overline {{X}} _ {s} \right] \\ \alpha_ {k} \Leftarrow \alpha_ {k} - \eta_ {k} \left[ \frac {\partial L _ {D}}{\partial \alpha_ {k}} \right] [ \text {Equivalent update} ] \end{array}
$$

In other words, the update for coordinate descent looks just like gradient-descent, except that it is done in component-wise fashion with a component-specific learning rate: 

repeat
    for each $k \in \{1 \ldots n\}$ do begin
    Update $\alpha_k \Leftarrow \alpha_k + \eta_k \left[ 1 - y_k \sum_{s=1}^n y_s \alpha_s \overline{X}_k \cdot \overline{X}_s \right]$ ;
    { Update is equivalent to $\alpha_k \Leftarrow \alpha_k - \eta_k \left[ \frac{\partial L_D}{\partial \alpha_k} \right]$ } $\alpha_k \Leftarrow \min\{\alpha_k, C\}$ ; $\alpha_k \Leftarrow \max\{\alpha_k, 0\}$ ;
endfor;
until convergence 

It is instructive to compare the pseudocode for coordinate descent with the pseudocode for gradient descent in the previous section. It is evident that the main difference is that all components of α are updated in gradient descent (with the learning rate heuristically chosen), whereas updates are performed one component at a time in coordinate descent (with the learning rate specifically chosen to ensure optimality). The coordinate descent procedure always yields faster convergence than gradient descent. Furthermore, block coordinate descent, in which more than one variable is chosen at a time, is even more efficient. In fact, Platt’s popular sequential minimal optimization (SMO) [102] is an example of block coordinate descent. We also provide a series of practice problems for the $L _ { 2 } \mathrm { - S V M }$ , which provide the systematic steps for formulating its dual and solving it. We strongly advise the reader to work out the practice problems below using the provided solution for the hinge-loss SVM as a guideline. Working out these practice problems will provide the reader a better feel for the way in which dual optimization problems are solved. 

Problem 6.4.2 (Relaxation of $L _ { \mathrm { { 2 } } } { \bf { - } } { \bf { S V } } { \bf { M } } )$ Consider the following formulation for the $L _ { 2 } { \mathrm { - } } S V M { \mathrm { : } }$ 

$$
\text { Minimize } J = \frac {1}{2} \| \overline {{W}} \| ^ {2} + C \sum_ {i = 1} ^ {n} \xi_ {i} ^ {2}
$$

subject to: 

$$
\xi_ {i} \geq 1 - y _ {i} [ \overline {{W}} \cdot \overline {{X}} _ {i} ^ {T} ], \quad \forall i \in \{1 \dots n \}
$$

In comparison with the hinge-loss SVM, the parameter $\xi$ is squared in the objective function, and the nonnegativity constraints on $\xi _ { i }$ have been dropped. Discuss why dropping of nonnegativity constraints on $\xi _ { i }$ does not affect the optimal solution in this case. Write the minimax Lagrangian relaxation containing both primal and dual variables. Use the Lagrange parameter $\alpha _ { i }$ for the ith slack constraint to enable comparison with the hinge-loss SVM. 

Problem 6.4.3 (Primal-Dual Constraints of $L _ { \mathrm { { 2 } } } { \bf { - } } { \bf { S V } } { \bf { M } } )$ Let $\alpha _ { i }$ be the Lagrange parameter associated with the ith slack constraint. Show that setting the gradients of the Lagrangian relaxation to 0 (with respect to primal variables) yields the following primal-dual constraints: 

$$
\begin{array}{l} \overline {{W}} = \sum_ {i = 1} ^ {n} \alpha_ {i} y _ {i} \overline {{X}} _ {i} ^ {T} \\ \xi_ {i} = \alpha_ {i} / 2 C \end{array}
$$

Problem 6.4.4 (Dual Formulation of $L _ { \mathrm { { 2 } } } { \bf { - } } { \bf { S V } } { \bf { M } } )$ Use the Lagrangian relaxation and the primal-dual constraints in the previous two exercises to eliminate the primal variables from the minimax formulation. Show that the dual problem of the $L _ { 2 } { - } S V M$ is as follows: 

$$
M a x i m i z e _ {\overline {{\alpha}} \geq 0} \sum_ {i = 1} ^ {n} \alpha_ {i} - \frac {1}{2} \sum_ {i = 1} ^ {n} \sum_ {j = 1} ^ {n} \alpha_ {i} \alpha_ {j} y _ {i} y _ {j} (\overline {{X}} _ {i} \cdot \overline {{X}} _ {j} + \delta_ {i j} / 2 C)
$$

Here, $\delta _ { i j }$ is 1 $i f i = j$ , and $\theta ,$ otherwise. Note that the main difference from the dual formulation of the hinge-loss SVM is the addition of $\delta _ { i j } / 2 C$ to the dot product ${ \overline { { X } } } _ { i } \cdot { \overline { { X } } } _ { j }$ , in order to constrain the magnitudes of $\alpha _ { i } ^ { 2 }$ in a soft way rather than the explicit constraint $\alpha _ { i } \leq C$ 

Problem 6.4.5 (Optimization Algorithm for $\mathbf { \Gamma } _ { L _ { 2 } - \mathbf { S } } \mathbf { V } \mathbf { M }$ Dual) Carefully examine the gradient-descent and coordinate-descent pseudo-codes for the hinge-loss SVM in Sections 6.4.4.1 and $6 . 4 . 4 . 2$ . The actual updates of each $\alpha _ { k }$ always contain terms with $\overline { { X } } _ { k } \cdot \overline { { X } } _ { s }$ as a multiplicative factor for each s. Show that the gradient descent and coordinate descent algorithms for the dual $L _ { 2 } { - } S V M$ are exactly the same as the hinge-loss SVM, except that the dot product $\overline { { \boldsymbol { X } } } _ { k } \cdot \overline { { \boldsymbol { X } } } _ { s }$ within each update equation is substituted with $[ \overline { { X } } _ { k } \cdot \overline { { X } } _ { s } + ( \delta _ { k s } / 2 C ) ]$ The value of $\delta _ { k s }$ is 1 $i f k = s .$ , and 0, otherwise. Furthermore, the values of $\alpha _ { i }$ are not reset to C when they are larger than C. 

## 6.4.5 Getting the Lagrangian Relaxation of Unconstrained Problems

The Lagrangian relaxation is naturally designed for constrained problems, and the Lagrange multipliers automatically yield the dual variables. A natural question arises as to how one can create the dual in cases where the optimization problem is unconstrained to begin with. There are several approaches for achieving this goal, one of which uses Lagrangian relaxation. For example, a dual approach for logistic regression uses a parametrization approach to construct the dual [68]. We refer the reader to the bibliographic notes for discussions of other forms of duality. 

Here, it is important to understand that an optimization problem need not be formulated in a unique way. An unconstrained optimization problem can always be recast as a constrained problem by simply introducing additional variables for various terms in the objective function, and defining those variables within the constraints. The way in which the dual was generated for the hinge-loss SVM already provides a hint for the kinds of formula tions that are more friendly to creating dual problems. For example, the SVM formulation in Section 4.8.2 of Chapter 4 does not use slack variables, whereas the dual SVM of the previous section introduces slack variables for specific portions of the objective function, and then defines those slack variables within the constraints. This approach of generating additional variables for specific terms within the objective function provides a natural way to create a Lagrangian relaxation. Therefore, we summarize the basic approach for creating a Lagrangian relaxation of an unconstrained problem: 

Introduce new variables in lieu of specific parts of the objective function, and define those variables within the constraints. 

Here, it is important to understand that there is more than one way in which one might choose ways of defining the new variables. Correspondingly, one would obtain a different dual, and the structure of some might be more friendly than others to optimization. Learning to define the correct variables and constraints is often a matter of skill and experience. 

Consider the following simple 2-variable optimization problem without constraints: 

$$
\text { Minimize } J = (x - 1) ^ {2} / 2 + (y - 2) ^ {2} / 2
$$

One can easily solve this problem in any number of ways, including the use of gradient descent, or by simply setting each partial derivative to 0. In either case, one obtains an optimal solution $x = 1$ , and $y = 2$ with a corresponding objective function value of 0. However, it is instructive to formulate the dual of this optimization problem. In this case, we choose to introduce two new variables $\xi = x - 1$ and $\beta = y - 2$ . The resulting optimization problem is as follows: 

$$
\begin{array}{r l} & \text {Minimize} J = \xi^ {2} / 2 + \beta^ {2} / 2 \\ & \text {subject to:} \\ & \xi = x - 1 \\ & \beta = y - 2 \end{array}
$$

It is noteworthy that the constraints are equality constraints, and therefore the Lagrange multipliers would not have nonnegativity constraints either. We introduce the Lagrange multiplier $\alpha _ { 1 }$ with the first constraint and the multiplier $\alpha _ { 2 }$ with the second constraint. The corresponding Lagrangian relaxation then becomes the following: 

$$
L (\alpha_ {1}, \alpha_ {2}) = \mathrm{Minimize} _ {\xi , \beta , x, y,} \xi^ {2} / 2 + \beta^ {2} / 2 + \alpha_ {1} (\xi - x + 1) + \alpha_ {2} (\beta - y + 2)
$$

Note that the minimization is performed only over the primal variables, and $L ( \alpha _ { 1 } , \alpha _ { 2 } )$ needs to be maximized over the dual variables. In order to eliminate the four primal variables, we need to set the partial derivative with respect to each to zero, and obtain four stationarity constraints, which we also refer to as (PD) constraints. However, in this particular case, the (PD) constraints have a simple form: 

$$
\begin{array}{l} \frac {\partial J}{\partial \xi} = \xi + \alpha_ {1}, \frac {\partial J}{\partial \beta} = \beta + \alpha_ {2} \\ \frac {\partial J}{\partial x} = - \alpha_ {1}, \frac {\partial J}{\partial y} = - \alpha_ {2} \end{array}
$$

Setting the first two derivatives with respect to $\xi$ and $\beta$ to $0$ allows us to replace $\xi$ and $\beta$ with $- \alpha _ { 1 }$ and $- \alpha _ { 2 }$ , respectively. However, setting the second two derivatives with respect to x and $y$ to 0 yields $\alpha _ { 1 } = \alpha _ { 2 } = 0$ , which allows us to drop the penalty portions of the objective function. However, we need to include<sup>2</sup> the constraints that are independent of the primal variables $( \mathrm { i . e . , ~ } \alpha _ { 1 } = \alpha _ { 2 } = 0 )$ within the dual formulation. This yields the following trivial dual problem: 

$$
\begin{array}{r l} & \text {Maximize} \alpha_ {1} ^ {2} + \alpha_ {2} ^ {2} \\ & \text {subject to:} \\ & \alpha_ {1} = 0, \alpha_ {2} = 0 \end{array}
$$

In this case, the feasible space contains only one point with an objective function value of $0 .$ . Therefore, the optimal dual objective function value is 0 at $\alpha _ { 1 } = \alpha _ { 2 } = 0$ . Furthermore, since $\xi$ and $\beta$ are equal to $- \alpha _ { 1 }$ and $- \alpha _ { 2 }$ (according to the stationarity constraints), it follows that we have $\xi = x - 1 = 0$ and $\beta = y - 2 = 0$ . Note that this solution of $x = 1$ and $y = 2$ can be obtained by simply setting the derivative of the primal objective function to 0. 

## 6.4.5.1 Machine Learning Application: Dual of Linear Regression

Another example of an unconstrained optimization problem is linear regression. The training data contains n feature-value pairs $( \overline { { X } } _ { i } , y _ { i } )$ , and the target $\hat { y } _ { i }$ is predicted using $\hat { y } _ { i } \approx \overline { { W } } \cdot \overline { { X } } _ { i } ^ { T }$ Each ${ \overline { { X } } } _ { i }$ is a row of the $n \times d$ data matrix $D$ . The column vector of response variables is denoted by $\overline { { y } } = [ y _ { 1 } \ldots y _ { n } ] ^ { T }$ . The objective function minimizes the sum-of-squared errors over all training instances: 

$$
J = \frac {1}{2} \sum_ {i = 1} ^ {n} (y _ {i} - \overline {{W}} \cdot \overline {{X}} _ {i} ^ {T}) ^ {2} + \frac {\lambda}{2} \| \overline {{W}} \| ^ {2}\tag{6.13}
$$

This is again an unconstrained problem, but we somehow want to create the Lagrangian relaxation for it in order to generate the dual. In order to do so, we create new variables and new constraints by introducing a new variable $\xi _ { i } = y _ { i } - \overline { { W } } \cdot \overline { { X } } _ { i } ^ { T }$ for the error of each data point. The corresponding optimization problem is as follows: 

$$
\begin{array}{l} \text {Minimize} J = \frac {1}{2} \sum_ {i = 1} ^ {n} \xi_ {i} ^ {2} + \frac {\lambda}{2} \| \overline {{W}} \| ^ {2} \\ \text {subject to:} \\ \xi_ {i} = y _ {i} - \overline {{W}} \cdot \overline {{X}} _ {i} ^ {T}, \quad \forall i \in \{1 \ldots n \} \end{array}
$$

We introduce the dual variable $\alpha _ { i }$ for the ith constraint, which results in the following dual objective function: 

$$
L (\overline {{\alpha}}) = \mathrm{Minimize} _ {\overline {{W}}, \xi_ {i}} J = \frac {1}{2} \sum_ {i = 1} ^ {n} \xi_ {i} ^ {2} + \frac {\lambda}{2} \| \overline {{W}} \| ^ {2} + \sum_ {i = 1} ^ {n} \alpha_ {i} (- \xi_ {i} + y _ {i} - (\overline {{W}} \cdot \overline {{X}} _ {i} ^ {T}))
$$

Next, we will generate the primal-dual (PD) constraints by differentiating the objective function with respect to all the primal variables and setting it to zero. 

$$
\begin{array}{l} \frac {\partial J}{\partial \overline {{W}}} = \lambda \overline {{W}} - \sum_ {i = 1} ^ {n} \alpha_ {i} \overline {{X}} _ {i} ^ {T} = \overline {{0}} \\ \frac {\partial J}{\partial \xi_ {i}} = \xi_ {i} - \alpha_ {i} = 0, \quad \forall i \in \{1 \dots n \} \end{array}
$$

Substituting $\xi _ { i } = \alpha _ { i }$ and $\begin{array} { r } { \overline { { W } } = \sum _ { j = 1 } ^ { n } \alpha _ { j } \overline { { X } } _ { j } ^ { T } / \lambda } \end{array}$ , we obtain the following for $L ( \overline { { \alpha } } )$ purely in terms of only the dual variables: 

$$
\begin{array}{c} L (\overline {{\alpha}}) = \frac {1}{2} \sum_ {i = 1} ^ {n} \alpha_ {i} ^ {2} + \frac {1}{2 \lambda} \sum_ {i = 1} ^ {n} \sum_ {j = 1} ^ {n} \alpha_ {i} \alpha_ {j} \overline {{X}} _ {i} \cdot \overline {{X}} _ {j} + \sum_ {i = 1} ^ {n} \alpha_ {i} \left(- \alpha_ {i} + y _ {i} - \overline {{X}} _ {i} ^ {T} \cdot [ \sum_ {j = 1} ^ {n} \alpha_ {j} \overline {{X}} _ {j} ^ {T} ] / \lambda\right) \\ = \sum_ {i = 1} ^ {n} \alpha_ {i} y _ {i} - \sum_ {i = 1} ^ {n} \alpha_ {i} ^ {2} / 2 - \frac {1}{2 \lambda} \sum_ {i = 1} ^ {n} \sum_ {j = 1} ^ {n} \alpha_ {i} \alpha_ {j} \overline {{X}} _ {i} \cdot \overline {{X}} _ {j} \end{array}
$$

One can rewrite the above objective function in matrix form by replacing the d-dimensional row vectors $\overline { { X } } _ { 1 } \ldots \overline { { X } } _ { n }$ with a single $n \times d$ matrix D whose rows contain these vectors in the same order. Furthermore, the scalar variables are converted to vector forms such as $\overline { { \alpha } } = [ \alpha _ { 1 } \ldots \overline { { \alpha } } _ { n } ] ^ { T }$ and $\overline { { y } } = [ y _ { 1 } \ldots y _ { n } ] ^ { T }$ : 

$$
\begin{array}{r} L (\overline {{\alpha}}) = \overline {{\alpha}} ^ {T} \overline {{y}} - \frac {1}{2} \| \overline {{\alpha}} \| ^ {2} - \frac {1}{2 \lambda} \overline {{\alpha}} ^ {T} D D ^ {T} \overline {{\alpha}} \\ = \overline {{\alpha}} ^ {T} \overline {{y}} - \frac {1}{2 \lambda} \overline {{\alpha}} ^ {T} (D D ^ {T} + \lambda I) \overline {{\alpha}} \end{array}
$$

One can simply set the gradient of the objective function to 0 in order to solve for $\overline { { \alpha } }$ in closed form. By using matrix calculus to compute the gradient of the objective function, we obtain the following: 

$$
\begin{array}{l} (D D ^ {T} + \lambda I) \overline {{\alpha}} = \lambda \overline {{y}} \\ \overline {{\alpha}} = \lambda (D D ^ {T} + \lambda I) ^ {- 1} \overline {{y}} \end{array}
$$

It now remains to relate the optimal dual variables to the optimal primal variables by using the primal-dual constraints. From the (PD) constraints, we already know that $\overline { { W } } =$ $\begin{array} { r } { \sum _ { j = 1 } ^ { n } \alpha _ { j } \overline { { X } } _ { j } ^ { T } / \lambda = D ^ { T } \overline { { \alpha } } / \lambda } \end{array}$ . This yields the following optimal solution for primal variable W: 

$$
\overline {{W}} = D ^ {T} (D D ^ {T} + \lambda I _ {n}) ^ {- 1} \overline {{y}}\tag{6.14}
$$

Here, $I _ { n }$ is the $n \times n$ identity matrix. It is helpful to compare this solution with that obtained by setting the gradient of the primal loss function to zero. The resulting solution is described in Section 4.7 of Chapter 4. We repeat Equation 4.39 from that section here: 

$$
\overline {{W}} = (D ^ {T} D + \lambda I _ {d}) ^ {- 1} D ^ {T} \overline {{y}}\tag{6.15}
$$

At first glance, this solution seems to be different. However, the two solutions are really equivalent, and one can derive this result from the push-through identity (cf. Problem 1.2.13 of Chapter 1). Specifically, the following can be shown: 

$$
D ^ {T} (D D ^ {T} + \lambda I _ {n}) ^ {- 1} = (D ^ {T} D + \lambda I _ {d}) ^ {- 1} D ^ {T}\tag{6.16}
$$

Another example of an unconstrained problem is logistic regression, which is discussed in Section 4.8.3 of Chapter 4. The following sequence of problems provides a step-by-step guide to how one can formulate the dual of logistic regression [140]. Since logistic regression is a fundamental problem in machine learning, it is to advised to work out this sequence of problems for better insights. 

Problem 6.4.6 (Relaxation of Logistic Regression) Logistic regression is an unconstrained optimization problem, as evident from its objective function in Equation 4.56 of Chapter 4. Consider the following formulation for logistic regression: 

$$
\begin{array}{r l} & M i n i m i z e J = \frac {1}{2} \| \overline {{W}} \| ^ {2} + C \sum_ {i = 1} ^ {n} l o g (1 + e x p [ \xi_ {i} ]) \\ & \quad s u b j e c t t o: \\ & \xi_ {i} = - y _ {i} (\overline {{W}} \cdot \overline {{X}} _ {i} ^ {T}) \end{array}
$$

Discuss why this objective function is the same as Equation 4.56 with an appropriate choice of C. Assume that the other notations are the same as Equation 4.56. Formulate a Lagrangian relaxation of this problem, where $\alpha _ { i }$ is the dual variable used for the ith constraint associated with ${ \overline { { X } } } _ { i }$ 

Since the Lagrange multiplier is sign-unconstrained in this case, and the constraints are equality constraints, one could obtain either of two possible answers to the previous problem with different signs of $\alpha _ { i }$ . This issue is also applicable to the next problem, where you might get the results in the statement of the exercise with the sign of $\alpha _ { i }$ flipped. 

Problem 6.4.7 (Primal-Dual Constraints of Logistic Regression) Let $\alpha _ { i }$ be the $L a \mathrm { - }$ grange parameter associated with the ith slack constraint. Show that setting the gradients of the Lagrangian relaxation to $\boldsymbol { \theta }$ (with respect to primal variables) yields the following primal-dual constraints: 

$$
\begin{array}{l} \overline {{W}} = \sum_ {i = 1} ^ {n} y _ {i} \alpha_ {i} \overline {{X}} _ {i} ^ {T} \\ \alpha_ {i} = \frac {C}{1 + e x p (- \xi_ {i})} \end{array}
$$

Now discuss why $\alpha _ { i }$ must lie in the range (0, C) based on the primal dual constraints (just like the hinge-loss SVM). 

The similarity of the logistic dual with the hinge-loss SVM dual is not particularly surprising, given the fact that we have shown the similarity of the primal logistic regression objective function with that of the hinge-loss SVM, especially for the critical, difficult-to-classify points (see Section 4.8.4 of Chapter 4). 

Problem 6.4.8 Show that the dual of logistic regression can be expressed in minimization form as follows: 

$$
M i n i m i z e _ {\overline {{\alpha}}} \frac {1}{2} \sum_ {i = 1} ^ {n} \sum_ {j = 1} ^ {n} \alpha_ {i} \alpha_ {j} y _ {i} y _ {j} (\overline {{X}} _ {i} \cdot \overline {{X}} _ {j}) + \sum_ {i = 1} ^ {n} \alpha_ {i} l o g (\alpha_ {i}) + \sum_ {i = 1} ^ {n} (C - \alpha_ {i}) l o g (C - \alpha_ {i})
$$

Note that the objective function of logistic regression only makes sense for $\alpha _ { i } \in \mathsf { \Gamma } ( 0 , C )$ because the logarithm function can only have positive arguments. In practice, one explicitly adds the constraints $\alpha _ { i } ~ \in ~ ( 0 , C )$ to avoid an undefined objective function. This makes the entire formulation very similar to the hinge-loss SVM dual, and the pseudo-code in Section 6.4.4.1 can be used directly, but with stronger box-constraint updates to strictly within $( 0 , C )$ . Another difference is that $\alpha _ { k }$ is updated as follows: 

$$
\alpha_ {k} \Leftarrow \alpha_ {k} + \eta \left[ \log \frac {C - \alpha_ {k}}{\alpha_ {k}} - y _ {k} \sum_ {s = 1} ^ {n} y _ {s} \alpha_ {s} \overline {{X}} _ {k} \cdot \overline {{X}} _ {s} \right]
$$

The term $\log ( [ C - \alpha _ { k } ] / \alpha _ { k } )$ replaces 1 in the pseudo-code, and it tries to keep $\alpha _ { k }$ in the middle of the range (0, C). 

## 6.5 Penalty-Based and Primal-Dual Methods

The Lagrangian relaxation methods formulate the dual of the optimization problem by re laxing primal constraints in terms of the penalty variables. The idea is that the relaxed version of the problem always satisfies weak duality. Therefore, if we can come up with a relaxed version (with appropriate values of the penalty multipliers) that satisfies the primal constraints, then the resulting solution is also an optimal solution to the original problem (i.e., unrelaxed primal problem with constraints). This type of approach requires us to suc cessively modify the penalty variables and perform gradient descent on the relaxed problem until the primal constraints are satisfied. In all cases, the solution to the relaxed problem provides us hints as to whether the penalty variables should be increased or decreased. For example, if the primal constraints are violated on solving the relaxed problem then the penalty variables for the violated primal constraints need to be increased. Otherwise, if the constraints are not satisfied tightly, the penalty variables for the primal constraints can be decreased. The form of the penalty is sometimes different from a traditional Lagrangian relaxation, and in other cases can be shown to be exactly or almost equivalent. In the latter case, these methods are sometimes referred to as primal-dual methods because they simultaneously learn primal and dual variables. Even in cases where the form of the penalty constraint is not the same as a traditional Lagrangian relaxation, the broader principle is quite similar. In order to understand this point, we will first work with an example of an optimization problem with a single constraint as a motivating idea. 

## 6.5.1 Penalty Method with Single Constraint

Consider the following optimization problem in which we wish to minimize a convex function subject to a distance constraint. In other words, we wish to find the optimum point of the convex objective function $F ( \overline { { w } } )$ subject to the constraint that the distance between vector w and constant vector $\overline { { a } }$ is at most δ. Note that this problem arises frequently in machine learning, when using trust-region optimization in conjunction with the Newton method (cf. Section 5.6.3.1 of Chapter 5). This problem is stated as follows: 

$$
\begin{array}{c} \text {Minimize F(\overline {{w}})} \\ \text {subject to:} \\ \| \overline {{w}} - \overline {{a}} \| ^ {2} \leq \delta^ {2} \end{array}
$$

The first step is to solve the optimization problem while ignoring the constraint. If the optimal solution already satisfies the constraint (in spite of the fact that it was not used), then we need to do nothing else. We can simply terminate. On the other hand, if the constraint is violated, then we formulate the following relaxed version of the problem with penalty parameter $\alpha > 0 \mathrm { { ; } }$ 

$$
\text { Minimize } F (\overline {{w}}) + \alpha \left(\max \{\| \overline {{w}} - \overline {{a}} \| ^ {2} - \delta^ {2}, 0 \}\right) ^ {2}
$$

Note that there is no penalty or gain when the constraint is satisfied. This ensures that the objective function value of the relaxed problem is the same as that of the original problem as long as one operates in the feasible space. Choosing very small values of α might result in violation of the constraints. On the other hand, choosing large enough values of α will always result in feasible solutions, in which the penalty does not contribute anything to the objective function. An important observation about penalty functions is as follows: 

Observation 6.5.1 Consider a penalty-based variation of a constrained optimization problem in which violation of constraints is penalized and added to the objective function. Furthermore, feasible points have zero penalties (or gains). If the optimal solution to the penaltybased relaxation is feasible for the constraints in the original problem, then that solution is also optimal for the original problem. 

The above observation is the key to the success of penalty-based methods. We simply need to start with small enough values of α and gradually test successively large values of α until the relaxation yields a feasible solution. One can solve this problem by starting at $\alpha = 1$ and solving the optimization problem. If the constraints are satisfied, we terminate and report the corresponding value of the parameter vector w as optimal. If the solution is not feasible, one can double the value of α and perform gradient descent again to find the best value of the parameter vector w with gradient descent. One can use the parameter vector w at the end of an iteration as the starting point for gradient descent in the next iteration (with increased α). This reduces the work in the next iteration. This approach of increasing α is continued until no constraints are violated. It is also noteworthy that the relaxed objective function is convex when the objective function and the constraints are convex. 

## 6.5.2 Penalty Method: General Formulation

The general formulation of convex optimization problems is as follows: 

$$
\begin{array}{l l} \text { Minimize } F (\overline {{w}}) \\ \text { subject   to: } \\ f _ {i} (\overline {{w}}) \leq 0, & \forall i \in \{1 \ldots m \} \\ h _ {i} (\overline {{w}}) = 0, & \forall i \in \{1 \ldots k \} \end{array}
$$

To ensure convexity of this problem, the function $F ( \overline { { w } } )$ is convex, all the functions $f _ { i } ( \cdot )$ must be convex, and all the functions $h _ { i } ( \cdot )$ are linear. Note that the penalty method can be used even in the cases where these conditions are not met; however, in those cases, one might not be able to obtain the global optimum. Then, the relaxed objective function of this problem is as follows: 

$$
\text { Minimize } R (\overline {{w}}, \alpha) = F (\overline {{w}}) + \frac {\alpha}{2} \left(\sum_ {i = 1} ^ {m} \max \{0, f _ {i} (\overline {{w}}) \} ^ {2} + \sum_ {i = 1} ^ {k} h _ {i} (\overline {{w}}) ^ {2}\right)\tag{6.17}
$$

Note the difference between how equality and inequality constraints are treated. The penalty parameter $\alpha$ is always greater than zero. We make the following observation: 

Observation 6.5.2 (Convexity of Relaxation) $I f F ( \overline { { w } } )$ is convex, each $f _ { i } ( \overline { { w } } )$ is convex, and each $h _ { i } ( \overline { { w } } )$ is linear, then the relaxed objective function of Equation 6.17 is convex for $\alpha > 0$ 

The gradient of this objective function with respect to $\overline { { w } }$ can be computed as follows: 

$$
\nabla_ {\overline {{w}}} R (\overline {{w}}, \alpha) = \nabla F (\overline {{w}}) + \alpha \sum_ {i = 1} ^ {m} \max \{f _ {i} (\overline {{w}}), 0 \} \nabla f _ {i} (\overline {{w}}) + \alpha \sum_ {i = 1} ^ {k} h _ {i} (\overline {{w}}) \nabla h _ {i} (\overline {{w}})
$$

As in the case of single-variable penalty methods, we perform gradient descent at a fixed value of $\alpha .$ . In the event that the resulting solution w at termination is feasible, we use this parameter vector as the optimal solution. Otherwise, we increase α and repeat the process. In the next iteration, we can start with the vector $\overline { { w } }$ obtained from the previous iteration as a starting point. 

A natural question arises as to why one should not start with the largest possible value of α to begin with. After all, choosing large values of α ensures feasibility of the solution with respect to the constraints of the original problem. The main problem with using very large values of $\alpha$ is that it often leads to ill-conditioning during intermediate stages of the gradient descent, where the gradient is much more sensitive to some directions than others. As we have seen in Chapter $5 ,$ this type of situation can cause problems (such as “bouncing” behavior) in gradient descent, and convergence will not occur. This is the reason that one should generally start with smaller values of α, and increase it over time. This ensures that the algorithm will show good convergence behavior. 

## 6.5.3 Barrier and Interior Point Methods

Penalty-based methods do not yield intermediate values of w that are feasible. In contrast, barrier methods always maintain values of w that are not only feasible but strictly feasible. The notion of strict feasibility makes sense only for inequality constraints. Therefore, barrier methods are designed only for inequality constraints of the form $f _ { i } ( { \overline { { w } } } ) \geq 0 .$ . Note that we have flipped the direction of the inequality for notational ease. A point w is strictly feasible if and only if we have $f _ { i } ( \overline { { w } } ) > 0$ for each constraint. Obviously, such a point exists only when the feasible region has non-zero volume in the space. This is the reason that barrier methods are not designed for the case of equality constraints. Consider the following optimization problem: 

Minimize F(w) 

subject to: 

$$
f _ {i} (\overline {{w}}) \geq 0, \forall i \in \{1 \dots m \}
$$

Then, the barrier function $B ( \overline { { w } } , \alpha )$ is well-defined only for feasible values of the parameter vector ${ \overline { { w } } } ,$ and it is defined as follows: 

$$
B (\overline {{w}}, \alpha) = F (\overline {{w}}) - \alpha \sum_ {i = 1} ^ {m} \log (f _ {i} (\overline {{w}}))
$$

This is an example of the use of the logarithmic barrier function, although other choices (such as the inverse barrier function) exist. One observation is that the barrier function is convex as long as $F ( \overline { { w } } )$ is convex, and each $f _ { i } ( \overline { { w } } )$ is concave. This is because the logarithm[^concave-log-composition] of a concave function is concave, and the negative logarithm is therefore convex. The sum of convex functions is convex, and therefore the barrier function is convex. Note that we require each $f _ { i } ( \overline { { w } } )$ to be concave (rather than convex) because our inequality constraints are of the form $f _ { i } ( \overline { { w } } ) \geq 0$ rather than $f _ { i } ( \overline { { w } } ) \leq 0$ 

A key point is that each $f _ { i } ( \overline { { w } } )$ must be strictly greater than zero even for the objective function to be meaningfully evaluated at a given step; one cannot compute the logarithm of zero or negative values. Therefore, barrier methods start with feasible solutions w in the interior of the data. Furthermore, unlike penalty methods, one starts with large values of α in early iterations, and this value is reduced over time. At any fixed value of $\alpha ,$ , gradientdescent is performed on $\overline { { w } }$ to optimize the weight vector. Smaller values of $\alpha$ allow $\overline { { w } }$ to approach closer to the boundary of the feasible region defined by the constraints. This is because the barrier function always approaches $\infty$ near the boundary irrespective of the value of α, but small values of α allow a closer approach. However, small values of α also result in sharp ill-conditioning, and using small values of α early is bad for convergence. For example, using high values of α in the initial phases is helpful in maintaining strict feasibility of the weight vector w. 

In cases where the true optimal solution is not near the boundary of the feasible region, one will often approach the optimal solution quickly, and convergence is smooth. In these cases, the constraints might even be redundant, and the unconstrained version of the problem will yield the same solution. In more difficult cases, the optimal weight vector might lie near the boundary of the feasible region. As the feasible weight vector $\overline { { w } }$ approaches close enough to the boundary $f _ { i } ( \overline { { w } } ) \geq 0$ , the penalty contribution increases rapidly like a “barrier” and increases to $\infty$ when one reaches the boundary $f _ { i } ( \overline { { w } } ) = 0$ . Therefore, we only need relatively small values of α in order to ensure feasibility. However, at small values of α, the function becomes ill-conditioned near the boundary. Therefore, the barrier method starts with large values of α and gradually reduces it, while performing gradient descent with respect to w and fixed α. The optimal vector $\overline { { w } }$ at the end of a particular iteration is used as a starting point for the next iteration (with a smaller value of $\alpha )$ 

For gradient descent, the gradient of the objective function is as follows: 

$$
\nabla_ {\overline {{w}}} B (\overline {{w}}, \alpha) = \nabla F (\overline {{w}}) - \alpha \sum_ {i = 1} ^ {m} \frac {\nabla f _ {i} (\overline {{w}})}{f _ {i} (\overline {{w}})}
$$

Setting this gradient to zero yields the optimality condition. It is instructive to compare this optimality condition with the primal-dual (PD) constraint of the Lagrangian $L ( \overline { { w } } , \overline { { \alpha } } ) =$ $\begin{array} { r } { F ( \overline { { w } } ) - \sum _ { i } \alpha _ { i } f _ { i } ( \overline { { w } } ) } \end{array}$ : 

$$
\nabla_ {\overline {{w}}} L (\overline {{w}}, \overline {{\alpha}}) = \nabla F (\overline {{w}}) - \sum_ {i = 1} ^ {m} \alpha_ {i} \nabla f _ {i} (\overline {{w}}) = \overline {{0}}
$$

Here, we are using $\alpha _ { 1 } \ldots \alpha _ { k }$ as the Lagrangian parameters, which can be distinguished from the penalty parameter α by virtue of having a subscript. Furthermore, since the Lagrangian relaxation is computed using the $^ { 6 6 } \leq ^ { 9 }$ form of the constraint (which is $- f _ { i } ( \overline { { w } } ) \leq 0 )$ , we have a negative sign in front of each penalty term. Note that the value of $\alpha / f _ { i } ( \overline { { w } } )$ is an estimate of the Lagrangian multiplier $\alpha _ { i }$ , if one were to use the traditional Lagrangian relaxation $\begin{array} { r } { L ( \overline { { w } } , \overline { { \alpha } } ) = F ( \overline { { w } } ) - \sum _ { i } \alpha _ { i } f _ { i } ( \overline { { w } } ) } \end{array}$ . Interestingly, this means that we have $\alpha _ { i } f _ { i } ( \overline { { w } } ) = \alpha$ . Note that this is almost the complementary-slackness condition of Lagrangian relaxation, except that we have substituted 0 with a small value $\alpha .$ . Therefore, at small values of $\alpha$ , the optimality conditions of the (traditional) dual relaxation are nearly satisfied when one views the barrier function as a Lagrangian relaxation. The barrier method belongs to the class of interior point methods that approach the optimal solution from the interior of the feasible space. Therefore, one benefit of such methods is that they yield estimates of the Lagrangian dual variables in addition to yielding the primal values. 

## 6.6 Norm-Constrained Optimization

The use of eigenvectors in norm-constrained optimization is discussed in Section 3.4.5 of Chapter 3. This problem appears repeatedly in different types of machine learning problems, such as principal component analysis, singular value decomposition, and spectral clustering. We revisit an optimization problem introduced in Section 3.4.5: 

$$
\begin{array}{l} \text {Minimize} \sum_ {i = 1} ^ {k} \overline {{x}} _ {i} ^ {T} A \overline {{x}} _ {i} \\ \text {subject to:} \\ \| \overline {{x}} _ {i} \| ^ {2} = 1, \quad \forall i \in \{1 \ldots k \} \\ \overline {{x}} _ {1} \ldots \overline {{x}} _ {k} \text {are mutually orthogonal} \end{array}
$$

Here, A is a symmetric $d \times d$ matrix, and $\overline { { x } } _ { 1 } \ldots \overline { { x } } _ { k }$ correspond to the d-dimensional vectors containing the optimization variables. The symmetric nature of A is important in this case, because it simplifies the handling of the orthogonality constraints. This problem essentially tries to find the top-k orthogonal vectors in d dimensions, such that the sum of $\overline { { x } } _ { i } ^ { T } A \overline { { x } } _ { i }$ over all i is as small as possible. It is assumed that the value of k is less than or equal to $d ,$ or else the problem will not have feasible solutions. One difference from the problem discussed in Section 3.4.5 is that we are explicitly trying to minimize the objective function in this case, whereas the problem of Section 3.4.5 is stated more generally in terms of either minimization or maximization. Although one can deal with the maximization in an exactly analogous way, we deal only with minimization in order to create a crisp and unambiguous Lagrangian. It is also noteworthy that the orthogonality constraints can be restated as $\binom { k } { 2 }$ constraints of the form $\overline { { x } } _ { i } \cdot \overline { { x } } _ { j } = 0$ for all $i < j \le k$ . We introduce the Lagrangian multiplier $- \alpha _ { i }$ with each constraint of the form $\| \overline { { x } } _ { i } \| ^ { 2 } = 1$ . However, we do not choose to relax the orthogonality constraints. This is an example of the fact that Lagrangian relaxations can choose not to relax all the constraints, although one can obtain an equivalent solution by relaxing all constraints. Note that the Lagrangian multipliers are not constrained to be nonnegative because we are relaxing equality constraints rather than inequality constraints. We also add a negative sign in front of the multipliers for algebraic interpretability of the Lagrangian multipliers as eigenvalues (as we will show later). Correspondingly, one can write the Lagrangian relaxation as follows: 

$$
L (\overline {{\alpha}}) = \mathrm{Minimize} _ {\overline {{x}} _ {1} \ldots \overline {{x}} _ {k}} \text { are orthogonal } \sum_ {i = 1} ^ {k} \overline {{x}} _ {i} ^ {T} A \overline {{x}} _ {i} - \sum_ {i = 1} ^ {k} \alpha_ {i} (\| \overline {{x}} _ {i} \| ^ {2} - 1)
$$

Setting the gradient of the Lagrangian with respect to each $\overline { { x } } _ { i }$ to $0 ,$ , one obtains the following: 

$$
A \overline {{{x}}} _ {i} = \alpha_ {i} \overline {{{x}}} _ {i}, \quad \forall i \in \{1 \dots k \}
$$

As discussed earlier, we need to use the primal-dual (PD) constraints to eliminate the primal variables, and obtain an optimization problem in terms of the dual variables. Note that the constrains $A { \overline { { x } } } _ { i } = \alpha _ { i } { \overline { { x } } } _ { i }$ implies that the feasible space for $\alpha _ { i }$ is restricted to the d eigenvalues of A. Note that the orthogonality constraints on the vectors $\overline { { x } } _ { 1 } \ldots \overline { { x } } _ { k }$ are automatically satisfied because the eigenvectors of the symmetric matrix A are orthonormal. Using the (PD) constraints to substitute $A { \overline { { x } } } _ { i } = \alpha _ { i } { \overline { { x } } } _ { i }$ within the Lagrangian relaxation, we obtain the following: 

$$
\begin{array}{l} L (\overline {{\alpha}}) = \text {Minimize} _ {[ \overline {{x}} _ {1} \dots \overline {{x}} _ {k} \text {are orthogonal} ]} \sum_ {i = 1} ^ {k} \alpha_ {i} \overline {{x}} _ {i} ^ {T} \overline {{x}} _ {i} - \sum_ {i = 1} ^ {k} \alpha_ {i} (\| \overline {{x}} _ {i} \| ^ {2} - 1) \\ = \text {Minimize} _ {[ \text {Eigenvalues of A} ]} \sum_ {i = 1} ^ {k} \alpha_ {i} \end{array}
$$

Clearly, the above objective function is minimized over the smallest eigenvalues of A. Therefore, one obtains the following trivial dual problem: 

$$
\begin{array}{l} \text { Maximize } L (\overline {{\alpha}}) = \sum_ {i = 1} ^ {k} \alpha_ {i} \\ \text { subject   to: } \\ \alpha_ {1} \ldots \alpha_ {k} \text { are   smallest   eigenvalues   of } A \end{array}
$$

Note that the dual problem has a single point in its feasible solution. The primal solutions $\overline { { x } } _ { 1 } \ldots \overline { { x } } _ { k }$ , correspond to the smallest eigenvectors of A because of the (PD) constraints $A { \overline { { x } } } _ { i } = \alpha _ { i } { \overline { { x } } } _ { i }$ . A key point is that even though we assumed that the matrix A is symmetric, we did not assume that it is positive semi-definite. Therefore, the objective function might not be convex. In other words, strong duality is not guaranteed, and there might be a gap between the primal and dual solutions. One way of checking optimality of the derived primal solution is to explicitly check if a gap exists. In other words, we substitute the derived primal solution into the primal objective function and compare it with the dual objective function value at optimality. On making this substitution, we find that the primal objective function is also the sum of the smallest k eigenvalues. Therefore, there is no gap between the derived primal and dual solutions. The result of this section, therefore, provides an example of how it is sometimes possible to use Lagrangian relaxation even in the case of objective functions that are not convex. This section also provides a detailed proof of the norm-constrained optimization problem introduced in Section 3.4.5. 

The maximization variant of this problem is very similar: 

$$
\begin{array}{l} \text {Maximize} \sum_ {i = 1} ^ {k} \overline {{x}} _ {i} ^ {T} A \overline {{x}} _ {i} \\ \text {subject to:} \\ \| \overline {{x}} _ {i} \| ^ {2} = 1, \quad \forall i \in \{1 \ldots k \} \\ \overline {{x}} _ {1} \ldots \overline {{x}} _ {k} \text {are mutually orthogonal} \end{array}
$$

As in the case of the minimization version of the problem, it is important for the matrix A to be symmetric (because of orthogonality constraints). The approach to the maximization variant of the problem is very similar, and one can show that the best solution is obtained by choosing the largest eigenvectors of A. We leave the proof of this result as an exercise for the reader. 

Problem 6.6.1 Show that the optimal solution to the maximization variant of normconstrained optimization with objective function $\textstyle \sum _ { i = 1 } ^ { k } { \overline { { x } } } _ { i } ^ { T } A { \overline { { x } } } _ { i }$ corresponds to the largest k eigenvectors of the symmetric matrix A. 

## 6.7 Primal Versus Dual Methods

A natural question arises as to whether primal methods or dual methods are desirable in terms of performance. For example, in the case of the support vector machine, dual methods are used so universally that it has sometimes led to the impression that it is the only reasonable way to solve the optimization problem. Interestingly, many machine learning problems like the SVM can be posed as purely unconstrained problems in the primal (cf. Section 4.8.2 of Chapter 4), as long as we allow functions like maximization (e.g., max x, 0 ) within the objective function; therefore, complicated techniques for gradientdescent are often not required in the primal. Even in cases where the primal contains constraints, one can use techniques like (primal) projected gradient descent. Interestingly, to create the dual problem, we actually add constraints and variables to the primal, so that a Lagrangian relaxation can be created (cf. Section 6.4.5). This fascination of the machine learning community with the dual has been pointed out in a seminal paper [28]: 

“The vast majority of text books and articles introducing support vector machines (SVMs) first state the primal optimization problem, and then go directly to the dual formulation. A reader could easily obtain the impression that this is the only possible way to train an SVM.” 

An incorrect perception among some data scientists is that the dual is useful for solving the kernel SVM using similarities between points (rather than feature values), whereas the primal can be solved using only the feature values. Here, one observation is that the primal optimization problem for an $n \times d$ data matrix D is often posed in terms of the scatter matrices $D ^ { T } D$ , whereas the dual optimization problem is often posed in terms of the similarity matrices $D D ^ { T }$ . Note that all the dual optimization problems posed in this chapter contain the dot-product similarity ${ \overline { { X } } } _ { i } \cdot { \overline { { X } } } _ { j }$ within the objective function; therefore, one can write the objective function in terms of only the similarities between the ith and jth points. This observation is useful in cases where one wants to use arbitrary similarities between points in lieu of their feature representations. In some cases, one might want to use a domainspecific similarity, another kernel-based similarity (cf. Chapter 9), or a heuristic similarity function between objects that are not inherently multidimensional. Such techniques are referred to as kernel methods. However, the idea that dual objective functions are essential for the use of kernel methods is a widespread misconception. As we will see in Chapter 9, there is a systematic way in which every primal objective function discussed in this chapter and the previous chapters can be recast in terms of similarities. This approach uses a fundamental idea in linear algebra, known as the representer theorem. Note that the dual problems are often constrained optimization problems like the primal (albeit with simple box constraints). Therefore, all that the dual formulation achieves is to provide another perspective to the problem, which might have (relatively minor) benefits. 

For example, consider the issue of computational efficiency for a problem with n data points and d dimensions. The scatter matrix (used in the primal) has $O ( d ^ { 2 } )$ entries, whereas the similarity matrix (used in the dual) has $O ( n ^ { 2 } )$ entries. Therefore, the primal is often cheaper to solve when the dimensionality is smaller than the number of points. This situation is quite common. On the other hand, if the number of points is smaller than the dimensionality, the dual methods can be cheaper. However, some principles like the representer theorem (cf. Chapter 9) enable techniques for the primal, which are of similar complexity as the dual. 

Another point to be kept in mind is that most gradient descent methods arrive at an approximately optimal objective function value. After all, there are many practical challenges associated with computational optimization, and one often arrives at a numerically approximate solution. However, the primal has the advantage that the level of final approximation is guaranteed, because we are directly optimizing the objective function we wanted in the first place. On the other hand, the final dual solution needs to be mapped to a primal solution via the primal-dual constraints. For example, on computing the dual variables $\alpha _ { 1 } \ldots \alpha _ { n }$ in the hinge-loss SVM, the primal solution W is computed as $\begin{array} { r } { \overline { { W } } = \sum _ { i } \alpha _ { i } y _ { i } \overline { { X } } _ { i } ^ { T } } \end{array}$ Optimizing the dual objective function approximately might provide an arbitrarily poor solution for the primal. Although the primal and dual objective function values are exactly the same at optimality (for convex objective functions like the SVM), this is not the case for approximately optimal solutions; the approximate dual objective function value (which is a function of $\alpha _ { 1 } \ldots . \alpha _ { n } )$ might be quite different from the final objective function value when translated to the primal solution. Finally, intermediate primal solutions are more interpretable than dual solutions. This interpretability has an advantage from a practical point of view, and early termination is easier in the event of computational constraints. The dual approach has been historically favored in models like support vector machines. However, there is no inherent reason to so so, given the vast number of simple methods available for primal optimization. Our recommendation is to always use a primal method where possible. 

## 6.8 Summary

Many optimization problems have constraints in them, which makes the solution methodol ogy more challenging. Several methods for handing constrained optimization were discussed in this chapter, such as projected gradient descent, coordinate descent, and Lagrangian re laxation. Penalty-based and barrier methods combine ideas from primal and dual formula tions. Among these methods, primal methods have some advantages because of their better interpretability. Nevertheless, dual problems can also work well in some settings, where the number of points is fewer than the number of variables. 

## 6.9 Further Reading

The dual algorithm for SVMs was introduced in the original paper by Cortes and Vap nik [30]. The formulation of the dual for logistic regression is discussed in [68, 140], and various numerical algorithms are compared in [93]. Techniques for kernel logistic regres sion based on the representer theorem are presented in [142]. Detailed discussions of dual methods for SVMs are provided in [31]. Dual coordinate descent methods for the SVM and logistic regression are proposed in [64, 136]. Although the Lagrangian relaxation is the most common approach for formulating the dual of a problem, it is not the only way to do so. As long as we can parameterize a problem with additional variables, so that its minimax solution provides the true optimum, it can be used to formulate a dual problem. An example of such an approach is that for logistic regression [68]. 

## 6.10 Exercises

1. Suppose you want to find the largest area of rectangle that can be inscribed in a circle of radius 1. Formulate a 2-variable optimization problem with constraints to solve this problem. Discuss how you can convert this problem into a single-variable optimization problem without constraints. 

2. Consider the following optimization problem: 

$$
\begin{array}{c} \text { Minimize } x ^ {2} + 2 x + y ^ {2} + 3 y \\ \text { subject   to: } \\ x + y = 1 \end{array}
$$

Suppose that $( x _ { 0 } , y _ { 0 } )$ is a point satisfying the constraint $x + y = 1$ . Compute the projected gradient at $( x _ { 0 } , y _ { 0 } )$ 

3. Use the method of Gaussian elimination to eliminate both the constraint and variable y in Exercise 2. Compute the optimal solution of the resulting unconstrained problem. What is the optimal objective function value? 

4. Compute the dual of the objective function in Exercise 2. Compute the optimal solution as well as the resulting objective function value. 

5. Implement a gradient-descent algorithm for linear regression with box constraints. Use Python or any other programming language of your choice. 

6. Linear programming dual: Consider the following linear programming optimiza tion problem with respect to primal variables $\overline { { w } } = [ w _ { 1 } , w _ { 2 } , \ldots w _ { d } ] ^ { T }$ 

$$
\begin{array}{l} \text {Minimize} \sum_ {i = 1} ^ {d} c _ {i} w _ {i} \\ \text {subject to:} \\ A \overline {{w}} \leq \overline {{b}} \end{array}
$$

Here, A is an $n \times d$ matrix, and $\bar { b }$ is an n-dimensional column vector. Formulate the dual of this optimization problem by using the Lagrangian relaxation only in terms of dual variables. Are there any conditions under which strong duality holds? 

7. Quadratic programming dual: Consider the following quadratic programming optimization problem with respect to primal variables $\overline { { w } } = [ w _ { 1 } , w _ { 2 } , \ldots w _ { d } ] ^ { T }$ : 

$$
\begin{array}{l} \text {Minimize} \frac {1}{2} \overline {{w}} ^ {T} Q \overline {{w}} + \sum_ {i = 1} ^ {d} \overline {{c}} ^ {T} \overline {{w}} \\ \text {subject to:} \\ A \overline {{w}} \leq \overline {{b}} \end{array}
$$

Here, $Q$ is a $d { \times } d$ matrix, A is an $n \times d$ matrix, c is a d-dimensional column vector, and b is an n-dimensional column vector. Formulate the dual of this optimization problem by using the Lagrangian relaxation only in terms of dual variables. Assume that $Q$ is invertible. Are there any conditions under which strong duality holds? 

8. Consider the SVM optimization problem where we explicitly allow a bias variable b. In other words, the primal SVM optimization problem is stated as follows: 

$$
J = \sum_ {i = 1} ^ {n} \max \{0, (1 - y _ {i} [ \overline {{W}} \cdot \overline {{X}} _ {i} ^ {T} ] + b) \} + \frac {\lambda}{2} \| \overline {{W}} \| ^ {2}
$$

Compute the dual of this optimization formulation by using analogous steps to those discussed in the chapter. How would you handle the additional constraint in the dual formulation during gradient descent? 

9. As you will learn in Chapter 9, the primal formulation for least-squares regression can be recast in terms of similarities $s _ { i j }$ between pairs of data points as follows: 

$$
J = \frac {1}{2} \sum_ {i = 1} ^ {n} (y _ {i} - \sum_ {p = 1} ^ {n} \beta_ {p} s _ {p i}) ^ {2} + \frac {\lambda}{2} \sum_ {i = 1} ^ {n} \sum_ {j = 1} ^ {n} \beta_ {i} \beta_ {j} s _ {i j}
$$

Here, $s _ { i j }$ is the similarity between points i and $j .$ . Convert this unconstrained optimization problem into a constrained problem, and formulate the dual of the problem in terms of $s _ { i j }$ 

10. Let $\overline { { z } } \in \mathcal { R } ^ { d }$ lie outside the ellipsoid $\overline { { x } } ^ { T } A \overline { { x } } + \overline { { b } } ^ { T } \overline { { x } } + c \leq 0$ , where A is a $d \times d$ positive semi-definite matrix and $\overline { { x } } \in \mathcal { R } ^ { d }$ . We want to find the closest projection of z on this convex ellipsoid to enable projected gradient descent. Use Lagrangian relaxation to show that the projection point $\overline { { z } } _ { 0 }$ must satisfy the following: 

$$
\overline {{z}} - \overline {{z}} _ {0} \propto 2 A \overline {{z}} _ {0} + \overline {{b}}
$$

Interpret this condition geometrically in terms of the tangent to the ellipsoid. 

11. Consider the following optimization problem: 

$$
\begin{array}{c} \text {Minimize} x ^ {2} - y ^ {2} - 2 x y + z ^ {2} \\ \text {subject to:} \\ x ^ {2} + y ^ {2} + z ^ {2} \leq 2 \end{array}
$$

Imagine that we are using coordinate descent in which we are currently optimizing the variable x, when y and z are set to 1 and 0, respectively. Solve for x. Then, solve for y by setting x and z to their current values. Finally, solve for z in the same way. Perform another full cycle of coordinate descent to confirm that coordinate descent cannot improve further. Provide an example of a solution with a better objective function value. Discuss why coordinate descent was unable to find an optimal solution. 

12. Consider the dual objective function in Lagrangian relaxation, as a function of only the dual variables: 

$$
L (\overline {{\alpha}}) = \mathrm{Minimize} _ {\overline {{w}}} \left[ F (\overline {{w}}) + \sum_ {i = 1} ^ {m} \alpha_ {i} f _ {i} (\overline {{w}}) \right]
$$

The notations here for $F ( \cdot )$ and $f _ { i } ( \cdot )$ are the same as those used in Section 6.4. Show that $L ( \overline { { \alpha } } )$ is always concave in α, irrespective of the convexity structure of the original optimization problem. 

13. Nonnegative box regression: Formulate the Lagrangian dual (purely in terms of dual variables) for L -regularized linear regression $D \overline { { w } } \approx \overline { { y } }$ with $n \times d$ data matrix D, regressand vector y, and with nonnegativity constraints $\overline { { w } } \geq 0$ on the parameter vector. 

14. Hard Regularization: Consider the case where instead of Tikhonov regularization, you solve the linear regression problem of minimizing $\| A { \overline { { x } } } - { \overline { { b } } } \| ^ { 2 }$ subject to the spherical constraint $\| \overline { { x } } \| \leq r$ . Formulate the Lagrangian dual of the problem with variable $\alpha \geq 0$ Show that the primal and dual variables are related at optimality in a similar way to Tikhonov regularization: 

$$
\overline {{{{x}}}} = (A ^ {T} A + \alpha I) ^ {- 1} A ^ {T} \overline {{{{b}}}}
$$

Under what conditions is α equal to 0? If α is non-zero, show that it is equal to the solution to the following secular equation: 

$$
\overline {{b}} ^ {T} A (A ^ {T} A + \alpha I) ^ {- 2} A ^ {T} \overline {{b}} = r ^ {2}
$$

15. Propose a (primal) gradient-descent algorithm for the hard regularization model of the previous exercise. Use the projected gradient-descent method. The key point is in knowing how to perform the projection step. 

16. Best subset selection: Consider an $n \times d$ data matrix D in which you want to find the best subset of k features that are related to the n-dimensional regressand vector y. Therefore, the following mixed integer program is formulated with d-dimensional real vector ${ \overline { { w } } } ,$ , d-dimensional binary vector z, and an a priori (constant) upper bound M on each coefficient in ${ \overline { { w } } } .$ . The optimization problem is to minimize $\| D \overline { { w } } - \overline { { y } } \| ^ { 2 }$ subject to the following constraints: 

$$
\overline {{z}} \in \{0, 1 \} ^ {d}, \overline {{w}} \leq M \overline {{z}}, \overline {{1}} ^ {T} \overline {{z}} = k
$$

The notation 1 denotes a d-dimensional vector of 1s. Propose an algorithm using block coordinate descent for this problem, where each optimized block contains just two integer variables and all real variables. 

17. Duality Gap: Suppose that you are running the dual gradient descent algorithm for the SVM, and you have the (possibly suboptimal) dual variables $\alpha _ { 1 } \ldots \alpha _ { n }$ in the current iteration. Propose a quick computational procedure to estimate an upper bound on how far this dual solution is from optimality. [Hint: The current dual solution can be used to construct a primal solution.] 

18. State whether the following minimax functions $f ( x , y )$ satisfy John von Neumann’s strong duality condition, where $x$ is the minimization variable and y is the maximization variable: (i) $f ( x , y ) = x ^ { 2 } + 3 x y - y ^ { 4 } , \mathrm { ( i i ) } f ( x , y ) = x ^ { 2 } + x y + y ^ { 2 }$ , (iii) $f ( x , y ) = \sin ( y - x )$ , and $( \operatorname { i v } ) \ f ( x , y ) = \sin ( y - x )$ for $0 \leq x \leq y \leq \pi / 2$ 

19. Failure of coordinate descent: Consider the problem of minimizing $x ^ { 2 } + y ^ { 2 }$ , subject to $x + y \ge 1$ . Show using Lagrangian relaxation that the optimal solution is $x = y =$ 0.5. Suppose that you start coordinate descent for this problem at $x = 1$ and $y = 0$ Discuss why coordinate descent will fail. 

20. Propose a linear variable transformation for Exercise 19, so that coordinate descent will work on the reformulated problem. 

21. Formulate a variation of an SVM with hinge loss, in which the binary target (drawn from $- 1 \ \mathrm { o r \ + 1 } )$ is known to be non-negatively correlated with each feature based on prior knowledge. Propose a variation of the gradient descent method by using only feasible directions.

[^concave-log-composition]: Since the logarithm is concave, we know that:
    
    $$
    \log[\lambda f_i(\overline{w}_1)+(1-\lambda)f_i(\overline{w}_2)] \geq \lambda\log[f_i(\overline{w}_1)]+(1-\lambda)\log[f_i(\overline{w}_2)]
    \tag{6.18}
    $$
    
    At the same time, we know that $f_i(\lambda\overline{w}_1+(1-\lambda)\overline{w}_2) \geq \lambda f_i(\overline{w}_1)+(1-\lambda)f_i(\overline{w}_2)$ because $f_i(\cdot)$ is concave. Since, the logarithm is an increasing function, we can take the logarithm of both sides to show the result that $\log[f_i(\lambda\overline{w}_1+(1-\lambda)\overline{w}_2)] \geq \log[\lambda f_i(\overline{w}_1)+(1-\lambda)f_i(\overline{w}_2)]$. Combining this inequality with Equation 6.18 using transitivity, we can show that $\log[f_i(\lambda\overline{w}_1+(1-\lambda)\overline{w}_2)] \geq \lambda\log[f_i(\overline{w}_1)]+(1-\lambda)\log[f_i(\overline{w}_2)]$. In other words, $\log(f_i(\cdot))$ is concave. More generally, we just went through all the steps required to show that the composition $g(f(\cdot))$ of two concave functions is concave as long as $g(\cdot)$ is non-decreasing. Closely related results are available in Lemma 4.3.2.
