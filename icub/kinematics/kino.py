from DummyRobot import DummyRobot as Robot

robot = Robot()

class Unit:
    def __init__(self,name,parent):
        self.name = name
        self.parent = parent
        self.is_configured = False
        self.is_completed = False
        self.is_root = (parent==None)
        self.rpy_xyz = None
        self.dh = None

    def set_base(self,data):
        #print("SET BASE HERE")
        return

    def set_rpy_xyz(self,data):
        self.rpy_xyz = data

    def set_dh(self,data):
        self.dh = data

    def set_terminal(self):
        pass

    def complete(self):
        self.is_completed = True
        if self.is_root:
            robot.finish()

    def configured(self):
        self.is_configured = True
        robot.addUnit(self)

def create_root(name):
    return Unit(name,None)

def create_joint(name,parent):
    return Unit(name,parent)
