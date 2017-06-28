# Basado en el curso de Atenas en Telecom ParisTech de Jean-Louis Dessales

import math
import Tkinter
from time import sleep
import random
from PIL import *
import PIL  # Interfaz de Python Imaging Library con Tkinter
from Simulation import *
from Simulation_Control import *
from Draw_Area import *
from Generic_Main_Frame import *
from Ground import *


class LandCell(object):
    #define una celda
    def __init__(self, N=0, NP=0, PP=0):
        self.Node = N
        self.PPheromone = PP # Feromona Atractiva
        self.fieldIndex = -1

    def __add__(self, Other):
        return LandCell(self.Node+Other.Node, self.PPheromone + Other.PPheromone)
    
    
class Node (object):
    def __init__(self,x=0,y=0,iden=0):
        self.Id = iden
        self.Position = [x,y]
        
    def setPosition(self,Pos):
        self.Position = Pos
    
class Landscape(object):
    """ Una cuadricula 2-D con celdas que contiene feromona o bordes (para graficos)
        el grafico esta representado por nodos y bordes
    """ 
    def __init__(self, Size):
        self.Size = Size
        self.Ground = [[LandCell() for x in range(Size)] for x in range(Size)]
        
        #Coordenadas de los bordes con feromonas que se dibujaran en el mapa
        #este campo se actualiza en la funcion vaporate
        self.EdgesWithPheromons = [];

        #representa los bordes - el valor de la feromona en cada borde
        self.Edges = [[0 for col in range(NbNodes)] for row in range(NbNodes)]
        
        #distancia entre nodos
        self.Distances = [[0 for col in range(NbNodes)] for row in range(NbNodes)]
        
        #se utiliza para almacenar la ruta optima actual                                                       
        self.OptimalPath = 10000000000
        
        #crea los nodos 
        self.Nodes = []
        self.Nodes.append(Node(100,260,0))
        self.Nodes.append(Node(150,100,1))
        self.Nodes.append(Node(200,120,2))
        self.Nodes.append(Node(30,200,3))
        self.Nodes.append(Node(225,123,4))
        self.Nodes.append(Node(250,250,5))
        
        self.Nodes.append(Node(124,90,6))
        self.Nodes.append(Node(50,221,7))
        self.Nodes.append(Node(152,152,8))
        self.Nodes.append(Node(80,80,9))
        self.Nodes.append(Node(210,85,10))
        
        #calcula las distancias de todos los nodos
        for ident in range(NbNodes):
          node = self.Nodes[ident]
          for prev in range(ident):
            Direction = (complex(node.Position[0],node.Position[1]) - complex(self.Nodes[prev].Position[0],self.Nodes[prev].Position[1]))
            Distance = abs(Direction)
            self.Distances[ident][prev] = Distance
            self.Distances[prev][ident] = Distance
        
        #Posicionamiento aleatorio de los nodos del grafico
        #for ident in range(NbNodes):
        #    #symetrical
        #    position = (100+50*(ident%3),100+50*(ident/3))
        #    #random
        #    #position = (random.randint(20,Size-20),random.randint(20,Size-20))
        #    node = Node(position[0],position[1],ident) 
        #    self.Nodes.append(node)
        #    Observer.record(('Node',position))
        #    for prev in range(ident):
        #        Direction = (node.Position - self.Nodes[prev].Position)
        #        Distance = abs(Direction)
        #        self.Distances[ident][prev] = Distance
        #        self.Distances[prev][ident] = Distance
        #                
        #    #make the nodes big
        #    for Pos in self.neighbours(position, Radius=2):
        #        Observer.record(('Node',Pos))
        #        self.node(Pos,10)
        
    def evaporate(self):
        Land.EdgesWithPheromons = []
        for i in range(NbNodes):
          for j in range(NbNodes):
            #este es el valor de la feromona en el nodo
            cell = Land.Edges[i][j]
            
            cell = (1-theta) * cell
            Land.Edges[i][j] = cell

            #si el valor es mayor que el limite - mostrar la feromona en la pantalla
            if cell > PToShow:
              Land.EdgesWithPheromons.append([Land.Nodes[i].Position,Land.Nodes[j].Position])


