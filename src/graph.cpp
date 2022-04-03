#include "graph.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cctype>
#include <stack>

using cs225::PNG;
using cs225::HSLAPixel;


Graph::Graph() {}

Graph::Graph(std::string filename) {
    std::string line;
    std::ifstream myfile(filename.c_str());

    std::string delim = " ";
    std::string current_node = " ";
    std::vector<std::string> connecting_verts;

    if (myfile.is_open()) {
        while(getline(myfile, line)) {
            size_t pos = line.find(delim);
            std::string main_node = line.substr(0, pos);
            std::string connecting_node = line.substr(pos + 1, line.length());

            main_node = clean_url(main_node);
            connecting_node = clean_url(connecting_node);
            connecting_node = connecting_node.substr(0, connecting_node.length() - 1);
            connecting_node = clean_url(connecting_node);

            centrality_map.insert(std::pair<std::string, double>(main_node, 0));

            //Making sure main and connecting node are different
            if (main_node.compare(connecting_node) == 0) {
                continue;
            }

            //Moving to next node
            if (main_node.compare(current_node) != 0) {
                current_node = main_node;
                connecting_verts.clear();
            }

            //Making sure no dupilcate main node and connecting pair
            if (std::find(connecting_verts.begin(),
                            connecting_verts.end(),
                            connecting_node) != connecting_verts.end()) {
                continue;
            } else {
                connecting_verts.push_back(connecting_node);
            }

            //Initialize new vector if main_node is not found
            if (web_graph.count(main_node) == 0) {
                web_graph.insert(
                    std::pair<std::string, std::vector<std::string>>
                    (main_node, std::vector<std::string>()));
            }
            web_graph.at(main_node).push_back(connecting_node);
        }
        myfile.close();
    }
}

const std::unordered_map<std::string, std::vector<std::string>>& Graph::get_graph() {
    return web_graph;
}

//Need to output every edge even if it is visited


void Graph::bfsTraversal(std::string start) {
    std::unordered_map<std::string, bool> visited_map;//Map with vertex and bool if visited
    std::queue<std::string> q;
    q.push(start);
    visited_map.insert(std::pair<std::string, bool>(start, false));

    std::ofstream outdata;
    outdata.open("bfs_output.txt");

    while (q.empty() != true) {
        std::string currString = q.front();
        q.pop();

        //Check to stop cycles
        if (visited_map.at(currString) == true){
            continue;
        }

        //Otherwise mark as visited
        else {
           visited_map.at(currString) = true; 
        }

        //Adding adjacent vertices to the queue
        if (!web_graph.count(currString)) {
            continue;
        }

        for (size_t i = 0; i < web_graph.at(currString).size(); i++) {
            std::string v = web_graph.at(currString)[i];
            visited_map.insert(std::pair<std::string, bool>(v, false));//Add the new vertex to the visited_map

            //Output to bfs_output.txt
            if (!outdata) {
                std::cout << "Error: file could not be opened" << std::endl;
            }

            outdata << currString << " " << v << std::endl;
            q.push(v);
        }
    }
    outdata.close();
}

std::string Graph::clean_url(std::string url) {
    if (url.back() == '/') {
        url = url.substr(0, url.length() - 1);
    }
    
    if (url.find("https://") == 0) {
        url = url.substr(8, url.length());
    } else if (url.find("http://") == 0) {
        url = url.substr(7, url.length());
    }
    
    if (url.find("www.") == 0) {
        url = url.substr(4, url.length());
    }

    return url;
}


// outputs web_graph to PNG and returns number of nodes drawn or -1 if failed
int Graph::graphToPNG() {

    // create canvas 
    PNG* canvas = new PNG(10000, 8000);

    // counter for number of nodes drawn
    int numOfNodesDrawn = 0;

    // create hashmap to store node positions on canvas
    // vector stores xPos and yPos
    std::unordered_map<std::string, std::vector<int>> nodePositions;

    // populate nodePositions with random position for all nodes in web_graph 
    for (auto& it : web_graph) {
        std::string nodeUrl = it.first;

        int numOfAdjV = (it.second).size(); // to determine size of node on canvas

        // randomly generate start x and y positions for each node
        std::random_device rd;
        std::mt19937 gen(rd()); // seed 
        // limit range of coordinates node can be generated at -- prevent node from going off edge of canvas
        std::uniform_int_distribution<> xdistr(1000, 9000);
        std::uniform_int_distribution<> ydistr(1000, 7000);

        int centerX = xdistr(gen);
        int centerY = ydistr(gen);

        // check if generated node position already has a node there and generate new position if so
        while (canvas->getPixel(centerX, centerY) != color::WHITE) {
            centerX = xdistr(gen);
            centerY = ydistr(gen);
        }
        
        // create vector to store node position in order to draw edges
        std::vector<int> nodeInfo = {centerX, centerY};
        nodePositions[nodeUrl] = nodeInfo;

        // Draw node
         drawNode(canvas, centerX, centerY, numOfAdjV, nodeUrl);
         numOfNodesDrawn++;
    }

    // Draw Edges 
    // loop through nodes
    for (auto& it : web_graph) {
        std::string currUrl = it.first;
        std::vector<std::string> adjNodes = it.second;

        // get x,y position for current node
        std::vector<int> currNodeVector = nodePositions.at(currUrl); 
        int currNodeX = currNodeVector.at(0);
        int currNodeY = currNodeVector.at(1);

        // loop through all outgoing adjacent nodes for each node
        for (std::string& adjNodeUrl : adjNodes) {
            // get rid of any unneccesary characters at end of adjNode url
            while (adjNodeUrl.length() > 0) {
                char c = adjNodeUrl[adjNodeUrl.length() - 1];
                if (std::isalnum(c) == 0) {
                    adjNodeUrl.pop_back();
                } else {
                    break;
                }
            }

            if (nodePositions.count(adjNodeUrl) != 0) {
                std::vector<int> adjNodeVector = nodePositions.at(adjNodeUrl); 
                 // get x,y position of each adjacent node
                int adjNodeX = adjNodeVector.at(0);
                int adjNodeY = adjNodeVector.at(1);
                // draw line from current node to adjacent node
                drawEdge(canvas, currNodeX, currNodeY, adjNodeX, adjNodeY);
            }
          
        }

    }

    // write canvas to file output
    bool outPut = canvas->writeToFile("graph_output.png");

    if (outPut == false) {
        numOfNodesDrawn = -1;
        std::cout << "file output failed" << std::endl;
    }  

    delete canvas;

    return numOfNodesDrawn;
} 

