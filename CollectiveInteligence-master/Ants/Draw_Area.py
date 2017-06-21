from Tkinter import *

class Draw_Area(Canvas):
    
    def __init__(self, parent):
        Canvas.__init__(self, parent)
        self.Offset = 3
        self.Offset1 = self.Offset + 33.0   # width of the surrounding margin
        self.OffsetX = self.Offset1    # left margin
        self.OffsetY = self.Offset1    # bottom margin
        self.W = 519
        self.H = 400
        self.scaleX = 100.0    # current maximal horizontal value
        self.scaleY = 100.0    # current maximal vertical value

    def erase(self):
            for obj in self.find_all():
                self.delete(obj)
            self.grid()
                
    
    