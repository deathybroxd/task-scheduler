### task-scheduler
This is a mock task scheduler for an operating system. It uses a graph data structure to add tasks and add dependencies/edges to other tasks.
The dependency graph also does a cycle check using a white/gray/black depth-first search to ensure it can work properly. If a cycle is detected in the graph,
the program is immediatelly terminated. This project also implements a EDF (earliest deadline first) scheduler to schedule the tasks accordingly. Data from
this program is outputted in a .csv file formatted as such:

```
Task Id|Arrival Time|Deadline|Completion Time|Status|Lateness
73|12|1|2|Met deadline
62|90|1|2|Met deadline
77|5|2|3|Met deadline
68|77|2|3|Met deadline
9|19|3|4|Met deadline
83|61|4|5|Met deadline
59|79|5|6|Met deadline
43|20|5|6|Met deadline
79|46|8|9|Met deadline
2|96|10|11|Met deadline
98|36|11|12|Met deadline
84|48|12|13|Met deadline
88|36|16|17|Met deadline
24|41|16|17|Late
35|8|17|18|Met deadline
36|50|18|19|Met deadline
61|21|19|20|Met deadline
15|77|19|20|Met deadline
74|0|20|21|Met deadline
96|81|22|23|Met deadline
85|22|22|23|Met deadline
75|3|22|23|Late
1|87|22|23|Met deadline
```