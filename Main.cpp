// NeoVerse AI City Survival System
// Console-Based C++ Game Engine

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <map>

using namespace std;

// enums and stuff
enum ClearanceLevel { LOW, MEDIUM, HIGH };

// the event types
enum EventType { TRAFFIC_ACCIDENT, POWER_FAILURE, NETWORK_OVERLOAD, WEATHER_ALERT };



// SECTION 1: ENGINEER CLASS
// for login system

class Engineer {
private:
    string engineerID;
    string username;
    string encryptedPassword;
    ClearanceLevel clearance;

public:
    Engineer() {
        engineerID = "";
        username = "";
        encryptedPassword = "";
        clearance = LOW;
    }
    
    Engineer(string id, string user, string pass, ClearanceLevel level) {
        engineerID = id;
        username = user;
        encryptedPassword = pass;
        clearance = level;
    }
    
    // getters
    string getEngineerID() { return engineerID; }
    string getUsername() { return username; }
    string getPassword() { return encryptedPassword; }
    ClearanceLevel getClearance() { return clearance; }
    
    // setters
    void setEngineerID(string id) { engineerID = id; }
    void setUsername(string user) { username = user; }
    void setPassword(string pass) { encryptedPassword = pass; }
    void setClearance(ClearanceLevel level) { clearance = level; }
    
    void display() {
        cout << "ID: " << engineerID;
        cout << " | Username: " << username;
        cout << " | Clearance: ";
        
        if (clearance == LOW) {
            cout << "Low";
        } else if (clearance == MEDIUM) {
            cout << "Medium";
        } else {
            cout << "High";
        }
        cout << endl;
    }
};



// SECTION 2: AUTHENTICATION
// login stuff

class AuthSystem {
private:
    vector<Engineer> engineers;
    
public:
    AuthSystem() {
        // adding engineers to test with
        engineers.push_back(Engineer("ENG001", "admin", "admin123", HIGH));
        engineers.push_back(Engineer("ENG002", "jane_doe", "jane456", MEDIUM));
        engineers.push_back(Engineer("ENG003", "john_smith", "john789", LOW));
        engineers.push_back(Engineer("ENG004", "alice_wong", "alice321", MEDIUM));
    }
    
    // linear search - O(n)
    bool loginLinear(string username, string password) {
        cout << "\n[INFO] Using Linear Search - O(n)" << endl;
        
        for (int i = 0; i < engineers.size(); i++) {
            if (engineers[i].getUsername() == username) {
                if (engineers[i].getPassword() == password) {
                    cout << "Login successful! Welcome " << username << "!" << endl;
                    return true;
                }
                else {
                    cout << "Login failed! Wrong password." << endl;
                    return false;
                }
            }
        }
        cout << "Login failed! Username not found." << endl;
        return false;
    }
    
    // binary search - O(log n)
    // had to look this up on stackoverflow ngl
    bool loginBinary(string username, string password) {
        cout << "\n[INFO] Using Binary Search - O(log n)" << endl;
        
        vector<Engineer> sortedEngineers = engineers;
        
        sort(sortedEngineers.begin(), sortedEngineers.end(),
             [](Engineer a, Engineer b) {
                 return a.getUsername() < b.getUsername();
             });
        
        int left = 0;
        int right = sortedEngineers.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (sortedEngineers[mid].getUsername() == username) {
                if (sortedEngineers[mid].getPassword() == password) {
                    cout << "Login successful! Welcome " << username << "!" << endl;
                    return true;
                } else {
                    cout << "Login failed! Wrong password." << endl;
                    return false;
                }
            }
            
            if (sortedEngineers[mid].getUsername() < username) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        cout << "Login failed! Username not found." << endl;
        return false;
    }
    
    // NEW: using std::find_if here because assignment said use <algorithm>
    // for searching. i found out find_if takes a lambda so i used that
    bool loginWithFindAlgorithm(string username, string password) {
        cout << "\n[INFO] Using std::find_if from <algorithm> - O(n)" << endl;
        
        auto it = find_if(engineers.begin(), engineers.end(),
            [&username](Engineer e) {
                return e.getUsername() == username;
            });
        
        if (it != engineers.end()) {
            if (it->getPassword() == password) {
                cout << "Login successful! Welcome " << username << "!" << endl;
                return true;
            }
            cout << "Login failed! Wrong password." << endl;
            return false;
        }
        
        cout << "Login failed! Username not found." << endl;
        return false;
    }
    
    void displayAllEngineers() {
        cout << "\n=== REGISTERED ENGINEERS ===" << endl;
        cout << "----------------------------" << endl;
        
        for (int i = 0; i < engineers.size(); i++) {
            cout << (i + 1) << ". ";
            engineers[i].display();
        }
        
        cout << "----------------------------" << endl;
        cout << "Total: " << engineers.size() << " engineers" << endl;
    }
    
