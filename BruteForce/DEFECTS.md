## Defects Found During Development

### Instructions:

Please list the following information when adding a defect:
ID# Name of defect (short description)
- Branch
- First name
- Date
- Module(s) reported as having the error, if any
- Nature of run-time events (steps/variable values used in executing the application)

### Recorded Defects:

1. # of projects vs students
- Branch: Canvas1
- Cristi
- 03/04/2020
- Run-time error
- Executed application from branch Canvas1 with 25 projects and 125 students.
- Status: CLOSED

2. Terminate error called after throwing an instance of 'JSON::LogicError'
- Branch: dev
- Cristi
- 03/29/2020
- Run-time error
- Version: SteamPunk | # of Projects: 10 | # of Students: 40 | Project file used: 100Projects.csv
- Cause: Incorrect .csv file used - task opened to add instructions for testing system.
- Status: OPEN

3. Cannot view "Continue" button on laptop screen
- Branch: dev
- Cristi
- 03/29/2020
- UX issue
- Version: SteamPunk
- Status: CLOSED

4. No message displayed for when there are no class sections for selected semester and year
- Branch: dev
- Cristi
- 03/29/2020
- UX issue
- Version: SteamPunk
- Status: OPEN

5. Text for "POST" and "SAVE" buttons after completion run over button boundaries (wrap-text needed)
- Branch: dev
- Cristi
- 04/01/2020
- UX issue
- Version: SteamPunk

6. System would run into cases where no team combinations could be formed.
- Branch: dev
- Myles
- 04/01/2020
- LOGICAL ERROR
- Version: SteamPunk / ASU
- Cause: csv file reader and writer. Reader for the projects was not assigning the correct skill values.
- Status: CLOSED

7. Certain values need to be hardcoded, such as the number of class sections.
- Branch: dev
- Myles
- 04/03/2020
- Thread Issue
- Cause: The threads do not allow arrays of dynamic size, so the threads cannot be used if the the 
 value is not hardcoded. It does not work with the ToConstInt function either. 
- Status: OPEN
