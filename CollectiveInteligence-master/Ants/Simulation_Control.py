from Simulation import *
class Simulation_Control(object):
    """ Controls the simulation, either step by step, or in
        a continuous mode.
    """

    def __init__(self, SimulationStep):

        self.OneStep = SimulationStep   # function that launches one step of the simulation

        ## Status of the simulation programme
        self.simulation = None  # name of the simulation thread
        self.busy = 0   # busy meter to avoid fatal parallelism between simulation and display

        #self.previous_Disp_period = self.Disp_period = 1    # display period

    def RunButtonClick(self, event=None):
        self.simulation_steady_mode = True     # Continuous functioning
        self.Simulation_resume()   

    def PauseButtonClick(self,event=None):
        self.Simulation_stop()
        
    def Simulation_stop(self):
        if self.simulation is not None:
            self.simulation.stop()
            if self.simulation.isAlive():
                #print 'strange...'
                #sleep(2)
                self.simulation = None  # well...
                return False
            self.simulation = None
        return True
        
    def Simulation_launch(self):
        if self.busy > 0:
            return False
        # A new simulation thread is created
        if self.Simulation_stop():
            self.simulation = Simulation(self.OneStep)
            self.simulation.start()
        return True
        
    def Simulation_resume(self):
        return self.Simulation_launch()