    // big O analysis for the assignment
    void printComplexityAnalysis() {
        cout << "\n=== BIG-O COMPLEXITY ANALYSIS ===" << endl;
        cout << "Linear Search: O(n) - checks everything" << endl;
        cout << "Binary Search: O(log n) - faster but needs sorted data" << endl;
        cout << "For our 4 engineers both work fine but binary is better for large data" << endl;
    }
    
    // this is so we can save engineers to file properly
    vector<Engineer> getAllEngineers() {
        return engineers;
    }
};


// sensor reading struct
struct SensorReading {
    string type;
    double value;
    time_t timestamp;
    
    SensorReading() {
        type = "";
        value = 0;
        timestamp = 0;
    }
    
    SensorReading(string t, double v) {
        type = t;
        value = v;
        timestamp = time(nullptr);
    }
    
    void display() {
        cout << "[" << type << "] Value: " << value;
        cout << " | Time: " << ctime(&timestamp);
    }
};

// city log struct
struct CityLog {
    string message;
    time_t timestamp;
    
    CityLog() {
        message = "";
        timestamp = 0;
    }
    
    CityLog(string msg) {
        message = msg;
        timestamp = time(nullptr);
    }
    
    void display() {
        cout << "[" << ctime(&timestamp) << "] " << message << endl;
    }
};



// SECTION 3: CITY DATA
// manages sensor data (vector) and logs (list)

class CityData {
private:
    vector<SensorReading> sensorData;
    list<CityLog> historicalLogs;
    
public:
    // The Vectors
    
    void addSensorReading(SensorReading reading) {
        sensorData.push_back(reading);
        cout << "Sensor reading added!" << endl;
    }
    
    void removeSensorReading(int index) {
        if (index >= 0 && index < sensorData.size()) {
            sensorData.erase(sensorData.begin() + index);
            cout << "Removed sensor reading at index " << index << endl;
        } else {
            cout << "Error: Invalid index!" << endl;
        }
    }
    
    void displayAllSensorData() {
        cout << "\n=== SENSOR READINGS ===" << endl;
        cout << "-----------------------" << endl;
        
        if (sensorData.empty()) {
            cout << "No sensor data available." << endl;
            return;
        }
        
        for (int i = 0; i < sensorData.size(); i++) {
            cout << i << ". ";
            sensorData[i].display();
        }
        
        cout << "-----------------------" << endl;
        cout << "Total: " << sensorData.size() << " readings" << endl;
    }
    
    SensorReading getSensorReading(int index) {
        return sensorData[index];
    }
    
    // The Lists 
    void addLog(CityLog log) {
        historicalLogs.push_back(log);
    }
    
    void removeOldestLog() {
        if (!historicalLogs.empty()) {
            historicalLogs.pop_front();
            cout << "Removed oldest log." << endl;
        }
        else {
            cout << "No logs to remove." << endl;
        }
    }
    
    void displayAllLogs() {
        cout << "\n=== HISTORICAL LOGS ===" << endl;
        cout << "-----------------------" << endl;
        
        if (historicalLogs.empty()) {
            cout << "No logs available." << endl;
            return;
        }
        
        // using iterator here because list needs them
        list<CityLog>::iterator it;
        for (it = historicalLogs.begin(); it != historicalLogs.end(); it++) {
            it->display();
        }
        
        cout << "-----------------------" << endl;
        cout << "Total: " << historicalLogs.size() << " logs" << endl;
    }
    
    // STL ALGORITHMS 
    void sortSensorData() {
        sort(sensorData.begin(), sensorData.end(),
             [](SensorReading a, SensorReading b) {
                 return a.value > b.value;
             });
        cout << "Sensor data sorted (highest to lowest)." << endl;
    }
    
    // using std::find to search for a reading by type
    void findSensorByType(string type) {
        cout << "\n[INFO] Using std::find - O(n)" << endl;
        cout << "Searching for first reading of type: " << type << endl;
        
        auto it = find_if(sensorData.begin(), sensorData.end(),
            [&type](SensorReading r) {
                return r.type == type;
            });
        
        if (it != sensorData.end()) {
            cout << "Found reading:" << endl;
            it->display();
        }
        else {
            cout << "No reading of type '" << type << "' found." << endl;
        }
    }
    
    double findHighestValue() {
        if (sensorData.empty()) return 0;
        
        auto it = max_element(sensorData.begin(), sensorData.end(),
            [](SensorReading a, SensorReading b) {
                return a.value < b.value;
            });
        return it->value;
    }
    
    double findLowestValue() {
        if (sensorData.empty()) return 0;
        
        auto it = min_element(sensorData.begin(), sensorData.end(),
            [](SensorReading a, SensorReading b) {
                return a.value < b.value;
            });
        return it->value;
    }
    
    int countCriticalAlerts() {
        int count = count_if(sensorData.begin(), sensorData.end(),
            [](SensorReading r) {
                return r.value > 80.0;
            });
        return count;
    }
    
