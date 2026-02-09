<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **AI - NOTES** 🔥🐦‍🔥

⚡ BY - THE AANSHIK-DEV

<br>

## 🐦‍🔥 INTELLIGENT AGENT

### 🔥 What is an agent ?

| Agent            | Sensors           | Actuators        |
| ---------------- | ----------------- | ---------------- |
| Human            | Eyes, ears        | Hands, legs      |
| Robot            | Camera, IR sensor | Motors           |
| Chess AI         | Board state       | Move pieces      |
| Self-driving car | Lidar, camera     | Steering, brakes |

### 🔥 Agent Function and Agent Program

<br>

## 🐦‍🔥 RATIONAL AGENT

An agent is rational if it:

- Chooses an action that maximizes expected performance
- Given:
  - percept history
  - knowledge of environment
  - available actions

<br>

## 🐦‍🔥 Types of Environment

### 🔥 Fully Observable vs Partially Observable

- Fully observable: agent sees entire state
  👉 Chess

- Partially observable: limited info
  👉 Driving in fog

### 🔥 Deterministic vs Stochastic

- Deterministic: next state fully determined
  👉 Chess
- Stochastic: randomness involved
  👉 Poker, real-world driving

### 🔥 Episodic vs Sequential

- Episodic: each action independent
  👉 Image classification
- Sequential: actions affect future
  👉 Chess, navigation

### 🔥 Static vs Dynamic

- Static: environment doesn’t change
  👉 Crossword puzzle
- Dynamic: changes while agent thinks
  👉 Traffic system

### 🔥 Discrete vs Continuous

- Discrete: finite actions/states
  👉 Board games
- Continuous: infinite states
  👉 Robot motion

### 🔥 Single-agent vs Multi-agent

- Single-agent: puzzle solving
- Multi-agent: chess, markets

<br>

## 🐦‍🔥 Types of Agents (CORE MODELS)

### 🔥 Simple Reflex Agent

- Acts only on current percept
- Uses condition–action rules
  ❌ No memory
  ❌ Fails in partially observable environments

### 🔥 Model-Based Reflex Agent

- Maintains internal state
- Tracks world changes
  ✅ Handles partial observability

### 🔥 Goal-Based Agent

- Has a goal
- Uses search & planning
  👉 Example: GPS navigation

### 🔥 Utility-Based Agent

- Uses utility function
- Chooses action with max utility
  👉 Handles trade-offs (speed vs safety)

### 🔥 Learning Agent

Improves with experience
Components:

- Performance element
- Learning element
- Critic
- Problem generator
