---
jupytext:
  formats: md:myst
  text_representation:
    extension: .md
    format_name: myst
kernelspec:
  display_name: Python 3
  language: python
  name: python3
---

# Solving the 1D Diffusion Equation using Finite Differences


In [Random Walks](random_walks_and_markov_processes.md) we looked at random walks, and we finished that lecture by showing how we can go from a discrete problem to a continuous partial differential equation called the Diffusion Equation.

$$\frac{\partial c}{\partial t} = D \frac{\partial^2 c}{\partial x^2}\nabla^2 c.$$

In this notebook, we will briefly look at how we can solve this equation numerically, and look at some solutions with different initial conditions and different boundary conditions. Most of the material here is presented as supplementary material, and is not considered part of IN1910's curriculum.


## Solving the Diffusion Equation using Finite Differences

A popular strategy for solving both ODEs and PDEs is discretizing them so that we only solve them at regular intervals, which we call *mesh points*. We can then approximate the derivatives with 'finite' differences, as opposed to the infinitesimal limit they actually represent.

Normally, this process is called *discretizing* the continuous differential equations. Somewhat ironic is it that this is the exact opposite process of what we did to find our PDE in the first place!

We denote the solution we are looking for by $c(x,t)$, because it can be seen as the *concentration* of some particles at a given location $x$ at time $t$. For example the concentration of oxygen in a room.

We discretize using a given step length $\Delta x$ in space, and a given time step $\Delta t$ in time, thus we will only solve for the concentration at points

$$c(x_i, t_j), \qquad x_i \equiv i\cdot \Delta x, \qquad t_j = j\cdot \Delta t,$$

where $i$ and $j$ are integers. To simplify writing, we define the shorthand

$$c_{i, j} \equiv c(x_i, t_j).$$

We can now start to approximate the derivatives. This can be done in many ways, but the most straight forward is using only the first terms of the Taylor series. This leads to the expression we found in L19

$$\frac{c_{i, j+1} - c_{i, j}}{\Delta t} = D\frac{c_{i+1, j} - 2 c_{i, j} + c_{i-1, j}}{\Delta x^2}.$$

Note however, that here we use a 1. order finite difference approximation in time, but a 2. order finite difference order in space. This means we should pick $\Delta t \leq \Delta x.$


### Approximating the spatial derivative

For the spatial derivative, we use a 2. order central difference approximation

$$\bigg(\frac{\partial^2 c}{\partial x^2}\bigg)_{i, j} \approx \frac{c_{i+1, j} - 2 c_{i, j} + c_{i-1, j}}{\Delta x^2}.$$

This is again found from truncating the Taylor series, but this time the error is $\mathcal{O}(\Delta x^2)$, meaning the solver will be a bit more forgiving to the second-order spatial step length, compared to the first-order time step. This means we should pick $\Delta t < \Delta x$.


### Finding our computational stencil

Our numerical expression is now

$$\frac{c_{i, j+1} - c_{i, j}}{\Delta t} = D\frac{c_{i+1, j} - 2 c_{i, j} + c_{i-1, j}}{\Delta x^2}.$$

We can massage this expression even further. By shuffling around some terms, we get

$$c_{i, j+1} = c_{i, j} + D\frac{\Delta t}{\Delta x^2}\big(c_{i+1, j} - 2 c_{i, j} + c_{i-1, j}\big).$$

Remember that $D$, $\Delta t$ and $\Delta x$ are all constants, and so we can also introduce a new constant to simplify further:

$$\alpha \equiv D\frac{\Delta t}{\Delta x^2},$$

which gives us the equation

$$c_{i, j+1} = c_{i, j} + \alpha\big(c_{i+1, j} - 2 c_{i, j} + c_{i-1, j}\big),$$

or

$$c_{i, j+1} = \alpha c_{i+1, j} - (1 - 2\alpha) c_{i, j} + \alpha c_{i-1, j}.$$

Such an equation is sometimes shown as a *computational stencil*

```{figure} ../../figures/computational_stencil.png
---
width: 500px
name: computational_stencil
alt: computational_stencil
---
```

Looking at the equation or the stencil, we see that we compute the concentration at the 'next' time step $t_{j+1}$, based on the values at the 'current' time step $t_j$, based on the three closest points in space $x_{i-1}$, $x_i$ and $x_{i+1}$.

### Explicit vs Implicit

