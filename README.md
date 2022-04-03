# jmjoen2-vedanm2-baizhen2-graced2
Final Project for jmjoen2-vedanm2-baizhen2-graced2<br>
## Deliverables
[Presentation Video](https://youtu.be/IKGehLVEiWM)<br>
[Presentation Slides](https://docs.google.com/presentation/d/1niFgtKfaILK-aQiBozPqfnhsXhyCd4qcY8kx82Y0ctw/edit?usp=sharing)<br>
[Project Results](https://docs.google.com/document/d/132ycSnQ92vxKGUVBlqIee7h4-OftdsI-bmSfMibHSdY/edit?usp=sharing)


## Code Overview:
Our final project creates a graph that represents a large portion of the UIUC webspace. Our graph aims to show all of the hyperlink connections to each webpage. Upon the creation of the graph structure, we can run a BFS traversal on the graph as well as create a meaningful graphical output of the graph. The graphical representation has nodes that represent the webpage, and the size of the nodes is the number of links from that page. The edges in the graph represent the links between two web pages via a hyperlink. We also have a non fully functioning implementation of Brandes Algorithm. Which is used to try to find the betweenness centrality of each node and change the color of the node according to that value.

## Code Organization
#### "Data Collection":
This folder contains a Python script that goes to “Illinois.edu” and traverses all of the links on that page, and then continues that traversal in a sort of BFS traversal. A condensed output of this data was stored to nodes.txt in the interest of runtime. 

#### "includes":
This next folder contains all of the .hpp files that are used. The graph.hpp is the main file that is used in the creation of graph structure, as well as the BFS traversal and Brandes algorithm. The rest of the .hpp files are used for the graphical output of the graph. 

#### "src":
This folder is where the .cpp files are stored. The two files here are graph.cpp and main.cpp. Graph.cpp is where the graph is created, BFS is run, the graphical output is created, and Brandes algorithm is used. Main is used to call the methods that we created.


#### "tests":
As is evident from its name this folder contains the files used to test our code. We have the catch.hpp file in here as well as the tests.cpp file. The “tests” folder also contains .txt files that are used to compare outputs for our test cases. A few of these .txt files were manually created by us so that we could make sure we get the desired output. In our test.cpp file we have test cases for:<br>
<ul>
  <li>URL cleaner</li>
  <li>Graph parsing and structure</li>
  <li>BFS traversal</li>
  <li>Graphical output</li>
  <li>Checking if nodes are colored properly</li>
</ul>
  
#### Other:
There are other files that exist that are not in any of the above mentioned folders:<br>
<ul>
  <li>Final Project Contract</li>
  <li>Final Project Proposal</li>
  <li>Output of the BFS Traversal</li>
  <li>Development Log</li>
  <li>The graphical output</li>
  <li>makefile</li>
  <li>nodes.txt which stores the data for the graph</li>
 </ul>
 
## Fileio
The code can be run by simply entering the following command:
<pre><code>make tests</code></pre>
Running this command will create and run an executable for the test cases that we created, as well as create the graphical output of the graph and the output of the BFS traversal.<br>
<ul>
  <li>The graphical output can be found in graph_output.png</li>
  <li>The BFS Traversal outpt can be found in bfs_output.txt</li>
</ul>
If you want to just run the executable for the test cases it can be done with the command:
<pre><code>./bin/tests.out</code></pre>
Also you just run the functions though main by enetering the following command:
<pre><code>make exec</code></pre>
And then just run the main executable by entering the command:
<pre><code>./bin/main.out</code></pre>
Which will store the outputs in the same location as "make tests".