    vector<SensorReading> searchByType(string type) {
        vector<SensorReading> result;
        
        for (int i = 0; i < sensorData.size(); i++) {
            if (sensorData[i].type == type) {
                result.push_back(sensorData[i]);
            }
        }
        return result;
    }
    
    void generateDataSummary() {
        cout << "\n=== DATA SUMMARY ===" << endl;
        cout << "Sensor readings (vector): " << sensorData.size() << endl;
        cout << "Historical logs (list): " << historicalLogs.size() << endl;
        
        if (!sensorData.empty()) {
            cout << "\nStats:" << endl;
            cout << "  Highest: " << findHighestValue() << endl;
            cout << "  Lowest: " << findLowestValue() << endl;
            cout << "  Critical alerts (>80): " << countCriticalAlerts() << endl;
        }
    }
    
    int getSensorCount() { return sensorData.size(); }
    int getLogCount() { return historicalLogs.size(); }
    vector<SensorReading> getAllSensorData() { return sensorData; }
    
    // NEW - need this so we can save logs to file
    list<CityLog> getAllLogs() { return historicalLogs; }
};



// SECTION 4: EVENT BASE CLASS

class Event {
protected:
    EventType type;
    string description;
    time_t timestamp;
    int priority;
    
public:
    Event() {
        type = TRAFFIC_ACCIDENT;
        description = "";
        priority = 1;
        timestamp = time(nullptr);
    }
    
    Event(EventType t, string desc, int prio) {
        type = t;
        description = desc;
        priority = prio;
        timestamp = time(nullptr);
    }
    
    // virtual destructor
    virtual ~Event() {}
    
    // pure virtual - makes this abstract
    virtual void processEvent() = 0;
    
    virtual void display() {
        cout << "Event: " << getTypeString();
        cout << " | " << description;
        cout << " | Priority: " << priority << endl;
    }
    
    string getTypeString() {
        if (type == TRAFFIC_ACCIDENT) return "Traffic Accident";
        else if (type == POWER_FAILURE) return "Power Failure";
        else if (type == NETWORK_OVERLOAD) return "Network Overload";
        else return "Weather Alert";
    }
    
    EventType getType() { return type; }
    int getPriority() { return priority; }
    string getDescription() { return description; }
    time_t getTimestamp() { return timestamp; }
};

// derived event classes - inheritance + polymorphism
class TrafficAccident : public Event {
public:
    TrafficAccident(string desc) : Event(TRAFFIC_ACCIDENT, desc, 8) {}
    
    void processEvent() {
        cout << "========================================" << endl;
        cout << "PROCESSING TRAFFIC ACCIDENT" << endl;
        cout << "========================================" << endl;
        cout << "1. Alerting emergency services..." << endl;
        cout << "2. Routing police to the scene..." << endl;
        cout << "3. Recalculating traffic routes..." << endl;
        cout << "4. Notifying nearby hospitals..." << endl;
        cout << "Est time: 15 minutes" << endl;
        cout << "========================================" << endl;
    }
};

class PowerFailure : public Event {
public:
    PowerFailure(string desc) : Event(POWER_FAILURE, desc, 10) {}
    
    void processEvent() {
        cout << "========================================" << endl;
        cout << "PROCESSING POWER FAILURE" << endl;
        cout << "========================================" << endl;
        cout << "1. Activating backup generators..." << endl;
        cout << "2. Switching to emergency power grid..." << endl;
        cout << "3. Notifying maintenance crew..." << endl;
        cout << "4. Alerting hospitals and critical services..." << endl;
        cout << "Est time: 30 minutes" << endl;
        cout << "========================================" << endl;
    }
};

class NetworkOverload : public Event {
public:
    NetworkOverload(string desc) : Event(NETWORK_OVERLOAD, desc, 6) {}
    
    void processEvent() {
        cout << "========================================" << endl;
        cout << "PROCESSING NETWORK OVERLOAD" << endl;
        cout << "========================================" << endl;
        cout << "1. Throttling non-essential traffic..." << endl;
        cout << "2. Redirecting bandwidth..." << endl;
        cout << "3. Scaling up servers..." << endl;
        cout << "4. Monitoring for further issues..." << endl;
        cout << "Est time: 5 minutes" << endl;
        cout << "========================================" << endl;
    }
};

class WeatherAlert : public Event {
public:
    WeatherAlert(string desc) : Event(WEATHER_ALERT, desc, 7) {}
    
    void processEvent() {
        cout << "========================================" << endl;
        cout << "PROCESSING WEATHER ALERT" << endl;
        cout << "========================================" << endl;
        cout << "1. Issuing public warnings..." << endl;
        cout << "2. Updating emergency protocols..." << endl;
        cout << "3. Alerting citizens via SMS..." << endl;
        cout << "4. Preparing emergency shelters..." << endl;
        cout << "Est time: 10 minutes" << endl;
        cout << "========================================" << endl;
    }
};



