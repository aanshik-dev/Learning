# CS306: Machine Learning — Comprehensive Master Exam Preparation Notes
**Course:** CS306 Machine Learning  
**Curriculum & Source Material:** IIIT Guwahati Lectures, Mid-Semester Exam Paper, and Student Handwritten Notebook (`myNotes-ml.pdf`)  
**Target:** Complete Theoretical Mastery, Mathematical Derivations, Conceptual Insights, and Numerical Problem Walkthroughs  

---

# Table of Contents
1. [Module 1: Introduction to Machine Learning & Data Fundamentals](#module-1-introduction-to-machine-learning--data-fundamentals)
2. [Module 2: Basic Statistics & Correlation Analysis](#module-2-basic-statistics--correlation-analysis)
3. [Module 3: Linear Regression & Ordinary Least Squares (OLS)](#module-3-linear-regression--ordinary-least-squares-ols)
4. [Module 4: Model Performance Metrics & Model Fitting](#module-4-model-performance-metrics--model-fitting)
5. [Module 5: Iterative Optimization — Gradient Descent (GD)](#module-5-iterative-optimization--gradient-descent-gd)
6. [Module 6: Hyperparameter Tuning & Data Preprocessing](#module-6-hyperparameter-tuning--data-preprocessing)
7. [Module 7: Logistic Regression (Binary & Multi-Class)](#module-7-logistic-regression-binary--multi-class)
8. [Module 8: Classification Evaluation Metrics](#module-8-classification-evaluation-metrics)
9. [Module 9: Step-by-Step Numerical Walkthroughs (Benchmark Problems)](#module-9-step-by-step-numerical-walkthroughs-benchmark-problems)
10. [Special Section: Comprehensive Solutions to All Unanswered Questions in `myNotes-ml.pdf`](#special-section-comprehensive-solutions-to-all-unanswered-questions-in-mynotes-mlpdf)
11. [Complete Solved Mid-Semester Examination Paper (Parts A, B, and C)](#complete-solved-mid-semester-examination-paper-parts-a-b-and-c)

---

# Module 1: Introduction to Machine Learning & Data Fundamentals

## 1.1 Definition of Machine Learning
Arthur Samuel (1959) famously described Machine Learning as *"the field of study that gives computers the ability to learn without being explicitly programmed."*

Tom Mitchell (1997) formulated the formal engineering operational definition:
$$\text{“A computer program is said to learn from experience } E \text{ with respect to some class of tasks } T \text{ and performance measure } P,$$
$$\text{if its performance at tasks in } T \text{, as measured by } P \text{, improves with experience } E\text{.”}$$

### Breakdown of ($P, T, E$) with Examples:
1. **Spam Email Filtering:**
   - **Task ($T$):** Classify incoming emails as spam or non-spam (ham).
   - **Experience ($E$):** A historical database of labeled emails (spam / not-spam).
   - **Performance Measure ($P$):** Classification accuracy (or $F_1$-score / precision-recall).
2. **Autonomous Driving:**
   - **Task ($T$):** Steering and braking navigation on a highway.
   - **Experience ($E$):** Sensory video stream, telemetry logs, and human driver interventions.
   - **Performance Measure ($P$):** Average distance traversed without human takeover, adherence to safety margins.
3. **Medical Diagnosis (e.g., Cancer Detection):**
   - **Task ($T$):** Predict benign vs. malignant tumors from biopsy imagery.
   - **Experience ($E$):** Database of clinical histology images with confirmed pathology labels.
   - **Performance Measure ($P$):** Sensitivity / Recall (minimizing False Negatives).

---

## 1.2 Data Representation & Terminology
In classical Machine Learning, structured data is organized into a 2D design matrix $\mathbf{X}$:
- **Patterns / Instances / Samples (Rows):** Each row represents an individual observation $x^{(i)}$ (e.g., student $i$, patient $i$). Total observations $= m$.
- **Features / Attributes / Variables (Columns):** Each column represents an individual measured characteristic $x_j$ (e.g., height, test score). Total input dimensions $= n$.
- **Target / Response Variable ($y$):** The ground-truth outcome to be predicted ($m \times 1$ vector).

### Matrix Formulation:
$$X = \begin{bmatrix} 
x_{11} & x_{12} & \dots & x_{1n} \\
x_{21} & x_{22} & \dots & x_{2n} \\
\vdots & \vdots & \ddots & \vdots \\
x_{m1} & x_{m2} & \dots & x_{mn}
\end{bmatrix} \in \mathbb{R}^{m \times n}, \quad 
Y = \begin{bmatrix} y_1 \\ y_2 \\ \vdots \\ y_m \end{bmatrix} \in \mathbb{R}^{m \times 1}$$

### Taxonomy of Data Types:
| Data Category | Definition | Real-World Examples | Mathematical Operations Allowed |
| :--- | :--- | :--- | :--- |
| **Continuous** | Real numbers on an unbroken interval $\mathbb{R}$. Infinite precision. | Height ($172.5\text{ cm}$), Salary ($\$84,250$), Temperature. | Addition, Subtraction, Multiplication, Ratios, Calculus. |
| **Discrete** | Countable values, typically non-negative integers $\mathbb{N}_0$. | Number of children, website visits, defective items. | Counting, Frequency, Arithmetic Mean. |
| **Ordinal** | Categorical values with a strict, unambiguous natural order or ranking. | Education level (B.Tech $<$ M.Tech $<$ Ph.D.), Grade (A, B, C, D). | Comparisons ($<, >$), Median, Rank correlation (Spearman). |
| **Nominal / Binary** | Categorical values with no intrinsic ordering. Binary has exactly 2 states. | Blood group (A, B, AB, O); Binary: Spam (1) vs. Ham (0), Gender. | Equality ($=, \neq$), Mode, Hamming distance, Jaccard distance. |

---

## 1.3 Machine Learning Lifecycle
The machine learning workflow follows a systematic 6-stage engineering pipeline:
1. **Data Collection:** Sourcing raw sensor outputs, transactional logs, web scraping, or survey records.
2. **Data Labeling & Annotation:** Assigning ground truth target variables $y$ (critical bottleneck for supervised learning).
3. **Feature Extraction & Engineering:** Transforming raw attributes into discriminative representations (e.g., polynomial features, one-hot encoding for nominal data, text tokenization).
4. **Exploratory Data Analysis (EDA):** Computing summary statistics ($\mu, \sigma^2, \text{Cov}, r_{xy}$), detecting outliers, handling missing values, and visualizing distributions.
5. **Model Building & Iterative Optimization:** Selecting hypothesis class $h(x)$, formulating loss objective $J(w)$, optimizing parameters via closed-form OLS or Gradient Descent.
6. **Evaluation & Diagnostic Validation:** Computing test metrics on unseen holdout splits, tuning hyperparameters, checking for overfitting vs. underfitting.

---

## 1.4 Learning Paradigms & Comprehensive Distance Metrics
- **Supervised Learning:** The model is provided with paired input-output training tuples $\mathcal{D} = \{(x^{(i)}, y^{(i)})\}_{i=1}^m$.
  - *Regression:* Target $y \in \mathbb{R}$ is continuous (e.g., predicting housing price, sales volume).
  - *Classification:* Target $y \in \{0, 1, \dots, C-1\}$ is discrete/categorical (e.g., tumor malignancy, digit classification).
- **Unsupervised Learning:** The model is provided with unlabeled inputs $\mathcal{D} = \{x^{(i)}\}_{i=1}^m$. The objective is to discover underlying structural properties, clusters, manifold embeddings, or latent density distributions (e.g., K-Means clustering, PCA).

### Distance Metrics Reference Table
Distance functions define proximity between two feature vectors $u, v \in \mathbb{R}^n$:

| Metric | Mathematical Formula | Key Properties & Assumptions | Ideal Use-Case |
| :--- | :--- | :--- | :--- |
| **Euclidean ($L_2$)** | $d_2(u, v) = \sqrt{\sum_{j=1}^n (u_j - v_j)^2}$ | Straight-line distance. Assumes isotropic, un-correlated features on identical scales. Highly sensitive to outliers due to squaring. | K-Means clustering, spatial distance. |
| **Manhattan ($L_1$)** | $d_1(u, v) = \sum_{j=1}^n \|u_j - v_j\|$ | Grid/taxicab metric. Less sensitive to extreme outliers than Euclidean. | High-dimensional data, grid routing, sparse feature spaces. |
| **Minkowski ($L_p$)** | $d_p(u, v) = \left(\sum_{j=1}^n \|u_j - v_j\|^p\right)^{1/p}$ | Generalization: $p=1 \to$ Manhattan; $p=2 \to$ Euclidean; $p \to \infty \to$ Chebyshev (max coordinate difference). | Metric space parameterization. |
| **Mahalanobis** | $d_M(u, v) = \sqrt{(u - v)^T \mathbf{\Sigma}^{-1} (u - v)}$ | Accounts for variance and covariance correlations between features using inverse covariance matrix $\mathbf{\Sigma}^{-1}$. Scale-invariant. | Multivariately correlated data, anomaly detection. |
| **Hamming** | $d_H(u, v) = \sum_{j=1}^n \mathbb{I}(u_j \neq v_j)$ | Counts exact number of coordinate mismatches between two equal-length strings or binary vectors. | Error-correcting codes, categorical comparison, DNA sequence analysis. |
| **Jaccard Distance** | $d_J(A, B) = 1 - \frac{\|A \cap B\|}{\|A \cup B\|}$ | Measures dissimilarity between sets or binary vectors. Ignores joint absences ($0-0$ matches). | Sparse text bag-of-words, recommendation systems. |

---

# Module 2: Basic Statistics & Correlation Analysis

## 2.1 Univariate Metrics & Bessel's Correction
For a random variable $X$ observed over a sample of size $n$:
- **Sample Mean ($\bar{x}$):**
  $$\bar{x} = \frac{1}{n} \sum_{i=1}^n x_i$$
- **Sample Variance ($s_x^2$):**
  $$s_x^2 = \frac{1}{n-1} \sum_{i=1}^n (x_i - \bar{x})^2$$

### Rigorous Justification of Bessel's Correction ($n-1$ factor):
Why do we divide by $n-1$ instead of $n$?
When calculating variance relative to the **sample mean** $\bar{x}$ rather than the true unknown population mean $\mu$, the deviations $(x_i - \bar{x})$ tend to be slightly smaller because $\bar{x}$ is mathematically positioned at the exact center of the sample itself (minimizing $\sum (x_i - c)^2$ at $c = \bar{x}$).

Mathematically:
$$\mathbb{E}\left[\frac{1}{n} \sum_{i=1}^n (x_i - \bar{x})^2\right] = \frac{n-1}{n} \sigma^2 < \sigma^2$$
Dividing by $n$ produces a systematically downward-biased estimate (underestimating true population variability). Multiplying by the correction factor $\frac{n}{n-1}$ recovers the **unbiased estimator**:
$$\mathbb{E}[s_x^2] = \mathbb{E}\left[\frac{1}{n-1} \sum_{i=1}^n (x_i - \bar{x})^2\right] = \sigma^2$$
The loss of 1 degree of freedom occurs because once $n-1$ deviations are known, the $n$-th deviation is strictly determined by $\sum_{i=1}^n (x_i - \bar{x}) = 0$.

---

## 2.2 Bivariate Metrics & Covariance
- **Sample Covariance:**
  $$\text{Cov}(X, Y) = s_{xy} = \frac{1}{n-1} \sum_{i=1}^n (x_i - \bar{x})(y_i - \bar{y})$$
- **Computational / Shortcut Formula:**
  $$\text{Cov}(X, Y) = \frac{1}{n-1} \left( \sum_{i=1}^n x_i y_i - n \bar{x} \bar{y} \right)$$

### Limitation of Covariance:
Covariance is **scale-dependent**. If we measure height in meters vs. millimeters, or income in dollars vs. cents, the numerical magnitude of $\text{Cov}(X, Y)$ changes by orders of magnitude:
$$\text{Cov}(c_1 X, c_2 Y) = c_1 c_2 \, \text{Cov}(X, Y)$$
Because covariance has units of $[\text{Units of } X] \times [\text{Units of } Y]$ and is unbounded ($-\infty < \text{Cov}(X, Y) < +\infty$), one cannot determine the strength of association purely from the raw value of covariance.

---

## 2.3 Pearson Correlation Coefficient ($r_{xy}$)
To eliminate scale dependency, we standardize covariance by dividing by the product of individual sample standard deviations ($s_x, s_y$):
$$r_{xy} = \frac{\text{Cov}(X, Y)}{s_x s_y} = \frac{\sum_{i=1}^n (x_i - \bar{x})(y_i - \bar{y})}{\sqrt{\sum_{i=1}^n (x_i - \bar{x})^2} \sqrt{\sum_{i=1}^n (y_i - \bar{y})^2}}$$

### Core Mathematical Properties:
1. **Bounded Range:** $-1 \le r_{xy} \le +1$ (guaranteed by the Cauchy-Schwarz inequality).
2. **Dimensionless:** $r_{xy}$ is a pure, unit-free scalar.
3. **Invariance Under Linear Affine Scaling:**
   If $X' = aX + b$ and $Y' = cY + d$ with $a > 0, c > 0$:
   $$r_{X'Y'} = r_{XY}$$
   If $a$ or $c$ is negative (e.g., $a = -1, c = 1$), the sign reverses: $r_{X'Y'} = -r_{XY}$.

---

## 2.4 Spearman's Rank Correlation Coefficient ($\rho$ or $r_s$)
When relationships are **non-linear but monotonic** (or when dealing with ordinal data), Pearson's $r$ underestimates the association. Spearman's rank correlation converts raw observations $x_i, y_i$ into their ordinal ranks $R(x_i), R(y_i)$ and computes Pearson's coefficient on those ranks.

When there are no tied ranks:
$$r_s = 1 - \frac{6 \sum_{i=1}^n d_i^2}{n(n^2 - 1)}$$
where $d_i = R(x_i) - R(y_i)$ is the rank difference for observation $i$.

---

## 2.5 In-Depth Conceptual Breakdown: Pearson Correlation Nuances
- **$r \to +1$ (Strong Positive Correlation):** As $X$ increases, $Y$ increases along a tight straight linear line.
- **$r \to -1$ (Strong Negative Correlation):** As $X$ increases, $Y$ decreases along a tight straight linear line.
- **$r = 0$ (Zero Linear Correlation):** No linear trend exists. Points may scatter spherically, or follow a horizontal line ($y = c$).

### Critical Warning: Why Pearson Measures *Only* Linear Relationships
$r = 0$ does **NOT** imply independence! It only implies the absence of a first-order linear relationship.
**Mathematical Proof / Counterexample:**
Let $X \in \{-3, -2, -1, 0, 1, 2, 3\}$ and $Y = X^2$.
- Here, $Y$ is completely, deterministically dependent on $X$ ($Y = f(X)$ with zero noise).
- Mean of $X$: $\bar{x} = \frac{-3-2-1+0+1+2+3}{7} = 0$.
- Computing $\sum (x_i - \bar{x})(y_i - \bar{y}) = \sum x_i y_i$:
  $$(-3)(9) + (-2)(4) + (-1)(1) + (0)(0) + (1)(1) + (2)(4) + (3)(9) = -27 - 8 - 1 + 0 + 1 + 8 + 27 = 0$$
- Therefore, $\text{Cov}(X, Y) = 0 \implies r_{xy} = 0$.
- Despite a perfect quadratic relationship, Pearson correlation yields $r = 0$ because the symmetric parabolic shape cancels positive and negative slopes equally.

---

# Module 3: Linear Regression & Ordinary Least Squares (OLS)

## 3.1 Problem Formulation
In Simple Linear Regression:
- **Independent Variable (Predictor / Regressor):** $x$
- **Dependent Variable (Response / Outcome):** $y$
- **Model Hypothesis:**
  $$\hat{y} = h(x) = w_0 + w_1 x$$
  where $w_0$ is the intercept ($y$-value when $x=0$) and $w_1$ is the slope (rate of change in $y$ per unit change in $x$).

- **True Data Generating Process:**
  $$y_i = w_0 + w_1 x_i + \epsilon_i$$
  where $\epsilon_i = y_i - \hat{y}_i$ is the random unobserved error (residual).

---

## 3.2 Loss Function: Residual Sum of Squares (RSS / LSE)
The objective of Ordinary Least Squares (OLS) is to minimize the total squared residual discrepancy between actual and predicted values:
$$LSE = RSS = SS_{\text{res}} = \sum_{i=1}^m \epsilon_i^2 = \sum_{i=1}^m (y_i - \hat{y}_i)^2 = \sum_{i=1}^m \Big( y_i - (w_0 + w_1 x_i) \Big)^2$$

### The Rationale Behind the $\frac{1}{2}$ or $\frac{1}{2m}$ Factor:
In optimization literature, the cost function is conventionally defined as:
$$J(w_0, w_1) = \frac{1}{2m} \sum_{i=1}^m (y_i - \hat{y}_i)^2$$
1. **Mathematical Cancellation:** Differentiating $(y_i - \hat{y}_i)^2$ using the chain rule brings down a factor of $2$: $\frac{d}{du}(u^2) = 2u$. Pre-multiplying by $\frac{1}{2}$ cancels this factor ($\frac{1}{2} \times 2 = 1$), yielding clean gradients.
2. **Sample Size Invariance ($\frac{1}{m}$):** Dividing by $m$ turns total sum of squared error into the Mean Squared Error (MSE). This ensures that the scale of the loss and the gradients do not blow up as dataset size $m$ grows.
3. **Argmin Invariance:** Because scaling a function by a positive constant $c > 0$ does not alter the location of its minimum:
   $$\arg\min_w J(w) \equiv \arg\min_w \left( \frac{1}{2m} \sum_{i=1}^m (y_i - \hat{y}_i)^2 \right) \equiv \arg\min_w \sum_{i=1}^m (y_i - \hat{y}_i)^2$$

---

## 3.3 Analytical Closed-Form Derivation (Single Variable OLS)
Let the loss function be:
$$J(w_0, w_1) = \sum_{i=1}^m \Big( y_i - w_0 - w_1 x_i \Big)^2$$
To find the global minimum, compute the partial derivatives w.r.t $w_0$ and $w_1$ and set them to zero.

### Step 1: Derivative w.r.t $w_0$ (Intercept)
$$\frac{\partial J}{\partial w_0} = \sum_{i=1}^m 2 \Big( y_i - w_0 - w_1 x_i \Big) (-1) = -2 \sum_{i=1}^m (y_i - w_0 - w_1 x_i) = 0$$
Dividing by $-2$:
$$\sum_{i=1}^m y_i - \sum_{i=1}^m w_0 - w_1 \sum_{i=1}^m x_i = 0$$
$$\sum_{i=1}^m y_i - m w_0 - w_1 \sum_{i=1}^m x_i = 0$$
Dividing both sides by $m$:
$$\bar{y} - w_0 - w_1 \bar{x} = 0 \implies \mathbf{w_0 = \bar{y} - w_1 \bar{x}} \quad \text{--- [Equation 1]}$$
*(Key Insight: The optimal OLS regression line always passes through the center of gravity $(\bar{x}, \bar{y})$).*

---

### Step 2: Derivative w.r.t $w_1$ (Slope)
$$\frac{\partial J}{\partial w_1} = \sum_{i=1}^m 2 \Big( y_i - w_0 - w_1 x_i \Big) (-x_i) = -2 \sum_{i=1}^m x_i (y_i - w_0 - w_1 x_i) = 0$$
Dividing by $-2$:
$$\sum_{i=1}^m x_i y_i - w_0 \sum_{i=1}^m x_i - w_1 \sum_{i=1}^m x_i^2 = 0 \quad \text{--- [Equation 2]}$$

### Step 3: Substitute Equation 1 into Equation 2
Substitute $w_0 = \bar{y} - w_1 \bar{x}$:
$$\sum_{i=1}^m x_i y_i - (\bar{y} - w_1 \bar{x}) \sum_{i=1}^m x_i - w_1 \sum_{i=1}^m x_i^2 = 0$$
Note that $\sum_{i=1}^m x_i = m \bar{x}$:
$$\sum_{i=1}^m x_i y_i - m \bar{x} \bar{y} + w_1 m \bar{x}^2 - w_1 \sum_{i=1}^m x_i^2 = 0$$
$$\sum_{i=1}^m x_i y_i - m \bar{x} \bar{y} = w_1 \left( \sum_{i=1}^m x_i^2 - m \bar{x}^2 \right)$$
Solving for $w_1$:
$$w_1 = \frac{\sum_{i=1}^m x_i y_i - m \bar{x} \bar{y}}{\sum_{i=1}^m x_i^2 - m \bar{x}^2}$$

### Step 4: Relation to Covariance and Pearson Correlation
From basic statistics identities:
$$\sum_{i=1}^m (x_i - \bar{x})(y_i - \bar{y}) = \sum_{i=1}^m x_i y_i - m \bar{x}\bar{y} = (m-1) \text{Cov}(X, Y)$$
$$\sum_{i=1}^m (x_i - \bar{x})^2 = \sum_{i=1}^m x_i^2 - m \bar{x}^2 = (m-1) s_x^2$$
Therefore:
$$w_1 = \frac{(m-1)\text{Cov}(X, Y)}{(m-1)s_x^2} = \mathbf{\frac{\text{Cov}(X, Y)}{s_x^2}}$$

Recalling that $r_{xy} = \frac{\text{Cov}(X, Y)}{s_x s_y} \implies \text{Cov}(X, Y) = r_{xy} s_x s_y$:
$$w_1 = \frac{r_{xy} s_x s_y}{s_x^2} = \mathbf{r_{xy} \frac{s_y}{s_x}} \quad \blacksquare$$

---

## 3.4 Multiple Linear Regression (Matrix Formulation)
When predicting $y$ from $n$ independent variables:
$$\hat{y}^{(i)} = w_0 + w_1 x_{i1} + w_2 x_{i2} + \dots + w_n x_{in} = \sum_{j=0}^n w_j x_{ij} \quad (\text{with } x_{i0} = 1)$$

### Matrix Dimension Definitions:
- **Design Matrix $\mathbf{X} \in \mathbb{R}^{m \times (n+1)}$:**
  $$X = \begin{bmatrix}
  1 & x_{11} & x_{12} & \dots & x_{1n} \\
  1 & x_{21} & x_{22} & \dots & x_{2n} \\
  \vdots & \vdots & \vdots & \ddots & \vdots \\
  1 & x_{m1} & x_{m2} & \dots & x_{mn}
  \end{bmatrix}$$
- **Weight Vector $\mathbf{w} \in \mathbb{R}^{(n+1) \times 1}$:** $w = \begin{bmatrix} w_0 & w_1 & \dots & w_n \end{bmatrix}^T$
- **Target Vector $\mathbf{Y} \in \mathbb{R}^{m \times 1}$:** $Y = \begin{bmatrix} y_1 & y_2 & \dots & y_m \end{bmatrix}^T$
- **Residual Vector $\mathbf{\epsilon} \in \mathbb{R}^{m \times 1}$:** $\epsilon = Y - Xw$

---

## 3.5 Derivation of the Matrix Normal Equations
The total cost in vector notation is:
$$J(w) = \frac{1}{2} \|Xw - Y\|^2 = \frac{1}{2} (Xw - Y)^T (Xw - Y)$$
Expanding the quadratic form:
$$J(w) = \frac{1}{2} \Big( (Xw)^T - Y^T \Big) (Xw - Y)$$
$$J(w) = \frac{1}{2} \Big( w^T X^T X w - w^T X^T Y - Y^T X w + Y^T Y \Big)$$
Since $w^T X^T Y$ is a scalar, its transpose is itself: $(w^T X^T Y)^T = Y^T X w$. Combining identical scalar terms:
$$J(w) = \frac{1}{2} \Big( w^T X^T X w - 2 Y^T X w + Y^T Y \Big)$$

Using matrix calculus identities:
$$\nabla_w (w^T A w) = 2 A w \quad (\text{for symmetric } A = X^T X)$$
$$\nabla_w (b^T w) = b$$

Computing the gradient $\nabla_w J(w)$ and setting it to the zero vector $\mathbf{0}$:
$$\nabla_w J(w) = \frac{1}{2} \Big( 2 X^T X w - 2 X^T Y \Big) = X^T X w - X^T Y = \mathbf{0}$$
$$\mathbf{X^T X w = X^T Y} \quad \text{(The Normal Equations)}$$

Multiplying both sides by the matrix inverse $(X^T X)^{-1}$ (assuming it is non-singular):
$$\mathbf{w = (X^T X)^{-1} X^T Y} \quad \blacksquare$$

---

## 3.6 Failure Modes of the OLS Closed-Form Solution
The analytical solution requires computing $(X^T X)^{-1}$. It fails under the following conditions:
1. **Singularity / Non-Invertibility of $X^T X$:** Occurs when $\det(X^T X) = 0$.
2. **Perfect Multicollinearity:** When two or more features are linearly dependent (e.g., $x_2 = 2 x_1$, or weight measured in kilograms and pounds). This reduces the rank of $X$, making $X^T X$ rank-deficient ($\text{rank}(X^T X) < n+1$).
3. **High-Dimensional Regime ($n > m$):** More features than training observations. In this case, $\text{rank}(X) \le m < n+1$, meaning $X^T X$ has size $(n+1) \times (n+1)$ but rank at most $m$. It is strictly singular with infinite solutions (underdetermined system).
4. **Computational Bottleneck:** Inverting an $(n+1) \times (n+1)$ matrix has time complexity $\mathcal{O}(n^3)$ (or $\mathcal{O}(n^{2.81})$ using Strassen). When $n > 10,000$, computing $(X^T X)^{-1}$ becomes computationally intractable and memory-prohibitive. Iterative Gradient Descent ($\mathcal{O}(m \cdot n)$ per iteration) is vastly superior in this regime.

---

# Module 4: Model Performance Metrics & Model Fitting

## 4.1 Regression Metrics
Given actual values $y_i$ and predictions $\hat{y}_i$ for $i = 1, \dots, m$:

| Metric | Formula | Dimensional Unit | Sensitivity to Outliers |
| :--- | :--- | :--- | :--- |
| **Mean Absolute Error (MAE)** | $\frac{1}{m} \sum_{i=1}^m \|y_i - \hat{y}_i\|$ | Same as $Y$ | **Low / Robust:** Linear penalty prevents outliers from dominating. |
| **Mean Squared Error (MSE)** | $\frac{1}{m} \sum_{i=1}^m (y_i - \hat{y}_i)^2$ | $(\text{Unit of } Y)^2$ | **High:** Squaring drastically penalizes large errors. |
| **Root Mean Squared Error (RMSE)** | $\sqrt{\frac{1}{m} \sum_{i=1}^m (y_i - \hat{y}_i)^2}$ | Same as $Y$ | **High:** Retains squared penalty while restoring interpretable units. |
| **Residual Sum of Squares ($SS_{\text{res}}$)** | $\sum_{i=1}^m (y_i - \hat{y}_i)^2$ | $(\text{Unit of } Y)^2$ | Direct measure of total unexplained variation. |
| **Total Sum of Squares ($SS_{\text{tot}}$)** | $\sum_{i=1}^m (y_i - \bar{y})^2$ | $(\text{Unit of } Y)^2$ | Total baseline variation around sample mean $\bar{y}$. |

---

## 4.2 Coefficient of Determination ($R^2$)
The $R^2$ score measures the proportion of variance in the dependent variable explained by the regression model:
$$R^2 = 1 - \frac{SS_{\text{res}}}{SS_{\text{tot}}} = 1 - \frac{\sum_{i=1}^m (y_i - \hat{y}_i)^2}{\sum_{i=1}^m (y_i - \bar{y})^2}$$

### Physical Interpretation:
- **$R^2 = 1$:** Perfect fit. $SS_{\text{res}} = 0 \implies \hat{y}_i = y_i$ for all $i$. All variance is captured.
- **$R^2 = 0$:** Baseline fit. The model performs no better than simply predicting the historical mean $\bar{y}$ for every input ($SS_{\text{res}} = SS_{\text{tot}}$).
- **$R^2 < 0$ (Negative $R^2$):** Occurs when $SS_{\text{res}} > SS_{\text{tot}}$. The model's predictions are **worse** than simply guessing the mean $\bar{y}$! This happens when:
  - An arbitrary or non-linear model is evaluated without an intercept.
  - A model evaluated on unseen test data has severe overfitting or incorrect parameters.

---

## 4.3 Overfitting vs. Underfitting & Bias-Variance Decomposition
Generalization error decomposes into three fundamental components:
$$\mathbb{E}\Big[(y - \hat{f}(x))^2\Big] = \text{Bias}^2\big[\hat{f}(x)\big] + \text{Variance}\big[\hat{f}(x)\big] + \sigma_{\text{irreducible}}^2$$

| Condition | Cause | Training Loss | Validation / Test Loss | Solution |
| :--- | :--- | :--- | :--- | :--- |
| **Underfitting** (High Bias) | Model is too simple (e.g., linear model on quadratic data). | **High** | **High** | Add polynomial features, increase model complexity, decrease regularization. |
| **Good Fit** (Optimal Balance) | Captures true underlying trend while ignoring noise. | **Low** | **Low** (close to train loss) | Optimal stopping point. |
| **Overfitting** (High Variance) | Model memorizes training noise and random fluctuations. | **Extremely Low** | **High** (diverges from train) | Add regularization (L1/L2), early stopping, increase training data size, feature selection. |

---

# Module 5: Iterative Optimization — Gradient Descent (GD)

## 5.1 Physical Intuition
Gradient Descent is a first-order optimization algorithm that iteratively finds the local (or global) minimum of a differentiable function.
- **Mountain Downhill Analogy:** Imagine standing on a foggy mountain where visibility is zero. To reach the valley floor, you sense the steepest slope beneath your feet and take a step in the exact opposite (downhill) direction.
- **Gradient Vector ($\nabla J(w)$):** Points in the direction of steepest *ascent*.
- **Descent Step:** Moving along $-\nabla J(w)$ decreases the cost function most rapidly.
- **Learning Rate ($\alpha$ or $\eta$):** The step size scaling factor.
  - If $\alpha$ is too small: Convergence is agonizingly slow.
  - If $\alpha$ is too large: The steps overshoot the valley, oscillate wildly, and may diverge to infinity.

---

## 5.2 Comparative Analysis: BGD vs. SGD vs. Mini-Batch GD

| Feature | Batch Gradient Descent (BGD) | Stochastic Gradient Descent (SGD) | Mini-Batch Gradient Descent |
| :--- | :--- | :--- | :--- |
| **Batch Size ($k$)** | Full dataset: $k = m$ | Single sample: $k = 1$ | Mini-batch: $1 < k < m$ (typically $32, 64, 128$) |
| **Weight Update Frequency** | Once per epoch (after scanning all $m$ samples) | $m$ times per epoch (after every individual sample) | $\frac{m}{k}$ times per epoch |
| **Computational Speed** | Very slow for large $m$ | Extremely fast per update | Fast; highly optimized for vectorized GPU computation |
| **Gradient Trajectory** | Smooth, deterministic, monotonic decrease | Highly noisy, erratic, zig-zags | Moderately smooth; balances stability and stochasticity |
| **Escape from Local Minima** | Prone to getting trapped in local minima/saddle points | Stochastic fluctuations help jump out of shallow local minima | Balances noise to jump saddle points with convergence stability |
| **Convergence Guarantee** | Converges to exact minimum (for convex $J$) | Fluctuates around minimum; needs learning rate decay | Converges smoothly to a tight neighborhood of the minimum |

---

## 5.3 Mathematical Derivation of GD Update Rules for Linear Regression
Let the MSE cost function be:
$$J(w) = \frac{1}{2m} \sum_{i=1}^m \Big( \hat{y}^{(i)} - y^{(i)} \Big)^2 = \frac{1}{2m} \sum_{i=1}^m \left( \sum_{j=0}^n w_j x_{ij} - y^{(i)} \right)^2$$

Differentiating partially w.r.t parameter $w_j$:
$$\frac{\partial J(w)}{\partial w_j} = \frac{\partial}{\partial w_j} \left[ \frac{1}{2m} \sum_{i=1}^m \left( \hat{y}^{(i)} - y^{(i)} \right)^2 \right]$$
Using the chain rule:
$$\frac{\partial J(w)}{\partial w_j} = \frac{1}{2m} \sum_{i=1}^m 2 \left( \hat{y}^{(i)} - y^{(i)} \right) \cdot \frac{\partial}{\partial w_j} \left( \sum_{k=0}^n w_k x_{ik} - y^{(i)} \right)$$
$$\frac{\partial J(w)}{\partial w_j} = \frac{1}{m} \sum_{i=1}^m \left( \hat{y}^{(i)} - y^{(i)} \right) \cdot x_{ij}$$

### General Parameter Update Rule:
$$\mathbf{w_j^{(t+1)} = w_j^{(t)} - \alpha \frac{\partial J(w)}{\partial w_j} = w_j^{(t)} - \frac{\alpha}{m} \sum_{i=1}^m \left( \hat{y}^{(i)} - y^{(i)} \right) x_{ij}}$$

- For Intercept $w_0$ ($x_{i0} = 1$):
  $$w_0^{(t+1)} = w_0^{(t)} - \frac{\alpha}{m} \sum_{i=1}^m \left( \hat{y}^{(i)} - y^{(i)} \right)$$
- In Vectorized Matrix Form:
  $$\mathbf{w^{(t+1)} = w^{(t)} - \frac{\alpha}{m} X^T (X w^{(t)} - Y)}$$

---

# Module 6: Hyperparameter Tuning & Data Preprocessing

## 6.1 Model Parameters vs. Hyperparameters

| Dimension | Model Parameters | Hyperparameters |
| :--- | :--- | :--- |
| **Definition** | Internal configuration variables learned directly from data during training. | External tuning knobs set prior to training that govern the learning process. |
| **Examples** | Regression weights $w_j$, bias $w_0$, logistic boundary hyperplanes. | Learning rate $\alpha$, number of epochs, batch size $k$, regularization strength $\lambda$, distance metric. |
| **Optimization Method** | OLS normal equations, Gradient Descent optimization. | Grid Search, Random Search, Bayesian Optimization, Cross-Validation. |

---

## 6.2 Data Partitioning & K-Fold Cross-Validation
- **Train-Validation-Test Split:**
  - **Training Set (60–70%):** Used by gradient descent to update weights $w$.
  - **Validation Set (15–20%):** Used to tune hyperparameters ($\alpha$, epochs) and detect overfitting.
  - **Testing Set (15–20%):** Strictly held out; used *only once* to report final unbiased generalization error.

### K-Fold Cross-Validation Algorithm:
1. Shuffle the dataset randomly.
2. Split dataset into $K$ equal-sized, mutually exclusive folds $\{F_1, F_2, \dots, F_K\}$.
3. For $k = 1$ to $K$:
   - Set fold $F_k$ as the **Validation Set**.
   - Combine the remaining $K-1$ folds as the **Training Set**.
   - Train model on the training set and evaluate performance score $S_k$ on fold $F_k$.
4. Compute the overall cross-validation score:
   $$\text{CV}_{(K)} = \frac{1}{K} \sum_{k=1}^K S_k$$
*Advantage:* Every single observation is used for validation exactly once, drastically reducing evaluation variance for small datasets.

---

## 6.3 Feature Scaling Techniques
When features have vastly different numerical ranges (e.g., $x_1 \in [1, 5]$ and $x_2 \in [10, 10000]$):

1. **Min-Max Normalization (Rescaling to $[0, 1]$):**
   $$x' = \frac{x - \min(x)}{\max(x) - \min(x)}$$
2. **Standardization / Z-Score Normalization ($\mu=0, \sigma=1$):**
   $$x' = \frac{x - \mu}{\sigma}$$
3. **Absolute Maximum Scaling (Rescaling to $[-1, 1]$):**
   $$x' = \frac{x}{\max(|x|)}$$

### Why Feature Scaling Accelerates Gradient Descent:
- **Unscaled Cost Surface:** The MSE cost contours form highly elongated, eccentric ellipses. The gradient vector (perpendicular to contour lines) does not point toward the minimum, causing GD to oscillate wildly and bounce between steep canyon walls, necessitating a tiny learning rate $\alpha$.
- **Scaled Cost Surface:** Contours transform into symmetric, spherical circles. Gradients point directly toward the center minimum, allowing large learning rates and rapid, straight-line convergence.

```
       UNSCALED FEATURES                     SCALED FEATURES
      (Elliptical Valleys)                  (Spherical Contours)
          w2 ^                                   w2 ^
             |  /-------------\                     |      .---.
             | /   /-------\   \                    |    /   |   \
             | |  |    *    |  |                    |   |  - * -  |
             | \   \-------/   /                    |    \   |   /
             |  \-------------/                     |      '---'
             +-----------------> w1                 +-----------------> w1
          (Wild oscillations)                     (Direct path to minimum)
```

---

# Module 7: Logistic Regression (Binary & Multi-Class)

## 7.1 Why Linear Regression Fails for Classification
Attempting to fit a linear regression model $\hat{y} = w^T x$ to discrete class labels $y \in \{0, 1\}$ suffers from three fatal theoretical flaws:
1. **Unbounded Output Range:** Linear regression outputs values in $(-\infty, +\infty)$. Probabilities must strictly be bounded in $[0, 1]$. Predicting $\hat{y} = 1.8$ or $\hat{y} = -0.4$ has no valid probabilistic interpretation.
2. **Extreme Vulnerability to Outliers:** Adding legitimate, easily classified positive points far from the decision boundary pulls the OLS line toward the outlier, shifting the decision threshold and misclassifying previously correct points.
3. **Masking & Non-convexity:** Linear regression cannot accommodate probability curvature or sharp decision transitions.

---

## 7.2 The Sigmoid (Logistic) Function
To map the real-valued linear score $z = w^T x \in (-\infty, +\infty)$ into a valid probability $p \in (0, 1)$, we apply the Sigmoid function:
$$g(z) = \sigma(z) = \frac{1}{1 + e^{-z}} = \frac{e^z}{1 + e^z}$$

### Key Properties:
- **Range:** $0 < g(z) < 1$
- **Symmetry:** $g(-z) = 1 - g(z)$
- **Center:** $g(0) = 0.5$
- **Asymptotes:** $\lim_{z \to +\infty} g(z) = 1$, $\lim_{z \to -\infty} g(z) = 0$

### Rigorous Derivation of the Sigmoid Derivative:
$$g'(z) = \frac{d}{dz} (1 + e^{-z})^{-1} = -(1 + e^{-z})^{-2} \cdot (-e^{-z}) = \frac{e^{-z}}{(1 + e^{-z})^2}$$
Splitting into two fractions:
$$g'(z) = \left( \frac{1}{1 + e^{-z}} \right) \left( \frac{e^{-z}}{1 + e^{-z}} \right) = \left( \frac{1}{1 + e^{-z}} \right) \left( \frac{1 + e^{-z} - 1}{1 + e^{-z}} \right) = g(z) \Big( 1 - g(z) \Big) \quad \blacksquare$$

---

## 7.3 Mathematical Definition of Decision Boundary
The hypothesis predicts class probabilities:
$$P(y=1|x; w) = h_w(x) = g(w^T x) = \frac{1}{1 + e^{-w^T x}}$$
Using standard classification threshold $\tau = 0.5$:
$$\text{Predict } y = 1 \iff h_w(x) \ge 0.5 \iff g(w^T x) \ge 0.5 \iff w^T x \ge 0$$
$$\text{Predict } y = 0 \iff h_w(x) < 0.5 \iff g(w^T x) < 0.5 \iff w^T x < 0$$

The **Decision Boundary** is the geometric hypersurface where predictions are equally probable ($P = 0.5$):
$$\mathbf{w^T x = w_0 + w_1 x_1 + w_2 x_2 + \dots + w_n x_n = 0}$$
This is an $(n-1)$-dimensional hyperplane partitioning the feature space into two decision half-spaces.

---

## 7.4 Loss Functions: Failure of MSE vs. Binary Cross-Entropy

### Why MSE Fails in Logistic Regression:
If we substitute $h_w(x) = g(w^T x)$ into the MSE cost function:
$$J_{\text{MSE}}(w) = \frac{1}{2m} \sum_{i=1}^m \Big( g(w^T x^{(i)}) - y^{(i)} \Big)^2$$
Because $g(z)$ is non-linear, $J_{\text{MSE}}(w)$ is **strictly non-convex** with respect to $w$. It is plagued by numerous local minima, flat plateaus, and saddle points. Gradient descent gets trapped in poor local optima.

Furthermore, differentiating MSE yields:
$$\frac{\partial J_{\text{MSE}}}{\partial w_j} = \frac{1}{m} \sum_{i=1}^m (\hat{y}_i - y_i) \cdot \mathbf{g'(z_i)} \cdot x_{ij} = \frac{1}{m} \sum_{i=1}^m (\hat{y}_i - y_i) \mathbf{\hat{y}_i (1 - \hat{y}_i)} x_{ij}$$
When a prediction is completely wrong (e.g., $y_i = 1$ but $\hat{y}_i \approx 0$), the factor $\hat{y}_i (1 - \hat{y}_i) \approx 0 \cdot 1 = 0$. The gradient **vanishes**, preventing the model from correcting egregious errors!

---

### Binary Cross-Entropy (Log-Loss):
Using Maximum Likelihood Estimation (MLE), the conditional probability for a single sample is Bernoulli:
$$P(y|x) = (h_w(x))^y (1 - h_w(x))^{1-y}$$
The negative log-likelihood over $m$ samples defines the **Log-Loss Cost Function**:
$$J(w) = -\frac{1}{m} \sum_{i=1}^m \Big[ y^{(i)} \log(\hat{y}^{(i)}) + (1 - y^{(i)}) \log(1 - \hat{y}^{(i)}) \Big]$$

### Intuition & Penalty Behavior:
- **If $y = 1$:** $\text{Cost} = -\log(\hat{y})$. As $\hat{y} \to 1$, $\text{Cost} \to 0$. As $\hat{y} \to 0$, $\text{Cost} \to \infty$ (infinitely penalizes confident false negatives).
- **If $y = 0$:** $\text{Cost} = -\log(1 - \hat{y})$. As $\hat{y} \to 0$, $\text{Cost} \to 0$. As $\hat{y} \to 1$, $\text{Cost} \to \infty$ (infinitely penalizes confident false positives).
- **Convexity:** $J(w)$ with Log-Loss is provably **strictly convex**, guaranteeing a unique global minimum!

---

## 7.5 Derivation of Logistic Regression Gradient Update Rule
Let $\hat{y} = g(z)$ where $z = w^T x = \sum_{j=0}^n w_j x_j$.
For a single sample with loss $\mathcal{L} = -\big[ y \log \hat{y} + (1-y) \log(1-\hat{y}) \big]$:
Using the chain rule:
$$\frac{\partial \mathcal{L}}{\partial w_j} = \frac{\partial \mathcal{L}}{\partial \hat{y}} \cdot \frac{\partial \hat{y}}{\partial z} \cdot \frac{\partial z}{\partial w_j}$$

1. $\frac{\partial \mathcal{L}}{\partial \hat{y}} = -\frac{y}{\hat{y}} - \frac{1-y}{1-\hat{y}} (-1) = -\frac{y}{\hat{y}} + \frac{1-y}{1-\hat{y}} = \frac{-y(1-\hat{y}) + \hat{y}(1-y)}{\hat{y}(1-\hat{y})} = \frac{\hat{y} - y}{\hat{y}(1-\hat{y})}$
2. $\frac{\partial \hat{y}}{\partial z} = g'(z) = \hat{y}(1 - \hat{y})$
3. $\frac{\partial z}{\partial w_j} = x_j$

Multiplying together:
$$\frac{\partial \mathcal{L}}{\partial w_j} = \left( \frac{\hat{y} - y}{\hat{y}(1-\hat{y})} \right) \cdot \Big( \hat{y}(1-\hat{y}) \Big) \cdot x_j = (\hat{y} - y) x_j$$
*(Notice how the non-linear sigmoid derivative terms cancel perfectly!)*

Summing over all $m$ instances:
$$\mathbf{\frac{\partial J(w)}{\partial w_j} = \frac{1}{m} \sum_{i=1}^m (\hat{y}^{(i)} - y^{(i)}) x_{ij}}$$
$$\mathbf{w_j^{(t+1)} = w_j^{(t)} - \frac{\alpha}{m} \sum_{i=1}^m (\hat{y}^{(i)} - y^{(i)}) x_{ij}} \quad \blacksquare$$
*(Remarkably, the algebraic update form is identical to linear regression, but here $\hat{y} = g(w^T x)$ rather than $w^T x$).*

---

## 7.6 Multi-Class Classification: One-vs-All (One-vs-Rest) Strategy
For a $C$-class classification problem ($y \in \{1, 2, \dots, C\}$):
1. **Training Phase:** Train $C$ independent binary logistic regression classifiers $h^{(k)}(x)$ for $k = 1, \dots, C$.
   - For classifier $k$, assign class $k$ as positive ($y=1$) and all remaining $C-1$ classes as negative ($y=0$).
   - Each classifier models: $h^{(k)}(x) = P(y=k | x; w^{(k)})$.
2. **Prediction Phase:** Given a new test instance $x_{\text{test}}$, evaluate all $C$ classifiers and assign $x_{\text{test}}$ to the class with the maximum predicted probability:
   $$\mathbf{\hat{y} = \arg\max_{k \in \{1, \dots, C\}} h^{(k)}(x_{\text{test}})}$$

---

# Module 8: Classification Evaluation Metrics

## 8.1 The Confusion Matrix (Binary)
A confusion matrix cross-tabulates actual ground truth classes against model predictions:

```
                      ACTUAL CLASS
                   Positive (1)     Negative (0)
PREDICTED   Pos (1) [    TP      ]  [    FP      ]  -> Precision = TP / (TP + FP)
CLASS       Neg (0) [    FN      ]  [    TN      ]
                      |               |
                      v               v
               Recall = TP/(TP+FN)  Specificity = TN/(TN+FP)
```

- **True Positive (TP):** Ground truth is Positive; model correctly predicts Positive.
- **True Negative (TN):** Ground truth is Negative; model correctly predicts Negative.
- **False Positive (FP - Type I Error):** Ground truth is Negative; model incorrectly predicts Positive.
- **False Negative (FN - Type II Error):** Ground truth is Positive; model incorrectly predicts Negative.

---

## 8.2 Standard Classification Formulas
$$\text{Overall Accuracy} = \frac{TP + TN}{TP + TN + FP + FN}$$
$$\text{Class-Specific Accuracy (Positives)} = \frac{TP}{TP + FN} = \text{Recall}$$
$$\text{Class-Specific Accuracy (Negatives)} = \frac{TN}{TN + FP} = \text{Specificity}$$
$$\text{Precision} = \frac{TP}{TP + FP} \quad \text{(Out of all predicted positives, how many are truly positive?)}$$
$$\text{Recall / Sensitivity} = \frac{TP}{TP + FN} \quad \text{(Out of all actual positives, how many did we successfully detect?)}$$
$$F_1\text{-Score} = 2 \times \frac{\text{Precision} \times \text{Recall}}{\text{Precision} + \text{Recall}} = \frac{2 TP}{2 TP + FP + FN} \quad \text{(Harmonic mean)}$$

---

## 8.3 Multi-Class Confusion Matrix (Worked Example from Lecture & Student Notes)
Consider a 3-class classification problem with classes: **Cat, Fish, Dog** over 25 test samples:

```
                           ACTUAL (Ground Truth)
                       Cat       Fish      Dog      Row Total (Predicted)
PREDICTED   Cat    [    4    ] [   6    ] [   3    ]      13
            Fish   [    1    ] [   2    ] [   0    ]       3
            Dog    [    1    ] [   2    ] [   6    ]       9
    Column Total        6         10         9          25
      (Actual)
```

### Step-by-Step Per-Class Metrics Calculation:

1. **For Class "Cat":**
   - $TP_{\text{Cat}} = 4$
   - $FP_{\text{Cat}} = 6 + 3 = 9$ (non-Cats predicted as Cat)
   - $FN_{\text{Cat}} = 1 + 1 = 2$ (Cats predicted as Fish or Dog)
   - $TN_{\text{Cat}} = 2 + 0 + 2 + 6 = 10$
   - **Precision (Cat):**
     $$\text{Precision}_{\text{Cat}} = \frac{TP}{TP + FP} = \frac{4}{4 + 6 + 3} = \frac{4}{13} \approx 0.3077 \quad (30.77\%)$$
   - **Recall (Cat):**
     $$\text{Recall}_{\text{Cat}} = \frac{TP}{TP + FN} = \frac{4}{4 + 1 + 1} = \frac{4}{6} = \frac{2}{3} \approx 0.6667 \quad (66.67\%)$$

2. **For Class "Fish":**
   - $TP_{\text{Fish}} = 2$
   - $FP_{\text{Fish}} = 1 + 0 = 1$
   - $FN_{\text{Fish}} = 6 + 2 = 8$
   - **Precision (Fish):**
     $$\text{Precision}_{\text{Fish}} = \frac{TP}{TP + FP} = \frac{2}{1 + 2 + 0} = \frac{2}{3} \approx 0.6667 \quad (66.67\%)$$
   - **Recall (Fish):**
     $$\text{Recall}_{\text{Fish}} = \frac{TP}{TP + FN} = \frac{2}{6 + 2 + 2} = \frac{2}{10} = 0.2000 \quad (20.00\%)$$

3. **For Class "Dog":**
   - $TP_{\text{Dog}} = 6$
   - $FP_{\text{Dog}} = 1 + 2 = 3$
   - $FN_{\text{Dog}} = 3 + 0 = 3$
   - **Precision (Dog):**
     $$\text{Precision}_{\text{Dog}} = \frac{TP}{TP + FP} = \frac{6}{1 + 2 + 6} = \frac{6}{9} = \frac{2}{3} \approx 0.6667 \quad (66.67\%)$$
   - **Recall (Dog):**
     $$\text{Recall}_{\text{Dog}} = \frac{TP}{TP + FN} = \frac{6}{3 + 0 + 6} = \frac{6}{9} = \frac{2}{3} \approx 0.6667 \quad (66.67\%)$$

4. **Overall System Accuracy:**
   $$\text{Accuracy} = \frac{\text{Trace of Matrix}}{\text{Total Samples}} = \frac{4 + 2 + 6}{25} = \frac{12}{25} = 0.4800 \quad (48.00\%)$$

---

# Module 9: Step-by-Step Numerical Walkthroughs (Benchmark Problems)

## Numerical A: Batch Gradient Descent for Linear Regression
### Problem Statement:
Given a dataset of two training points with two input features:
- $x^{(1)} = [x_1=1, x_2=4], \quad y^{(1)} = 9$
- $x^{(2)} = [x_2=2, x_2=5], \quad y^{(2)} = 12$

Model Hypothesis: $\hat{y} = w_0 + w_1 x_1 + w_2 x_2$  
Hyperparameters: Learning rate $\eta = \alpha = 0.1$, Number of Epochs $= 2$.  
Initial parameters: $w_0 = 1.0, w_1 = 1.0, w_2 = 1.0$.  
Dataset size: $m = 2$.

---

### Full Step-by-Step Solution:

#### --- EPOCH 1 ---
1. **Compute Model Predictions ($\hat{y}^{(i)}$):**
   - For $x^{(1)} = [1, 4]$:
     $$\hat{y}^{(1)} = w_0 + w_1(1) + w_2(4) = 1.0 + 1.0(1) + 1.0(4) = 6.0$$
   - For $x^{(2)} = [2, 5]$:
     $$\hat{y}^{(2)} = w_0 + w_1(2) + w_2(5) = 1.0 + 1.0(2) + 1.0(5) = 8.0$$

2. **Compute Prediction Residuals / Errors $(\hat{y}^{(i)} - y^{(i)})$:**
   - $e^{(1)} = \hat{y}^{(1)} - y^{(1)} = 6.0 - 9.0 = -3.0$
   - $e^{(2)} = \hat{y}^{(2)} - y^{(2)} = 8.0 - 12.0 = -4.0$

3. **Compute Batch Gradients $\frac{\partial J}{\partial w_j} = \frac{1}{m} \sum_{i=1}^m (\hat{y}^{(i)} - y^{(i)}) x_{ij}$:**
   - For $w_0$ ($x_{i0} = 1$):
     $$\frac{\partial J}{\partial w_0} = \frac{1}{2} \Big[ (-3.0)(1) + (-4.0)(1) \Big] = \frac{-7.0}{2} = -3.5$$
   - For $w_1$:
     $$\frac{\partial J}{\partial w_1} = \frac{1}{2} \Big[ (-3.0)(1) + (-4.0)(2) \Big] = \frac{-3.0 - 8.0}{2} = \frac{-11.0}{2} = -5.5$$
   - For $w_2$:
     $$\frac{\partial J}{\partial w_2} = \frac{1}{2} \Big[ (-3.0)(4) + (-4.0)(5) \Big] = \frac{-12.0 - 20.0}{2} = \frac{-32.0}{2} = -16.0$$

4. **Update Parameters Using Gradient Descent ($w_j \leftarrow w_j - \alpha \frac{\partial J}{\partial w_j}$):**
   - $w_0^{(1)} = 1.0 - (0.1)(-3.5) = 1.0 + 0.35 = \mathbf{1.35}$
   - $w_1^{(1)} = 1.0 - (0.1)(-5.5) = 1.0 + 0.55 = \mathbf{1.55}$
   - $w_2^{(1)} = 1.0 - (0.1)(-16.0) = 1.0 + 1.60 = \mathbf{2.60}$

---

#### --- EPOCH 2 ---
Current weights: $w_0 = 1.35, w_1 = 1.55, w_2 = 2.60$.

1. **Compute Predictions ($\hat{y}^{(i)}$):**
   - For $x^{(1)} = [1, 4]$:
     $$\hat{y}^{(1)} = 1.35 + 1.55(1) + 2.60(4) = 1.35 + 1.55 + 10.40 = \mathbf{13.30}$$
   - For $x^{(2)} = [2, 5]$:
     $$\hat{y}^{(2)} = 1.35 + 1.55(2) + 2.60(5) = 1.35 + 3.10 + 13.00 = \mathbf{17.45}$$

2. **Compute Errors $(\hat{y}^{(i)} - y^{(i)})$:**
   - $e^{(1)} = 13.30 - 9.0 = \mathbf{+4.30}$
   - $e^{(2)} = 17.45 - 12.0 = \mathbf{+5.45}$

3. **Compute Batch Gradients:**
   - For $w_0$:
     $$\frac{\partial J}{\partial w_0} = \frac{1}{2} \Big[ (4.30)(1) + (5.45)(1) \Big] = \frac{9.75}{2} = \mathbf{4.875}$$
   - For $w_1$:
     $$\frac{\partial J}{\partial w_1} = \frac{1}{2} \Big[ (4.30)(1) + (5.45)(2) \Big] = \frac{4.30 + 10.90}{2} = \frac{15.20}{2} = \mathbf{7.60}$$
   - For $w_2$:
     $$\frac{\partial J}{\partial w_2} = \frac{1}{2} \Big[ (4.30)(4) + (5.45)(5) \Big] = \frac{17.20 + 27.25}{2} = \frac{44.45}{2} = \mathbf{22.225}$$

4. **Update Parameters:**
   - $w_0^{(2)} = 1.35 - (0.1)(4.875) = 1.35 - 0.4875 = \mathbf{0.8625}$
   - $w_1^{(2)} = 1.55 - (0.1)(7.60) = 1.55 - 0.7600 = \mathbf{0.7900}$
   - $w_2^{(2)} = 2.60 - (0.1)(22.225) = 2.60 - 2.2225 = \mathbf{0.3775}$

---

#### --- TEST PREDICTIONS ---
Using final parameters after Epoch 2:
$$w_0 = 0.8625, \quad w_1 = 0.7900, \quad w_2 = 0.3775$$

- **Prediction for Input Pattern $[3, 12]$ (from prompt):**
  $$\hat{y}_{[3, 12]} = 0.8625 + 0.7900(3) + 0.3775(12) = 0.8625 + 2.3700 + 4.5300 = \mathbf{7.7625}$$

- **Prediction for Input Pattern $[6, 2]$ (from Mid-Sem exam paper):**
  $$\hat{y}_{[6, 2]} = 0.8625 + 0.7900(6) + 0.3775(2) = 0.8625 + 4.7400 + 0.7550 = \mathbf{6.3575}$$

#### Commentary on Convergence:
*Is the result after 2 epochs likely to be close to the true value?*  
**No.** Notice that in Epoch 1 the errors were negative ($-3, -4$), causing weights to increase drastically. In Epoch 2, the predictions overshot significantly ($+4.3, +5.45$), causing the gradients to flip sign and become large positive values. The learning rate $\alpha = 0.1$ is relatively large for this unnormalized feature magnitude, causing visible oscillations. Two epochs are far too few for gradient descent to settle near the global minimum.

---

## Numerical B: Mini-Batch Gradient Descent for Logistic Regression
### Problem Statement:
Dataset of 4 training points:
- $x^{(1)} = [1, 2], \quad y^{(1)} = 0$
- $x^{(2)} = [2, 1], \quad y^{(2)} = 0$
- $x^{(3)} = [3, 4], \quad y^{(3)} = 1$
- $x^{(4)} = [4, 3], \quad y^{(4)} = 1$

Hyperparameters: $\alpha = \eta = 0.1$, Mini-batch size $= 2$, Epochs $= 1$.  
Mini-batch 1: $\{x^{(1)}, x^{(2)}\}$, Mini-batch 2: $\{x^{(3)}, x^{(4)}\}$.  
Loss function: Log-Loss.  
Initial weights: $w_0 = 1.0, w_1 = 1.0, w_2 = 1.0$.  
Model: $\hat{y} = g(z) = \frac{1}{1 + e^{-z}}$ where $z = w_0 + w_1 x_1 + w_2 x_2$.

---

### Full Step-by-Step Solution:

#### --- MINI-BATCH 1: $\{x^{(1)}, x^{(2)}\}$ ---
Current weights: $w_0 = 1, w_1 = 1, w_2 = 1$. Ground truth: $y^{(1)} = 0, y^{(2)} = 0$.

1. **Compute Linear Activations ($z$):**
   - $z^{(1)} = 1.0 + 1.0(1) + 1.0(2) = 4.0$
   - $z^{(2)} = 1.0 + 1.0(2) + 1.0(1) = 4.0$

2. **Compute Sigmoid Probability Predictions ($\hat{y} = g(z)$):**
   - $\hat{y}^{(1)} = \frac{1}{1 + e^{-4}} = \frac{1}{1 + 0.0183156} \approx \mathbf{0.982014}$
   - $\hat{y}^{(2)} = \frac{1}{1 + e^{-4}} \approx \mathbf{0.982014}$

3. **Compute Residual Errors $(\hat{y}^{(i)} - y^{(i)})$:**
   - $e^{(1)} = 0.982014 - 0 = \mathbf{0.982014}$
   - $e^{(2)} = 0.982014 - 0 = \mathbf{0.982014}$

4. **Compute Mini-Batch 1 Gradients $\frac{\partial J}{\partial w_j} = \frac{1}{2} \sum_{i=1}^2 (\hat{y}^{(i)} - y^{(i)}) x_{ij}$:**
   - For $w_0$:
     $$\frac{\partial J}{\partial w_0} = \frac{1}{2} [0.982014(1) + 0.982014(1)] = \mathbf{0.982014}$$
   - For $w_1$:
     $$\frac{\partial J}{\partial w_1} = \frac{1}{2} [0.982014(1) + 0.982014(2)] = \frac{0.982014 \times 3}{2} = \mathbf{1.473021}$$
   - For $w_2$:
     $$\frac{\partial J}{\partial w_2} = \frac{1}{2} [0.982014(2) + 0.982014(1)] = \frac{0.982014 \times 3}{2} = \mathbf{1.473021}$$

5. **Update Parameters After Mini-Batch 1 ($w_j \leftarrow w_j - \alpha \frac{\partial J}{\partial w_j}$):**
   - $w_0^{(1)} = 1.0 - (0.1)(0.982014) = 1.0 - 0.098201 = \mathbf{0.901799}$
   - $w_1^{(1)} = 1.0 - (0.1)(1.473021) = 1.0 - 0.147302 = \mathbf{0.852698}$
   - $w_2^{(1)} = 1.0 - (0.1)(1.473021) = 1.0 - 0.147302 = \mathbf{0.852698}$

---

#### --- MINI-BATCH 2: $\{x^{(3)}, x^{(4)}\}$ ---
Updated weights from MB1: $w_0 = 0.901799, w_1 = 0.852698, w_2 = 0.852698$.  
Ground truth: $y^{(3)} = 1, y^{(4)} = 1$. Points: $x^{(3)} = [3, 4], x^{(4)} = [4, 3]$.

1. **Compute Linear Activations ($z$):**
   - $z^{(3)} = 0.901799 + 0.852698(3) + 0.852698(4) = 0.901799 + 0.852698(7) = 0.901799 + 5.968886 = \mathbf{6.870685}$
   - $z^{(4)} = 0.901799 + 0.852698(4) + 0.852698(3) = \mathbf{6.870685}$

2. **Compute Sigmoid Probability Predictions ($\hat{y} = g(z)$):**
   - $\hat{y}^{(3)} = \frac{1}{1 + e^{-6.870685}} = \frac{1}{1 + 0.0010377} \approx \mathbf{0.998963}$
   - $\hat{y}^{(4)} = \mathbf{0.998963}$

3. **Compute Residual Errors $(\hat{y}^{(i)} - y^{(i)})$:**
   - $e^{(3)} = 0.998963 - 1.0 = \mathbf{-0.001037}$
   - $e^{(4)} = 0.998963 - 1.0 = \mathbf{-0.001037}$

4. **Compute Mini-Batch 2 Gradients:**
   - For $w_0$:
     $$\frac{\partial J}{\partial w_0} = \frac{1}{2} [(-0.001037)(1) + (-0.001037)(1)] = \mathbf{-0.001037}$$
   - For $w_1$:
     $$\frac{\partial J}{\partial w_1} = \frac{1}{2} [(-0.001037)(3) + (-0.001037)(4)] = \frac{-0.001037 \times 7}{2} = \mathbf{-0.003630}$$
   - For $w_2$:
     $$\frac{\partial J}{\partial w_2} = \frac{1}{2} [(-0.001037)(4) + (-0.001037)(3)] = \frac{-0.001037 \times 7}{2} = \mathbf{-0.003630}$$

5. **Update Parameters After Mini-Batch 2:**
   - $w_0^{(2)} = 0.901799 - (0.1)(-0.001037) = 0.901799 + 0.000104 = \mathbf{0.901903}$
   - $w_1^{(2)} = 0.852698 - (0.1)(-0.003630) = 0.852698 + 0.000363 = \mathbf{0.853061}$
   - $w_2^{(2)} = 0.852698 - (0.1)(-0.003630) = 0.852698 + 0.000363 = \mathbf{0.853061}$

---

#### --- TEST PREDICTION ---
Predict the probability of input pattern $x_{\text{test}} = [3, 1]$ belonging to Class 1:
$$z_{\text{test}} = w_0 + w_1(3) + w_2(1) = 0.901903 + 0.853061(3) + 0.853061(1)$$
$$z_{\text{test}} = 0.901903 + 2.559183 + 0.853061 = \mathbf{4.314147}$$
$$\hat{y}_{\text{test}} = g(4.314147) = \frac{1}{1 + e^{-4.314147}} = \frac{1}{1 + 0.013378} \approx \mathbf{0.9868} \quad (98.68\%)$$
**Conclusion:** The input pattern $[3, 1]$ is classified as **Class 1** with $98.68\%$ confidence.

#### Discussion on Gradient Magnitude Across Mini-Batches:
In Mini-Batch 1, the model predicted $\approx 0.982$ for true negative instances ($y=0$). This huge classification error produced a large gradient ($\approx 1.47$), driving a substantial reduction in weights. In Mini-Batch 2, the updated weights produced $\approx 0.999$ for true positive instances ($y=1$). Because the prediction was already nearly optimal for positive labels, the error was tiny ($-0.001$), resulting in near-zero gradients. Thus, gradient magnitudes dropped dramatically from MB1 to MB2, illustrating how parameter updates diminish as the model approaches alignment with target classes.

---

## Numerical C: K-Means Clustering
### Problem Statement:
Given 4 two-dimensional data points:
$$x^{(1)} = (2, 3), \quad x^{(2)} = (3, 3), \quad x^{(3)} = (8, 7), \quad x^{(4)} = (9, 8)$$
Number of clusters: $K = 2$.  
Initial Centroids:
$$C_1 = (2, 3), \quad C_2 = (8, 7)$$
Distance metric: Standard Euclidean distance: $d(x, C) = \sqrt{(x_1 - c_1)^2 + (x_2 - c_2)^2}$.  
Objective: Perform two complete iterations (distance computation, cluster assignment, centroid recomputation).

---

### Full Step-by-Step Solution:

#### --- ITERATION 1 ---

1. **Calculate Euclidean Distances to Initial Centroids $C_1=(2, 3)$ and $C_2=(8, 7)$:**
   - **For $x^{(1)} = (2, 3)$:**
     $$d(x^{(1)}, C_1) = \sqrt{(2-2)^2 + (3-3)^2} = \sqrt{0 + 0} = \mathbf{0.0}$$
     $$d(x^{(1)}, C_2) = \sqrt{(2-8)^2 + (3-7)^2} = \sqrt{(-6)^2 + (-4)^2} = \sqrt{36 + 16} = \sqrt{52} \approx \mathbf{7.211}$$
     $\implies \min(0.0, 7.211) \to \mathbf{\text{Cluster 1}}$

   - **For $x^{(2)} = (3, 3)$:**
     $$d(x^{(2)}, C_1) = \sqrt{(3-2)^2 + (3-3)^2} = \sqrt{1^2 + 0} = \mathbf{1.0}$$
     $$d(x^{(2)}, C_2) = \sqrt{(3-8)^2 + (3-7)^2} = \sqrt{(-5)^2 + (-4)^2} = \sqrt{25 + 16} = \sqrt{41} \approx \mathbf{6.403}$$
     $\implies \min(1.0, 6.403) \to \mathbf{\text{Cluster 1}}$

   - **For $x^{(3)} = (8, 7)$:**
     $$d(x^{(3)}, C_1) = \sqrt{(8-2)^2 + (7-3)^2} = \sqrt{6^2 + 4^2} = \sqrt{36 + 16} = \sqrt{52} \approx \mathbf{7.211}$$
     $$d(x^{(3)}, C_2) = \sqrt{(8-8)^2 + (7-7)^2} = \sqrt{0 + 0} = \mathbf{0.0}$$
     $\implies \min(7.211, 0.0) \to \mathbf{\text{Cluster 2}}$

   - **For $x^{(4)} = (9, 8)$:**
     $$d(x^{(4)}, C_1) = \sqrt{(9-2)^2 + (8-3)^2} = \sqrt{7^2 + 5^2} = \sqrt{49 + 25} = \sqrt{74} \approx \mathbf{8.602}$$
     $$d(x^{(4)}, C_2) = \sqrt{(9-8)^2 + (8-7)^2} = \sqrt{1^2 + 1^2} = \sqrt{1 + 1} = \sqrt{2} \approx \mathbf{1.414}$$
     $\implies \min(8.602, 1.414) \to \mathbf{\text{Cluster 2}}$

2. **Cluster Assignment Summary after Iteration 1:**
   - **Cluster 1 ($S_1$):** $\{x^{(1)}, x^{(2)}\} = \{(2, 3), (3, 3)\}$
   - **Cluster 2 ($S_2$):** $\{x^{(3)}, x^{(4)}\} = \{(8, 7), (9, 8)\}$

3. **Centroid Update Step (Arithmetic Mean of Assigned Points):**
   - **New Centroid $C_1^{(1)}$:**
     $$C_1^{(1)} = \left( \frac{2 + 3}{2}, \frac{3 + 3}{2} \right) = \left( \frac{5}{2}, \frac{6}{2} \right) = \mathbf{(2.5, 3.0)}$$
   - **New Centroid $C_2^{(1)}$:**
     $$C_2^{(1)} = \left( \frac{8 + 9}{2}, \frac{7 + 8}{2} \right) = \left( \frac{17}{2}, \frac{15}{2} \right) = \mathbf{(8.5, 7.5)}$$

---

#### --- ITERATION 2 ---
Current Centroids: $C_1 = (2.5, 3.0), \quad C_2 = (8.5, 7.5)$.

1. **Recalculate Euclidean Distances:**
   - **For $x^{(1)} = (2, 3)$:**
     $$d(x^{(1)}, C_1) = \sqrt{(2-2.5)^2 + (3-3.0)^2} = \sqrt{(-0.5)^2 + 0} = \mathbf{0.5}$$
     $$d(x^{(1)}, C_2) = \sqrt{(2-8.5)^2 + (3-7.5)^2} = \sqrt{(-6.5)^2 + (-4.5)^2} = \sqrt{42.25 + 20.25} = \sqrt{62.5} \approx \mathbf{7.906}$$
     $\implies \text{Assigned to } \mathbf{\text{Cluster 1}}$

   - **For $x^{(2)} = (3, 3)$:**
     $$d(x^{(2)}, C_1) = \sqrt{(3-2.5)^2 + (3-3.0)^2} = \sqrt{0.5^2 + 0} = \mathbf{0.5}$$
     $$d(x^{(2)}, C_2) = \sqrt{(3-8.5)^2 + (3-7.5)^2} = \sqrt{(-5.5)^2 + (-4.5)^2} = \sqrt{30.25 + 20.25} = \sqrt{50.5} \approx \mathbf{7.106}$$
     $\implies \text{Assigned to } \mathbf{\text{Cluster 1}}$

   - **For $x^{(3)} = (8, 7)$:**
     $$d(x^{(3)}, C_1) = \sqrt{(8-2.5)^2 + (7-3.0)^2} = \sqrt{5.5^2 + 4.0^2} = \sqrt{30.25 + 16} = \sqrt{46.25} \approx \mathbf{6.801}$$
     $$d(x^{(3)}, C_2) = \sqrt{(8-8.5)^2 + (7-7.5)^2} = \sqrt{(-0.5)^2 + (-0.5)^2} = \sqrt{0.25 + 0.25} = \sqrt{0.50} \approx \mathbf{0.707}$$
     $\implies \text{Assigned to } \mathbf{\text{Cluster 2}}$

   - **For $x^{(4)} = (9, 8)$:**
     $$d(x^{(4)}, C_1) = \sqrt{(9-2.5)^2 + (8-3.0)^2} = \sqrt{6.5^2 + 5.0^2} = \sqrt{42.25 + 25} = \sqrt{67.25} \approx \mathbf{8.201}$$
     $$d(x^{(4)}, C_2) = \sqrt{(9-8.5)^2 + (8-7.5)^2} = \sqrt{0.5^2 + 0.5^2} = \sqrt{0.25 + 0.25} = \sqrt{0.50} \approx \mathbf{0.707}$$
     $\implies \text{Assigned to } \mathbf{\text{Cluster 2}}$

2. **Cluster Assignment Summary after Iteration 2:**
   - **Cluster 1:** $\{x^{(1)}, x^{(2)}\}$
   - **Cluster 2:** $\{x^{(3)}, x^{(4)}\}$

3. **Centroid Recomputation:**
   $$C_1^{(2)} = (2.5, 3.0), \quad C_2^{(2)} = (8.5, 7.5)$$
   **Convergence State:** The cluster assignments in Iteration 2 are identical to Iteration 1, and the centroids have not shifted ($\Delta C = 0$). **The algorithm has fully converged.**

---

# Special Section: Comprehensive Solutions to All Unanswered Questions in `myNotes-ml.pdf`

This section contains rigorous, complete answers to every single unanswered question, margin note, and homework problem present in the student's notebook.

---

## Unanswered Item 1 (Page 4):
### Question: "What is meaning strong +ve & -ve correlation?"
**Answer:**
- **Strong Positive Correlation ($r \to +1$):** Indicates that the two variables move in lockstep in the same direction. When $X$ increases, $Y$ increases almost proportionally along a straight line with positive slope. The data scatter plot resembles a tightly bundled upward-sloping ellipse or line. Real-life example: Hours studied vs. exam marks obtained.
- **Strong Negative Correlation ($r \to -1$):** Indicates an inverse linear relationship. When $X$ increases, $Y$ decreases almost proportionally along a straight line with negative slope. The data scatter plot resembles a tightly bundled downward-sloping ellipse. Real-life example: Elevation above sea level vs. atmospheric temperature.
- **Zero Correlation ($r = 0$):** Indicates no linear tendency between the two variables. Knowledge of $X$ provides zero predictive linear information about $Y$. Points scatter in an isotropic cloud or a horizontal line.

---

## Unanswered Item 2 (Page 4):
### Question: "Justify the reason that Pearson correlation is used for linear only."
**Answer:**
Pearson correlation is defined as:
$$r_{xy} = \frac{\sum (x_i - \bar{x})(y_i - \bar{y})}{\sqrt{\sum (x_i - \bar{x})^2 \sum (y_i - \bar{y})^2}}$$
1. **Mathematical Structure:** The numerator computes the inner product between the centralized vector $(x - \bar{x})$ and $(y - \bar{y})$, which measures cosine similarity (an angular measure of collinearity). It is maximized if and only if one vector is an exact positive scalar multiple of the other: $(y_i - \bar{y}) = c(x_i - \bar{x})$ ($c > 0$).
2. **Failure on Non-Linear Symmetries:** If a relationship is non-linear and symmetric (e.g., $Y = X^2$ over $[-k, k]$), for every point $(x, x^2)$, there exists a matching point $(-x, x^2)$. In the covariance summation, the term $(x)(x^2) = x^3$ exactly cancels the term $(-x)(x^2) = -x^3$. Thus, the total covariance sums to $0$, yielding $r = 0$ despite a perfect deterministic relationship.
3. **Conclusion:** Pearson correlation measures exclusively the degree of **straight-line collinearity**. For non-linear monotonic relationships, Spearman's rank correlation or mutual information must be used.

---

## Unanswered Item 3 (Page 8):
### Question: "What is relation b/w slope & correlation?"
**Answer:**
From the OLS derivation for simple linear regression $\hat{y} = w_0 + w_1 x$:
$$w_1 = \frac{\text{Cov}(X, Y)}{s_x^2}$$
Since $r_{xy} = \frac{\text{Cov}(X, Y)}{s_x s_y} \implies \text{Cov}(X, Y) = r_{xy} s_x s_y$, substituting gives:
$$\mathbf{w_1 = r_{xy} \left(\frac{s_y}{s_x}\right)}$$

### Critical Insights:
1. **Directional Concordance:** The sign of the regression slope $w_1$ is always identical to the sign of the Pearson correlation coefficient $r_{xy}$ (because standard deviations $s_x, s_y > 0$).
2. **Special Case of Standardized Variables:** If both $X$ and $Y$ are standardized to unit variance ($s_x = 1, s_y = 1$), then **$w_1 = r_{xy}$** exactly.
3. **Asymmetry vs. Symmetry:** Correlation is symmetric ($r_{xy} = r_{yx}$), but regression slope is asymmetric: predicting $X$ from $Y$ yields slope $w_1' = r_{xy} \frac{s_x}{s_y} \neq w_1$.

---

## Unanswered Item 4 (Page 9):
### Question: "Why we normalize $r$ by $S_x$ & $S_y$ and not by $S_x^2$ & $S_y^2$?"
**Answer:**
1. **Dimensional Homogeneity (Unit Cancellation):**
   - The covariance $\text{Cov}(X, Y)$ has units: $[\text{Units of } X] \times [\text{Units of } Y]$.
   - The product $s_x s_y$ has units: $[\text{Units of } X] \times [\text{Units of } Y]$.
   - Dividing $\text{Cov}(X,Y)$ by $s_x s_y$ cancels all physical units, making $r$ a dimensionless pure number.
   - If we normalized by $s_x^2 s_y^2$, the resulting metric would have units $\frac{1}{[\text{Units of } X][\text{Units of } Y]}$, which would remain scale-dependent!
2. **Cauchy-Schwarz Inequality Bound:**
   By the Cauchy-Schwarz inequality for inner products in $\mathbb{R}^n$:
   $$\left| \sum_{i=1}^n (x_i - \bar{x})(y_i - \bar{y}) \right| \le \sqrt{\sum_{i=1}^n (x_i - \bar{x})^2} \sqrt{\sum_{i=1}^n (y_i - \bar{y})^2}$$
   Dividing through by the right-hand side rigorously bounds the ratio to the interval $[-1, +1]$. Dividing by variances $s_x^2 s_y^2$ would violate this fundamental mathematical bound.

---

## Unanswered Item 5 (Pages 9–12):
### Question: "Estimate $y$ using $x$ by OLS for dataset $x=[1,2,3,4,5], y=[1.2, 1.8, 2.6, 3.2, 3.8]$. What is $y$ when $x=6$?"
**Answer:**
Let $n = 5$.

#### 1. Compute Means:
$$\bar{x} = \frac{1 + 2 + 3 + 4 + 5}{5} = \frac{15}{5} = \mathbf{3.0}$$
$$\bar{y} = \frac{1.2 + 1.8 + 2.6 + 3.2 + 3.8}{5} = \frac{12.6}{5} = \mathbf{2.52}$$

#### 2. Tabulate Deviations and Products:
| $i$ | $x_i$ | $y_i$ | $(x_i - \bar{x})$ | $(y_i - \bar{y})$ | $(x_i - \bar{x})^2$ | $(x_i - \bar{x})(y_i - \bar{y})$ |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| 1 | 1 | 1.2 | $-2.0$ | $-1.32$ | 4.0 | $+2.64$ |
| 2 | 2 | 1.8 | $-1.0$ | $-0.72$ | 1.0 | $+0.72$ |
| 3 | 3 | 2.6 | $0.0$ | $+0.08$ | 0.0 | $0.00$ |
| 4 | 4 | 3.2 | $+1.0$ | $+0.68$ | 1.0 | $+0.68$ |
| 5 | 5 | 3.8 | $+2.0$ | $+1.28$ | 4.0 | $+2.56$ |
| **Sum** | **15** | **12.6** | **0.0** | **0.0** | **10.0** | **+6.60** |

#### 3. Compute Slope ($w_1$ / $b$) and Intercept ($w_0$ / $a$):
$$w_1 = \frac{\sum (x_i - \bar{x})(y_i - \bar{y})}{\sum (x_i - \bar{x})^2} = \frac{6.60}{10.0} = \mathbf{0.66}$$
$$w_0 = \bar{y} - w_1 \bar{x} = 2.52 - 0.66(3.0) = 2.52 - 1.98 = \mathbf{0.54}$$

Regression Equation: $\mathbf{\hat{y} = 0.54 + 0.66 x}$

#### 4. Prediction for $x = 6$:
$$\hat{y}(6) = 0.54 + 0.66(6) = 0.54 + 3.96 = \mathbf{4.50}$$

---

## Unanswered Item 6 (Page 13):
### Homework Prompt: "H.W. in terms of $X_i, y_i$ (Derive GD update for MSE)"
**Answer:**
Starting with $J(w) = \frac{1}{2m} \sum_{i=1}^m (\hat{y}_i - y_i)^2$ with $\hat{y}_i = \sum_{k=0}^n w_k x_{ik}$:
$$\frac{\partial J}{\partial w_j} = \frac{1}{2m} \sum_{i=1}^m \frac{\partial}{\partial w_j} (\hat{y}_i - y_i)^2 = \frac{1}{2m} \sum_{i=1}^m 2(\hat{y}_i - y_i) \frac{\partial \hat{y}_i}{\partial w_j}$$
Since $\frac{\partial \hat{y}_i}{\partial w_j} = \frac{\partial}{\partial w_j}(w_0 x_{i0} + \dots + w_j x_{ij} + \dots) = x_{ij}$:
$$\mathbf{\frac{\partial J}{\partial w_j} = \frac{1}{m} \sum_{i=1}^m (\hat{y}_i - y_i) x_{ij}}$$
The update rule is:
$$\mathbf{w_j^{(t+1)} = w_j^{(t)} - \frac{\alpha}{m} \sum_{i=1}^m (\hat{y}_i - y_i) x_{ij}}$$

---

## Unanswered Item 7 (Page 14):
### Homework Prompt: "H.W. Incremental gradient descent & What is limitation of SGD?"
**Answer:**
- **Incremental Gradient Descent (Stochastic Gradient Descent - SGD):** Instead of evaluating the entire dataset to compute the true average gradient, SGD updates parameters immediately after inspecting each individual training example $(x^{(i)}, y^{(i)})$:
  $$w_j^{(t+1)} = w_j^{(t)} - \alpha (\hat{y}_i - y_i) x_{ij}$$
- **Limitations of SGD:**
  1. **Severe High-Variance Oscillations:** Individual sample gradients are noisy approximations of the true gradient. The loss trajectory fluctuates wildly instead of descending smoothly.
  2. **Never Settles at Exact Minimum with Constant $\alpha$:** Because of persistent gradient noise, SGD oscillates continuously around the minimum and does not stabilize unless the learning rate is systematically decayed (annealed).
  3. **Loss of Vectorized SIMD / GPU Acceleration:** Computing updates one sample at a time cannot exploit parallel matrix hardware multipliers (unlike batch/mini-batch modes).
  4. **Vulnerability to Noisy Labels & Outliers:** A single mislabeled training instance can deflect the optimization path drastically off course.

---

## Unanswered Item 8 (Page 15):
### Question 1: "How to test over-fitting during training itself?"
**Answer:**
1. **Learning Curves (Train vs. Validation Loss Tracking):**
   At the end of every epoch, evaluate and plot both the Training Loss and the Validation Loss on a holdout validation split:
   - **Normal Fitting:** Both train loss and validation loss decrease concurrently.
   - **Overfitting Point:** The training loss continues decreasing toward zero, while the validation loss reaches a minimum and begins **rising / diverging upward**.
2. **Early Stopping:** Programmatically halt training the moment validation loss fails to improve for a pre-set number of consecutive epochs (patience threshold), saving the weights from the epoch with the lowest validation error.

### Question 2: "Too many features & less samples ($p > n$ problem)?"
**Answer:**
When the number of features $p$ (or $n$) exceeds the number of observations $m$:
1. **Mathematical Singularity:** The design matrix $X$ has rank at most $m$. The $(p \times p)$ matrix $X^T X$ is strictly rank-deficient and singular ($\det(X^T X) = 0$). Ordinary Least Squares closed-form cannot be solved.
2. **Extreme Overfitting (Interpolation):** There are infinite parameter combinations that achieve $0$ training error by simply memorizing the points, resulting in disastrous generalization error.
3. **Remedies:**
   - **Regularization:** Add $L_2$ Ridge penalty ($\mathbf{X^T X + \lambda I}$ is always invertible) or $L_1$ Lasso penalty (forces sparse weights, selecting a subset of features).
   - **Dimensionality Reduction:** Apply Principal Component Analysis (PCA) to project data into a lower-dimensional orthogonal subspace.
   - **Feature Selection:** Filter irrelevant or redundant features using mutual information or correlation thresholds.

---

## Unanswered Item 9 (Pages 16–18):
### Notebook Case Study: Student's Exploding Linear Regression Batch GD
In the student notebook (pages 16–18), Batch GD was attempted on:
- $x^{(1)} = [1, 2], y^{(1)} = 6$
- $x^{(2)} = [2, 10], y^{(2)} = 24$
With initial weights $w = [1, 1, 1]$ and $\alpha = 0.1$.
- **Result in Notes:** After Epoch 1, weights became $w_0 = 1.65, w_1 = 2.2, w_2 = 6.7$.
- In Epoch 2, predictions exploded to $\hat{y}_1 = 17.25, \hat{y}_2 = 73.05$, errors became $+11.25$ and $+49.05$, and prediction for $[3, 12]$ exploded to **$-238.56$**!

### Why Did the Algorithm Explode?
**Root Cause: Learning Rate Overstepping the Lipschitz Spectral Bound on Unscaled Data.**
- In linear regression, Batch GD converges if and only if:
  $$\alpha < \frac{2}{\lambda_{\max}\left(\frac{1}{m} X^T X\right)}$$
  where $\lambda_{\max}$ is the maximum eigenvalue of the Hessian matrix.
- Because feature $x_2$ has large unscaled values ($2$ and $10$), $x_{i2}^2$ reaches $100$.
- The maximum eigenvalue $\lambda_{\max}$ for this dataset is approximately $53.5$.
- The maximum stable learning rate was:
  $$\alpha_{\max} = \frac{2}{53.5} \approx \mathbf{0.037}$$
- The student chose $\alpha = 0.1$, which was nearly **$3\times$ larger than the maximum mathematical stability threshold**! As a result, each gradient update overcorrected exponentially, driving the weights into unstable geometric oscillation.
- **Remedy:** Standardize features or set $\alpha \le 0.01$.

---

## Unanswered Item 10 (Page 19):
### Question 1: "Considering MSE cost func. if we apply batch GD what will be the formula for updation?"
**Answer:**
Let $J_{\text{MSE}}(w) = \frac{1}{2m} \sum_{i=1}^m (\hat{y}_i - y_i)^2$ where $\hat{y}_i = g(z_i) = \frac{1}{1 + e^{-z_i}}$.
Using the chain rule:
$$\frac{\partial J_{\text{MSE}}}{\partial w_j} = \frac{1}{m} \sum_{i=1}^m (\hat{y}_i - y_i) \cdot g'(z_i) \cdot \frac{\partial z_i}{\partial w_j}$$
Since $g'(z_i) = \hat{y}_i (1 - \hat{y}_i)$ and $\frac{\partial z_i}{\partial w_j} = x_{ij}$:
$$\mathbf{\frac{\partial J_{\text{MSE}}}{\partial w_j} = \frac{1}{m} \sum_{i=1}^m (\hat{y}_i - y_i) \hat{y}_i (1 - \hat{y}_i) x_{ij}}$$
The resulting update formula is:
$$\mathbf{w_j^{(t+1)} = w_j^{(t)} - \frac{\alpha}{m} \sum_{i=1}^m (\hat{y}_i - y_i) \hat{y}_i (1 - \hat{y}_i) x_{ij}}$$
*Flaw:* As proved in Module 7.4, this formula causes vanishing gradients when the prediction is completely incorrect ($\hat{y}_i \approx 0$ when $y_i = 1$).

### Question 2: "What is the function used for calculating loss in multiple [classes]?"
**Answer:**
For multi-class classification with $K$ mutual classes, we use the **Categorical Cross-Entropy Loss** (Multiclass Log-Loss) paired with the **Softmax activation function**:
1. **Softmax Function:**
   $$\hat{y}_{ik} = P(y = k | x^{(i)}) = \frac{e^{w_k^T x^{(i)}}}{\sum_{j=1}^K e^{w_j^T x^{(i)}}}$$
2. **Categorical Cross-Entropy Loss Function:**
   $$\mathbf{J(W) = -\frac{1}{m} \sum_{i=1}^m \sum_{k=1}^K y_{ik} \log(\hat{y}_{ik})}$$
   where $y_{ik}$ is the one-hot encoded ground truth binary indicator ($y_{ik} = 1$ if instance $i$ belongs to class $k$, else $0$).

---

## Unanswered Item 11 (Page 20):
### Question: "Difference b/w Loss function / Cost function?"
**Answer:**

| Concept | Scope & Definition | Mathematical Formulation |
| :--- | :--- | :--- |
| **Loss Function $\mathcal{L}(\hat{y}^{(i)}, y^{(i)})$** | Measures the error/discrepancy on a **single, individual training instance**. | $\mathcal{L}(\hat{y}, y) = \frac{1}{2}(\hat{y} - y)^2$ (Squared error)<br>$\mathcal{L}(\hat{y}, y) = -\big[y\log\hat{y} + (1-y)\log(1-\hat{y})\big]$ (Log-loss) |
| **Cost Function $J(w)$** | Measures the **aggregate / average error across the entire training dataset** of $m$ examples (often plus a regularization term). | $J(w) = \frac{1}{m} \sum_{i=1}^m \mathcal{L}(\hat{y}^{(i)}, y^{(i)}) + \lambda R(w)$ |

---

## Unanswered Item 12 (Page 23):
### Completion of Unfinished Logistic Regression Problem from Student Notebook
In page 23 of `myNotes-ml.pdf`, the student began solving a problem but stopped mid-way:
- Point $P_1: x = [1, 2], \quad y = 1$
- Point $P_2: x = [2, 1], \quad y = 0$
- Initial weights: $w_0 = 0.0, \quad w_1 = 0.1, \quad w_2 = -0.2$
- Learning rate $\alpha = 0.1$, Epochs $= 2$, Batch size $m = 2$.

The student correctly computed initial predictions:
- $z(P_1) = 0 + 0.1(1) + (-0.2)(2) = -0.3 \implies \hat{y}(P_1) = \frac{1}{1 + e^{0.3}} \approx 0.425557$
- $z(P_2) = 0 + 0.1(2) + (-0.2)(1) = 0.0 \implies \hat{y}(P_2) = \frac{1}{1 + e^0} = 0.500000$

Here is the complete solution for both Epochs:

#### --- Complete Epoch 1 Updates ---
1. **Errors $(\hat{y} - y)$:**
   - $e_1 = 0.425557 - 1 = \mathbf{-0.574443}$
   - $e_2 = 0.500000 - 0 = \mathbf{+0.500000}$
2. **Gradients $\frac{\partial J}{\partial w_j} = \frac{1}{2} \sum_{i=1}^2 e_i x_{ij}$:**
   - $\frac{\partial J}{\partial w_0} = \frac{1}{2}[(-0.574443)(1) + (0.5)(1)] = \frac{-0.074443}{2} = \mathbf{-0.037221}$
   - $\frac{\partial J}{\partial w_1} = \frac{1}{2}[(-0.574443)(1) + (0.5)(2)] = \frac{-0.574443 + 1.0}{2} = \frac{0.425557}{2} = \mathbf{+0.212779}$
   - $\frac{\partial J}{\partial w_2} = \frac{1}{2}[(-0.574443)(2) + (0.5)(1)] = \frac{-1.148885 + 0.5}{2} = \frac{-0.648885}{2} = \mathbf{-0.324443}$
3. **Update Weights:**
   - $w_0^{(1)} = 0.0 - (0.1)(-0.037221) = \mathbf{+0.003722}$
   - $w_1^{(1)} = 0.1 - (0.1)(0.212779) = 0.1 - 0.021278 = \mathbf{+0.078722}$
   - $w_2^{(1)} = -0.2 - (0.1)(-0.324443) = -0.2 + 0.032444 = \mathbf{-0.167556}$

#### --- Complete Epoch 2 Updates ---
Current weights: $w_0 = 0.003722, w_1 = 0.078722, w_2 = -0.167556$.
1. **Activations & Predictions:**
   - $z(P_1) = 0.003722 + 0.078722(1) - 0.167556(2) = -0.252667 \implies \hat{y}_1 = \frac{1}{1 + e^{0.252667}} = \mathbf{0.437167}$
   - $z(P_2) = 0.003722 + 0.078722(2) - 0.167556(1) = -0.006389 \implies \hat{y}_2 = \frac{1}{1 + e^{0.006389}} = \mathbf{0.498403}$
2. **Errors:**
   - $e_1 = 0.437167 - 1 = \mathbf{-0.562833}$
   - $e_2 = 0.498403 - 0 = \mathbf{+0.498403}$
3. **Gradients:**
   - $\frac{\partial J}{\partial w_0} = \frac{1}{2}[-0.562833 + 0.498403] = \mathbf{-0.032215}$
   - $\frac{\partial J}{\partial w_1} = \frac{1}{2}[-0.562833(1) + 0.498403(2)] = \frac{0.433973}{2} = \mathbf{+0.216986}$
   - $\frac{\partial J}{\partial w_2} = \frac{1}{2}[-0.562833(2) + 0.498403(1)] = \frac{-0.627263}{2} = \mathbf{-0.313632}$
4. **Final Updated Weights After Epoch 2:**
   - $w_0^{(2)} = 0.003722 - (0.1)(-0.032215) = \mathbf{+0.006944}$
   - $w_1^{(2)} = 0.078722 - (0.1)(0.216986) = \mathbf{+0.057024}$
   - $w_2^{(2)} = -0.167556 - (0.1)(-0.313632) = \mathbf{-0.136193}$

---

# Complete Solved Mid-Semester Examination Paper (Parts A, B, and C)
**Institution:** Indian Institute of Information Technology Guwahati (IIITG)  
**Course:** CS306 Machine Learning | **Time:** 2 Hours | **Max Marks:** 40  

---

## PART A: Objective Section (15 Marks)
*Marking Scheme: Each question has at least one correct option. Score $+1$ for all correct options selected; $+0.5$ if at least one correct and no wrong; $0$ if not answered; $-1$ if any wrong option selected.*

---

### Question 1
**Suppose two variables $X$ and $Y$ have a Pearson correlation coefficient of $r = 0$. Which of the following is the most correct interpretation?**
- A. There is no linear relationship between $X$ and $Y$.
- B. The regression line of $Y$ on $X$ will be horizontal.
- C. There is no relationship between $X$ and $Y$.
- D. $X$ and $Y$ are independent.

> **Correct Answers:** **A, B**  
> **Exhaustive Explanation:**
> - **A is TRUE:** Pearson's $r$ evaluates exclusively linear dependency. $r = 0$ strictly means zero linear association.
> - **B is TRUE:** The OLS regression slope is $w_1 = r \frac{s_y}{s_x}$. If $r = 0$, then $w_1 = 0$. The regression line is $\hat{y} = w_0 + 0 \cdot x = \bar{y}$, which is a completely horizontal line.
> - **C is FALSE:** Non-linear dependencies can exist (e.g., $Y = X^2$ on symmetric bounds yields $r=0$).
> - **D is FALSE:** Independence implies zero correlation, but zero correlation does not imply independence.

---

### Question 2
**Which of the following scenarios will not change the value of the Pearson correlation coefficient between $X$ and $Y$?**
- A. Adding a constant to all values of $Y$.
- B. Scaling all values of $X$ by a positive constant.
- C. Adding random noise to $Y$ that is uncorrelated with $X$.
- D. Multiplying all values of $X$ by $-1$.

> **Correct Answers:** **A, B**  
> **Exhaustive Explanation:**
> - **A is TRUE:** Shifting $Y \to Y + c$ leaves deviations $(y_i - \bar{y})$ and standard deviation $s_y$ unchanged.
> - **B is TRUE:** Scaling $X \to aX$ with $a > 0$ scales both covariance and $s_x$ by factor $a$, which cancel out: $\frac{a \text{Cov}}{a s_x s_y} = r$.
> - **C is FALSE:** Adding noise adds independent variance to $Y$, increasing $s_y$ without increasing covariance, shrinking $r$ toward 0.
> - **D is FALSE:** Multiplying by $-1$ flips the sign of the covariance: $r_{\text{new}} = -r$.

---

### Question 3
**Suppose $\text{Cov}(X, Y) = 12$, $\sigma_X = 4$, and $\sigma_Y = 6$. What is the Pearson correlation coefficient $r_{XY}$?**
- A. $2.00$
- B. $3.00$
- C. $0.25$
- D. $0.50$

> **Correct Answer:** **D**  
> **Exhaustive Explanation:**
> $$r_{XY} = \frac{\text{Cov}(X, Y)}{\sigma_X \sigma_Y} = \frac{12}{4 \times 6} = \frac{12}{24} = \mathbf{0.50}$$

---

### Question 4
**Which of the following statements about Euclidean distance are correct?**
- A. It is the most common distance metric in K-means.
- B. It is less sensitive to outliers than Manhattan distance.
- C. It assumes features are on the same scale.
- D. It accounts for correlation among features.

> **Correct Answers:** **A, C**  
> **Exhaustive Explanation:**
> - **A is TRUE:** Standard Lloyd's K-Means algorithm minimizes within-cluster sum of squared Euclidean distances.
> - **B is FALSE:** Euclidean distance squares differences ($(u_j - v_j)^2$), making it significantly *more* sensitive to extreme outliers than Manhattan ($|u_j - v_j|$).
> - **C is TRUE:** If features are unscaled, the feature with the largest numerical magnitude dominates the distance calculation.
> - **D is FALSE:** Euclidean distance assumes isotropic orthogonal axes. Mahalanobis distance accounts for correlations.

---

### Question 5
**Mahalanobis distance is useful because:**
- A. It ignores feature scaling.
- B. It accounts for correlations between variables.
- C. It uses the inverse covariance matrix.
- D. It is equivalent to Manhattan distance.

> **Correct Answers:** **B, C**  
> **Exhaustive Explanation:**
> The Mahalanobis distance is defined as $d_M(u, v) = \sqrt{(u-v)^T \mathbf{\Sigma}^{-1} (u-v)}$. It explicitly incorporates the inverse covariance matrix $\mathbf{\Sigma}^{-1}$ (C is TRUE) and automatically accounts for both feature variance scaling and cross-feature correlations (B is TRUE).

---

### Question 6
**For ordinal data, rank-based distances:**
- A. Always yield zero distance.
- B. Often require normalization.
- C. Preserve order of categories.
- D. Ignore ordering of categories.

> **Correct Answers:** **B, C**  
> **Exhaustive Explanation:**
> Ordinal data encodes relative rankings without equal spacing. Rank-based metrics preserve the ordinal rank order (C is TRUE) and typically require normalization into the range $[0, 1]$ to make comparisons across attributes with different numbers of tiers meaningful (B is TRUE).

---

### Question 7
**Hamming distance is suitable for:**
- A. Highly correlated multivariate data.
- B. Continuous numerical data.
- C. DNA sequence comparison.
- D. Binary data.

> **Correct Answers:** **C, D**  
> **Exhaustive Explanation:**
> Hamming distance counts coordinate mismatches. It is ideal for binary bitstrings (D is TRUE) and categorical symbol strings such as DNA nucleotide sequences $\{A, C, G, T\}$ (C is TRUE).

---

### Question 8
**Jaccard distance between two sets is:**
- A. $\frac{|X \cap Y|}{|X \cup Y|}$
- B. Always equal to Hamming distance.
- C. $1 - \frac{|X \cap Y|}{|X \cup Y|}$
- D. Useful for sparse binary data.

> **Correct Answers:** **C, D**  
> **Exhaustive Explanation:**
> Jaccard similarity is $J(X, Y) = \frac{|X \cap Y|}{|X \cup Y|}$. The Jaccard distance is the complementary metric $d_J = 1 - J(X, Y)$ (C is TRUE). It ignores joint zeroes ($0-0$ negative matches), making it optimal for high-dimensional sparse binary vectors (D is TRUE).

---

### Question 9
**In simple linear regression $y = w_0 + w_1 x + \epsilon$:**
- A. $\epsilon$ is the independent variable.
- B. $x$ is the dependent variable.
- C. $w_0$ is the intercept.
- D. $w_1$ is the slope.

> **Correct Answers:** **C, D**  
> **Exhaustive Explanation:**
> In standard terminology, $y$ is the dependent variable, $x$ is the independent variable, $\epsilon$ is the random unobserved error, $w_0$ is the constant intercept, and $w_1$ is the regression slope.

---

### Question 10
**The ordinary least squares (OLS) method:**
- A. Minimizes the sum of squared errors.
- B. Ignores variance of residuals.
- C. Provides a closed-form solution.
- D. Always requires gradient descent.

> **Correct Answers:** **A, C**  
> **Exhaustive Explanation:**
> OLS analytically minimizes the sum of squared residuals $\sum (y_i - \hat{y}_i)^2$ (A is TRUE) and yields an exact closed-form solution via the normal equations $w = (X^T X)^{-1} X^T Y$ without needing iterative gradient descent (C is TRUE).

---

### Question 11
**$R^2$ (coefficient of determination):**
- A. Can be negative in standard definition.
- B. Lies between 0 and 1.
- C. Measures variance explained by the model.
- D. Always equals correlation coefficient.

> **Correct Answers:** **A, C**  
> **Exhaustive Explanation:**
> $R^2 = 1 - \frac{SS_{\text{res}}}{SS_{\text{tot}}}$. It quantifies the proportion of target variance explained by the model (C is TRUE). In standard statistical definition, if a model's predictions are worse than the baseline sample mean ($SS_{\text{res}} > SS_{\text{tot}}$), $R^2$ becomes negative (A is TRUE). (Note: B is only true for in-sample simple linear regression with an intercept).

---

### Question 12
**Gradient descent in regression:**
- A. Guarantees global optimum for non-convex functions.
- B. Sensitive to learning rate.
- C. Has variants: batch, stochastic, mini-batch.
- D. Updates parameters in direction of negative gradient.

> **Correct Answers:** **B, C, D**  
> **Exhaustive Explanation:**
> GD updates along $-\nabla J$ (D is TRUE), comes in BGD, SGD, and Mini-Batch variants (C is TRUE), and is highly sensitive to step size $\alpha$ (B is TRUE). It does NOT guarantee a global optimum on non-convex surfaces (A is FALSE).

---

### Question 13
**Which are the hyperparameters in linear regression training?**
- A. $w_0, w_1$
- B. Residuals.
- C. Number of epochs.
- D. Learning rate.

> **Correct Answers:** **C, D**  
> **Exhaustive Explanation:**
> $w_0, w_1$ are model parameters learned during training. Residuals are errors. Learning rate ($\alpha$) and number of epochs are external configuration knobs chosen before optimization begins.

---

### Question 14
**Overfitting occurs when:**
- A. Model performs well on training but poorly on test data.
- B. Model underfits both training and test data.
- C. Model has low training accuracy.
- D. Model learns noise in the dataset.

> **Correct Answers:** **A, D**  
> **Exhaustive Explanation:**
> Overfitting is characterized by high variance: the hypothesis memorizes random noise and idiosyncrasies in the training sample (D is TRUE), producing near-zero training error but high generalization error on unseen test data (A is TRUE).

---

### Question 15
**In multiple linear regression, the closed form solution is valid if:**
- A. Independent variables are perfectly correlated.
- B. Dataset size is always large.
- C. No severe multicollinearity exists.
- D. $X^T X$ is invertible.

> **Correct Answers:** **C, D**  
> **Exhaustive Explanation:**
> The normal equation $w = (X^T X)^{-1} X^T Y$ requires $(X^T X)$ to be non-singular and invertible (D is TRUE). Invertibility requires that no column of $X$ is a perfect linear combination of other columns (i.e., no multicollinearity) (C is TRUE).

---

## PART B: Short Answer Questions (10 Marks)

### Question 1: List and briefly explain two key assumptions of linear regression.
**Answer:**
1. **Linearity of the Data Relationship:** The relationship between the independent input variables $X$ and the conditional expectation of the dependent target variable $Y$ is strictly linear in the parameters: $\mathbb{E}[Y|X] = Xw$. If non-linear relationships exist, polynomial transformations or non-linear models must be employed.
2. **Independence and Homoscedasticity of Residuals:** The unobserved errors $\epsilon_i = y_i - \hat{y}_i$ must be independent (no autocorrelation, $\text{Cov}(\epsilon_i, \epsilon_j) = 0$ for $i \neq j$) and exhibit constant variance across all levels of the predictor variables ($\text{Var}(\epsilon_i) = \sigma^2$, homoscedasticity).

---

### Question 2: What does overfitting mean in the context of regression models? Mention one method to prevent it.
**Answer:**
- **Meaning:** In regression, overfitting occurs when a model possesses excessive capacity/complexity relative to the sample size, causing it to fit the random stochastic noise and outliers in the training set rather than the underlying population function. This manifests as very low training MSE but high test MSE.
- **Prevention Method:** **Regularization (Ridge $L_2$ / Lasso $L_1$).** Adding a penalty term to the cost function penalizes excessively large parameter weights:
  $$J_{\text{Ridge}}(w) = \frac{1}{2m} \sum_{i=1}^m (y_i - \hat{y}_i)^2 + \lambda \sum_{j=1}^n w_j^2$$
  This shrinks coefficients toward zero, reduces model variance, and prevents complex oscillations. *(Alternative valid methods: Holdout validation split with early stopping, feature reduction via PCA).*

---

### Question 3: Why is feature scaling important in logistic regression but not always in linear regression?
**Answer:**
1. **In Logistic Regression:** Optimization must be conducted using iterative gradient-based methods (e.g., Gradient Descent) because no closed-form solution exists for log-loss. Unscaled features produce highly eccentric elliptical cost contours that cause gradient descent to oscillate inefficiently. Furthermore, large unscaled feature values ($|z| \gg 0$) push the linear combination into the flat asymptotic saturation regions of the sigmoid function, where $g'(z) \approx 0$, causing severe **vanishing gradients** that freeze learning.
2. **In Linear Regression:** If linear regression is solved using the **analytical OLS closed-form normal equation** ($w = (X^T X)^{-1} X^T Y$), feature scaling is mathematically irrelevant. Scaling features simply scales the resulting weight coefficients inversely, leaving predictions and optimal loss entirely identical. *(Note: If linear regression is trained using Gradient Descent rather than OLS, feature scaling remains important).*

---

### Question 4: What role do residuals play in checking the validity of a linear regression model?
**Answer:**
Residuals ($\epsilon_i = y_i - \hat{y}_i$) serve as the primary diagnostic vehicle for validating model assumptions:
1. **Goodness-of-Fit Assessment:** The sum of squared residuals directly computes $R^2 = 1 - \frac{SS_{\text{res}}}{SS_{\text{tot}}}$, quantifying the proportion of unexplained variance.
2. **Residual Diagnostic Plots:**
   - **Linearity Check:** Plotting residuals $\epsilon_i$ against fitted values $\hat{y}_i$ should show a random, horizontal band around zero. Any curved pattern indicates an unmodeled non-linear relationship.
   - **Homoscedasticity Check:** A funnel-shaped spread (expanding variance) indicates heteroscedasticity, violating OLS optimality.
   - **Normality Check:** A Q-Q plot of standardized residuals verifies the normality assumption required for hypothesis testing and confidence intervals.

---

### Question 5: In logistic regression, how is the decision boundary defined mathematically?
**Answer:**
The decision boundary is defined as the geometric locus of points in the feature space where the model is completely indifferent between classes ($P(y=1|x) = P(y=0|x) = 0.5$).

Mathematically:
$$h_w(x) = g(w^T x) = \frac{1}{1 + e^{-w^T x}} = 0.5$$
Taking the reciprocal and solving:
$$1 + e^{-w^T x} = 2 \implies e^{-w^T x} = 1 \implies -w^T x = 0$$
$$\mathbf{w^T x = w_0 + w_1 x_1 + w_2 x_2 + \dots + w_n x_n = 0}$$
Thus, the decision boundary is an $(n-1)$-dimensional linear hyperplane. Points satisfying $w^T x > 0$ map to $\hat{y} > 0.5$ (Class 1), while points satisfying $w^T x < 0$ map to $\hat{y} < 0.5$ (Class 0).

---

## PART C: Numerical Demonstration Problems (15 Marks)
*The complete, verified step-by-step arithmetic solutions for Questions 1, 2, and 3 of Part C are fully documented in [Module 9: Step-by-Step Numerical Walkthroughs](#module-9-step-by-step-numerical-walkthroughs-benchmark-problems).*
- **Part C Question 1:** Linear Regression Batch GD $\to$ See [Numerical A](#numerical-a-batch-gradient-descent-for-linear-regression).
- **Part C Question 2:** Logistic Regression Mini-Batch GD $\to$ See [Numerical B](#numerical-b-mini-batch-gradient-descent-for-logistic-regression).
- **Part C Question 3:** K-Means Clustering ($K=2$, 2 iterations) $\to$ See [Numerical C](#numerical-c-k-means-clustering).

---

# Summary Quick Reference Sheet for Exam Day

| Concept | Key Formula | Core Takeaway / Exam Trap |
| :--- | :--- | :--- |
| **Mitchell ML Definition** | $P, T, E$ | Performance $P$ on Task $T$ improves with Experience $E$. |
| **Bessel's Correction** | $s^2 = \frac{1}{n-1}\sum (x_i - \bar{x})^2$ | Eliminates downward bias from estimating around $\bar{x}$. |
| **Pearson Correlation** | $r = \frac{\text{Cov}(X,Y)}{s_x s_y}$ | Range $[-1, +1]$. Measures strictly linear relationships. |
| **OLS Slope & Intercept** | $w_1 = r \frac{s_y}{s_x}, \quad w_0 = \bar{y} - w_1 \bar{x}$ | Line always passes through center of mass $(\bar{x}, \bar{y})$. |
| **Normal Equations** | $w = (X^T X)^{-1} X^T Y$ | Fails if $X^T X$ is singular, multicollinear, or $n > m$. |
| **$R^2$ Score** | $R^2 = 1 - \frac{SS_{\text{res}}}{SS_{\text{tot}}}$ | Can be negative if fit is worse than horizontal mean line. |
| **GD Update Rule** | $w_j \leftarrow w_j - \frac{\alpha}{m}\sum (\hat{y}_i - y_i) x_{ij}$ | Minus sign moves opposite to steepest ascent gradient. |
| **Feature Scaling** | $x' = \frac{x - \mu}{\sigma}$ or $\frac{x - x_{\min}}{x_{\max} - x_{\min}}$ | Spherical contours accelerate gradient descent convergence. |
| **Sigmoid Function** | $g(z) = \frac{1}{1 + e^{-z}}, \quad g'(z) = g(z)(1-g(z))$ | Bounded in $(0, 1)$. Output thresholded at $0.5$. |
| **Decision Boundary** | $w^T x = 0$ | Hyperplane separating Class 1 from Class 0. |
| **Cross-Entropy Loss** | $J = -\frac{1}{m}\sum [y\log\hat{y} + (1-y)\log(1-\hat{y})]$ | Strictly convex for logistic regression; prevents vanishing gradients. |
| **Precision & Recall** | $\text{Prec} = \frac{TP}{TP+FP}, \quad \text{Rec} = \frac{TP}{TP+FN}$ | Precision penalizes false alarms; Recall penalizes missed detections. |
| **K-Means Centroid** | $C_k = \frac{1}{|S_k|} \sum_{x \in S_k} x$ | Arithmetic mean of points currently assigned to cluster $k$. |
