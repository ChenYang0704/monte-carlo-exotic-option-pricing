# Validation, Testing and Numerical Studies
## Overview

The library includes a collection of validation programs and numerical studies to verify pricing accuracy, implementation correctness and statistical behaviour.

Validation is performed using a combination of:

* Analytical benchmarks
* Pricing identities
* Deterministic test cases
* Statistical consistency checks
* Numerical studies

Implementation validation is primarily contained in the `tests/` directory, while numerical behaviour studies are provided in the `examples/` directory.

---

## European Option Validation

European options provide the primary benchmark for the Monte Carlo engine because analytical Black-Scholes prices are available.

The tests cover representative moneyness regimes:

* At-the-money (ATM)
* Deep in-the-money (deep ITM)
* Deep out-of-the-money (deep OTM)

The validation process compares:

* Monte Carlo price
* Analytical Black-Scholes price
* Absolute error
* Standard error
* 95% confidence interval

A correctly implemented Monte Carlo engine should produce analytical prices that lie within the reported confidence interval for sufficiently large simulation counts.

---

## Binary Option Validation

Binary options are validated against analytical Black-Scholes cash-or-nothing formulas.

The tests cover representative moneyness regimes:

* At-the-money (ATM)
* Deep in-the-money (deep ITM)
* Deep out-of-the-money (deep OTM)

The validation process compares:

* Monte Carlo price
* Analytical price
* Absolute error
* Standard error
* 95% confidence interval

Binary options provide a useful benchmark because their discontinuous payoff structure is generally more challenging to simulate accurately than smooth European payoffs.

---

## Asian Option Validation

No analytical benchmark is currently implemented for Asian options.

Validation is therefore performed using consistency checks and timestep sensitivity checks.

The Asian option tests include:

* Fixed-strike Asian versus European
* Floating-strike Asian non-negativity
* Timestep sensitivity between coarse and fine monitoring grids

For the fixed-strike comparison, the test checks:

$$
V_{\text{Fixed Asian Call}}
\leq
V_{\text{European Call}}
$$

$$
V_{\text{Fixed Asian Put}}
\leq
V_{\text{European Put}}
$$


For floating-strike Asian options, the test checks:

$$
V_{\text{Floating Asian Call}}
\geq 0
$$

$$
V_{\text{Floating Asian Put}}
\geq 0
$$

The timestep sensitivity check compares a fixed-strike Asian call using 4 timesteps and 256 timesteps.

---

## Barrier Option Validation

No analytical benchmark is currently implemented for barrier options.

Validation is therefore performed using parity checks and timestep sensitivity checks.

The barrier option tests include:

* Up barrier call parity
* Down barrier call parity
* Up barrier put parity
* Down barrier put parity
* Timestep sensitivity between coarse and fine monitoring grids

For the parity checks, the tests verify:

$$
V_{\text{Knock-In Call}}
+
V_{\text{Knock-Out Call}}
=
V_{\text{European Call}}
$$

$$
V_{\text{Knock-In Put}}
+
V_{\text{Knock-Out Put}}
=
V_{\text{European Put}}
$$

for both up and down barriers.

The timestep sensitivity check compares an up-and-out call using 4 timesteps and 256 timesteps.

For an up-and-out call, finer monitoring detects more barrier breaches and should therefore not increase the option value. The test checks:

$$
V_{\text{fine}}
\leq
V_{\text{coarse}}
$$

---

## Lookback Option Validation

No analytical benchmark is currently implemented for lookback options.

Validation is therefore performed using consistency checks and timestep sensitivity checks.

The lookback option tests include:

* Fixed-strike lookback versus European
* Floating-strike lookback non-negativity
* Fixed-strike lookback volatility monotonicity
* Timestep sensitivity between coarse and fine monitoring grids

For the fixed-strike comparison, the tests check:

$$
V_{\text{Fixed Lookback Call}}
\geq
V_{\text{European Call}}
$$

$$
V_{\text{Fixed Lookback Put}}
\geq
V_{\text{European Put}}
$$

For floating-strike lookback options, the tests check:

$$
V_{\text{Floating Lookback Call}}
\geq 0
$$

$$
V_{\text{Floating Lookback Put}}
\geq 0
$$

For volatility monotonicity, the test checks that the fixed-strike lookback call price increases as volatility increases.

For the timestep sensitivity check, the test compares a fixed-strike lookback call using 4 timesteps and 256 timesteps.

Since finer monitoring captures more path extrema, the test checks:

$$
V_{\text{fine}}
\geq
V_{\text{coarse}}
$$

---

## Monte Carlo Engine Validation

The Monte Carlo engine is validated using reproducibility, convergence and deterministic test cases.

The engine tests include:

* Random number reproducibility
* Simulation convergence sanity check
* Zero-volatility deterministic test

For reproducibility, simulations using identical parameters and random seeds should produce identical results.

For simulation convergence, increasing the number of simulation paths should reduce the standard error.

$$
SE \propto \frac{1}{\sqrt{M}}
$$

where $M$ is the number of simulation paths.

For the zero-volatility test,

$$
\sigma = 0
$$

the asset path becomes deterministic and the Monte Carlo price should match the deterministic discounted payoff.

---

## Numerical Studies

The `examples/` directory contains numerical behaviour studies.

### Simulation Convergence

`ExampleSimulationConvergence.cpp` studies how the Monte Carlo price, absolute error, standard error and confidence interval change as the number of simulations increases.

Typical simulation counts include:

* 1,000
* 10,000
* 100,000
* 1,000,000

The expected convergence behaviour is:

$$
SE \propto \frac{1}{\sqrt{M}}
$$

where $M$ is the number of simulation paths.

### Timestep Sensitivity

`ExampleTimestepSensitivity.cpp` studies timestep sensitivity for:

* Asian options
* Barrier options
* Lookback options

This example demonstrates that path-dependent products can be sensitive to the timestep grid because monitoring occurs only at simulated path points.

Barrier and lookback options generally show stronger timestep sensitivity because their payoffs depend directly on barrier crossings or path extrema.

---

## Current Coverage

| Component | Validation Method |
|----------|----------|
| European Option | Analytical Black-Scholes benchmark |
| Binary Option | Analytical Black-Scholes benchmark |
| Asian Option | Fixed-strike comparison, floating-strike non-negativity and timestep sensitivity |
| Barrier Option | Knock-in / knock-out parity and timestep sensitivity |
| Lookback Option | Fixed-strike comparison, floating-strike non-negativity, volatility monotonicity and timestep sensitivity |
| Monte Carlo Engine | Reproducibility, simulation convergence and zero-volatility deterministic tests |
| Numerical Studies | Simulation convergence and timestep sensitivity |

The current validation framework combines analytical benchmarks, pricing identities, consistency checks, deterministic tests and numerical studies to provide confidence in both implementation correctness and numerical behaviour under the Black-Scholes framework.

---