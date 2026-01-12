Here is the breakdown of the commands you provided, presented with the **Output** first, followed by the **Code** used to create it.

---

### **1. Inline Math Modes**

**Output:**

**Code:**

```latex
$x + y = z$

```

**Output:**

**Code:**

```latex
$\frac{a}{b}$

```

**Output:**
(x + y = z)
**Code:**

```latex
\(x + y = z\)

```

**Output:**
(\frac{a}{b})
**Code:**

```latex
\(\frac{a}{b}\)

```

---

### **2. Inline Math Styling**

**Output:**
 (Forces display size)
**Code:**

```latex
$\displaystyle \frac{a}{b}$

```

**Output:**
 (Forces inline size)
**Code:**

```latex
$\textstyle \frac{a}{b}$

```

**Output:**
 (Smaller script size)
**Code:**

```latex
$\scriptstyle x$

```

---

### **3. Fractions**

**Output:**
 (Standard)
**Code:**

```latex
$\frac{a}{b}$

```

**Output:**
 (Text-style/small)
**Code:**

```latex
$\tfrac{a}{b}$

```

**Output:**
 (Display-style/big)
**Code:**

```latex
$\dfrac{a}{b}$

```

**Output:**
 (Continued fraction - extra vertical space)
**Code:**

```latex
$\cfrac{a}{b}$

```

---

### **4. Superscript/Subscript**

**Output:**

**Code:**

```latex
$x^2 + y_1$

```

**Output:**

**Code:**

```latex
$x^{2n}$

```

**Output:**

**Code:**

```latex
$x_{i,j}$

```

**Output:**

**Code:**

```latex
$x_1^2$

```

---

### **5. Square Root**

**Output:**

**Code:**

```latex
$\sqrt{x}$, $\sqrt[3]{x}$, $\sqrt[n]{x^m}$

```

---

### **6. Display Math Environments**

**Output:**



*(Note: The (1) appears automatically in LaTeX)*
**Code:**

```latex
\begin{equation}
E = mc^2
\label{eq:einstein}
\end{equation}

```

**Output:**



*(No number)*
**Code:**

```latex
\begin{equation*}
E = mc^2
\end{equation*}

```

**Output:**



*(Numbers both lines)*
**Code:**

```latex
\begin{align}
x &= 1 \\
y &= 2
\end{align}

```

**Output:**



*(No numbers)*
**Code:**

```latex
\begin{align*}
x &= 1 \\
y &= 2
\end{align*}

```

**Output:**



*(One number for the whole block)*
**Code:**

```latex
\begin{equation}
\begin{split}
x &= 1 + 2 \\
&= 3
\end{split}
\end{equation}

```

**Output:**
*(Centered pile of equations, no alignment)*



**Code:**

```latex
\begin{gather}
x = 1 \\
y = 2
\end{gather}

```

---

### **7. Advanced Math Formatting**

**Output:**

**Code:**

```latex
$\mathbf{A}$, $\mathbf{x}$

```

**Output:**

**Code:**

```latex
$\boldsymbol{x}$

```

**Output:**

**Code:**

```latex
$\mathbb{R}$, $\mathbb{N}$, $\mathbb{Z}$

```

**Output:**

**Code:**

```latex
$\mathcal{L}$, $\mathcal{F}$

```

**Output:**

**Code:**

```latex
$\mathfrak{G}$, $\mathfrak{A}$

```

**Output:**

**Code:**

```latex
$\mathrm{d}x$

```

**Output:**

**Code:**

```latex
$\text{if } x > 0$

```

**Output:**

**Code:**

```latex
$\operatorname{sin}(x)$

```

**Output:**

**Code:**

```latex
$\mathit{xyz}$

```

**Output:**

**Code:**

```latex
$\mathsf{A}$

```

**Output:**

**Code:**

```latex
$\mathtt{code}$

```

**Output:**

**Code:**

```latex
$\textcolor{red}{x} + \textcolor{blue}{y}$

```

---

### **8. Operators and Relations**

**Output:**

**Code:**

```latex
$a \pm b$, $a \mp b$, $a \times b$, $a \div b$

```

**Output:**

**Code:**

```latex
$a \cdot b$, $a^b$, $\sqrt[n]{a}$

```

**Output:**

**Code:**

```latex
$a = b$, $a \neq b$, $a < b$, $a > b$

```

**Output:**

**Code:**

```latex
$a \leq b$, $a \geq b$, $a \equiv b$

```

**Output:**

**Code:**

```latex
$a \approx b$, $a \sim b$, $a \propto b$

```

---

### **9. Set Notation & Logic**

**Output:**

**Code:**

```latex
$a \in A$, $a \notin A$, $A \subset B$

```

**Output:**

**Code:**

```latex
$A \subseteq B$, $A \cap B$, $A \cup B$

```

**Output:**

**Code:**

```latex
$A \setminus B$, $A \times B$, $\emptyset$

```

**Output:**

**Code:**

```latex
$\forall x$, $\exists x$, $\neg p$, $p \land q$, $p \lor q$

```

**Output:**

**Code:**

```latex
$\Rightarrow$, $\Leftarrow$, $\Leftrightarrow$

```

---

### **10. Calculus**

**Output:**

**Code:**

```latex
$\frac{dy}{dx}$, $\partial_x f$, $\nabla f$

```

**Output:**

**Code:**

```latex
$\int f(x) dx$, $\iint f dA$, $\oint f ds$

```

**Output:**

**Code:**

```latex
$\sum_{i=1}^{n}$, $\prod_{i=1}^{n}$

```

**Output:**

**Code:**

```latex
$\lim_{x \to \infty}$

```

---

### **11. Matrix Environments**

**Output:**

**Code:**

```latex
\begin{pmatrix}
a & b \\
c & d
\end{pmatrix}

```

**Output:**

**Code:**

```latex
\begin{bmatrix}
a & b \\
c & d
\end{bmatrix}

```

**Output:**

**Code:**

```latex
\begin{vmatrix}
a & b \\
c & d
\end{vmatrix}

```

**Output:**

**Code:**

```latex
\begin{Vmatrix}
a & b \\
c & d
\end{Vmatrix}

```

**Output:**

**Code:**

```latex
\begin{matrix}
a & b \\
c & d
\end{matrix}

```

---

### **12. Cases, Binomials, and Braces**

**Output:**

**Code:**

```latex
f(x) = \begin{cases}
0 & \text{if } x < 0 \\
1 & \text{if } x \geq 0
\end{cases}

```

**Output:**

**Code:**

```latex
$\binom{n}{k}$, $\dbinom{n}{k}$, $\tbinom{n}{k}$

```

**Output:**

**Code:**

```latex
$\underbrace{a+b}_{2}$, $\overbrace{a+b}^{2}$

```

---

### **13. Delimiters (Parentheses Sizing)**

**Output:**

*(Note: These automatically grow to fit the fraction)*
**Code:**

```latex
\left( \right), \left[ \right], \left\{ \right\}

```

**Output:**

**Code:**

```latex
\left| \right|, \left\| \right\|, \left\langle \right\rangle

```

**Output:**

*(Manual sizing)*
**Code:**

```latex
\big(, \Big(, \bigg(, \Bigg(

```
