原文：https://compilation-course.github.io/lexical-and-syntax-analysis/5-grammars.html

保存日期：2026-09-13。网站当前版本；图片及外部资源仍使用在线链接。

## Limited Expressivity for finite automata

DFA (Deterministic Finite Automata) are very efficient at parsing regular
languages. Unfortunately the expressivity of regular languages is limited.

For example, the language \(L\_{ab} = {a^nb^n}\) with \(n \geq 1\) is not regular.

Indeed, a DFA has a finite number of states. Recognizing words in \(L\_{ab}\)
requires keeping track of the number of \(a\) symbols to ensure that it matches
the number of \(b\) symbols. Since \(n\) is arbitrarily large, this is not possible
with a finite number of states.

More formally, this can be proved by contradiction with the *pumping lemma (Lemme de l’étoile)*.

---

**Proof**

Suppose \(L\_{ab}\) is regular.

The *pumping lemma* tells us that there is a \(n \geq 1\) such that every string
\(w \in L\_{ab}\) with \(|w| \geq n\) can be written as \(w = xyz\) satisfying

* \[|y| \geq 1\]
* \[|xy| \leq n\]
* \[\forall k \geq 0, xy^kz \in L\_{ab}\]

Let us consider \(w = a^nb^n\) which belongs to \(L\_{ab}\) and is longer than \(n\).
Therefore \(a^nb^n\) can be decomposed as three substrings \(xyz\) satisfying above
properties. Because \(|xy| \leq n\), \(x\) and \(y\) are only composed of \(a\) symbols.

Let us consider \(w'=xy^2z\). Since \(y\) is only composed of \(a\) symbols, \(w'\) has
exactly \(n\) symbols \(b\) and strictly more than \(n\) symbols \(a\). Therefore \(w'\)
does not belong to \(L\_{ab}\), contradicting the pumping lemma.

---

Most programming languages include recursively nested constructions. For
example nested parenthesis, such as `((3+(7/9)) - 2)` or nested control blocks
such as `if a then (if b then c else d) else f`. These constructs with
arbitrarily deep recursive nesting cannot be parsed with DFA, as we just saw.

Since we cannot use DFA, parsers will use the more expressive formalism of
*Context Free Grammars*.

## Context Free Grammars

### Definition

A context-free grammar \(G\) is defined by four elements, \(G=(V, S, \Sigma, P)\), where

1. \(V\) is the finite alphabet of the *non-terminal* symbols.
2. \(S\) is the *start non-terminal symbol* and belongs to \(V\).
3. \(\Sigma\) is the finite alphabet of the *terminal* symbols. \(V\) and \(\Sigma\) are disjoint.
4. \(P\) is a finite set of grammar rules. \(P \subset V \times (V \cup \Sigma)^\*\)

A grammar rule is usually written, with \(\alpha \in V\) and \(\beta\_1, \beta\_2, \ldots, \beta\_k \in (V \cup \Sigma)\), as

\(\alpha \rightarrow \beta\_1 \beta\_2 \ldots \beta\_k\).

In the above expression,

* \(\alpha\) is a non-terminal.
* \(\beta\_1, \ldots \beta\_k\) are either terminals or non-terminals.

---

**Example**

Consider a grammar \(G\_1\) with

1. \[V = \{S, T\}\]
2. \(S\) start symbol
3. \[\Sigma = \{a,b,\#\}\]
4. The following \(P\) set of grammar rules,

\[\begin{aligned}
S &\rightarrow T\#\\
T &\rightarrow aTb \\
T &\rightarrow ab \\
\end{aligned}\]

---

### Applying grammar rules

When applying a grammar rule, we replace inside a word, the left-hand-side
symbol \(\alpha\) by the right-hand-side symbols \(\beta\_1\ldots\beta\_k\).

Let us have two words \(u,v \in (V \cup \Sigma)^\*\). We will say that \(v\) is
produced from \(u\), when \(u\) is obtained by replacing left-hand-side symbol in
\(u\) by its right-hand-side counterpart in a grammar. We will note \(u
\Rightarrow v\).

In case of one or more rule applications, \(u\_1 \Rightarrow u\_2 \Rightarrow \ldots v\), we will say that \(v\) derives from \(u\) and we will write \(u\stackrel{\*}{\Rightarrow} v\).

---

**Example**

Consider grammar \(G\_1\) from previous example.

The word, \(aaabbb\#\) derives from \(S\), indeed
\(\begin{aligned}
S &\Rightarrow T\# &&\text{(by applying first rule)} \\
T\# &\Rightarrow aTb\# &&\text{(by applying second rule)} \\
aTb\# &\Rightarrow aaTbb\# &&\text{(by applying second rule)} \\
aaTbb\# &\Rightarrow aaabbb\# &&\text{(by applying third rule)} \\
\end{aligned}\)

---

Context Free Grammars are called *context free* because rules can be applied
independently of the context, that is to say the neighboring symbols.

### Language recognized by a grammar

We will say that the language \(L(G)\) recognized by a grammar \(G\) is the set of
all words composed of terminal symbols that derive from \(S\).

\[L(G) = \{w \in \Sigma\* | S \stackrel{\*}{\Rightarrow} w \}\]

For instance, in the previous example, \(L(G\_1) = L\_{ab}\)

### Parse Trees and ambiguous grammars

Given grammar \(G\_2\),

1. \[V = \{S, E\}\]
2. \(S\) start symbol
3. \[\Sigma = \{num, \#\}\]
4. The following \(P\) set of grammar rules,

\[\begin{aligned}
S &\rightarrow E\#\\
E &\rightarrow E + E\\
E &\rightarrow num \\
\end{aligned}\]

Let’s consider the word, \(num + num + num\).
This word belongs to \(L(G\_2)\) because
\(S \Rightarrow E\# \Rightarrow E+E\# \\
\Rightarrow E+num\# \Rightarrow E+E+num\# \\
\Rightarrow E+num+num\# \Rightarrow num+num+num\#\)

This first derivation can also be represented as a *Parse Tree*,

```
Parse tree for first derivation
           S
           |
           E#
           |                       ((num+num)+num)
         E + E#
        /     \
      E + E   num
      |   |
     num num
```

Interestingly, in this grammar a second derivation also produces this same word.
\(S \Rightarrow E\# \Rightarrow E+E\# \\
\Rightarrow num+E\# \Rightarrow num+E+E\# \\
\Rightarrow num+num+E\# \Rightarrow num+num+num\#\)

```
Parse tree for second derivation
           S
           |
           E#
           |                       (num+(num+num))
         E + E#
        /     \
       num   E + E  
             |   |
            num num
```

When the same word admits multiple parse trees, we will say that the grammar is
ambiguous.

## Backus-Naur Form (BNF)

A common notation to represent grammars is the [Backus-Naur Form](https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form#Introduction).  
This notation will be used during lab 2.