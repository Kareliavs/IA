from Tkinter import *
from math import log
from time import sleep
from Simulation_Control import *

class Generic_Main_Frame(Frame, Simulation_Control):
    """ Defines a generic main window.
        The left panel contains various control buttons.
        The right panel is a plot area that displays curves.
        This window can launche a simulation, either step by step, or in
        a continuous mode.
    """

    def __init__(self, parent=None, SimulationStep=None, Wtitle=""):

        Frame.__init__(self,master=parent)
        self.Parent = parent
        ###################################
        # Creation of the main window     #
        ###################################
        Simulation_Control.__init__(self, SimulationStep)
        self.bind("<Destroy>", self.Destruction)

        # Setting the main window parameters
        self.Parent.geometry("640x400")
        self.Parent.minsize(206,300)
        self.Parent.title(Wtitle)
        self.Name = Wtitle

        self.pack(expand=YES, fill=BOTH)    # displaying the frame
        self.alive = True
        self.Finish = False

        # control frame
        self.control_frame = Frame(self)
        self.control_frame.pack(side=LEFT, expand=NO, fill=Y, anchor=N)
        
        
        # buttons frame
        self.buttons_frame = Frame(self.control_frame)
        self.buttons_frame.pack(side=TOP, expand=YES,
                                fill=NONE, ipadx=1, ipady=0)

        # Create buttons
        self.CreateBigButton("Run", self.buttons_frame, self.RunButtonClick)       
        self.CreateBigButton("Pause",self.buttons_frame,self.PauseButtonClick)

        
    def CreateBigButton(self, ButtonName, Parent, ActionFunction, VPosition=TOP):
        " Creates a button and inserts it into the parent frame "

        BigButton = Button(Parent,
                text=ButtonName,  
                font=("Times", "12","bold"),
                width=6, padx="2m", pady="0m")
        if VPosition == TOP:
            BigButton.pack(side=TOP, anchor=N, fill=Y)
        elif VPosition == BOTTOM:
            BigButton.pack(side=BOTTOM, anchor=S)
        
        BigButton.bind("<Button-1>", ActionFunction)   
        BigButton.bind("<Return>", ActionFunction)

        return BigButton
        
    def Destruction(self, event=None):
        self.Finish = True
        self.simulation_steady_mode = False    # Stepwise functioning
        self.Simulation_stop()
        self.alive = False
        self.Parent.quit()