class Ant(object):
    """ Define agentes individuales - una hormiga concreta. El comportamiento de hormiga se puede expresar como una maquina de estado con el estado:
        SearchNextNode (busque el siguiente nodo), ReturnToFirstNode, GoToNode (solo vaya al nodo seleccionado).
    """
    def __init__(self, IdNb):
        self.IdNb = IdNb    # Numero de identificacion
        self.Action = 'SearchNextNode' #Cada hormiga buscara ejecutar una determinada accion
        self.Node = Node()
        self.Path = []
        self.PathLength = 0
        self.NodeDistance = -1
        self.PrevNodeIndex  = -1
        self.ToVisit = []		 # array que contendra los nodos a visitar desde el nodo actual
        self.Visited = []        # array vacio de nodos visitados 
        
        for i in range(NbNodes):
            self.Visited.append(0) # Llenamos el array Visited de 0
            self.ToVisit.append(i) # Anadimos el nodo i para Visitarlo

	#Funcion que Verifica: Si todos los Nodos ya han sido visitados -> Se ha completado el camino
    def isCompleted(self):
        for i in range(NbNodes):
            if self.Visited[i]==0:
                return 0
                
        return 1
    
	#Accion de la Hormiga que marca como visitado a Un nodo con 1 y calcula la distancia que le tomo llegar a este nodo
    def goToNode(self):
        self.Visited[self.Node.Id] = 1
        self.Path.append(self.Node.Id)
        
        # Anade la distancia calculada , a PathLength, se van acumulando todas las Distancias
        self.PathLength+= self.NodeDistance
        
        # Verificamos: Si todos los nodos han sido visitados, Volvemos al primer nodo (Punto de Partida)
        if self.isCompleted():
            self.Action = 'GoToFirst'
            firstNode = self.Path[0]
            # Anadimos la distancia del nodo actual hacia el primero
            self.PathLength+= Land.Distances[self.Node.Id][firstNode]
            self.Node = Land.Nodes[self.Path[0]]
            
        else:
            self.Action = 'SearchNextNode'
       
	# Otra accion de la hormiga : Se dirige al Primer Nodo del que partio       
    def goToFirst(self):
        # Se anade el nodo al camino para que esten todos los nodos
        self.Path.append(self.Node.Id)
                     
        # Calculamos el Valor de la feromona 1 /longitudRuta ^ k, donde k es un coeficiente para amplificar el impacto de la 			longitud de la ruta a la decision.
        self.PheromoneValue = 1/math.pow(self.PathLength,k)
              
        # Se anade la distancia del ultimo Nodo
        if self.PathLength<Land.OptimalPath:
          print self.Path
          print self.PathLength
          Land.OptimalPath = self.PathLength
        # Se remueve el ultimo NOdo
        self.Path.pop()
            
        # Se copia la ruta recorrida Y Regresamos al inicio
        self.Action = 'ReturnToStart'
        to = self.Path.pop()
        Land.Edges[self.Node.Id][to] += self.PheromoneValue
        Land.Edges[to][self.Node.Id] += self.PheromoneValue
        self.Node = Land.Nodes[to]
            
	# Accion de la hormiga que: Busca el siguiente Nodo ( Que no haya sido visitado y con > cant de feromonas)
    def searchNextNode(self):
        nodeindex = self.Node.Id        
        # La maxima probabilidad
        pMax = 0
        p = 0

        # Tratar de seleccionar el mejor nodo por las feromonas 
        # Para ello hay que iterar todos los nodos
        for i in range(NbNodes):
          if i!=self.Node.Id and self.Visited[i]==0:
            d = Land.Distances[self.Node.Id][i]
            
            # Obtenemos el valor de la Feromona de la Arista en la que estamos 
            pi = Land.Edges[self.Node.Id][i]
            
            # Evitamos posible error de : Division por 0
            # Se lanza una excepcion
            if d==0:
              print i
              print self.Node.Id
            
            # Hayamos la calidad de la Ruta
            nij = 1/d
              
            pselected = math.pow(pi,alfa) * math.pow(nij,beta)
            
            # Normalizaion: 
            # Calculamos la suma de las otras Opciones
            sum = 0
            for j in range(NbNodes):
              if j!=self.Node.Id and self.Visited[j]==0 and j!=i:
                dj = Land.Distances[self.Node.Id][j]
                pij = Land.Edges[self.Node.Id][j]
                nj = 1/dj
                pj = math.pow(pij,alfa) * math.pow(nj,beta)
                sum+=pj
            if sum>0:
              p = pselected/sum

            # Si tenemos una nueva mejor trayectoria - entonces conservamos el indice
            if p > pMax:
              pMax = p
              nodeindex = i        
        
        # La primera vez(En cuanto scoger el sgnte nodo) se escoge cualquier nodo (Aleatorio)
        while nodeindex == self.Node.Id:
            nodeindex = random.randint(0,NbNodes-1)

        # Anadimos la distancia de este nuevo nodo y vamos a Visitarlo
        self.PathLength += Land.Distances[self.Node.Id][nodeindex]                       
        self.Node = Land.Nodes[nodeindex]
        self.Action = 'GoToNode'
        
       
	#Accion de la hormiga: Para una vez terminados de recorrer todos los Nodos, Ir al inicio
    def returnToStart(self):    
        self.Visited[self.Node.Id] = 0
            
        if len(self.Path):
            to = self.Path.pop()
            #Se coloca la feromona en el borde
            Land.Edges[self.Node.Id][to] += self.PheromoneValue
            Land.Edges[to][self.Node.Id] += self.PheromoneValue

            #Cambiar de poscicion
            self.Node = Land.Nodes[to]
            
        else:
            #Llego a casa despues del viaje
            self.Action = "SearchNextNode"
            #Se establece el valor precalculado en 0
            self.PheromoneValue = 0;
            for i in range(NbNodes):
              self.ToVisit.append(i)
            self.PathLength = 0
        
    def moves(self):
        #La hormiga se movera de acuerdo a una de las siguientes acciones
        if self.Action == 'GoToNode':
            self.goToNode()
        if self.Action == 'SearchNextNode':
            self.searchNextNode()
        if self.Action == 'ReturnToStart':
            self.returnToStart()
        if self.Action == "GoToFirst":
            self.goToFirst()