Note that our computational stencil only involves a single 'next' time step, we call this an *explicit* scheme, as it explicitly states how to compute the new values. The opposite would be an implicit scheme, where for each time step the solver must solve a set of equations algebraically to find the new values. Simply put, explicit schemes are a lot easier to implement and solve. The downside is that explicit schemes can sometimes be unstable, and we need to be a bit more careful with our computational resolution and such with explicit schemes. Some implicit schemes, such as the *backward* Euler scheme, are much more stable, and can handle a wider variety of parameters and resolutions.

### Handling the boundaries

Looking at the stencil, we notice there will be an issue at the boundaries of the domain. To calculate the point at the edge of the boundary, $u_{0, j+1}$, we need to know $u_{-1, j+1}$, which doesn't exist! To get around this problem, we need to specify boundary conditions.

The simplest boundary conditions are the *Dirichlet* conditions, also known as a concentration clamp. This simply forces the solution to have certain values at the boundary, and thus, we don't need to actually compute them, we can just set them to their clamped values: $u(0, t) = u_0$ and $u(L, t) = u_L$.

The other common form of boundary conditions are the *Neumann* conditions. With these, it is the flux over the boundary that is clamped, and not the concentration itself. Most commonly, the flux is set to 0, meaning no concentration can every cross the boundary. This specific condition is often referred to as a 'no-flow' or 'reflective' boundary. To implement this condition, we pretend that that the points immediately outside the boundary, such as $u_{-1, j}$ exists, and set these imaginary 'ghost points' equal to the value at the boundary. As a diffusion flux is driven by a concentration difference, by setting $u_{-1,j} = u_{0,j}$, the math itself will make sure no flux occurs across the boundary.



## Implementing the Solver

Now that we have gone through the mathematical basis, we are ready to implement everything. We start by importing everything we need.

```{code-cell} python
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import animation, rc
from IPython.display import HTML

%matplotlib inline
```

### A note on stability

Here we have chosen to use a forward Euler scheme because it is easy to describe briefly. It is also very easy to implement, thanks to it being an explicit scheme. However, it does have quite a larger error, but more important is that it is *unstable*, meaning it will produce a completely wrong answer to the equation for certain parameters. Mathematical analysis shows that the *stability* criterion for this scheme is:

$$\alpha \leq 0.5 \qquad \Leftrightarrow \qquad \Delta t ≤ \frac{\Delta x^2}{2D}.$$

Because of this, we will use $D=5$, $\Delta x = 0.5$ and $\Delta t = 0.02$ for all our simulations, giving $\alpha = 0.4$, ensuring stability.

```{code-cell} python tags=[]
D = 5
dx = 0.5
dt = 0.020
alpha = D*dt/dx/dx

# Double check stability
if alpha > 0.5:
    raise ValueError('The scheme is not stable with the chosen parameters.')
else:
    print(alpha)
```

We now implement a function we can call to update our solution by one time step. We cannot solve for the boundaries, as it is system-specific how we handle those, so the function we implement will only update the internal points.

```{code-cell} python
def step(u):
    """A function that iterates the solution one step in time.
    Note: This function does not enforce any boundary conditions."""
    up[:] = u[:]
    u[1:-1] = alpha*up[2:] + (1-2*alpha)*up[1:-1] + alpha*up[:-2]
```

With the `step` function defined, we are ready to solve specific systems.


## System 1: An initial concentration spike

The first system we will look at is what happens to an initial spike of concentration in the middle of a domain. First we will let the domain have open boundaries, so that the concentration can escape from the box, and then we change to reflective boundaries, so that nothing can escape from the box.

```{code-cell} python
# Define the spatial mesh
L = 10
x = np.arange(0, L+dx, dx)
n = len(x)

# Set up arrays to hold the solution at the current and previous time steps
u = np.empty(n)
up = np.empty(n)
```

### Open boundaries

First we will let the domain have open boundaries, so that the concentration can escape from the box


```{code-cell} python
%%capture

# Set up initial condition
u[:] = 0
u[n//2-1:n//2+1] = 4

fig, ax = plt.subplots();
ax.set_xlim((0, L));
ax.set_ylim((0, 2));
line, = ax.plot(x, u, linewidth=2);

def animate(i):
    # Calculate solution for next time step
    step(u)
    u[0] = 0
    u[-1] = 0

    # Update plot
    line.set_ydata(u)
    return (line,)

anim = animation.FuncAnimation(fig, animate, repeat=False,
                               frames=400, interval=20);
```

```{code-cell} python
HTML(anim.to_html5_video())
```

### Reflective boundaries