// Emergency Event - for the stack

class EmergencyEvent {
private:
    string emergencyID;
    string description;
    time_t timestamp;
    int severity;
    string emergencyType;  
    
public:
    EmergencyEvent() {
        emergencyID = "";
        description = "";
        severity = 1;
        timestamp = time(nullptr);
        emergencyType = "Unknown";
    }
    
    EmergencyEvent(string id, string desc, int sev, string type = "General") {
        emergencyID = id;
        description = desc;
        severity = sev;
        timestamp = time(nullptr);
        emergencyType = type;
    }
    
    void process() {
        cout << "========================================" << endl;
        cout << "EMERGENCY OVERRIDE ACTIVATED!" << endl;
        cout << "========================================" << endl;
        cout << "ID: " << emergencyID << endl;
        cout << "Description: " << description << endl;
        cout << "Severity: " << severity << "/10" << endl;
        cout << "Action: Immediate response required!" << endl;
        cout << "========================================" << endl;
    }
    
    void display() {
        cout << "[EMERGENCY] ID: " << emergencyID;
        cout << " | " << description;
        cout << " | Severity: " << severity << "/10" << endl;
    }
    
    string getDescription() { return description; }
    int getSeverity() { return severity; }
    string getEmergencyType() { return emergencyType; }
    time_t getTimestamp() { return timestamp; }
};



// SECTION 5: EVENT SYSTEM
// queue for normal events, stack for emergencies

class EventSystem {
private:
    queue<Event*> eventQueue;
    stack<EmergencyEvent> emergencyStack;
    vector<Event*> processedEvents;
    vector<EmergencyEvent> processedEmergencies;
    int totalEventsProcessed;
    
    // track response times for the report
    vector<double> responseTimes;
    
public:
    EventSystem() {
        totalEventsProcessed = 0;
    }
    
    ~EventSystem() {
        while (!eventQueue.empty()) {
            delete eventQueue.front();
            eventQueue.pop();
        }
        for (int i = 0; i < processedEvents.size(); i++) {
            delete processedEvents[i];
        }
    }
    
    // add event to queue (FIFO)
    void addEvent(Event* event) {
        eventQueue.push(event);
        cout << "Event added to queue: " << event->getDescription() << endl;
        cout << "Queue size: " << eventQueue.size() << endl;
    }
    
    // add emergency to stack (LIFO)
    void addEmergency(EmergencyEvent emergency) {
        emergencyStack.push(emergency);
        cout << "Emergency added to stack!" << endl;
        cout << "Stack size: " << emergencyStack.size() << endl;
    }
    
    // process next event (FIFO)
    void processNextEvent() {
        if (eventQueue.empty()) {
            cout << "No events in queue." << endl;
            return;
        }
        
        Event* event = eventQueue.front();
        eventQueue.pop();
        
        // track time for response time report
        time_t startTime = time(nullptr);
        
        cout << "\n--- PROCESSING NEXT EVENT (FIFO) ---" << endl;
        event->processEvent();
        
        // calculate response time
        time_t endTime = time(nullptr);
        double responseTime = difftime(endTime, startTime) + (rand() % 30 + 5);  // sim response time
        responseTimes.push_back(responseTime);
        
        processedEvents.push_back(event);
        totalEventsProcessed++;
        
        cout << "--- DONE ---\n" << endl;
    }
    
    // process top emergency (LIFO)
    void processTopEmergency() {
        if (emergencyStack.empty()) {
            cout << "No emergencies in stack." << endl;
            return;
        }
        
        EmergencyEvent emergency = emergencyStack.top();
        emergencyStack.pop();
        
        time_t startTime = time(nullptr);
        
        cout << "\n--- PROCESSING EMERGENCY (LIFO) ---" << endl;
        emergency.process();
        
        time_t endTime = time(nullptr);
        double responseTime = difftime(endTime, startTime) + (rand() % 20 + 10);
        responseTimes.push_back(responseTime);
        
        processedEmergencies.push_back(emergency);
        cout << "--- DONE ---\n" << endl;
    }
    
    void processAllEvents() {
        cout << "\n=== PROCESSING ALL EVENTS (FIFO) ===" << endl;
        while (!eventQueue.empty()) {
            processNextEvent();
        }
        cout << "All events processed!" << endl;
    }
    
    void processAllEmergencies() {
        cout << "\n=== PROCESSING ALL EMERGENCIES (LIFO) ===" << endl;
        while (!emergencyStack.empty()) {
            processTopEmergency();
        }
        cout << "All emergencies resolved!" << endl;
    }
    
