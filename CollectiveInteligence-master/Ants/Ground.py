from Tkinter import *
from Draw_Area import *

##################################################
# 2-D Graphic area for displaying moving agents  #
##################################################
class Ground(Draw_Area):
    # Defines a 2-D region where agents are located and may move
    
    def __init__(self, parent, Toric=True):
        Draw_Area.__init__(self, parent)
        self.Offset = 3    # width of the surrounding border
        self.Offset1 = self.Offset +3   # width of the surrounding margin
        self.OffsetX = self.Offset1    # additional left margin
        self.OffsetY = self.Offset1    # additional bottom margin

        self.configure( background="#FFFFFF",borderwidth=self.Offset,relief=GROOVE)
        self.W = 400
        self.H = 340
        self.configure(width = self.W, height = self.H)
        self.Toric = Toric  # says whether right (resp. top) edge
                            # is supposed to touch left (resp. bottom) edge
        self.positions = dict() # positions of agents


    def grid(self):
        " Writing maximal values  "
        # First, delete all unnamed objects (named objects are agents)
        for Item in self.find_all():
            if len(self.gettags(Item)) == 0:
                self.delete(Item)
    
        
    def redraw(self):
        " the whole picture is redrawn when the scale changes "
        self.grid()

                                 

    