class Ant_Frame(Generic_Main_Frame):

    def __init__(self, Parent,NbAgents):
        #Algunas carateristicas adicionales de las hormigas se encuentran en este frame
        Generic_Main_Frame.__init__(self,Parent,self.oneStep,Wtitle='Ants')
        self.startGround()
        self.LastTimeStep = 0
        self.Counter = 0
        #Se crea una poblacion de agentes
        self.Pop = [Ant('A%d' % IdNb) for IdNb in range(NbAgents)]
        self.PopSize = NbAgents
        self.Moves = 0  # contador que almacena el numero de veces que se ha movido un agente
        t = Thread(target=self.redraw)
        t.start()
          
    def startGround(self):
        """ El suelo es un espacio 2D que representa el campo donde las hormigas vagan
        """
        self.Ground = Ground(self, Toric=True)
        self.Ground.scaleX = self.Ground.scaleY = LandSize   # Coordenadas logicas
        self.Ground.W = self.Ground.H = LandWindowSize      # Coordenadas fisicas
        self.Ground.configure(width=self.Ground.W, height=self.Ground.H)
        self.Ground.pack(expand=Tkinter.YES,fill=Tkinter.BOTH)  # Ventana que muestra la pantalla
           
    def oneStep(self):
        #Esta funcion es llamada atras despues del paso de la simulacion
        Land.evaporate()
        
        for agent in self.Pop:
            agent.moves()
        
        self.Moves += 1
        return 0
    
    def redraw(self):
        while 1:
            # El paisaje es totalmente redisenado
            self.Ground.erase() # Destruye los objetos sobre el terreno
            
            self.displayNodes(Land.Nodes)
            self.displayPheromons(Land.EdgesWithPheromons)
            sleep(1)
    

    def displayPheromons(self, edges):
        for edge in edges:
            coord1 = edge[0]
            coord2 = edge[1]
            self.Ground.create_line(coord1[0], coord1[1], coord2[0],coord2[1], fill="red", dash=(4, 4))

    def displayNodes(self, Nodes):
        for node in Nodes:
            coord = node.Position
            self.Ground.create_rectangle(coord[0]-2, coord[1]-2, coord[0]+2, coord[1]+2,outline='black',fill='gray50')
        
def Start():
    MainWindow = Tkinter.Tk()   # Crea la ventana principal
    MainWindow.title('Ants')
    MainWindow.GParent = MainWindow

    Frame = Ant_Frame(MainWindow, 80)   

    # displaying the window
    MainWindow.lift()
    MainWindow.focus_force()
    # Entering main loop
    MainWindow.mainloop()   # Se controla el sistema de ventanas
    OptimalPath=10000000000




if __name__ == "__main__":
    LandSize = 300
    NbNodes = 11

    # Nivel de feromonas
    PToShow = 0.004
    
    #Factor que disminuye el valor dado por una trayectoria en la funcion de longitud de los trayectos
    k=1
    
    #El factor de evaporacion
    theta = 0.07
   
    #Parametro que amplifica el valor de la feromona ( pi^alpha )
    alfa = 4

    #Parametro que amplifica el impacto de la calidad de la ruta ni ^ beta; Ni = 1 / de
    beta = 2.5

    Land = Landscape(LandSize)
    LandWindowSize = 700 
    Start()