    // NEW - search for specific event by type
    void searchEventByType(int typeChoice) {
        cout << "\n[INFO] Searching events by type (using iterator)..." << endl;
        
        string searchType;
        if (typeChoice == 1) searchType = "Traffic Accident";
        else if (typeChoice == 2) searchType = "Power Failure";
        else if (typeChoice == 3) searchType = "Network Overload";
        else searchType = "Weather Alert";
        
        cout << "Looking for: " << searchType << endl;
        
        // copy queue since we can't iterate through it directly
        queue<Event*> tempQueue = eventQueue;
        bool found = false;
        int position = 0;
        
        while (!tempQueue.empty()) {
            Event* e = tempQueue.front();
            if (e->getTypeString() == searchType) {
                cout << "Found at position " << position << ": ";
                e->display();
                found = true;
            }
            tempQueue.pop();
            position++;
        }
        
        // check processed events using iterator
        cout << "\nChecking processed events history..." << endl;
        vector<Event*>::iterator it;
        for (it = processedEvents.begin(); it != processedEvents.end(); it++) {
            if ((*it)->getTypeString() == searchType) {
                cout << "Was processed: ";
                (*it)->display();
                found = true;
            }
        }
        
        if (!found) {
            cout << "No events of type '" << searchType << "' found." << endl;
        }
    }
    
    void displayStatus() {
        cout << "\n=== EVENT SYSTEM STATUS ===" << endl;
        cout << "Events in queue: " << eventQueue.size() << endl;
        cout << "Emergencies in stack: " << emergencyStack.size() << endl;
        cout << "Processed events: " << processedEvents.size() << endl;
        cout << "Processed emergencies: " << processedEmergencies.size() << endl;
        cout << "Total processed: " << totalEventsProcessed << endl;
        
        cout << "\nWhy Queue vs Stack?" << endl;
        cout << "Queue (FIFO) - for normal events, fair processing" << endl;
        cout << "Stack (LIFO) - for emergencies, most recent first" << endl;
    }
    
    int getProcessedCount() { return totalEventsProcessed; }
    
    // getters for reports
    vector<EmergencyEvent> getProcessedEmergencies() { return processedEmergencies; }
    vector<Event*> getProcessedEvents() { return processedEvents; }
    vector<double> getResponseTimes() { return responseTimes; }
};



// SECTION 6: CITY SYSTEM

class CitySystem {
private:
    string cityName;
    CityData cityData;
    EventSystem eventSystem;
    AuthSystem authSystem;  
    bool isRunning;
    
public:
    CitySystem(string name) {
        cityName = name;
        isRunning = false;
    }
    
    void initialize() {
        cout << "\nInitializing " << cityName << "..." << endl;
        srand(time(nullptr));
        
        // initial data
        cityData.addLog(CityLog("System initialized"));
        cityData.addSensorReading(SensorReading("energy", 75.5));
        cityData.addSensorReading(SensorReading("traffic", 62.3));
        cityData.addSensorReading(SensorReading("population", 1500000));
        cityData.addSensorReading(SensorReading("energy", 82.1));
        cityData.addSensorReading(SensorReading("traffic", 91.7));
        cityData.addSensorReading(SensorReading("population", 1520000));
        
        isRunning = true;
        cout << "System ready!" << endl;
    }
    
    void shutdown() {
        cout << "\nShutting down " << cityName << "..." << endl;
        cityData.addLog(CityLog("System shutdown"));
        isRunning = false;
        cout << "Shutdown complete." << endl;
    }
    
    void addSensorReading(string type, double value) {
        SensorReading reading(type, value);
        cityData.addSensorReading(reading);
    }
    
    void generateEvent() {
        int eventType = rand() % 4;
        
        Event* event = nullptr;
        string desc;
        
        if (eventType == 0) {
            desc = "Car collision at intersection 5";
            event = new TrafficAccident(desc);
        } else if (eventType == 1) {
            desc = "Grid failure in sector 7";
            event = new PowerFailure(desc);
        } else if (eventType == 2) {
            desc = "Bandwidth spike detected";
            event = new NetworkOverload(desc);
        } else {
            desc = "Severe thunderstorm approaching";
            event = new WeatherAlert(desc);
        }
        
        eventSystem.addEvent(event);
        cityData.addLog(CityLog("New event: " + desc));
        cout << "Event type: " << event->getTypeString() << endl;
    }
    
    void generateEmergency() {
        int severity = rand() % 10 + 1;
        int idNum = rand() % 1000;
        string id = "EMG-" + to_string(idNum);
        int zone = rand() % 10;
        
        // random emergency type so we can report on it
        string types[] = {"Fire", "Medical", "Security", "Flood", "Gas Leak"};
        string eType = types[rand() % 5];
        
        string desc = eType + " emergency in zone " + to_string(zone);
        
        EmergencyEvent emergency(id, desc, severity, eType);
        eventSystem.addEmergency(emergency);
        cityData.addLog(CityLog("Emergency: " + desc));
    }
    
