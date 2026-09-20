# NeoVerse: AI City Survival System 🏙️

A console-based C++ simulation of an AI-controlled smart city in the year 2035.

Built as part of my coursework at **Richfield Graduate Institute of Technology**.

---

## 📖 About This Project

So basically, this is a C++ program that pretends to be the operating system for a smart city run by AI. It's a training simulator for engineers who will eventually work on real smart cities.

The idea is simple:
- Citizens generate events all the time (accidents, power failures, etc.)
- Resources need to be managed
- Emergencies need to be handled in the right order
- Performance matters (Big-O is important!)

I built this using STL containers, algorithms, and OOP principles — which is basically everything we learned this year.

---

## ✨ Features

Here's what the system can do:

### 🔐 Engineer Login System
- Registered engineers need to log in before they can use the system
- Uses **binary search** for fast credential lookup (O(log n))
- Also has a linear search option for comparison (O(n))
- Stores engineer ID, username, password, and clearance level

### 📊 City Data Management
- **Sensor readings** stored in a `vector` (fast random access)
- **Historical logs** stored in a `list` (unlimited growth)
- Add, remove, and view data anytime
- Automatic stats: highest, lowest, and critical alerts

### ⚡ Real-Time Event Processing
- Normal events use a **queue** (FIFO — first in, first out)
- Emergencies use a **stack** (LIFO — last in, first out)
- 4 event types: Traffic Accident, Power Failure, Network Overload, Weather Alert
- Emergencies always get priority over normal events

### 🏗️ Object-Oriented Design
- Abstract `Event` base class with pure virtual `processEvent()`
- 4 derived classes demonstrating **polymorphism**
- Encapsulation everywhere (private data + getters/setters)
- Proper constructors and virtual destructors

### 🔧 STL Algorithms
- `sort()` — sorts sensor data by value
- `find_if()` — searches for specific readings/events
- `min_element()` / `max_element()` — finds extremes
- `count_if()` — counts critical alerts

### 📈 Reports & Analytics
- Total events processed
- Most common emergency type (uses `map` for counting)
- Average response time
- System load summary
- Full Big-O analysis breakdown

### 💾 File Persistence
- Saves state to `engineers.dat`, `events.dat`, `city_logs.dat`, `config.txt`
- Exports sensor data to CSV
- Exports logs to text file
- Can reload previous state on restart

---

## 🚀 How to Run

### Requirements
- A C++ compiler with C++11 support (g++, clang++, or MSVC)
- That's it — no external libraries needed

### Compile & Run

**On Linux / macOS:**
```bash
g++ -std=c++11 Main.cpp -o NeoVerse

./NeoVerse


This is coursework for Richfield Graduate Institute of Technology. Feel free to look at it for learning purposes, but don't submit it as your own work if you're doing the same assignment! 😅
