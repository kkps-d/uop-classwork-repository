class Process {
    pid;
    arrival_time;
    burst_time;
    start_time;
    end_time;
    running_time;
    waiting_time;

    constructor() {
        this.pid = -1;
        this.arrival_time = -1;
        this.burst_time = -1;
        this.start_time = -1;
        this.end_time = -1;
        this.running_time = 0;
        this.waiting_time = 0;
    }

    execute() {
        this.running_time++;
        if (this.running_time == this.burst_time) {
            return true;
        } else {
            return false;
        }
    }
}

module.exports = Process;