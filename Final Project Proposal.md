**CS 225 Final Project Proposal**

# **Group Members:**

Baizhen Wang (baizhen2)

Grace Delacruz (graced2)

Justin Mjoen (jmjoen2)

Vedan Malhotra (vedanm2)

1. **Leading Question:** How can we visually represent the UIUC web page domain space through hyperlinks?

1. **Dataset Acquisition and Processing** :

We&#39;ll acquire the hyperlink of the main UIUC page, and find all other web pages that have been linked to that page through a python script. Afterwards, we recursively go through each webpage to find out other webpages they access, until a certain limit or no links are left. Some problems arise in this process of acquiring the data however. One of these issues is infinite loops as we go through the links, and another issue is making sure that we stay within the domain of UIUC&#39;s web pages. Upon successful acquisition of data we will store each of these links and the page they are a part of in a CSV file. This file will be what we use to create our graph and run our algorithms on.

1. **Graph Algorithms** :

- Traversal: BFS - Traversing every level of the graph is equivalent to clicking every link on the previous webpage. If a loop is encountered, the previous nodes would have already been marked as visited, so we continue on to the next valid node.
  - Runtime: O(N + M), where N is the number of vertices, and M is the number of edges.

- Brandes Algorithm: Betweenness Centrality -
  - This calculates the number of times that the shortest path between any two nodes passes through       every node in the graph. This will be used to show which nodes in the graph are the most central     or connected. Using this algorithm we will be able to later colorcode our graph to show which         nodes are the most centrally connected. 
  - Unweighted, Directed graph
  - Runtime: O(N * M)

- Graphic Output of Graph - (Complex)
  - Node represents each of the webpages
  - Node size is the number of links leading to that webpage
  - Edges are links between webpages
  - Input will be our data of webpages scraped from the UIUC web domain
  - Output will be the graph visualization
  - Runtime: O(N + M)

1. **Timeline:**

The following is an outline of proposed deadlines we will aim to meet for each task of the project:

Data acquisition and data processing by: November 14, 2021

Traversal Algorithm by: November 19, 2021

Mid Project Check-In: December 1, 2021

Shortest Path Algorithm by: December 5, 2021

Graphic Output and Visualization by: December 12, 2021

Final Code Base: December 12, 2021

Code Base Read Me Document: December 12, 2021
 Written Report by: December 13, 2021

Final Video Presentation by: December 13, 2021


Vedan Malhotra (vedanm2), Justin Mjoen (jmjoen2), Grace Delacruz (graced2), Baizhen Wang (baizhen2)
