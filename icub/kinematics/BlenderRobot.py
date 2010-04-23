class BlenderRobot:
    def __init__(self):
        try:
            bpy.context.scene.objects.unlink(bpy.data.objects.get('Cube'))
        except:
            pass
        try:
            bpy.context.scene.objects.unlink(bpy.data.objects.get('robot'))
        except:
            pass


    def finish(self):
        print("SHUTTING DOWN")
        bpy.ops.wm.save_as_mainfile(filename = "test.blend",
                                    path = "/tmp/test.blend",
                                    directory = "/tmp",
                                    check_existing = False)

        print("SHUT DOWN")

    def addRoot(self,unit):
        print("Add root " + unit.name)
        bpy.data.armatures.new(unit.name)
        self.armature = bpy.data.armatures[0]
        self.robot = bpy.data.objects.new("robot", self.armature)
        self.robot.location.x = 0;
        self.robot.location.y = 0;
        bpy.context.scene.objects.link(self.robot)
        bpy.context.scene.update()
        bpy.context.scene.update()
        
    def addJoint(self,unit,parent):
        print("Add joint " + unit.name + " with parent " + parent.name)
        try:
            parent_bone = self.armature.edit_bones[parent.name]
        except:
            parent_bone = None
            bpy.context.scene.objects.active = bpy.context.scene.objects['robot']
        bpy.data.objects['robot'].selected = True
        bpy.ops.object.mode_set(mode='OBJECT')
        bpy.ops.object.mode_set(mode='EDIT')
        bone = self.armature.edit_bones.new(unit.name)
        bone.tail.y = 1

    def addUnit(self,unit):
        if unit.parent == None:
            self.addRoot(unit)
            return
        self.addJoint(unit,unit.parent)
        
