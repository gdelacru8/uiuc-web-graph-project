from bs4 import BeautifulSoup
import requests
import random
import proxy

def driver(start_url, proxiesFormatted):
    with open('nodes.txt', 'w') as file:

        to_visit = []
        visited = set()
        to_visit.append(start_url)

        node_counter = 0
        while len(to_visit) != 0:

            # start a session with new proxy
            # Note: proxies may not be needed
            # but to access some urls SSL verification needs to be set to false
            # this can be done with request.get(url, verify=False)
            session = requests.Session()
            rand_proxy = random.choice(proxiesFormatted)
            session.proxies.update(rand_proxy)
            session.verify = False

            current_url = to_visit.pop(0)

            # URL reformat
            if current_url.find("httsp") != -1:
                current_url = current_url.replace("httsp", "https")

            # Current node already visited
            if current_url in visited:
                continue
            visited.add(current_url)

            # No more edges on mailing address
            if current_url.find("mailto") != -1:
                continue

            # To catch all of the remaining errors
            try:
                response = session.get(current_url)

                # Bad server response
                if response.status_code != 200:
                    continue

                html_page = response.text
                print(response.status_code)
                soup = BeautifulSoup(html_page, "lxml")

                for link in soup.findAll('a'):
                    node = ""
                    link_part = link.get('href')

                    # No link
                    if type(link_part) == None:
                        continue

                    # Don't want to visit facebook
                    try:
                        if link_part.find("facebook") != -1:
                            continue
                    except:
                        continue

                    # Link rebuilding if necessary
                    if link_part.find('.html') != -1 and link_part.find('illinois.edu') == -1:
                        node = "https://illinois.edu/" + link_part
                    elif link_part.find('illinois.edu') != -1:
                        node = link_part

                    if node != "":
                        file.write(current_url + " " + node + "\n")

                    # Don't need to revisit if node doesn't exist or already visited
                    if node in visited or node == "":
                        continue
                    else:
                        to_visit.append(node)

                node_counter += 1

                print("Current # of nodes: " + str(node_counter))
            except:
                continue


        print("Number of unique accessible URLS/Nodes" + str(node_counter))

proxy_list = proxy.validProxyList("proxy.txt")
driver("https://illinois.edu/", proxy_list)