    void displayDashboard() {
        cout << "\n========================================" << endl;
        cout << "       " << cityName << " DASHBOARD" << endl;
        cout << "========================================" << endl;
        
        cityData.generateDataSummary();
        eventSystem.displayStatus();
        
        cout << "\n=== OOP CONCEPTS USED ===" << endl;
        cout << "Encapsulation: private data + getters/setters" << endl;
        cout << "Inheritance: derived events from Event base" << endl;
        cout << "Polymorphism: processEvent() overridden" << endl;
        cout << "Abstract class: Event has pure virtual function" << endl;
    }
    
    void generateFullReport() {
        cout << "\n========================================" << endl;
        cout << "         SYSTEM REPORT" << endl;
        cout << "========================================" << endl;
        cout << "City: " << cityName << endl;
        time_t now = time(nullptr);
        cout << "Report time: " << ctime(&now);
        
        // 1. Total events processed
        cout << "\n--- TOTAL EVENTS PROCESSED ---" << endl;
        cout << "Total: " << eventSystem.getProcessedCount() << endl;
        
        // 2. Most common emergency type
        cout << "\n--- MOST COMMON EMERGENCY TYPE ---" << endl;
        vector<EmergencyEvent> emergencies = eventSystem.getProcessedEmergencies();
        
        if (emergencies.empty()) {
            cout << "No emergencies processed yet." << endl;
        }
        else {
            map<string, int> emergencyCounts;
            map<string, int>::iterator mapIt;
            
            for (int i = 0; i < emergencies.size(); i++) {
                emergencyCounts[emergencies[i].getEmergencyType()]++;
            }
            
            // find the max
            string mostCommon = "";
            int maxCount = 0;
            
            for (mapIt = emergencyCounts.begin(); mapIt != emergencyCounts.end(); mapIt++) {
                cout << "  " << mapIt->first << ": " << mapIt->second << " times" << endl;
                if (mapIt->second > maxCount) {
                    maxCount = mapIt->second;
                    mostCommon = mapIt->first;
                }
            }
            
            cout << "\nMost common: " << mostCommon << " (" << maxCount << " occurrences)" << endl;
        }
        
        // 3. Average response time
        cout << "\n--- AVERAGE RESPONSE TIME ---" << endl;
        vector<double> times = eventSystem.getResponseTimes();
        
        if (times.empty()) {
            cout << "No response times recorded yet." << endl;
        }
        else {
            double total = 0;
            // using iterator here too
            vector<double>::iterator timeIt;
            for (timeIt = times.begin(); timeIt != times.end(); timeIt++) {
                total += *timeIt;
            }
            double avg = total / times.size();
            cout << "Average response time: " << fixed << setprecision(2) << avg << " seconds" << endl;
            cout << "Based on " << times.size() << " processed events" << endl;
        }
        
        // 4. System load summary
        cout << "\n--- SYSTEM LOAD SUMMARY ---" << endl;
        cout << "Sensor readings: " << cityData.getSensorCount() << endl;
        cout << "Historical logs: " << cityData.getLogCount() << endl;
        cout << "Processed events: " << eventSystem.getProcessedEvents().size() << endl;
        cout << "Processed emergencies: " << emergencies.size() << endl;
        
        // system load based on data
        int totalData = cityData.getSensorCount() + cityData.getLogCount() + eventSystem.getProcessedCount();
        string loadLevel = "Low";
        if (totalData > 20) loadLevel = "Medium";
        if (totalData > 50) loadLevel = "High";
        
        cout << "Current system load: " << loadLevel << endl;
        
        cout << "\n=== BIG-O SUMMARY ===" << endl;
        cout << "Vector: access O(1), insert/delete O(n)" << endl;
        cout << "List: access O(n), insert/delete O(1)" << endl;
        cout << "Queue: push O(1), pop O(1) - FIFO" << endl;
        cout << "Stack: push O(1), pop O(1) - LIFO" << endl;
        cout << "sort: O(n log n)" << endl;
        cout << "find/find_if: O(n)" << endl;
        cout << "max_element/min_element: O(n)" << endl;
        cout << "count_if: O(n)" << endl;
        
        cout << "\n========================================" << endl;
        cout << "         END OF REPORT" << endl;
        cout << "========================================" << endl;
    }
    
    void displayMenu() {
        cout << "\n========================================" << endl;
        cout << "          SYSTEM CONTROL MENU" << endl;
        cout << "========================================" << endl;
        cout << "1.  View sensor data" << endl;
        cout << "2.  View historical logs" << endl;
        cout << "3.  Add sensor reading" << endl;
        cout << "4.  Generate random event" << endl;
        cout << "5.  Process next event (FIFO)" << endl;
        cout << "6.  Process all events" << endl;
        cout << "7.  Generate emergency" << endl;
        cout << "8.  Process top emergency (LIFO)" << endl;
        cout << "9.  Process all emergencies" << endl;
        cout << "10. Display dashboard" << endl;
        cout << "11. Sort sensor data" << endl;
        cout << "12. Search sensor data by type" << endl;
        cout << "13. Search events by type" << endl;  // NEW
        cout << "14. Save system state" << endl;
        cout << "15. Load system state" << endl;
        cout << "16. Export to CSV" << endl;
        cout << "17. Generate Full Report" << endl;  // NEW
        cout << "0.  Shutdown system" << endl;
        cout << "========================================" << endl;
        cout << "Enter your choice: ";
    }
    
