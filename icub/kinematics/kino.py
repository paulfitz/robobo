from DummyRobot import DummyRobot as Robot

robot = Robot()

class Unit:
    def __init__(self,name,parent):
        self.name = name
        self.parent = parent
        self.is_configured = False
        self.is_completed = False
        self.is_root = (parent==None)

    def set_base(self,data):
        print("SET BASE HERE")

    def set_rpy_xyz(self,data):
        print("SET RPY_XYZ HERE")

    def set_dh(self,data):
        print("SET DH HERE")

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