We now change to no-flow boundaries, so that nothing can escape from the box.

```{code-cell} python
%%capture

# Set up initial condition
u[:] = 0
u[n//2-1:n//2+1] = 4

# Set up plot
fig, ax = plt.subplots();
ax.set_xlim((0, L));
ax.set_ylim((0, 2));
line, = ax.plot(x, u, linewidth=2);

def animate(i):
    # Calculate solution for next time step
    step(u)
    u[0] = (1 - alpha)*up[0] + alpha*up[1]
    u[-1] = (1 - alpha)*up[-1] + alpha*up[-2]

    # Update plot
    line.set_ydata(u)
    return (line,)

anim = animation.FuncAnimation(fig, animate, repeat=False,
                               frames=400, interval=20);
```

```{code-cell} python
HTML(anim.to_html5_video())
```

## System 2 - Transport across the synaptic cleft

For our second system, we will look at the diffusive transport of neurotransmitters across a synapse. When a signal is to be sent from one neuron to another, an action potential in the pre-synaptic membrane causes the release of neurotransmitter molecules into the synaptic cleft between the cells.

To model this system, we assume the concentration to be zero initially. At time $t=0$ the pre-synaptic side, which we place on the left, starts releasing neurotransmitters. For simplicity sake, we implement this as a concentration clamp $u(0, t) = C$, which can be thought of as the release of neurotransmitters as being some sort of equilibrium process. At the other side of the synapse, the neurotransmitters will be absorbed. Let us assume, again for simplicity, that this absorption occurs so rapidly that we can assume there is never any unabsorbed neurotransmitters at this point. This means we can use another concentration clamp of $u(L, t)=0$.

```{code-cell} python
%%capture

# Pre-synaptic concentration
C = 5

# Set up initial condition
u[:] = 0

fig, ax = plt.subplots();
ax.set_xlim((0, L));
ax.set_ylim((0, C));
line, = ax.plot(x, u, linewidth=2);

def animate(i):
    # Calculate solution for next time step
    step(u)
    u[0] = C
    u[-1] = 0

    # Update plot
    line.set_ydata(u)
    return (line,)

anim = animation.FuncAnimation(fig, animate, repeat=False,
                               frames=300, interval=20);
```

```{code-cell} python
HTML(anim.to_html5_video())
```

### Steady State Solution

We see that eventually, the solution hits a pseudo steady-state, where the solution is no longer changing. This is because the solution has become a linear solution, $c=Ax + b$ which means that
$$\frac{\partial c}{\partial x} = A, \qquad \frac{\partial^2 c}{\partial x^2} = 0 \quad \Rightarrow \quad \frac{\partial c}{\partial t} = 0.$$

We call such a situation a *pseudo* steady state, because it looks like nothing is changing, but there is a constant flux of neurotransmitter molecules through the cleft.

We could have found this steady state solution analytical the diffusion equation, using the fact that it is unchanging in time

$$\frac{\partial c}{\partial t} = 0 = D\frac{\partial^2 c}{\partial x^2},$$
giving
$$\frac{\partial^2 c}{\partial x^2} = 0 \Rightarrow c = Ax + B.$$

Adding in the boundary conditions of $c(0) = C$ and $c(L) = 0$ gives
$$c(x, \infty) = C\bigg(1 - \frac{x}{L}\bigg).$$

Interestingly enough, the steady state solution doesn't depend on the diffusion coefficient, $D$, at all! The diffusion coefficient decides how fast the system reaches the steady state however. And will enter into the net transport of neurotransmitters through Ficks law: $J = -D \nabla c = CD/L$.


### Shutting of the source

Let us now assume that the system has had enough time to reach steady state. Eventually the release event will stop, which we model by changing the concentration clamp on the left to a no-flow boundary instead. We assume the right hand side keeps absorbing molecules.

```{code-cell} python
%%capture

# Set up initial condition
u[:] = C*(1-x/L)

fig, ax = plt.subplots();
ax.set_xlim((0, L));
ax.set_ylim((0, C));
line, = ax.plot(x, u, linewidth=2);

def animate(i):
    # Calculate solution for next time step
    step(u)
    u[0] = (1-alpha)*up[0] + alpha*up[1]
    u[-1] = 0

    # Update plot
    line.set_ydata(u)
    return (line,)

anim = animation.FuncAnimation(fig, animate, repeat=False,
                               frames=600, interval=20);
```

```{code-cell} python
HTML(anim.to_html5_video())
```
