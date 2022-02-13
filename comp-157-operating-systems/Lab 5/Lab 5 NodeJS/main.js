const Process = require("./classes");
const fs = require('fs');
const internal = require("stream");

const args = process.argv.slice(2);
var filename = args[0], algorithm = args[1], rr_quantum = args[2];
var file;

// Input error checking
if (!args[0]) {
    console.log("USAGE: node main.js [input text file] [FCFS|SJF|RR] [QUANTUM]");
    return;
}
try {
    file = fs.readFileSync(filename, {
        encoding: 'utf8',
        flag: 'r'
    });
} catch (error) {
    console.error("ERR: File not found!");
    return;
}
try {
    switch (algorithm.toLowerCase()) {
        case 'fcfs':
        case 'sjf':
        case 'rr':
            break;
        default:
            throw 'no';
    }
} catch (error) {
    console.log("ERR: Invalid algorithm, please choose from FCFS|SJF|RR");
    return;
}
if (algorithm.toLowerCase() == 'rr' && !rr_quantum) {
    console.log("ERR: Quantum required for RR algorithm!");
    return;
}

// Parse text file
let strings = file.split('\n');
// console.log(strings);
let numProcess = parseInt(strings[0]);
let processes = []; // shift - removes first, push - pushes to back

for (let i = 0; i < numProcess; i++) {
    let props = strings[i + 1].split(' ');
    let temp = new Process();
    temp.pid = parseInt(props[0]);
    temp.arrival_time = parseInt(props[1]);
    temp.burst_time = parseInt(props[2]);
    processes.push(temp);
}
// console.log(processes);

let complete;
let avg;
switch (algorithm.toLowerCase()) {
    case 'fcfs':
        complete = fcfs(processes, numProcess);
        avg = 0;
        console.log("Algorithm: FCFS");
        console.log("---------------");
        console.log("PID   Arrival Time   Start Time   End Time   Running Time   Waiting Time");
        complete.forEach(process => {
            console.log(
                process.pid.toString().padEnd(3)
                + '   '
                + process.arrival_time.toString().padEnd(12)
                + '   '
                + process.start_time.toString().padEnd(10)
                + '   '
                + process.end_time.toString().padEnd(8)
                + '   '
                + process.running_time.toString().padEnd(12)
                + '   '
                + process.waiting_time.toString().padEnd(12)
            );
            avg += process.waiting_time;
        });
        console.log("Average waiting time: " + avg / numProcess);
        break;
    case 'sjf':
        complete = sjf(processes, numProcess);
        avg = 0;
        console.log("Algorithm: SJF");
        console.log("---------------");
        console.log("PID   Arrival Time   Start Time   End Time   Running Time   Waiting Time");
        complete.forEach(process => {
            console.log(
                process.pid.toString().padEnd(3)
                + '   '
                + process.arrival_time.toString().padEnd(12)
                + '   '
                + process.start_time.toString().padEnd(10)
                + '   '
                + process.end_time.toString().padEnd(8)
                + '   '
                + process.running_time.toString().padEnd(12)
                + '   '
                + process.waiting_time.toString().padEnd(12)
            );
            avg += process.waiting_time;
        });
        console.log("Average waiting time: " + avg / numProcess);
        break;
    case 'rr':
        console.log("Algorithm: RR, Quantum: " + rr_quantum);
        console.log("---------------");
        complete = rr(processes, numProcess, rr_quantum);
        avg = 0;
        console.log("PID   Arrival Time   Running Time   End Time   Waiting Time");
        processes.forEach(process => {
            console.log(
                process.pid.toString().padEnd(3)
                + '   '
                + process.arrival_time.toString().padEnd(12)
                + '   '
                + process.running_time.toString().padEnd(12)
                + '   '
                + process.end_time.toString().padEnd(8)
                + '   '
                + process.waiting_time.toString().padEnd(12)
            );
            avg += process.waiting_time;
        });
        console.log("Average waiting time: " + avg / numProcess);
        break;
}

/**
 * Feed processes that arrive at current time to queue
 * @param {Process[]} processes 
 * @param {Process[]} queue 
 * @param {Number} time 
 */
function feedToQ(processes, queue, time) {
    processes.forEach(process => {
        if (process.arrival_time == time) {
            queue.push(process);
        }
    });
}

/**
 * First come first served Algorithm
 * @param {Process[]} processes 
 * @param {Number} numProcess 
 * @returns {Process[]} completeQ
 */
