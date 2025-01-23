# PS7: Kronos Time Clock Parser
## Contact
Name: Daniel Dsouza
Section: 201
Time to Complete: almost 6 hours

## Description
The program processes a Kronos log file to extract detailed information about device boot times. It generates a new output file that documents when each device began booting, when the boot process completed, and the duration of the boot process. The program organizes these details into a report file, listing each startup event along with relevant data and a summary. If a device fails to boot, this is also reflected in the output report.

### Features
I decided to implement the entire program in a single file, unlike previous projects. I chose this approach because I felt there was no need to create a new class with additional methods for this project. Instead, a simple structure was sufficient to hold and organize the necessary data for generating the report on each device boot. The program uses regular expressions to identify startup and completion events in the log file, and the boot time calculation determines the elapsed time between these events using the Boost Date-Time library.

### Approach
The approach for the program was pretty straightforward. It reads through each line of the log file, using regular expressions to identify boot start and completion events. These events are stored and paired to calculate the time between them. Each startup message is matched with its corresponding completion message. If no match is found before another startup message or the end of the file, the startup is flagged as a failure. The results are written in the required format, including line numbers, timestamps, success or failure status, and the elapsed time for each boot event.

### Regex
1) Boot Start Detection:
R"(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}: \(log.c.166\) server started)"
 - This regex captures the timestamp and the specific log message indicating that the server has started.

2) Boot Completion Detection:
R"(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}.\d{3}:INFO:oejs.AbstractConnector:Started SelectChannelConnector@0.0.0.0:9080)"
 - This regex captures the timestamp and the specific log message indicating that the server has successfully completed booting by starting the SelectChannelConnector.

### Issues
Initially, I struggled with creating the correct regular expressions to capture the required timestamps accurately. Handling nested or overlapping log entries also proved challenging, as it required careful pairing logic to ensure proper matches. Additionally, I encountered difficulties in formatting the date and time correctly for the report output for each boot event. However, both of these issues were successfully resolved by the end of the project.

### Extra Credit
I successfully implemented a header in the output reports that summarizes the total number of boot processes initiated and the number that were successfully completed.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.

CPPreference.com
Youtube.com, blackboard pdf, and stackoverflow.com
