import pprint

class Vertex(object):

    def __init__(self,value):
        self.value=value
        self.adjacentList=[]

    def addEdge(self,edge):
        self.adjacentList.append(edge)

    def getNeighbors(self):
        list=[]
        for i in range(len(self.adjacentList)):
            list.append(self.adjacentList[i].end)

        return list

    def getCostTo(self,destination):

        for i in range(len(self.adjacentList)):
            if self.adjacentList[i].end==destination:
                return self.adjacentList[i].weight


class Edge(object):

    def __init__(self,start,end,weight):
        
        self.weight=weight
        self.start=start
        self.end=end


class WeightedDirectedGraph(object):

    def __init__(self,start):
        self.list=[]
        self.list.append(start)

    def addVertex(self,value):
        self.list.append(Vertex(value))

    def addEdge(self,start,end,weight):
     
        self.getVertex(start).addEdge(Edge(start,end,weight))
    
    def getVertex(self,value):
        for i in range(len(self.list)):
            if self.list[i].value==value:
                return self.list[i]


    def printGraph(self):
        
        for i in range(len(self.list)):
            print("For Vertex {}:".format(self.list[i].value))
            for j in range(len(self.list[i].adjacentList)):
                print("From {} to {} with Weight {} ".format(
                self.list[i].adjacentList[j].start,
                self.list[i].adjacentList[j].end,
                self.list[i].adjacentList[j].weight))
            print("")



class DijkstrasAlgorithm(object):

    def __init__(self,graph):
        self.graph=graph

    def smallest(self,nodes):
        smallest=float('inf')
        index=0
        for i in range(len(nodes)):
            if self.table[nodes[i]][0]<smallest:
                smallest=self.table[nodes[i]][0]
                index=i

        return nodes[index]

    def getSmallestUnvisited(self):
        
        list=[]
        for key in self.table.keys(): 
            if key in self.unvisited:
                list.append(key)

        return self.smallest(list)


    def visitNode(self,node):
        
        list=[]
        index=0
        for i in range(len(self.graph.list)):
            if self.graph.list[i].value==node:
                list=self.graph.list[i].getNeighbors()
                index=i

        for i in list:

            if  (self.table[node][0]+self.graph.list[index].getCostTo(i))<self.table[i][0]:
                
                self.table[i][0]=(self.table[node][0]+self.graph.list[index].getCostTo(i))
                self.table[i][1]=node
 
        self.visited.append(node)
        self.unvisited.remove(node)


    def findPath(self,source,destination):
        self.visited=[]
        self.unvisited=[]
        self.table={}
        pp = pprint.PrettyPrinter(width=41, compact=True)

        for i in range(len(self.graph.list)):
            
            if self.graph.list[i].value!=source:
                self.unvisited.append(i)
                self.table[self.graph.list[i].value]=[float('inf'),None]
            else:
                self.table[self.graph.list[i].value]=[0,None]
                self.unvisited.append(i)    

        (self.visitNode(source))

        while(1):
            self.visitNode(self.getSmallestUnvisited())
            if len(self.unvisited)==0:
                break
     
        pp.pprint(self.table)


class Stack(object):

    def __init__(self):
        self.stack=[]

    def isEmpty(self):
        
        if len(self.stack)==0:
            return True
        else:
            return False

    def push(self,entity):
        self.stack.append(entity)

    def pop(self):
        self.stack.pop()


class Queue(object):

    def __init__(self):
        self.queue=[]

    def isEmpty(self):
        
        if len(self.queue)==0:
            return True
        else:
            return False

    def enqueue(self,entity):
        self.queue.append(entity)

    def dequeue(self):
        self.queue.pop(0)


def main():
    
    graph=WeightedDirectedGraph(Vertex(0))

    graph.addVertex(1)
    graph.addVertex(2)
    graph.addVertex(3)
    graph.addVertex(4)

    graph.addEdge(0,1,5)
    graph.addEdge(1,3,6)
    graph.addEdge(0,2,5)
    graph.addEdge(2,3,1)
    graph.addEdge(2,4,6)
    graph.addEdge(3,4,3)

    graph.printGraph()

    DijkstrasAlgorithm(graph).findPath(0,4)
   




if __name__ == '__main__':
    main()