    void processMenuChoice(int choice) {
        if (choice == 1) {
            cityData.displayAllSensorData();
        } else if (choice == 2) {
            cityData.displayAllLogs();
        } else if (choice == 3) {
            string type;
            double value;
            cout << "Enter sensor type (energy/traffic/population): ";
            cin >> type;
            cout << "Enter value: ";
            cin >> value;
            addSensorReading(type, value);
        } else if (choice == 4) {
            generateEvent();
        } else if (choice == 5) {
            eventSystem.processNextEvent();
        } else if (choice == 6) {
            eventSystem.processAllEvents();
        } else if (choice == 7) {
            generateEmergency();
        } else if (choice == 8) {
            eventSystem.processTopEmergency();
        } else if (choice == 9) {
            eventSystem.processAllEmergencies();
        } else if (choice == 10) {
            displayDashboard();
        } else if (choice == 11) {
            cityData.sortSensorData();
        } else if (choice == 12) {
            string type;
            cout << "Enter type to search: ";
            cin >> type;
            vector<SensorReading> results = cityData.searchByType(type);
            cout << "\nFound " << results.size() << " readings:" << endl;
            for (int i = 0; i < results.size(); i++) {
                cout << "  " << (i + 1) << ". ";
                results[i].display();
            }
        } else if (choice == 13) {
            // NEW - search events by type
            cout << "\nSearch for which event type?" << endl;
            cout << "1. Traffic Accident" << endl;
            cout << "2. Power Failure" << endl;
            cout << "3. Network Overload" << endl;
            cout << "4. Weather Alert" << endl;
            cout << "Choice: ";
            int typeChoice;
            cin >> typeChoice;
            eventSystem.searchEventByType(typeChoice);
        } else if (choice == 14) {
            saveSystemState();
        } else if (choice == 15) {
            loadSystemState();
        } else if (choice == 16) {
            exportToCSV();
        } else if (choice == 17) {
            generateFullReport();  // NEW
        } else if (choice == 0) {
            shutdown();
        } else {
            cout << "Invalid choice!" << endl;
        }
    }
    
    // ===== FILE HANDLING =====
    
    void saveSystemState() {
        cout << "\n=== SAVING SYSTEM STATE ===" << endl;
        
        ofstream configFile("config.txt");
        if (configFile.is_open()) {
            configFile << "City Name: " << cityName << endl;
            configFile << "Last Saved: " << time(nullptr) << endl;
            configFile << "Sensor Count: " << cityData.getSensorCount() << endl;
            configFile << "Log Count: " << cityData.getLogCount() << endl;
            configFile.close();
            cout << "Saved config.txt" << endl;
        }
        else {
            cout << "Error: Could not open config.txt" << endl;
        }
        
        // UPDATED - now actually saves engineer data properly
        ofstream engineersFile("engineers.dat");
        if (engineersFile.is_open()) {
            vector<Engineer> engs = authSystem.getAllEngineers();
            engineersFile << engs.size() << endl;
            for (int i = 0; i < engs.size(); i++) {
                engineersFile << engs[i].getEngineerID() << "|";
                engineersFile << engs[i].getUsername() << "|";
                engineersFile << engs[i].getPassword() << "|";
                engineersFile << engs[i].getClearance() << endl;
            }
            engineersFile.close();
            cout << "Saved " << engs.size() << " engineers to engineers.dat" << endl;
        }
        else {
            cout << "Error with engineers.dat" << endl;
        }
        
        ofstream eventsFile("events.dat");
        if (eventsFile.is_open()) {
            eventsFile << "Events Processed: " << eventSystem.getProcessedCount() << endl;
            eventsFile << "Save Time: " << time(nullptr) << endl;
            
            // save processed event descriptions
            vector<Event*> processed = eventSystem.getProcessedEvents();
            eventsFile << "Event count: " << processed.size() << endl;
            for (int i = 0; i < processed.size(); i++) {
                eventsFile << processed[i]->getTypeString() << ": " 
                           << processed[i]->getDescription() << endl;
            }
            eventsFile.close();
            cout << "Saved events.dat" << endl;
        }
        else {
            cout << "Error with events.dat" << endl;
        }
        
        // UPDATED - now saves actual log messages
        ofstream logsFile("city_logs.dat");
        if (logsFile.is_open()) {
            list<CityLog> logs = cityData.getAllLogs();
            logsFile << "Total Logs: " << logs.size() << endl;
            
            list<CityLog>::iterator it;
            for (it = logs.begin(); it != logs.end(); it++) {
                logsFile << it->timestamp << "|" << it->message << endl;
            }
            logsFile.close();
            cout << "Saved " << logs.size() << " logs to city_logs.dat" << endl;
        }
        else {
            cout << "Error with city_logs.dat" << endl;
        }
        
        cout << "System state saved!" << endl;
    }
    
