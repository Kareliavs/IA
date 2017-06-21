from sys import excepthook, exc_info
from threading import Thread
from time import sleep

class Simulation(Thread):
    """ Thread triggered by the "Step" and "Run" buttons
        of the Evolife window system
    """
    def __init__(self, OneStep):
        Thread.__init__(self)
        self.OneStep = OneStep      # function that runs one simulation step

    def stop(self):
        """ stops the thread """
        if self.Running:
            self.Running = False
        
    def run(self):
        """ launched by start() """
        self.Running = True
        
        while 1:
            if self.Running:
                self.OneStep();
        