void Graph::drawNode(cs225::PNG* canvas, int xCord, int yCord, int size, std::string node) {
    
    // set position of center of circle on canvas
    const Vector2 circle_center(xCord, yCord);
    // set radius as num of adj. nodes
    const int circle_radius = size;
    // set node color 
    const HSLAPixel circle_color = getNodeColor(centrality_map[node]);
    Circle* circle = new Circle(circle_center, circle_color, circle_radius);

    // draw circle on canvas 
    circle->draw(canvas);

    delete circle;

}

void Graph::drawEdge(cs225::PNG* canvas, int startX, int startY, int endX, int endY) {
    // set start and end points on canvas 
     const Vector2 startPoint(startX, startY);
     const Vector2 endPoint(endX, endY);

     const HSLAPixel line_color = color::BLUE;
     Line* line = new Line(startPoint, endPoint, line_color);

     line->draw(canvas);

     delete line;

}

const cs225::HSLAPixel& Graph::getNodeColor(double probability) {
    // Changes color of node dependent on its centrality probability value.
    
    if (probability <= 0.2) {
        return color::ORANGE;

    } else if (probability <= 0.4) {
        return color::RED;

    } else if (probability <= 0.6) {
        return color::GREEN;

    } else if (probability <= 0.8) {
        return color::PURPLE;

    } else if (probability <= 1.0) {
        return color::YELLOW;
    }
    
    return color::BLACK;
}


void Graph::brandes(){
    // web_graph name of graph map
    for (auto & it : centrality_map) {//For every vertex in the graph
        std::string starting_node = it.first;//s = starting node

        std::stack <std::string> S;
        std::unordered_map<std::string, double> sigma_map;
        std::unordered_map<std::string, double> distance_map;//Distance from s
        std::unordered_map<std::string, double> delta_map;
        std::unordered_map<std::string, std::vector<std::string>> P;//Stores the vertices that point to the node, unlike web_graph map which is stores the outwards edges

        for (auto & weblink : centrality_map) {//Intilize the maps
            sigma_map.insert(std::make_pair(weblink.first, 0));
            distance_map.insert(std::make_pair(weblink.first, -1));
            delta_map.insert(std::make_pair(weblink.first, 0));
            P.insert(std::make_pair(weblink.first, std::vector<std::string>()));
        }
        std::unordered_map<std::string, bool> brandes_visited_map (0);//Used for the BFS
        //Initilze starting node values
        distance_map[starting_node] = 0;
        sigma_map[starting_node] = 1;
        std::queue <std::string> Q;

        Q.push(starting_node);
        //BFS portion populating stack and P
        while (!Q.empty()){
            std::string v = Q.front();
            S.push(v);
            Q.pop();
            
            std::vector<std::string> adjVertices = web_graph.at(v);//Getting the vertices that v points to
            for (size_t i = 0; i < adjVertices.size(); i++) {
                std::string w = adjVertices[i];//One of the vertices v points to
                if (brandes_visited_map[w] == false){//If the node has not been visited yet
                    if (distance_map[w] < 0){
                        brandes_visited_map[w] = true;
                        Q.push(w);
                        distance_map[w] = distance_map[v] + 1;
                    }
                }
                if (distance_map[w] == distance_map[v] + 1){//If shortest path to w is via v
                    sigma_map[w] += sigma_map[v];
                    P[w].push_back(v);
                }
            }
        }
        while (!S.empty()){
            std::string w = S.top();
            S.pop();
            std::vector<std::string> vertices = P.at(w);//Get all of the vertices pointing to w
            for (unsigned i = 0; i < vertices.size(); i++){
                std::string v = vertices.at(i);
                delta_map[v] += (sigma_map[v]/sigma_map[w]) * (1 + delta_map[w] + P.at(w).size());

            }
            if (w.compare(starting_node) == 0){
                centrality_map[w] += delta_map[w] * (P.at(starting_node).size() + 1);
            }
        }
    }
    //Output for test with brandes, does not work correctly
    // for (auto & it : centrality_map){
    //     std::cout<<"Node = "<<it.first<<" "<<"Centrality value = "<<it.second<<std::endl;
    // }
    return;
}