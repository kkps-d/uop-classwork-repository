const fs = require('fs');
const args = process.argv.slice(2);
const MAX_NUM_LOOPS = 100; // Used to termiante program if deadlock happens

class Process {
    allocated; requested; completed;

    constructor(a, r) {
        this.allocated = a;
        this.requested = r;
        this.completed = false;
    }
}

// Get arguments
if (!args[0]) {
    console.log("USAGE: node main.js [input text file]");
    return;
}
try {
    file = fs.readFileSync(args[0], {
        encoding: 'utf8',
        flag: 'r'
    });
} catch (error) {
    console.error("ERR: File not found!");
    return;
}

// Parse text file
let strings = file.split('\n');
let numProcess = parseInt(strings.shift());
let numResourceTypes = parseInt(strings.shift());
console.log(`Num processes: ${numProcess}, resource types: ${numResourceTypes}`);

let availableResources = [];
let allocationMatrix = [];
let requestMatrix = [];

// Parse available resources
let t = strings.shift().split(' ');
t.forEach(elm => {
    availableResources.push(parseInt(elm));
});

// Parse allocation matrix
for (let i = 0; i < numProcess; i++) {
    const line = strings.shift().split(' ');
    const lineInt = [];
    line.forEach(resource => {
        lineInt.push(parseInt(resource));
    });
    allocationMatrix.push(lineInt);
}
console.log(`Allocation Matrix:`);
allocationMatrix.forEach(line => {
    console.log(line);
});

// Parse request matrix
for (let i = 0; i < numProcess; i++) {
    const line = strings.shift().split(' ');
    const lineInt = [];
    line.forEach(resource => {
        lineInt.push(parseInt(resource));
    });
    requestMatrix.push(lineInt);
}
console.log(`Request Matrix:`);
requestMatrix.forEach(line => {
    console.log(line);
});

// Create Processes from two matrixes
let processes = [];
for (let i = 0; i < numProcess; i++) {
    let process = new Process(allocationMatrix[i], requestMatrix[i]);
    processes.push(process);
}

// Start executing processes
let executing = 0; // Process that is being executed
let processesComplete = 0;
let runCounter = 0; // tracks how many times loop has run, used to terminate if deadlock happens
while (processesComplete < numProcess) {
    let process = processes[executing];
    if (!process.completed) {
        console.log(`Executing process with allocation: ${process.allocated}, requesting: ${process.requested}, resources available: ${availableResources}`);
        let enoughResources = true;
        // Compare request matrix to available resources
        for (let i = 0; i < numResourceTypes; i++) {
            if (process.requested[i] > availableResources[i]) {
                // Cannot grant resources, skip process and come back later
                console.log('Insufficient resources, skipping');
                enoughResources = false;
                break;
            }
        }

        if (enoughResources) {
            process.completed = true;
            // Add allocated resources back to available resources
            for (let i = 0; i < numResourceTypes; i++) {
                availableResources[i] += process.allocated[i];
            }
            console.log(`Process completed. Freed resources. Resources available now: ${availableResources}`);
            processesComplete++;
        }
    }
    executing++;
    executing = executing % numProcess;
    runCounter++;
    if (runCounter == MAX_NUM_LOOPS) break;
}
console.log("\n===================");
if (runCounter == MAX_NUM_LOOPS) {
    console.log('Deadlock detected. Program terminated');
    console.log(`Remaining processes to be executed: ${numProcess - processesComplete}`);
    console.log(`Resources available: ${availableResources}`);
    processes.forEach(p => {
        if (!p.completed) {
            console.log(p);
        }
    });
} else {
    console.log('Finished executing processes');
    console.log(`Processes executed: ${processesComplete}.\nFinal resources available: ${availableResources}`);
}