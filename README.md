# Artificial_Intelligence

**Uninformed-Search**

There is an old city that has an antique plumbing system. There are a lot of pipes in the city that are  useless  or  rarely  work.  We  want  to  find  a  route  for  water  to  traverse  from  one  side  of  the city  to  the  other  side.  There  is a  source  of  water  in  which  water  will  start  flowing  through  the system.  And  there  are  some  destinations  which  whenever  water  reaches  one  of them;we consider the  task of routing the water through  the city to be  done. So, formally speaking, there is one start node (source) and one or more end nodes (destinations) in the city.

One  strange  fact  about  this  city  is  that  some  of  the  pipes  which  a re  old  do  not  function  in specific  times.  So,  the  route  for  water  might  be  different  in  different  times. We are given the  time  periods  when  each pipe doesn’t work. But if water is already flowing in a pipe, it will continue  flowing  even  if  time  reaches  one  of  those  periods.  We  just  have  to  make  sure  that when we  want  to select the next  pipe for the rest of your water route, it is in its working time! Water  cannot  stay  in  one  point  waiting  for  a  pipe  to  start  working.  If  we reach a point where there is no pipe open from there, simply this route isn’t a valid route and we have to disregard it.

We  have  to  keep  track  of  the  time  too.  This  is simple.  We  assume  that  it  takes  n  units  of  time for water to flow  through a pipe if the length of the  pipe is n. For example if we have two pipes with length 3 and 4 in our route till now and we have started from ti me 2, current time willbe 2 + 3 + 4 = 9. 

Our  task  is  to  find  a  route  based  on  the  availability  of  the  pipes  in  a  given  time  using  search algorithms.  We  are  given  the  start  time  that  water  will  start  flowing  and  then  we  have  to report the time which water reaches the other side of the city.We  will  be  using  uninformed  search  algorithms: DFS –BFS –UCS for this.
