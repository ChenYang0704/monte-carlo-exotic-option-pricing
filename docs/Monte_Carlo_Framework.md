# Monte Carlo Framework

## Overview

This library prices options using Monte Carlo simulation under the Black-Scholes framework.

The implementation separates the pricing workflow into the following components:

* `MarketData` stores market inputs such as spot price, risk-free rate, volatility and dividend yield.
* `PathGenerator` generates simulated asset paths.
* `MonteCarloEngine` simulates paths, evaluates option payoffs and discounts the expected payoff.
* `Option` defines the payoff logic for each product.
* `Statistics` computes mean, variance, standard deviation, standard error and confidence intervals.

This separation keeps the option payoff logic independent from the simulation engine.

---

## Black-Scholes Model

Under the Black-Scholes model, the underlying asset follows geometric Brownian motion (GBM):

$$
dS_t = (r-q)S_t,dt + \sigma S_t,dW_t
$$

where:

* $S_t$ = asset price at time $t$
* $r$ = risk-free rate
* $q$ = continuous dividend yield
* $\sigma$ = volatility
* $W_t$ = Brownian motion

Under the risk-neutral measure, the option price is given by the discounted expected payoff.

---

## Exact Path Simulation

The asset paths are generated using the exact geometric Brownian motion transition:

$$
S_{t+\Delta t}
=
S_t
\exp
\left[
\left(r-q-\frac{1}{2}\sigma^2\right)\Delta t
+
\sigma\sqrt{\Delta t}Z
\right]
$$

where:

* $Z \sim N(0,1)$
* $\Delta t = T/N$
* $T$ = option maturity
* $N$ = number of timesteps

For geometric Brownian motion, this transition samples directly from the conditional distribution of the asset price and therefore avoids the discretisation error associated with approximate SDE schemes.

As a result, European and binary option prices are generally insensitive to the number of timesteps used in the simulation.

---

## Path-Dependent Monitoring

Although the asset process is simulated exactly, path-dependent options still depend on the timestep grid used for monitoring.

Examples:

* Asian options use the average asset price along the simulated path.
* Barrier options monitor whether a barrier level has been breached.
* Lookback options depend on the maximum or minimum asset price observed on the path.

Increasing the number of timesteps improves the monitoring resolution and reduces monitoring error.

Barrier and lookback options are typically more timestep-sensitive than European and binary options because their payoffs depend directly on barrier crossings or path extrema.

---

## Monte Carlo Pricing

For a payoff $P_i$ generated on simulation path $i$, the Monte Carlo price estimator is:

$$
V
=
e^{-rT}
\frac{1}{M}
\sum_{i=1}^{M} P_i
$$

where:

* $V$ = estimated option price
* $M$ = number of simulated paths
* $P_i$ = payoff generated from path $i$
* $r$ = risk-free rate
* $T$ = option maturity

The engine evaluates the payoff on every simulated path, discounts each payoff to the present value, and computes the sample mean.

---

## Statistical Measures

### Standard Deviation

The standard deviation measures the dispersion of discounted payoffs across simulation paths.

The sample variance is computed using the unbiased estimator:

$$
s^2
=
\frac{1}{M-1}
\sum_{i=1}^{M}
(X_i-\bar X)^2
$$

where:

* $X_i$ = discounted payoff from path $i$
* $\bar{X}$ = sample mean of discounted payoffs
* $M$ = number of simulated paths

The sample standard deviation is:

$$
s = \sqrt{s^2}
$$

### Standard Error

The standard error measures the uncertainty of the Monte Carlo price estimate.

$$
SE
=
\frac{s}{\sqrt{M}}
$$

where:

* $s$ = sample standard deviation
* $M$ = number of simulated paths

The standard error decreases according to:

$$
SE
\propto
\frac{1}{\sqrt{M}}
$$

Therefore, reducing the standard error by half requires approximately four times as many simulations.


### Confidence Interval

The library reports an approximate 95% confidence interval:

$$
\bar{X}
\pm
1.96,SE
$$

where:

* $\bar{X}$ = Monte Carlo price estimate
* $SE$ = standard error

The confidence interval quantifies sampling uncertainty arising from a finite number of simulation paths.

---

## Numerical Error Sources

The main numerical error sources are:

### Sampling Error

Sampling error arises because the Monte Carlo estimator uses a finite number of simulation paths.

This error is measured by the standard error and decreases as the number of simulations increases.

### Monitoring Error

Monitoring error occurs when path-dependent events are only observed at discrete timesteps.

Examples include:

* Missing a barrier crossing between two monitoring dates.
* Missing a path maximum or minimum between two monitoring dates.
* Changes in the arithmetic average caused by a coarse monitoring grid.

Increasing the number of timesteps reduces monitoring error.

### Model Error

Model error arises from the assumptions of the Black-Scholes framework, including:

* Constant volatility
* Constant interest rates
* Continuous trading
* Lognormal asset dynamics

This library focuses on numerical pricing under the Black-Scholes model and does not attempt to model volatility smiles, stochastic volatility or jump processes.

---

## Current Implementation

The current implementation includes:

* Exact geometric Brownian motion path simulation
* Discrete timestep monitoring
* Standard Monte Carlo sampling
* Sample standard deviation
* Standard error estimation
* Approximate 95% confidence intervals

The framework is designed to keep pricing logic, path generation and statistical calculations separated, allowing new products and numerical techniques to be added without modifying the existing option payoff classes.