function fcfs(processes, numProcess) {
    /** @type Number */
    let time = -1;
    /** @type Process[] */
    let readyQ = [];
    /** @type Process[] */
    let completeQ = [];
    /** @type Process */
    let executing = undefined;
    /** @type Boolean */
    let runComplete = false;

    while (true) {
        time++;

        // Scan for processes that arrive at current time
        feedToQ(processes, readyQ, time);

        // If no processes are being executed and queue has at least one process
        if (!executing && readyQ.length > 0) {
            // Get a process from ready queue
            executing = readyQ.shift();
            executing.start_time = time;
            executing.waiting_time = time - executing.arrival_time;
            console.log(`PID: ${executing.pid} start time: ${executing.start_time}`);
        }

        // Execute until it completes executing
        if (executing) {
            if (time > 0) { runComplete = executing.execute(); }
        }

        if (runComplete) {
            // If done executing, assign end time, push to completeQ and retrieve another process
            executing.end_time = time;
            console.log(`PID: ${executing.pid} end time: ${executing.end_time}`);
            completeQ.push(executing);
            executing = undefined;

            if (completeQ.length == numProcess) {
                break;
            }

            executing = readyQ.shift();
            executing.start_time = time;
            executing.waiting_time = time - executing.arrival_time;
            console.log(`PID: ${executing.pid} start time: ${executing.start_time}`);
        }
    }

    return completeQ;
}

/**
 * Shortest job first number
 * @param {Process[]}} processes 
 * @param {Number} numProcess 
 * @returns {Process[]} completeQ
 */
function sjf(processes, numProcess) {
    /** @type Number */
    let time = -1;
    /** @type Process[] */
    let readyQ = [];
    /** @type Process[] */
    let completeQ = [];
    /** @type Process */
    let executing = undefined;
    /** @type Boolean */
    let runComplete = false;

    while (true) {
        time++;

        // Scan for processes that arrive at current time
        feedToQ(processes, readyQ, time);
        readyQ.sort((a, b) => { return a.burst_time - b.burst_time });

        // If no processes are being executed and queue has at least one process
        if (!executing && readyQ.length > 0) {
            // Get a process from ready queue
            executing = readyQ.shift();
            executing.start_time = time;
            executing.waiting_time = time - executing.arrival_time;
            console.log(`PID: ${executing.pid} start time: ${executing.start_time}`);
        }

        // Execute until it completes executing
        if (executing) {
            if (time > 0) { runComplete = executing.execute(); }
        }

        if (runComplete) {
            // If done executing, assign end time, push to completeQ and retrieve another process
            executing.end_time = time;
            console.log(`PID: ${executing.pid} end time: ${executing.end_time}`);
            completeQ.push(executing);
            executing = undefined;

            if (completeQ.length == numProcess) {
                break;
            }

            executing = readyQ.shift();
            executing.start_time = time;
            executing.waiting_time = time - executing.arrival_time;
            console.log(`PID: ${executing.pid} start time: ${executing.start_time}`);
        }
    }

    return completeQ;
}

/**
 * Round Robin Algorithm
 * @param {Process[]} processes 
 * @param {Number} numProcess 
 * @param {Number} quantum
 * @returns {Process[]} completeQ
 */
function rr(processes, numProcess, quantum) {
    /** @type Number */
    let time = -1;
    /** @type Process[] */
    let readyQ = [];
    /** @type Process[] */
    let completeQ = [];
    /** @type Process */
    let executing = undefined;
    /** @type Boolean */
    let runComplete = false;
    /** @type Number */
    let qtm = 0;
    /** @type Number */
    let runtime = 0;

    console.log('PID   Start Time   End Time   Running Time');

    while (true) {
        time++;

        // Scan for processes that arrive at current time
        feedToQ(processes, readyQ, time);

        // If no processes are being executed and queue has at least one process
        if (!executing && readyQ.length > 0) {
            // Get a process from ready queue
            executing = readyQ.shift();
            executing.start_time = time;
            // executing.waiting_time = time - executing.arrival_time;
        }

        // Execute until it completes executing
        if (executing) {
            if (time > 0) { 
                runComplete = executing.execute(); 
                qtm++;
                runtime++;
            }
        }

        if (runComplete || qtm == quantum) {
            // If done executing, assign end time, push to completeQ and retrieve another process
            executing.end_time = time;
            console.log(
                executing.pid.toString().padEnd(3) + '   '
                + executing.start_time.toString().padEnd(10) + '   '
                + executing.end_time.toString().padEnd(8) + '   '
                + runtime.toString().padEnd(12) + '   '
            );
            runtime = 0;
            if (qtm == quantum && !runComplete) {
                readyQ.push(executing);
            } else {
                executing.waiting_time = (time - executing.arrival_time) - executing.burst_time;
                completeQ.push(executing);
            }
            qtm = 0;
            executing = undefined;

            if (completeQ.length == numProcess) {
                break;
            }

            executing = readyQ.shift();
            executing.start_time = time;
        }
    }

    return completeQ;
}