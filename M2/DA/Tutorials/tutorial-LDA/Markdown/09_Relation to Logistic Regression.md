## 9. Relation to Logistic Regression

According to Eqs. (16) and (32), Gaussian and Bernoulli distributions are used for likelihood (class conditional) and prior, respectively, in LDA and QDA. Thus, we are making assumptions for the likelihood and prior, although we finally work with posterior in LDA and QDA according to Eq. (15). Logistic regression (Kleinbaum et al., 2002) says why do we make assumptions on the likelihood and prior when we want to work on posterior finally. Let us make assumption directly for the posterior. 

In logistic regression, first a linear function is applied to the data to have $\beta ^ { \top } { \boldsymbol x } ^ { \prime }$ where $\mathbb { R } ^ { d + 1 } \ni \pmb { x } ^ { \prime } = [ \pmb { x } ^ { \top } , \hat { 1 } ] ^ { \top }$ and $\beta \in \mathbb { R } ^ { d + 1 }$ include the intercept. Then, logistic function is used in order to have a value in range $( 0 , 1 )$ to simulate probability. Therefore, in logistic regression, the posterior is assumed to be: 

$$
\begin{array}{l} \mathbb {P} (\mathcal {C} (\boldsymbol {x}) \mid X = \boldsymbol {x}) \\ = \Big (\frac {\exp (\boldsymbol {\beta} ^ {\top} \boldsymbol {x} ^ {\prime})}{1 + \exp (\boldsymbol {\beta} ^ {\top} \boldsymbol {x} ^ {\prime})} \Big) ^ {\mathcal {C} (\boldsymbol {x})} \Big (\frac {1}{1 + \exp (\boldsymbol {\beta} ^ {\top} \boldsymbol {x} ^ {\prime})} \Big) ^ {1 - \mathcal {C} (\boldsymbol {x})}, \end{array}\tag{55}
$$

where $\mathcal { C } ( \pmb { x } ) \in \{ - 1 , + 1 \}$ for the two classes. Logistic regression considers the coefficient $\beta$ as the parameter to be optimized and uses Newton’s method (Boyd & Vandenberghe, 2004) for the optimization. Therefore, in summary, logistic regression makes assumption on the posterior while LDA and QDA make assumption on likelihood and prior. 

