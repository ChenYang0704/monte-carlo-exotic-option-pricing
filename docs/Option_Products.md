# Option Products

## Overview

This library supports the pricing of several equity option products using Monte Carlo simulation under the Black-Scholes framework.

The current implementation includes:

* European Options
* Binary Options
* Asian Options
* Barrier Options
* Lookback Options

All products are priced using risk-neutral valuation and simulated asset paths generated under geometric Brownian motion (GBM).

---

## European Option

A European option can only be exercised at maturity.

### Call Payoff

$$
\max(S_T - K, 0)
$$

### Put Payoff

$$
\max(K - S_T, 0)
$$

where:

* $S_T$ = asset price at maturity
* $K$ = strike price

European options serve as benchmark products because analytical Black-Scholes prices are available.

---

## Binary Option

A binary (cash-or-nothing) option pays a fixed cash amount if the option finishes in-the-money at maturity.

### Call Payoff

$$
\begin{cases}
1, & S_T > K \\
0, & \text{otherwise}
\end{cases}
$$

### Put Payoff

$$
\begin{cases}
1, & S_T < K \\
0, & \text{otherwise}
\end{cases}
$$

Binary options provide a useful validation product because analytical Black-Scholes prices are available.

---

## Asian Option

Asian options depend on the average asset price observed during the life of the option.

The library supports:

* Fixed-strike Asian options
* Floating-strike Asian options

### Fixed-Strike Call Payoff

$$
\max(\bar{S} - K, 0)
$$

### Fixed-Strike Put Payoff

$$
\max(K - \bar{S}, 0)
$$

where

$$
\bar{S}
=
\frac{1}{N+1}
\sum_{i=0}^{N}
S_i
$$

is the arithmetic average of the simulated asset path.

### Floating-Strike Call Payoff

$$
\max(S_T - \bar{S}, 0)
$$

### Floating-Strike Put Payoff

$$
\max(\bar{S} - S_T, 0)
$$

### Monitoring Convention

The arithmetic average includes all simulated path values, including the initial spot price $S_0$.

---

## Barrier Option

Barrier options become activated or deactivated when the underlying asset crosses a specified barrier level.

The library supports all combinations of:

* Call and Put options
* Knock-In and Knock-Out barriers
* Up and Down barriers

### Example: Up-and-Out Call

The option payoff is

$$
\max(S_T - K, 0)
$$

provided the barrier is never breached.

Otherwise the payoff is

$$
0
$$

### Monitoring Convention

Barrier monitoring is performed at every simulated timestep.

The implementation therefore represents a discretely monitored barrier option. Increasing the number of timesteps improves the monitoring resolution and reduces barrier-monitoring bias.

---

## Lookback Option

Lookback options depend on the maximum or minimum asset price observed during the life of the option.

The library supports:

* Fixed-strike lookback options
* Floating-strike lookback options

### Fixed-Strike Call Payoff

$$
\max(S_{\max} - K, 0)
$$

### Fixed-Strike Put Payoff

$$
\max(K - S_{\min}, 0)
$$

### Floating-Strike Call Payoff

$$
\max(S_T - S_{\min}, 0)
$$

### Floating-Strike Put Payoff

$$
\max(S_{\max} - S_T, 0)
$$

where:

* $S_{\max}$ = maximum asset price observed on the path
* $S_{\min}$ = minimum asset price observed on the path

### Monitoring Convention

The maximum and minimum values are computed from all simulated path values, including the initial spot price $S_0$.

---

## Product Summary

| Product  | Path Dependent | Analytical Benchmark |
| -------- | -------------- | -------------------- |
| European | No             | Black-Scholes        |
| Binary   | No             | Black-Scholes        |
| Asian    | Yes            | None                 |
| Barrier  | Yes            | Future Release       |
| Lookback | Yes            | Future Release       |

---