    void loadSystemState() {
        cout << "\n=== LOADING SYSTEM STATE ===" << endl;
        
        ifstream configFile("config.txt");
        if (configFile.is_open()) {
            string line;
            cout << "Reading config.txt:" << endl;
            while (getline(configFile, line)) {
                cout << "  " << line << endl;
            }
            configFile.close();
        } else {
            cout << "No config.txt found." << endl;
        }
        
        ifstream eventsFile("events.dat");
        if (eventsFile.is_open()) {
            string line;
            cout << "\nReading events.dat:" << endl;
            while (getline(eventsFile, line)) {
                cout << "  " << line << endl;
            }
            eventsFile.close();
        } else {
            cout << "No events.dat found." << endl;
        }
        
        ifstream logsFile("city_logs.dat");
        if (logsFile.is_open()) {
            string line;
            cout << "\nReading city_logs.dat:" << endl;
            int count = 0;
            while (getline(logsFile, line) && count < 5) {  // just show first 5
                cout << "  " << line << endl;
                count++;
            }
            logsFile.close();
            cout << "  ... (showing first 5 lines)" << endl;
        } else {
            cout << "No city_logs.dat found." << endl;
        }
        
        cout << "Load complete!" << endl;
    }
    
    void exportToCSV() {
        cout << "\n=== EXPORTING TO CSV ===" << endl;
        
        ofstream csvFile("sensor_data.csv");
        if (csvFile.is_open()) {
            csvFile << "Type,Value,Timestamp" << endl;
            
            vector<SensorReading> data = cityData.getAllSensorData();
            for (int i = 0; i < data.size(); i++) {
                csvFile << data[i].type << ",";
                csvFile << data[i].value << ",";
                csvFile << data[i].timestamp << endl;
            }
            csvFile.close();
            cout << "Exported " << data.size() << " readings to sensor_data.csv" << endl;
        }
        else {
            cout << "Error creating CSV!" << endl;
        }
        
        // also export logs to a text file
        ofstream logsExport("city_logs_export.txt");
        if (logsExport.is_open()) {
            list<CityLog> logs = cityData.getAllLogs();
            list<CityLog>::iterator it;
            for (it = logs.begin(); it != logs.end(); it++) {
                logsExport << ctime(&it->timestamp) << " | " << it->message << endl;
            }
            logsExport.close();
            cout << "Exported " << logs.size() << " logs to city_logs_export.txt" << endl;
        }
    }
    
    void run() {
        initialize();
        
        int choice;
        while (isRunning) {
            displayMenu();
            cin >> choice;
            
            cin.clear();
            cin.ignore(10000, '\n');
            
            processMenuChoice(choice);
            
            if (isRunning) {
                cout << "\nPress Enter to continue...";
                cin.get();
            }
        }
    }
    
    string getCityName() { return cityName; }
    bool getRunningStatus() { return isRunning; }
};

// ============================================================
// main
// ============================================================

int main() {
    cout << "==========================================" << endl;
    cout << "   NEOVERSE AI CITY SURVIVAL SYSTEM       " << endl;
    cout << "   Version 1.0                            " << endl;
    cout << "   Console-Based C++ Simulation           " << endl;
    cout << "   by: Junior Systems Engineer            " << endl;
    cout << "==========================================" << endl;
    cout << endl;
    
    AuthSystem auth;
    
    cout << "LOGIN REQUIRED" << endl;
    cout << "----------------------------------------" << endl;
    
    auth.displayAllEngineers();
    auth.printComplexityAnalysis();
    
    cout << "\n----------------------------------------" << endl;
    
    string username;
    string password;
    
    cout << "Username: ";
    getline(cin, username);
    
    cout << "Password: ";
    getline(cin, password);
    
    bool loggedIn = auth.loginBinary(username, password);
    
    if (!loggedIn) {
        cout << "\nAccess denied!" << endl;
        cout << "Hint: Try admin / admin123" << endl;
        cout << "\nPress Enter to exit...";
        cin.get();
        return 0;
    }
    
    cout << "\nAccess granted! Welcome, " << username << "!" << endl;
    cout << "Loading city system...\n" << endl;
    
    CitySystem city("NeoVerse City 2035");
    city.run();
    
    cout << "\nThank you for using NeoVerse!" << endl;
    cout << "\nPress Enter to exit...";
    cin.get();
    
    return 0;
}