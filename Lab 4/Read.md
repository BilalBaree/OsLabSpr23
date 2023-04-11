5(A) : The limit of child processes that a process can create is determined by the system's resources, specifically the maximum number of processes that can be created on the system. This limit can vary depending on the operating system and its configuration.

On Linux systems, for example, the maximum number of processes is controlled by the kernel parameter "kernel.pid_max", which can be viewed and modified using the "sysctl" command. The default value for this parameter is usually set to a very large number, such as 32768 or higher, so most applications will not encounter any issues with creating child processes.

However, it is still possible to encounter limitations if the system is heavily loaded or if the process is creating a large number of child processes. In such cases, the process may fail to create additional child processes, or the system may become unresponsive or unstable.

It is therefore important to monitor system resource usage and adjust process behavior as necessary to avoid exceeding resource limits and causing system instability.
The Average Process Created are 10.

5(B) : Yes, the limit of the maximum number of processes that can be created can be increased in some cases. However, this typically requires modifying system settings or kernel parameters, which can be complex and may have unintended consequences.

On Linux systems, for example, the maximum number of processes that can be created can be increased by modifying the "kernel.pid_max" parameter using the "sysctl" command or by modifying the "nr_max_processes" value in the "/proc/sys/kernel" file system. However, modifying these values can have system-wide effects and may impact the performance and stability of the system.

In general, it is recommended to avoid creating excessive numbers of child processes and to monitor system resource usage to ensure that the system does not become overloaded. If your application requires the creation of a large number of child processes, consider implementing alternative designs or using alternative technologies that are better suited to the task.
