#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <queue>

#include "PNG.hpp"
#include "HSLAPixel.hpp"
#include "vector2.hpp"
#include "shape.hpp"
#include "circle.hpp"
#include "line.hpp"


class Graph {
    public:
        /**Default graph constructor
         */
        Graph();

        /**Creates a graph object from a file that contains nodes given in the form of
         * (main URL) (connected URL reached from hyperlink on the main URL page)
         *           ^ 
         *          is a single space
         * @param: The name of the file that the nodes are stored in
         */
        Graph(std::string filename);

        const std::unordered_map<std::string, std::vector<std::string>>& get_graph();

        /**Runs a bfs on the graph object starting at a specific node
         * 
         * @param: the URL that the traversal starts on
         * @return: Nothing since void, but output is stored in bfs_output.txt
         */
        void bfsTraversal(std::string);
        
        /**Cleans the URLs from the nodes.txt file so it can be properly 
         * run in other functions 
         * 
         * @param: a string that you want to be cleaned
         * @return: the cleaned string
         */
        std::string clean_url(std::string);

        /**Uses the graph object and makes a graphical PNG output
         * 
         * @return: the number of nodes drawn in the graph or -1 if failed
         */
        int graphToPNG();


        /**Runs Brandes algorithm on the graph object
         */
        void brandes();

        /** Changes the color of a given node dependent on it's betweenness centraility value
         * @param: the betweenness centrality value of the node
         * @return: the color to set the node to
         */
        const cs225::HSLAPixel& getNodeColor(double);

    private:
        std::unordered_map<std::string, std::vector<std::string>> web_graph;
        std::unordered_map<std::string, double> centrality_map;
        void drawNode(cs225::PNG* canvas, int xCord, int yCord, int size, std::string node);
        void drawEdge(cs225::PNG* canvas, int startX, int startY, int endX, int endY);
    };

