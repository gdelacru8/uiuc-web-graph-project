#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "graph.hpp"

bool checkFilesEqual(std::string url1, std::string url2) {
    std::string line1;
    std::string line2;
    std::string delim = " ";
    std::ifstream file1(url1);
    std::ifstream file2(url2);

    if (file1.is_open() && file2.is_open()) {
        while (getline(file1, line1) && getline(file2, line2)) {
            size_t pos1 = line1.find(delim);
            std::string main_node1 = line1.substr(0, pos1);
            std::string connecting_node1 = line1.substr(pos1 + 1, line1.length());

            size_t pos2 = line2.find(delim);
            std::string main_node2 = line2.substr(0, pos2);
            std::string connecting_node2 = line2.substr(pos2 + 1, line2.length());

            if (main_node1 != main_node2 || connecting_node1 != connecting_node2) {
                return false;
            }
        }

        if ((line1 == "" && line2 != "") || (line1 != "" && line2 == "")) {
            return false;
        }

    } else {
        return false;
    }

    file1.close();
    file2.close();

    return true;
}

TEST_CASE("Test url cleaner is valid") {
    Graph graph;
    std::string line = "https://illinois.edu/";
    REQUIRE(graph.clean_url(line) == "illinois.edu");

    line = "http://blog.admissions.illinois.edu";
    REQUIRE(graph.clean_url(line) == "blog.admissions.illinois.edu");

    line = "https://admissions.illinois.edu/Visit/virtual-visits";
    REQUIRE(graph.clean_url(line) == "admissions.illinois.edu/Visit/virtual-visits");

    line = "http://publish.illinois.edu/student-affairs-advancement/";
    REQUIRE(graph.clean_url(line) == "publish.illinois.edu/student-affairs-advancement");

    line = "http://www.blog.admissions.illinois.edu";
    REQUIRE(graph.clean_url(line) == "blog.admissions.illinois.edu");
}

TEST_CASE("Test valid graph parsing") {
    Graph graph("tests/sample_nodes.txt");
    const std::unordered_map<std::string, std::vector<std::string>>& test_graph = graph.get_graph();

    std::string line;
    std::string delim = " ";
    std::ifstream myfile("tests/sample_nodes_test_file.txt");
    std::string current_node = "";
    int index = 0;

    if (myfile.is_open()) {
        while (getline(myfile, line)) {

            size_t pos = line.find(delim);
            std::string main_node = line.substr(0, pos);
            std::string connecting_node = line.substr(pos + 1, line.length());

            main_node = graph.clean_url(main_node);
            connecting_node = graph.clean_url(connecting_node);
            connecting_node = connecting_node.substr(0, connecting_node.length() - 1);
            connecting_node = graph.clean_url(connecting_node);

            if (main_node.compare(connecting_node) == 0) {
                continue;
            }

            if (main_node.compare(current_node) != 0) {
                current_node = main_node;
                index = 0;
            }

            REQUIRE(test_graph.at(current_node)[index].compare(connecting_node) == 0);
            index++;
        }
        myfile.close();
    }
}

TEST_CASE("Test BFS properly functions") {
    Graph graph("tests/bfs_test.txt");
    graph.bfsTraversal("illinois.edu");
    REQUIRE(checkFilesEqual("tests/expected_bfs.txt", "bfs_output.txt"));
}

TEST_CASE("Test graphical output") {
    Graph graph("nodes.txt");
    int numOfNodesDrawn = graph.graphToPNG();
    int numOfKeysInWebGraph = graph.get_graph().size();
    REQUIRE(numOfNodesDrawn == numOfKeysInWebGraph);

}

TEST_CASE("Test Brandes"){
    Graph graph("tests/brandes_test.txt");
    graph.brandes();
}

TEST_CASE("Test node is colored properly") {
    Graph graph;
    std::unordered_map<std::string, double> brandes_test_vals = {{"illinois.edu", 0.2}, {"illinois.edu/index.html", 0.31}, 
                                                                {"directory.illinois.edu/search", 0.833}, {"illinois.edu/about/facts.html", 0.15},
                                                                {"publicaffairs.illinois.edu/services/social-media/verified-accounts", 0.23}};
    REQUIRE(graph.getNodeColor(brandes_test_vals["illinois.edu"]) == color::ORANGE);
    REQUIRE(graph.getNodeColor(brandes_test_vals["illinois.edu/index.html"]) == color::RED);
    REQUIRE(graph.getNodeColor(brandes_test_vals["directory.illinois.edu/search"]) == color::YELLOW);
    REQUIRE(graph.getNodeColor(brandes_test_vals["illinois.edu/about/facts.html"]) == color::ORANGE);
    REQUIRE(graph.getNodeColor(brandes_test_vals["publicaffairs.illinois.edu/services/social-media/verified-accounts"]) == color::RED);
}

/////////////////////////////////////////////////////////////////////////////////////////////